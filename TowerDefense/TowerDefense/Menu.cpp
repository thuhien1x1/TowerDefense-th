#include "Menu.h"
#include <SFML/Graphics.hpp>

Menu::Menu() : playButtonClicked(false) {
    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        // Handle font loading error
        throw std::runtime_error("Failed to load font");
    }

    // Set up title
    title.setFont(font);
    title.setString("Tower Defense");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(400, 100);

    // Set up play button
    playButton.setSize(sf::Vector2f(200, 50));
    playButton.setFillColor(sf::Color(100, 100, 200));
    playButton.setPosition(500, 250);

    playButtonText.setFont(font);
    playButtonText.setString("Play Game");
    playButtonText.setCharacterSize(24);
    playButtonText.setFillColor(sf::Color::White);
    playButtonText.setPosition(535, 260);

    // Set up exit button
    exitButton.setSize(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color(200, 100, 100));
    exitButton.setPosition(500, 350);

    exitButtonText.setFont(font);
    exitButtonText.setString("Exit Game");
    exitButtonText.setCharacterSize(24);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setPosition(535, 360);
}

void Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window) {  
    playButtonClicked = false; // Reset flag  
    
    if (event.type == sf::Event::MouseButtonPressed &&  
        event.mouseButton.button == sf::Mouse::Left) {  
        
        // Get mouse position  
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);  
        sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);  
        
        // Check if play button is clicked  
        if (playButton.getGlobalBounds().contains(mousePosFloat)) {  
            playButtonClicked = true;  
        }  
        
        // Check if exit button is clicked  
        if (exitButton.getGlobalBounds().contains(mousePosFloat)) {  
            window.close();  
        }  
    }  
    
    // Update button hover effects  
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);  
    sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);  
    
    if (playButton.getGlobalBounds().contains(mousePosFloat)) {  
        playButton.setFillColor(sf::Color(120, 120, 255)); // Lighter blue when hovering  
    } else {  
        playButton.setFillColor(sf::Color(100, 100, 200)); // Normal blue  
    }  
    
    if (exitButton.getGlobalBounds().contains(mousePosFloat)) {  
        exitButton.setFillColor(sf::Color(255, 120, 120)); // Lighter red when hovering  
    } else {  
        exitButton.setFillColor(sf::Color(200, 100, 100)); // Normal red  
    }  
}

bool Menu::isPlayButtonClicked() const {
    return playButtonClicked;
}

void Menu::draw(sf::RenderWindow& window) {
    // Draw a background
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(50, 50, 70));
    window.draw(background);
    
    // Draw menu elements
    window.draw(title);
    window.draw(playButton);
    window.draw(playButtonText);
    window.draw(exitButton);
    window.draw(exitButtonText);
}
