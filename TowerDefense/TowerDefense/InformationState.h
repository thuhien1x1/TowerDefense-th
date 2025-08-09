#pragma once

#include "State.h"
#include <SFML/Graphics.hpp>
#include <vector>

class InformationState : public State
{
public:
    InformationState(StateStack& stack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    void clampScrollOffset();  // Helper function

    sf::Sprite mBackgroundSprite;
    sf::Sprite mCloseInfoButton;
    sf::RectangleShape mScrollArea;

    sf::Font mFont;  // Store font as member
    std::vector<sf::Text> mInfoTexts;

    float mScrollOffset;
    bool mIsDragging;
    float mLastMouseY;
};