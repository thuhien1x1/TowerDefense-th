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

    float gameSpeed = 1.0f;

    sf::RenderWindow mWindow;
    TextureHolder mTextures;
    FontHolder mFonts;
    Player mPlayer;
    int mVictoryStars;
    StateStack mStateStack;

    MusicState currentMusic = MusicState::None; // NEW FEATURE
    SoundBufferHolder mSoundBuffers;    // NEW FEATURE
    MusicHolder mMusics;                // NEW FEATURE

    bool isMusicOn = true;          // NEW FEATURE
    bool isSoundOn = true;              // NEW FEATURE

private:
    sf::Sound mClickSound;
};