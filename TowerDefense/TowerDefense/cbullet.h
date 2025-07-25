#pragma once
#include "cpoint.h"
#include "cenemy.h" 
#include <SFML/Graphics.hpp>

class cbullet
{
    int _n, _speed;
    cpoint _p[cpoint::MAP_ROW * cpoint::MAP_COL];
    cpoint _m[cpoint::MAP_ROW][cpoint::MAP_COL];
    cpoint _curr;
    // Add
    float _posX, _posY;
    bool _active;
    int _targetIdx;
    int _damage;
    sf::Sprite _sprite;

    // Add animation for bullets
    sf::IntRect _frameRect;   // Current frame of the sprite sheet
    int _frameWidth;
    int _frameHeight;
    int _currentFrame;
    int _totalFrames;
    float _animationTimer;
    float _animationSpeed; // Time for per frame

    // Add laser
    bool isLaser;
    float laserDuration;
    float laserTimer;
    sf::Sprite laserSprite;
    sf::Vector2f startPos;
    sf::Vector2f targetPos;

    // Bomb: 16, 15, 7, scale 4.f
    // Fire bullet: 1667, 1167, 4, scale 0.1f

public:
    cbullet();
    void updateMap(cpoint map[][cpoint::MAP_COL]); // Update

    cpoint getCurr() const;
    cpoint* getP();
    int getSpeed() const;
    int getN() const;

    void setCurr(const cpoint& tcurr);
    void setN(int tn);
    void setSpeed(int tspeed);

    int queryCFromRowCol(int row, int col) const;
    int calcPathBullet(const cpoint& tower);

    // Bullet collision detection
    bool checkCollision(const cenemy& enemy) const;

    // Move bullet one step toward the enemy's current position
    void trackEnemy(const cenemy& enemy, float deltaTime);

    // Position and movement
    void init(const sf::Texture& tex, float x, float y, int frameWidth, int frameHeight, int totalFrames, float animSpeed); // Update
    void updateAnimation(float deltaTime); // Add
    void updateSprite();
    const sf::Sprite& getSprite() const { return _sprite; }

    float getX() const { return _posX; }
    float getY() const { return _posY; }

    void setPosition(float x, float y);
    void move(float dx, float dy);

    // Bullet logic
    int getTargetIdx() const { return _targetIdx; } // Returns the index of the current enemy target the bullet is tracking
    int getDamage() const { return _damage; } // Returns how much damage the bullet will deal on impact.

    void setTargetIdx(int idx) { _targetIdx = idx; } // Assign the index of the target enemy for the bullet to track.
    void setDamage(int dmg) { _damage = dmg; } // Define how much damage this bullet should inflict (useful for upgrade towers)

    bool isActive() const { return _active; } // Returns true if the bullet is still active (on screen, valid target), used to skip deactivated bullets.
    void deactivate() { _active = false; } // Marks the bullet as inactive after hitting an enemy or going off - screen, Prevents further updates or rendering.

    // Add laser
    void initLaser(const sf::Texture& tex, float x, float y, float targetX, float targetY, float duration = 0.2f);
    bool isLaserBullet() const { return isLaser; }
    const sf::Sprite& getLaserSprite() const { return laserSprite; }
    void updateLaser(float deltaTime);
};
