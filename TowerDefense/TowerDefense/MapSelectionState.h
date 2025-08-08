#pragma once
#include "State.h"
#include "MenuState.h"
#include "SaveManagement.h" // NEW FEATURE
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>

class MapSelectionState : public State
{
public:
    MapSelectionState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Sprite				    backgroundSprite;
    sf::Sprite                  homeButton;
    std::vector<sf::Sprite>     unlockedLevels;
    std::vector<sf::Sprite>     lockedLevels;

public:
    static int levelID;

private:
    Font font;
    vector<sf::Text>      stars;
    vector<sf::Text>      currentWave;

    sf::Text      playerName;
};

