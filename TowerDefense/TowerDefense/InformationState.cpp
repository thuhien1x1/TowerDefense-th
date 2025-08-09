#include "InformationState.h"
#include "Utility.h"
#include "Foreach.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

InformationState::InformationState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::Texture& texture = context.textures->get(Textures::infoPanel);
	mBackgroundSprite.setTexture(texture);

	// Close Info Button
	mCloseInfoButton.setTexture(context.textures->get(Textures::closeButton));
	mCloseInfoButton.setPosition(1400.f, 290.f);
	centerOrigin(mCloseInfoButton);

	// Get the font
	mFont = context.fonts->get(Fonts::KnightWarrior);

	// These coordinates should match the box in your background image
	const sf::Vector2f textAreaPosition(640.f, 300.f);  // Top-left of visible box
	const sf::Vector2f textAreaSize(770.f, 440.f);     // Dimensions of visible box
	
	// Create text elements
	std::vector<std::string> lines = {
		"STORYLINE:",
		"The factory is under siege by its own creations. A rogue AI has turned",
		"service robots into deadly enforcers. What was built to serve now seeks",
		"to dominate.",
		"",
		"You're to fight through machine-controlled zones and shut the enemy down",
		"before it expands its influence beyond the walls. Failure is not an option.",
		"Save the factory. Everything rides on you.",
		"Good luck, our noble warrior.",
		"",
		"TEAM",
		"A game by",
		"TEAM 7",
		"24127022 - Pham Tan Dat",
		"24127365 - Tran Le Thu Hien",
		"24127445 - Truong Hien Long",
		"24127574 - Nguyen Thi Ngoc Trinh",
		"",
		"ENEMIES TYPE:",
		"Fast Scout:",
		"The fastest unit on the battlefield. These lightweight bots are great",
		"for hit-and-run tactics, but fragile.",
		"",
		"Ranged Mech:",
		"A balanced speed and health unit. They maintain a quite fast speed",
		"while not being too easy to kill.",
		"",
		"Heavy Walker:",
		"Slow-moving unit with reinforced armour. While their speed is low,",
		"their endurance is remarkable."
	};

	// Text formatting
	float yPosition = 0.f;
	for (const auto& line : lines) {
		sf::Text text(line, mFont, 24);  // Adjust size as needed

		text.setPosition(20.f, yPosition);

		mInfoTexts.push_back(text);
		yPosition += text.getGlobalBounds().height + 10.f;
	}

	// Set up an green scroll area that matches the visible box
	mScrollArea.setSize(textAreaSize);
	mScrollArea.setPosition(textAreaPosition);
	mScrollArea.setFillColor(sf::Color(0, 255, 0, 100)); // Semi-transparent green
	mScrollArea.setOutlineColor(sf::Color::Green);
	mScrollArea.setOutlineThickness(2.f);
}

void InformationState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	// Draw background (with visible box)
	window.draw(mBackgroundSprite);

	// Set up scroll view that matches the visible box area
	sf::View scrollView(sf::FloatRect(0, 0, mScrollArea.getSize().x, mScrollArea.getSize().y));
	scrollView.setViewport(sf::Rect(
		mScrollArea.getPosition().x / window.getSize().x,
		mScrollArea.getPosition().y / window.getSize().y,
		mScrollArea.getSize().x / window.getSize().x,
		mScrollArea.getSize().y / window.getSize().y
	));
	scrollView.move(0, +mScrollOffset);

	// Draw text within the scrollable area
	window.setView(scrollView);
	for (const auto& text : mInfoTexts) {
		window.draw(text);
	}

	// Reset to default view for other elements
	window.setView(window.getDefaultView());

	//window.draw(mScrollArea);

	// Button hover effect (existing code)
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
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
		sf::Vector2f mousePos = getContext().window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

		if (mCloseInfoButton.getGlobalBounds().contains(mousePos)) {
			requestStackPop();
			requestStackPush(States::Menu);
		}
		else if (mScrollArea.getGlobalBounds().contains(mousePos)) {
			mIsDragging = true;
			mLastMouseY = mousePos.y;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		mIsDragging = false;
	}
	else if (event.type == sf::Event::MouseMoved && mIsDragging) {
		sf::Vector2f mousePos = getContext().window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
		float deltaY = mLastMouseY + mousePos.y;
		mScrollOffset += deltaY;

		// Clamp the scroll offset
		float maxOffset = 30.f * mInfoTexts.size() - mScrollArea.getSize().y;
		mScrollOffset = std::max(0.f, std::min(mScrollOffset, maxOffset));

		mLastMouseY = mousePos.y;
	}
	else if (event.type == sf::Event::MouseWheelScrolled) {
		mScrollOffset -= event.mouseWheelScroll.delta * 30.f;

		// Clamp the scroll offset
		float maxOffset = mInfoTexts.back().getPosition().y + 
                 mInfoTexts.back().getGlobalBounds().height - 
                 mScrollArea.getSize().y + 20.f;
		mScrollOffset = std::max(0.f, std::min(mScrollOffset, maxOffset));
	}

	return true;
}