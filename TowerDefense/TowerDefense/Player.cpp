// TowerDefense\Player.cpp
#include "Player.h"

Player::Player()
    : mMousePosition(0.f, 0.f)
    , mMoney(100)
    , mSelectedTowerType(0)
{
}

void Player::handleEvent(const sf::Event& event)
{
    // Handle events like tower selection, purchases, etc.
    if (event.type == sf::Event::MouseMoved)
    {
        setMousePosition(static_cast<float>(event.mouseMove.x),
            static_cast<float>(event.mouseMove.y));
    }
}

void Player::handleRealtimeInput()
{
    // Handle any continuous input needed
}

void Player::setMousePosition(float x, float y)
{
    mMousePosition.x = x;
    mMousePosition.y = y;
}

sf::Vector2f Player::getMousePosition() const
{
    return mMousePosition;
}