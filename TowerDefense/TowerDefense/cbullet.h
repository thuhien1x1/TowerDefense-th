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
    float _posX, _posY;
    bool _active;
    int _targetIdx;
    int _damage;
    sf::Sprite _sprite;

    // Animation
    sf::IntRect _frameRect;   // Current frame of the sprite sheet
    int _frameWidth;
    int _frameHeight;
    int _currentFrame;
    int _totalFrames;
    float _animationTimer;
    float _animationSpeed; // Time for per frame

    // Bomb: 16, 15, 7, scale 4.f
    // Fire bullet: 1667, 1167, 4, scale 0.1f
    // Ice bullet: 705, 114, 5, scale 0.8f

public:
    cbullet();
    void updateMap(cpoint map[][cpoint::MAP_COL]);

    // Getter
    cpoint getCurr() const { return _curr; }
    cpoint* getP() { return _p; }
    int getSpeed() const { return _speed; }
    int getN() const { return _n; }
    float getX() const { return _posX; }
    float getY() const { return _posY; }
    int getTargetIdx() const { return _targetIdx; }
    int getDamage() const { return _damage; }
    const sf::Sprite& getSprite() const { return _sprite; }

    // Setter
    void setCurr(const cpoint& tcurr) { _curr = tcurr; }
    void setN(int tn) { if (tn >= 0 && tn <= cpoint::MAP_ROW * cpoint::MAP_COL) _n = tn; }
    void setSpeed(int tspeed) { if (tspeed > 0 && tspeed < 20) _speed = tspeed; }
    void setPosition(float x, float y);
    void setTargetIdx(int idx) { _targetIdx = idx; }
    void setDamage(int dmg) { _damage = dmg; }

    int queryCFromRowCol(int row, int col) const;
    int calcPathBullet(const cpoint& tower);

    // Bullet collision detection
    bool checkCollision(const cenemy& enemy) const;

    // Move bullet one step toward the enemy's current position
    void trackEnemy(const cenemy& enemy, float deltaTime);

    // Position and movement
    void init(const sf::Texture& tex, float x, float y, int frameWidth, int frameHeight, int totalFrames, float animSpeed);
    void updateAnimation(float deltaTime); // Add
    void updateSprite();
    void move(float dx, float dy);

    // Bullet logic
    bool isActive() const { return _active; } // Returns true if the bullet is still active (on screen, valid target), used to skip deactivated bullets.
    void deactivate() { _active = false; } // Marks the bullet as inactive after hitting an enemy or going off - screen, Prevents further updates or rendering.
};
