#pragma once
#include "cpoint.h"
#include <SFML/Graphics.hpp>

class cenemy
{
private:
    int _speed;
    cpoint _start, _end, _curr;
    cpoint _p[cpoint::MAP_ROW * cpoint::MAP_COL];
    int _pathLength;
    int dd[4], dc[4];
    // Add
    int _health;
    float _posX, _posY; 
    sf::Sprite _sprite;
    bool _reachedEnd;
    int _currentTarget;

public:
    cenemy();
    cenemy(cpoint tstart, cpoint tend, cpoint tcurr);

    cpoint* getP() { return _p; }
    int getPathLength() const { return _pathLength; }
    cpoint getStart() const { return _start; }
    cpoint getEnd() const { return _end; }
    int getSpeed() const { return _speed; }
    cpoint getCurr() const { return _curr; }

    void setSpeed(int tspeed);
    void setStart(const cpoint& tstart);
    void setEnd(const cpoint& tend);
    void setCurr(const cpoint& tcurr);

    void reachEnd() { _reachedEnd = true; }
    bool hasReachedEnd() const { return _reachedEnd; }
    void findPath(cpoint a[][cpoint::MAP_COL], cpoint s, cpoint e);

    // Health logic
    int getHealth() const { return _health; }
    void setHealth(int hp) { _health = hp; }
    bool isDead() const { return _health <= 0; }
    void takeDamage(int damage);

    // Position and movement
    void init(const sf::Texture& tex, float x, float y, int hp);
    void updateSprite();

    float getX() const { return _posX; }
    int getCurrentTarget() const { return _currentTarget; } // Control enemy movement along route, check when enemy reaches destination, update next point on route
    float getY() const { return _posY; }
    const sf::Sprite& getSprite() const { return _sprite; }

    void setPosition(float x, float y);
    void setCurrentTarget(int t) { _currentTarget = t; }
    void move(float dx, float dy);
    void incrementTarget() { _currentTarget++; }

private:
    void calcPath(int a[][cpoint::MAP_COL], int n, cpoint s, cpoint e);
};
