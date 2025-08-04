#include "cenemy.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

cenemy::cenemy()
    : _posX(0.f), _posY(0.f), _health(3), _speed(3), _currentTarget(1), _reachedEnd(false), _pathLength(0) {

    // Directions: up, left, down, right for pathfinding
    dd[0] = -1; dd[1] = 0; dd[2] = 1; dd[3] = 0;
    dc[0] = 0; dc[1] = -1; dc[2] = 0; dc[3] = 1;

    // Default positions in grid
    _start = cpoint();
    _end = cpoint();
    _curr = cpoint();

    // Path array initialization
    for (int i = 0; i < cpoint::MAP_ROW * cpoint::MAP_COL; i++)
        _p[i] = cpoint();

    // Add
    _state = WALK;
    _isDead = false;
}


cenemy::cenemy(cpoint tstart, cpoint tend, cpoint tcurr) : cenemy() {
    _start = tstart;
    _end = tend;
    _curr = tcurr;
}

void cenemy::calcPath(int a[][cpoint::MAP_COL], int n, cpoint s, cpoint e) {
    std::queue<cpoint> q;
    bool visited[cpoint::MAP_ROW][cpoint::MAP_COL] = {};
    cpoint parent[cpoint::MAP_ROW][cpoint::MAP_COL];

    q.push(s);
    visited[s.getRow()][s.getCol()] = true;
    parent[s.getRow()][s.getCol()] = s;

    bool found = false;
    while (!q.empty()) {
        cpoint curr = q.front(); q.pop();
        if (curr.getRow() == e.getRow() && curr.getCol() == e.getCol()) {
            found = true;
            break;
        }
        for (int i = 0; i < 4; i++) {
            int dmoi = dd[i] + curr.getRow(), cmoi = dc[i] + curr.getCol();
            if (dmoi >= 0 && dmoi < cpoint::MAP_ROW && cmoi >= 0 && cmoi < cpoint::MAP_COL
                && !visited[dmoi][cmoi] && a[dmoi][cmoi] == 0) {
                visited[dmoi][cmoi] = true;
                parent[dmoi][cmoi] = curr;
                q.push(cpoint(dmoi, cmoi, 0));
            }
        }
    }

    if (found) {
        std::vector<cpoint> pathList;
        cpoint curr = e;
        while (!(curr.getRow() == s.getRow() && curr.getCol() == s.getCol())) {
            pathList.push_back(curr);
            curr = parent[curr.getRow()][curr.getCol()];
        }
        pathList.push_back(s);
        std::reverse(pathList.begin(), pathList.end());
        int i = 0;
        for (auto& p : pathList) _p[i++] = p;
        _pathLength = i;
    }
    else {
        _pathLength = 0;
    }
}

void cenemy::findPath(cpoint a[][cpoint::MAP_COL], cpoint s, cpoint e) {
    int ta[cpoint::MAP_ROW][cpoint::MAP_COL];
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            ta[i][j] = a[i][j].getC();
    calcPath(ta, cpoint::MAP_ROW, s, e);
}

void cenemy::updateSprite() {
    _sprite.setPosition(_posX, _posY);
}

void cenemy::setPosition(float x, float y) {
    _posX = x;
    _posY = y;
    updateSprite();
}

void cenemy::move(float dx, float dy) {
    _posX += dx;
    _posY += dy;
    updateSprite();
}

void cenemy::takeDamage(int damage) {
    if (_state == DEATH) return;

    _health -= damage;
    if (_health <= 0) {
        _sprite.setTexture(*_deathTex);
        _state = DEATH;
        _currentFrame = 0;
        _animationTimer = 0.f;

        _totalFrames = _deathFrames;
        _animationSpeed = _deathSpeed;
        _frameWidth = _deathFrameWidth;
        _frameHeight = _deathFrameHeight;

        _frameRect = sf::IntRect(0, 0, _frameWidth, _frameHeight);
        _sprite.setTextureRect(_frameRect);
        _sprite.setOrigin(_frameWidth / 2.f, _frameHeight / 1.25f);
    }
}

void cenemy::init(EnemyType type, float x, float y, int hp, const EnemyAnimationData& data) {
    _posX = x;
    _posY = y;
    _health = hp;
    _type = type;

    _sprite.setTexture(*_walkTex);
    _totalFrames = _walkFrames;
    _animationSpeed = _walkSpeed;
    _frameWidth = _walkFrameWidth;
    _frameHeight = _walkFrameHeight;

    _currentFrame = 0;
    _animationTimer = 0.f;
    _state = WALK;
    _isDead = false;
    _reachedEnd = false;

    _frameRect = sf::IntRect(0, 0, _frameWidth, _frameHeight);
    _sprite.setTextureRect(_frameRect);
    _sprite.setOrigin(_frameWidth / 2.f, _frameHeight / 1.25f);

    updateSprite();
}

void cenemy::loadFromData(const EnemyAnimationData& data) {
    _walkTex = data.walkTex;
    _attackTex = data.attackTex;
    _deathTex = data.deathTex;

    _walkFrames = data.walkFrames;
    _attackFrames = data.attackFrames;
    _deathFrames = data.deathFrames;

    _walkSpeed = data.walkSpeed;
    _attackSpeed = data.attackSpeed;
    _deathSpeed = data.deathSpeed;

    _walkFrameWidth = data.walkFrameWidth;
    _walkFrameHeight = data.walkFrameHeight;
    _attackFrameWidth = data.attackFrameWidth;
    _attackFrameHeight = data.attackFrameHeight;
    _deathFrameWidth = data.deathFrameWidth;
    _deathFrameHeight = data.deathFrameHeight;

    _sprite.setScale(data.scaleX, data.scaleY); // Because the sizes of the sprite sheets are not the same
}

void cenemy::triggerAttack(float towerX, float towerY) {
    if (_state != WALK) return;

    _sprite.setTexture(*_attackTex);
    _state = ATTACK;
    _currentFrame = 0;
    _animationTimer = 0.f;
    _attackTimer = 0.f;

    _totalFrames = _attackFrames;
    _animationSpeed = _attackSpeed;
    _frameWidth = _attackFrameWidth;
    _frameHeight = _attackFrameHeight;

    _frameRect = IntRect(0, 0, _frameWidth, _frameHeight);
    _sprite.setTextureRect(_frameRect);
    _sprite.setOrigin(_frameWidth / 2.f, _frameHeight / 1.25f);
}

void cenemy::updateAnimation(float deltaTime) {
    if (_state == DEATH && _isDead) return;

    if (_state == ATTACK && _isAttack) return;

    _animationTimer += deltaTime;
    if (_animationTimer >= _animationSpeed) {
        _animationTimer -= _animationSpeed;
        _currentFrame++;

        if (_currentFrame >= _totalFrames) {
            if (_state == DEATH) {
                _currentFrame = _totalFrames - 1;
                _isDead = true;
            }

            else if (_state == ATTACK) {
                _currentFrame = _totalFrames - 1;
                _isAttack = true;
            }

            else
                _currentFrame = 0;
        }

        _frameRect.left = _currentFrame * _frameWidth;
        _frameRect.top = 0;
        _sprite.setTextureRect(_frameRect);
    }
}

void cenemy::faceLeft(EnemyType type) {
    if (type == RANGED_MECH)
        _sprite.setScale(-1.f, 1.f);
    else
        _sprite.setScale(-0.5f, 0.5f);
}

void cenemy::faceRight(EnemyType type) {
    if (type == RANGED_MECH)
        _sprite.setScale(1.f, 1.f);
    else
        _sprite.setScale(0.5f, 0.5f);
}

int cenemy::getHealthByType(EnemyType type) {
    switch (type) {
    case FAST_SCOUT: return 3;
    case RANGED_MECH: return 5;
    case HEAVY_WALKER: return 8;
    default: return 3;
    }
}

int cenemy::getSpeedByType(EnemyType type) {
    switch (type) {
    case FAST_SCOUT: return 120;
    case RANGED_MECH: return 100;
    case HEAVY_WALKER: return 70;
    default: return 70;
    }
}

int cenemy::getResourcesByType(EnemyType type) {
    switch (type) {
    case FAST_SCOUT: return 20;
    case RANGED_MECH: return 30;
    case HEAVY_WALKER: return 40;
    default: return 20;
    }
}



