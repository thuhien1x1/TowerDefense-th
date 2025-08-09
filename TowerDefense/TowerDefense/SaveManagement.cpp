#include "SaveManagement.h"
#include "Utility.h"
#include "Foreach.h"
#include "ResourceHolder.h"

#include <filesystem>
#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace fs = std::filesystem;

vector<SaveManagement::levelResult> SaveManagement::playerResult(4);
string SaveManagement::playerName = "";

SaveManagement::SaveManagement(StateStack& stack, Context context)
	: State(stack, context)
	, mOptions()
	, mOptionIndex(0)
{
	sf::Texture& texture = context.textures->get(Textures::Map1);
	sf::Font& font = context.fonts->get(Fonts::KnightWarrior);

	mBackgroundSprite.setTexture(texture);

	// Get files saved
	scanSaveFolder();

	// Display player names
	int nameSize = fmin(savedNames.size(), 6); // show 6 or less
	for (int i = 0; i < nameSize; ++i)
	{
		sf::Text name;
		name.setFont(font);
		name.setString(savedNames[i]);
		centerOrigin(name);

		if (i == 0)
			name.setPosition(sf::Vector2f(200.f, 100.f)); // first name to appear on left col
		else if (i == 1)
			name.setPosition(sf::Vector2f(400.f, 100.f)); // first name to appear on right col
		else
			name.setPosition(mOptions[i - 2].getPosition() + sf::Vector2f(0.f, 40.f));

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
			SaveManagement::load(SaveManagement::playerName);
			MenuState::isNewPlayer = false;
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

		updateOptionText();
	}

	else if (event.key.code == sf::Keyboard::Down)
	{
		// Increment and wrap-around
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

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
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

	namespace fs = std::filesystem;

	savedNames.clear();
	if (!fs::exists("saves")) fs::create_directory("saves");

	// Temporary vector to store pairs of (file_path, last_write_time)
	std::vector<std::pair<fs::path, fs::file_time_type>> fileEntries;

	for (auto& p : fs::directory_iterator("saves")) {
		if (p.is_regular_file() && p.path().extension() == ".txt") {
			fileEntries.emplace_back(p.path(), fs::last_write_time(p));
		}
	}

	// Sort by last_write_time (oldest first)
	std::sort(fileEntries.begin(), fileEntries.end(),
		[](const auto& a, const auto& b) {
			return a.second > b.second;
		});

	// Push sorted names into savedNames
	for (const auto& entry : fileEntries) {
		savedNames.push_back(entry.first.stem().string());
	}

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
		if (SaveManagement::playerResult[i].status == -1)
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
				<< SaveManagement::playerResult[i].towers[j].getLocation().getRow() << " "
				<< SaveManagement::playerResult[i].towers[j].getLocation().getCol() << " ";
		}

		fout << endl;
	}

	fout.close();
}

void SaveManagement::setName(string pName)
{
	SaveManagement::playerName = pName;
}

