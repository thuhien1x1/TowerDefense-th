#include "MapSelectionState.h"
#include "Utility.h"
#include "Foreach.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

int MapSelectionState::levelID = 0;

MapSelectionState::MapSelectionState(StateStack& stack, Context context)
	: State(stack, context)
{
	// Set background
	sf::Texture& texture = context.textures->get(Textures::mapSelectionBackground);
	backgroundSprite.setTexture(texture);

	// Load homebutton texture
	homeButton.setTexture(context.textures->get(Textures::homeButton));
	homeButton.setPosition(1840.0f, 90.0f);
	centerOrigin(homeButton);

	// Load unlocked map textures
	sf::Sprite level1;
	level1.setTexture(context.textures->get(Textures::miniMap1));
	level1.setPosition(580.0f, 360.0f);
	centerOrigin(level1);
	unlockedLevels.push_back(level1);

	sf::Sprite level2;
	level2.setTexture(context.textures->get(Textures::miniMap2));
	level2.setPosition(1380.0f, 360.0f);
	centerOrigin(level2);
	unlockedLevels.push_back(level2);

	sf::Sprite level3;
	level3.setTexture(context.textures->get(Textures::miniMap3));
	level3.setPosition(580.0f, 800.0f);
	centerOrigin(level3);
	unlockedLevels.push_back(level3);

	sf::Sprite level4;
	level4.setTexture(context.textures->get(Textures::miniMap4));
	level4.setPosition(1380.0f, 800.0f);
	centerOrigin(level4);
	unlockedLevels.push_back(level4);

	// Load locked map textures (map 1 is always unlocked) (use later)
	sf::Sprite level2Locked;
	level2Locked.setTexture(context.textures->get(Textures::miniMap2Locked));
	level2Locked.setPosition(1380.0f, 360.0f);
	centerOrigin(level2Locked);
	lockedLevels.push_back(level2Locked);

	sf::Sprite level3Locked;
	level3Locked.setTexture(context.textures->get(Textures::miniMap3Locked));
	level3Locked.setPosition(580.0f, 800.0f);
	centerOrigin(level3Locked);
	lockedLevels.push_back(level3Locked);

	sf::Sprite level4Locked;
	level4Locked.setTexture(context.textures->get(Textures::miniMap4Locked));
	level4Locked.setPosition(1380.0f, 800.0f);
	centerOrigin(level4Locked);
	lockedLevels.push_back(level4Locked);

	// NEW FEATURE: Load Text shown for 4 maps
	font = getContext().fonts->get(Fonts::BruceForever);

	for (int i = 0; i < 4; i++)
	{
		if (SaveManagement::playerResult[i].status == -1) // not done playing
		{
			string temp = to_string(SaveManagement::playerResult[i].curWave + 1);

			Text wave;
			if (i == 0)
			{
				wave.setString(temp + "/" + to_string(3));
				wave.setPosition(580.0f, 360.0f);
			}
			else if (i == 1)
			{
				wave.setString(temp + "/" + to_string(3));
				wave.setPosition(1380.0f, 360.0f);
			}
			else if (i == 2)
			{
				wave.setString(temp + "/" + to_string(4));
				wave.setPosition(580.0f, 800.0f);
			}
			else if (i == 3)
			{
				wave.setString(temp + "/" + to_string(5));
				wave.setPosition(1380.0f, 800.0f);
			}

			wave.setFont(font);
			wave.setCharacterSize(20);
			wave.setFillColor(Color::Yellow);
			currentWave.push_back(wave);
		}
		else if (SaveManagement::playerResult[i].status == 1) // done playing
		{
			string temp = to_string(SaveManagement::playerResult[i].stars);
			Text star;
			star.setString("STAR" + temp);

			if (i == 0) star.setPosition(580.0f, 360.0f);
			else if (i == 1) star.setPosition(1380.0f, 360.0f);
			else if (i == 2) star.setPosition(580.0f, 800.0f);
			else star.setPosition(1380.0f, 800.0f);

			star.setFont(font);
			star.setCharacterSize(20);
			star.setFillColor(Color::Yellow);
			stars.push_back(star);
		}
	}

	// NEW FEATURE: Set up text to display name
	playerName.setFont(font);
	playerName.setCharacterSize(50);
	playerName.setFillColor(Color::White);
	playerName.setPosition(80.f, 45.f);
	playerName.setString(SaveManagement::playerName);
}

void MapSelectionState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);
	window.draw(playerName); // NEW FEATURE

	// Home button
	if (homeButton.getGlobalBounds().contains(mousePos))
		homeButton.setScale(1.1f, 1.1f);
	else
		homeButton.setScale(1.f, 1.f);
	window.draw(homeButton);

	// 4 Mini maps - NEW FEATURE
	int currentWaveIndex = 0;
	int starsIndex = 0;

	for (int i = 0; i < 4; i++)
	{
		if (i == 0)			// Map 1: always unlocked
		{
			if (unlockedLevels[i].getGlobalBounds().contains(mousePos))
				unlockedLevels[i].setScale(1.1f, 1.1f);
			else
				unlockedLevels[i].setScale(1.f, 1.f);

			window.draw(unlockedLevels[i]);

			if (SaveManagement::playerResult[i].status == -1)
			{
				if (currentWaveIndex < currentWave.size())
					window.draw(currentWave[currentWaveIndex]);
				currentWaveIndex++;
			}
			else if (SaveManagement::playerResult[i].status == 1)
			{
				if (starsIndex < stars.size())
					window.draw(stars[starsIndex]);
				starsIndex++;
			}
			continue;
		}
		else
		{
			if (!(SaveManagement::playerResult[i - 1].win)) // Locked: previous level is not done
			{
				if (lockedLevels[i - 1].getGlobalBounds().contains(mousePos))
					lockedLevels[i - 1].setScale(1.1f, 1.1f);
				else
					lockedLevels[i - 1].setScale(1.f, 1.f);

				window.draw(lockedLevels[i - 1]);
			}
			else // Unlocked
			{
				if (unlockedLevels[i].getGlobalBounds().contains(mousePos))
					unlockedLevels[i].setScale(1.1f, 1.1f);
				else
					unlockedLevels[i].setScale(1.f, 1.f);

				window.draw(unlockedLevels[i]);

				if (SaveManagement::playerResult[i].status == -1)
				{
					if (currentWaveIndex < currentWave.size())
						window.draw(currentWave[currentWaveIndex]);
					currentWaveIndex++;
				}
				else if (SaveManagement::playerResult[i].status == 1)
				{
					if (starsIndex < stars.size())
						window.draw(stars[starsIndex]);
					starsIndex++;
				}
			}
		}
	}
}

bool MapSelectionState::update(sf::Time dt)
{
	return true;
}

bool MapSelectionState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		// Convert mouse position from screen pixels to world coordinates (considering the current view)
		sf::Vector2f mousePos = getContext().window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

		// Click home button
		if (homeButton.getGlobalBounds().contains(mousePos))
		{
			requestStackPop();
			requestStackPush(States::Menu);
		}

		// Choose level
		for (size_t i = 0; i < unlockedLevels.size(); i++) {
			if (i == 0 || SaveManagement::playerResult[i - 1].win) // NEW FEATURE: check if last level was done
			{
				if (unlockedLevels[i].getGlobalBounds().contains(mousePos))
				{
					levelID = i;
					requestStackPop();
					requestStackPush(States::Game);
				}
			}
		}
	}

	return true;
}

