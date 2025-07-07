#pragma once

#include <SFML/Graphics.hpp>

class Menu {
private:
    bool playButtonClicked;
    sf::Font font;
    sf::Text title;

    sf::RectangleShape playButton;
    sf::Text playButtonText;

    sf::RectangleShape exitButton;
    sf::Text exitButtonText;

public:
    Menu();
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    bool isPlayButtonClicked() const;
    void draw(sf::RenderWindow& window);
};
