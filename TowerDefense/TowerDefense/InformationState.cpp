#include "InformationState.h"
#include "Utility.h"
#include "Foreach.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

InformationState::InformationState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::Texture& texture = context.textures->get(Textures::infoPanel);
	mBackgroundSprite.setTexture(texture);

	// Close Info Button
	mCloseInfoButton.setTexture(context.textures->get(Textures::closeButton));
	mCloseInfoButton.setPosition(1400.f, 290.f);
	centerOrigin(mCloseInfoButton);
}

void InformationState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	if (mCloseInfoButton.getGlobalBounds().contains(mousePos))
		mCloseInfoButton.setScale(1.2f, 1.2f);
	else
		mCloseInfoButton.setScale(1.1f, 1.1f);
	window.draw(mCloseInfoButton);
}

bool InformationState::update(sf::Time)
{
	return true;
}

bool InformationState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		// Convert mouse position from screen pixels to world coordinates (considering the current view)
		sf::Vector2f mousePos = getContext().window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

		if (mCloseInfoButton.getGlobalBounds().contains(mousePos)) {
			requestStackPop();
			requestStackPush(States::Menu);
		}
	}

	return true;
}