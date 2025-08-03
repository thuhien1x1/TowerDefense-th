#include "SaveManagement.h"
#include "Utility.h"
#include "Foreach.h"
#include "ResourceHolder.h"

#include <filesystem>
#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace fs = std::filesystem;

vector<SaveManagement::levelResult> SaveManagement::playerResult;
string SaveManagement::playerName = "";

SaveManagement::SaveManagement(StateStack& stack, Context context)
	: State(stack, context)
	, mOptions()
	, mOptionIndex(0)
{
	sf::Texture& texture = context.textures->get(Textures::Map1);
	sf::Font& font = context.fonts->get(Fonts::KnightWarrior);

	mBackgroundSprite.setTexture(texture);

	// temporary Title
	sf::Text listFiles;
	listFiles.setFont(font);
	listFiles.setString("Play");
	centerOrigin(listFiles);
	listFiles.setPosition(context.window->getView().getSize() / 4.f);
	mOptions.push_back(listFiles);

	// Get files saved
	scanSaveFolder();
	for (int i = 0; i < savedNames.size(); ++i)
	{
		sf::Text name;
		name.setFont(font);
		name.setString(savedNames[i]);
		centerOrigin(name);
		if (i == 0) // first name to appear
			name.setPosition(listFiles.getPosition() + sf::Vector2f(0.f, 40.f));
		else
			name.setPosition(mOptions[i].getPosition() + sf::Vector2f(0.f, 40.f)); // should be mOptions[i - 1] if no title

		mOptions.push_back(name);
	}

	// Exit
	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(mOptions[mOptions.size() - 1].getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(exitOption);

	updateOptionText();
}

void SaveManagement::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text & text, mOptions)
		window.draw(text);
}

bool SaveManagement::update(sf::Time dt)
{
	return true;
}

bool SaveManagement::handleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptions[mOptionIndex].getString() == "Exit")
		{
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			requestStackPop();
			requestStackPush(States::Menu);
		}
		else
		{
			SaveManagement::setName(mOptions[mOptionIndex].getString());

			requestStackPop();
			requestStackPush(States::MapSelection);
		}

	}
	else if (event.key.code == sf::Keyboard::Up)
	{
		// Decrement and wrap-around
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		cout << mOptionIndex << endl;
		updateOptionText();
	}

	else if (event.key.code == sf::Keyboard::Down)
	{
		// Increment and wrap-around
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		cout << mOptionIndex << endl;
		updateOptionText();
	}

	return true;
}

void SaveManagement::updateOptionText()
{
	if (mOptions.empty())
		return;

	// White all texts
	FOREACH(sf::Text & text, mOptions)
		text.setFillColor(sf::Color::White);

	// Red the selected text
	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}

void SaveManagement::scanSaveFolder()
{
	savedNames.clear();
	if (!fs::exists("saves")) fs::create_directory("saves");
	for (auto& p : fs::directory_iterator("saves"))
		if (p.is_regular_file() && p.path().extension() == ".txt")
			savedNames.push_back(p.path().stem().string());
}

bool SaveManagement::load(string pName)
{
	ifstream fin("saves/" + pName + ".txt");
	if (!fin) return false;

	string line;

	for (int i = 0; i < 4; i++)
	{
		getline(fin, line);
		stringstream ss(line);
		string temp;

		getline(ss, temp, ' ');
		SaveManagement::playerResult[i].status = stoi(temp);

		getline(ss, temp, ' ');
		SaveManagement::playerResult[i].stars = stoi(temp);

		if (SaveManagement::playerResult[i].status)
		{
			getline(ss, temp, ' ');
			SaveManagement::playerResult[i].health = stoi(temp);

			getline(ss, temp, ' ');
			SaveManagement::playerResult[i].curWave = stoi(temp);

			getline(ss, temp, ' ');
			SaveManagement::playerResult[i].curGold = stoi(temp);

			while (getline(ss, temp, ' '))
			{
				ctower t;
				t.setType(stoi(temp));

				getline(ss, temp, ' '); int x = stoi(temp);
				getline(ss, temp, ' '); int y = stoi(temp);

				t.setLocation(cpoint(x, y, 1));
				SaveManagement::playerResult[i].towers.push_back(t);
			}
		}
	}

	return true;
}

void SaveManagement::save(const string playerName)
{
	ofstream fout("saves/" + playerName + ".txt");
	if (!fout) return;

	for (int i = 0; i < 4; i++)
	{
		fout << SaveManagement::playerResult[i].status << " "
			<< SaveManagement::playerResult[i].stars << " "
			<< SaveManagement::playerResult[i].health << " "
			<< SaveManagement::playerResult[i].curWave << " "
			<< SaveManagement::playerResult[i].curGold << " ";
		for (int j = 0; j < SaveManagement::playerResult[i].towers.size(); j++)
		{
			fout << SaveManagement::playerResult[i].towers[j].getType() << " "
				<< SaveManagement::playerResult[i].towers[j].getLocation().getPixelX() << " "
				<< SaveManagement::playerResult[i].towers[j].getLocation().getPixelY() << " ";
		}

		fout << endl;
	}

	fout.close();
}

void SaveManagement::setName(string pName)
{
	SaveManagement::playerName = pName;
}

