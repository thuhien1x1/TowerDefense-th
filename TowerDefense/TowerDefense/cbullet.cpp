#include "cbullet.h"
#include <vector>
#include <cmath>      
#include <algorithm> 
#include <SFML/Graphics.hpp>
#include "cenemy.h"
#include "cpoint.h"

using namespace std;

cbullet::cbullet()
    : _posX(0.f), _posY(0.f), _speed(4), _active(true), _targetIdx(-1), _damage(1), _n(0),
    isLaser(false), laserDuration(0.f), laserTimer(0.f)
{
    for (int i = 0; i < cpoint::MAP_ROW * cpoint::MAP_COL; i++)
        _p[i] = cpoint(0, 0, 0);

    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            _m[i][j] = cpoint(0, 0, 0);
}

void cbullet::updateMap(cpoint map[][cpoint::MAP_COL]) {
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            _m[i][j] = map[i][j];
}

int cbullet::queryCFromRowCol(int row, int col) const {
    if (row < 0 || row >= cpoint::MAP_ROW || col < 0 || col >= cpoint::MAP_COL)
        return -2;
    return _m[row][col].getC();
}

int cbullet::calcPathBullet(const cpoint& tower) {
    int row = tower.getRow(), col = tower.getCol(), i = 0;

    do {
        col++; row--;
        if (queryCFromRowCol(row, col) == 0) {
            _p[i] = cpoint(row, col, 0);
            i += 2;
        }
        else break;
    } while (i < cpoint::MAP_ROW * cpoint::MAP_COL);

    _n = i;

    for (i = 1; i < _n; i += 2)
        _p[i] = cpoint(_p[i - 1].getRow(), _p[i - 1].getCol(), 0);

    if (_n > 0)
        _curr = _p[0];
    return _n;
}

// Check collision by calculating pixel distance between bullet and enemy instead of grid - based
bool cbullet::checkCollision(const cenemy& enemy) const {
    float dx = _posX - enemy.getX(); // Cal horizontal distance between bullet and enemy
    float dy = _posY - enemy.getY(); // // Cal vertical distance between bullet and enemy

    // Collision threshold
    return sqrt(dx * dx + dy * dy) < 15.f;
}

// Move the bullet towards the enemy using pixel-based tracking instead of grid - based
void cbullet::trackEnemy(const cenemy& enemy, float deltaTime) {
    if (isLaser || !_active) return;

    float dx = enemy.getX() - _posX;
    float dy = enemy.getY() - _posY;
    float len = sqrt(dx * dx + dy * dy);

    if (len > 0.01f) {
        dx /= len;
        dy /= len;

        // Move the bullet towards the enemy based on speed and frame time
        move(dx * _speed * deltaTime * 200.f, dy * _speed * deltaTime * 200.f);

        // Cal angle in degrees and rotate
        // atan2(dy, dx): calculates the angle (in radians) between the positive X-axis and the line from the bullet to the enemy
        // 180.f / 3.14159f: convert radians to degrees
        float angle = atan2(dy, dx) * 180.f / 3.14159f;
        _sprite.setRotation(angle);
    }
}

void cbullet::updateSprite() {
    _sprite.setPosition(_posX, _posY);
}

void cbullet::setPosition(float x, float y) {
    _posX = x;
    _posY = y;
    updateSprite();
}

void cbullet::move(float dx, float dy) {
    _posX += dx;
    _posY += dy;
    updateSprite();
}

void cbullet::init(const sf::Texture& tex, float x, float y, int frameWidth, int frameHeight, int totalFrames, float animSpeed) {
    _sprite.setTexture(tex);
    _frameWidth = frameWidth;
    _frameHeight = frameHeight;
    _totalFrames = totalFrames;
    _animationSpeed = animSpeed;
    _currentFrame = 0;
    _animationTimer = 0.f;

    _frameRect = sf::IntRect(0, 0, _frameWidth, _frameHeight);
    _sprite.setTextureRect(_frameRect);
    _sprite.setOrigin(_frameWidth / 2.f, _frameHeight / 2.f);
    _sprite.setScale(4.f, 4.f);

    _posX = x;
    _posY = y;
    _sprite.setPosition(_posX, _posY);

    _curr = cpoint::fromXYToRowCol(x, y);
}

void cbullet::updateAnimation(float deltaTime) {
    if (isLaser) {
        updateLaser(deltaTime);
        return;
    }

    _animationTimer += deltaTime;

    if (_animationTimer >= _animationSpeed) {
        _animationTimer -= _animationSpeed;
        _currentFrame++;

        if (_currentFrame >= _totalFrames)
            _currentFrame = 0;

        int col = _currentFrame;
        _frameRect.left = col * _frameWidth;
        _frameRect.top = 0;

        _sprite.setTextureRect(_frameRect);
    }
}

void cbullet::initLaser(const sf::Texture& tex, float x, float y, float targetX, float targetY, float duration) {
    isLaser = true;
    laserDuration = duration;
    laserTimer = 0.f;
    startPos = sf::Vector2f(x, y);
    targetPos = sf::Vector2f(targetX, targetY);

    laserSprite.setTexture(tex);
    laserSprite.setOrigin(0.f, tex.getSize().y / 2.f);
    laserSprite.setPosition(startPos);

    float dx = targetX - x;
    float dy = targetY - y;
    float distance = sqrtf(dx * dx + dy * dy);
    float angle = atan2f(dy, dx) * 180.f / 3.14159265f;

    laserSprite.setRotation(angle);
    laserSprite.setScale(distance / tex.getSize().x, 0.1f);

    _active = true;
}


void cbullet::updateLaser(float deltaTime) {
    if (!isLaser || !_active) return;
    laserTimer += deltaTime;
    if (laserTimer >= laserDuration)
        _active = false;
}


