// cBaseTower.h
#pragma once
#include <SFML/Graphics.hpp>
#include "cpoint.h"

class cBaseTower {
private:
    int maxHealth;
    int currentHealth;
    sf::Sprite sprite;
    cpoint position;
    float scale;

    sf::Clock mDamageTimer;
    bool mRecentlyDamaged;

    // Health bar members (only declare once)
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBarFill;

public:
    cBaseTower();
    cBaseTower(int row, int col);

    void setTexture(const sf::Texture& texture);
    void setPosition(int row, int col);
    void setPixelPosition(float x, float y);
    void setMaxHealh(int hp);
    void takeDamage(int damage);
    void heal(int amount);
    bool isDestroyed() const;
    bool recentlyDamaged() const;

    int getHealth() const { return currentHealth; }
    int getMaxHealth() const { return maxHealth; }
    sf::Sprite& getSprite() { return sprite; }
    const sf::Sprite& getSprite() const { return sprite; }
    const cpoint& getPosition() const { return position; }

    // For visual health display
    void setHealthBarSize(float width, float height);
    void drawHealthBar(sf::RenderWindow& window) const;

private:
    void updateSpritePosition();
};