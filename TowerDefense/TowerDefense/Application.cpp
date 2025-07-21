#include "Application.h"
#include "StateIdentifiers.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"

Application::Application()
    : mWindow(sf::VideoMode(1024, 768), "Tower Defense", sf::Style::Close)
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