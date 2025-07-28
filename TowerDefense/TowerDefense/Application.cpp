#include "Application.h"
#include "StateIdentifiers.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "SettingState.h"
#include "InformationState.h"

Application::Application()
    : mWindow(sf::VideoMode(1920, 1080), "Tower Defense", sf::Style::Close)
    , mTextures()
    , mFonts()
    , mPlayer()
    , mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{
    mWindow.setVerticalSyncEnabled(true); // Smoother rendering

    // Load essential resources
    mFonts.load(Fonts::Main, "Media/arial.ttf");
    mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");

    registerStates();
    mStateStack.pushState(States::Title); // Start with title screen

    mTextures.load(Textures::Map1, "Media/Textures/map 1.png");
    mTextures.load(Textures::Map2, "Media/Textures/map 2.png");
    mTextures.load(Textures::Map3, "Media/Textures/map 3.png");
    mTextures.load(Textures::Map4, "Media/Textures/map 4.png");

    mTextures.load(Textures::MainTower, "Media/Textures/mainTower.png");
    mTextures.load(Textures::Tower, "Media/Textures/tower.png");
    mTextures.load(Textures::ShootEffect, "Media/Textures/shootEffect.png");

    mTextures.load(Textures::Bomb, "Media/Textures/bomb_sprite_sheet.png");

    mTextures.load(Textures::Enemy1_Walk, "Media/Textures/enemy_1_walk_126_123_6.png");
    mTextures.load(Textures::Enemy1_Attack, "Media/Textures/enemy_1_attack_125_125_6.png");
    mTextures.load(Textures::Enemy1_Death, "Media/Textures/enemy_1_death_125_125_6.png");
    mTextures.load(Textures::Enemy2_Fly, "Media/Textures/enemy_2_fly_209_203_4.png");
    mTextures.load(Textures::Enemy2_Attack, "Media/Textures/enemy_2_attack_209_203_6.png");
    mTextures.load(Textures::Enemy2_Death, "Media/Textures/enemy_2_death_209_203_6.png");
    mTextures.load(Textures::Enemy3_Walk, "Media/Textures/enemy_3_walk_213_211_6.png");
    mTextures.load(Textures::Enemy3_Attack, "Media/Textures/enemy_3_attack_212_210_6.png");
    mTextures.load(Textures::Enemy3_Death, "Media/Textures/enemy_3_death_212_210_6.png");
}

void Application::run()
{
    sf::Clock clock;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        processInput();
        update(dt);
        render();
    }
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<SettingState>(States::Setting);
    mStateStack.registerState<InformationState>(States::Information);
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);

    if (mStateStack.isEmpty())
        mWindow.close();
}

void Application::render()
{
    mWindow.clear();
    mStateStack.draw();
    mWindow.display();
}