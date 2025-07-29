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
}

void MapSelectionState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);

	// Home button
	if (homeButton.getGlobalBounds().contains(mousePos))
		homeButton.setScale(1.1f, 1.1f);
	else
		homeButton.setScale(1.f, 1.f);
	window.draw(homeButton);

	for (size_t i = 0; i < unlockedLevels.size(); i++) {
		if (unlockedLevels[i].getGlobalBounds().contains(mousePos))
			unlockedLevels[i].setScale(1.1f, 1.1f);
		else
			unlockedLevels[i].setScale(1.f, 1.f);
		window.draw(unlockedLevels[i]);
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
			if (unlockedLevels[i].getGlobalBounds().contains(mousePos))
			{
				levelID = i;
				requestStackPop();
				requestStackPush(States::Game);
			}
		}
	}

	return true;
}

