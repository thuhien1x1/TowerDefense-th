#include "SettingState.h"
#include "Utility.h"
#include "Foreach.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

SettingState::SettingState(StateStack& stack, Context context)
	: State(stack, context)
	, mOptions()
	, mOptionIndex(0)
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Main);

	mBackgroundSprite.setTexture(texture);

	// A simple menu demonstration
	sf::Text Music;
	Music.setFont(font);
	Music.setString("Music");
	centerOrigin(Music);
	Music.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(Music);

	sf::Text Sound;
	Sound.setFont(font);
	Sound.setString("Sound");
	centerOrigin(Sound);
	Sound.setPosition(Music.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(Sound);

	sf::Text Return;
	Return.setFont(font);
	Return.setString("Return");
	centerOrigin(Return);
	Return.setPosition(Sound.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(Return);

	updateOptionText();
}

void SettingState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text & text, mOptions)
		window.draw(text);
}

bool SettingState::update(sf::Time)
{
	return true;
}

bool SettingState::handleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == Music)
		{
		}

		else if (mOptionIndex == Effect) {
		}

		else if (mOptionIndex == Return)
		{
			requestStackPop();
			requestStackPush(States::Menu);
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

void SettingState::updateOptionText()
{
	if (mOptions.empty())
		return;

	// White all texts
	FOREACH(sf::Text & text, mOptions)
		text.setFillColor(sf::Color::White);

	// Red the selected text
	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}