#pragma once

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class InformationState : public State
{
public:
	InformationState(StateStack& stack, Context context);

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

private:
	sf::Sprite				mBackgroundSprite;
	sf::Sprite				mCloseInfoButton;
};

