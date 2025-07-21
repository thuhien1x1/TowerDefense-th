#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context)
{
    // Create a simple shape (no texture loading)
    mTestShape.setSize(sf::Vector2f(100.f, 100.f));
    mTestShape.setFillColor(sf::Color::Green);
    mTestShape.setPosition(150.f, 150.f);

    // Simple text (using default font)
    mTestText.setString("Game Running\nPress ESC to pause");
    mTestText.setCharacterSize(20);
    mTestText.setFillColor(sf::Color::White);
    mTestText.setPosition(20.f, 20.f);

    // Try to load font if available, but don't fail if missing
    if (context.fonts) {
        mTestText.setFont(context.fonts->get(Fonts::Main));
    }
}

void GameState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.clear(sf::Color::Black);

    window.draw(mTestShape);
    window.draw(mTestText);
}

bool GameState::update(sf::Time dt)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Check for pause key (typically Escape)
        if (event.key.code == sf::Keyboard::Escape)
        {
            // Request pushing pause state
            requestStackPush(States::Pause);
            return false; // Stop event propagation
        }
    }
    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Check for pause key (typically Escape)
        if (event.key.code == sf::Keyboard::Escape)
        {
            // Request pushing pause state
            requestStackPush(States::Pause);
            return false; // Stop event propagation
        }
    }
    return true;
}