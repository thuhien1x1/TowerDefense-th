#pragma once
#include "cpoint.h"
#include "cbullet.h"
#include <SFML/Graphics.hpp>

class ctower {
private:
    sf::Sprite _sprite;
    cpoint _location;
    cbullet _cb;
    float _shootTimer;
    int _targetEnemyIdx;

public:
    ctower();

    int getTargetEnemyIdx() const;
    void setTargetEnemyIdx(int idx);
    void setMapForBullet(cpoint map[][cpoint::MAP_COL]);
    int calcPathBullet();
    cbullet& getBullet();

    // Add
    void init(const sf::Texture& tex, float x, float y);
    const sf::Sprite& getSprite() const;

    void setLocation(const cpoint& loc);
    cpoint getLocation() const;

    void resetShootTimer(); // Reset the shoot timer to 0 after firing a bullet
    void addShootTimer(float dt); // Add delta time to the shoot timer, used to track cooldown between shots
    float getShootTimer() const; // Get the current value of the shoot timer to check if the tower is ready to shootc
};
