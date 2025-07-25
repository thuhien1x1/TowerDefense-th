#pragma once
#include "cpoint.h"
#include <SFML/Graphics.hpp>

using namespace sf;

// Add
enum EnemyState { WALK, ATTACK, DEATH };
enum EnemyType { FAST_SCOUT = 0, RANGED_MECH = 1, HEAVY_WALKER = 2 };

struct EnemyAnimationData {
    const Texture* walkTex;
    const Texture* attackTex;
    const Texture* deathTex;

    int walkFrames, attackFrames, deathFrames;
    float walkSpeed, attackSpeed, deathSpeed;

    int walkFrameWidth, walkFrameHeight;
    int attackFrameWidth, attackFrameHeight;
    int deathFrameWidth, deathFrameHeight;

    float scaleX;
    float scaleY;
};

class cenemy
{
private:
    // Path finding
    cpoint _start, _end, _curr;
    cpoint _p[cpoint::MAP_ROW * cpoint::MAP_COL];
    int _pathLength;
    int _currentTarget;
    int dd[4], dc[4];

    // Stats
    int _speed;
    int _health;
    int resources;
    EnemyType _type;

    // Position
    float _posX, _posY;
    bool _reachedEnd;

    // Add frame data
    Sprite _sprite;
    IntRect _frameRect;
    int _frameWidth, _frameHeight;
    int _currentFrame, _totalFrames;
    float _animationTimer, _animationSpeed;

    const Texture* _walkTex;
    const Texture* _attackTex;
    const Texture* _deathTex;

    int _walkFrames, _attackFrames, _deathFrames;
    int _walkCols, _attackCols, _deathCols;
    int _walkRows, _attackRows, _deathRows;
    float _walkAnimSpeed, _attackAnimSpeed, _deathAnimSpeed;
    float _walkSpeed, _attackSpeed, _deathSpeed;
    float _walkFrameWidth, _walkFrameHeight, _attackFrameWidth, _attackFrameHeight, _deathFrameWidth, _deathFrameHeight;

    // Add animation
    EnemyState _state;
    bool _isDead;
    bool _isAttackTriggered;
    bool _isAttackingMainTower = false;
    float _attackTimer = 0.f;
    float _attackCooldown = 1.f;

public:
    cenemy();
    cenemy(cpoint tstart, cpoint tend, cpoint tcurr);

    // Init/reset
    void init(EnemyType type, float x, float y, int hp, const EnemyAnimationData& data);

    // Getters
    cpoint* getP() { return _p; }
    cpoint getStart() const { return _start; }
    cpoint getEnd() const { return _end; }
    cpoint getCurr() const { return _curr; }
    int getPathLength() const { return _pathLength; }
    int getSpeed() const { return _speed; }
    int getHealth() const { return _health; }
    int getResources() const { return resources; }
    int getCurrentTarget() const { return _currentTarget; }
    float getX() const { return _posX; }
    float getY() const { return _posY; }
    EnemyState getState() const { return _state; }
    EnemyType getType() const { return _type; }
    const Sprite& getSprite() const { return _sprite; }
    static int getHealthByType(EnemyType type);
    static int getSpeedByType(EnemyType type);
    static int getResourcesByType(EnemyType type);

    // Setters 
    void setSpeed(int tspeed) { if (tspeed > 0 && tspeed < 10) _speed = tspeed; }
    void setHealth(int hp) { _health = hp; }
    void setStart(const cpoint& tstart) { _start = tstart; }
    void setEnd(const cpoint& tend) { _end = tend; }
    void setCurr(const cpoint& tcurr) { _curr = tcurr; }
    void setPosition(float x, float y);
    void setCurrentTarget(int t) { _currentTarget = t; }
    void loadFromData(const EnemyAnimationData& data);
    bool hasReachedEnd() const { return _reachedEnd; }
    bool isDead() const { return _health <= 0; }

    // Movement
    void updateSprite();
    void updateAnimation(float deltaTime);
    void move(float dx, float dy);
    void incrementTarget() { _currentTarget++; }
    void reachEnd() { _reachedEnd = true; }
    void faceLeft(EnemyType type);
    void faceRight(EnemyType type);

    // Combat
    bool hasFinishedDeathAnim() const { return _isDead; }
    void triggerAttack(float towerX, float towerY);
    void takeDamage(int damage);

    // Pathfinding
    void findPath(cpoint a[][cpoint::MAP_COL], cpoint s, cpoint e);

private:
    void calcPath(int a[][cpoint::MAP_COL], int n, cpoint s, cpoint e);
};

