#pragma once

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Player.h"
#include "StateStack.h"

#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
    Application();
    void run();

private:
    void processInput();
    void update(sf::Time dt);
    void render();
    void registerStates();

    float gameSpeed = 2.0f;

    sf::RenderWindow mWindow;
    TextureHolder mTextures;
    FontHolder mFonts;
    Player mPlayer;
    int mVictoryStars;
    StateStack mStateStack;
};