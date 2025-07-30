#pragma once
#include "cpoint.h"
#include "cbullet.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class ctower {
private:
    Sprite _sprite;
    cpoint _location;
    cbullet _cb;
    float _shootTimer;
    int _targetEnemyIdx;

    // Add mainTower
    Sprite _mainTowerSprite;
    Texture* _mainTowerTexture;
    Vector2f _mainTowerPos;
    int _mainTowerHealth;

    // Add animation 
    Sprite _effectSprite;
    IntRect _effectFrameRect;
    int _effectFrameWidth;
    int _effectFrameHeight;
    int _effectTotalFrames;
    int _effectCurrentFrame;
    float _effectTimer;
    float _effectSpeed;
    bool _effectPlaying;

    // Type tower
    int Type;
public:
    ctower();

    int getTargetEnemyIdx() const;
    void setTargetEnemyIdx(int idx);
    void setMapForBullet(cpoint map[][cpoint::MAP_COL]);
    int calcPathBullet();
    cbullet& getBullet();
    int getType() const { return Type; } // Tower 1 = 0 ...
    void setType(int n) { Type = n; }

    void init(const Texture& tex, float x, float y);
    const Sprite& getSprite() const;

    void setLocation(const cpoint& loc);
    cpoint getLocation() const;

    void resetShootTimer(); // Reset the shoot timer to 0 after firing a bullet
    void addShootTimer(float dt); // Add delta time to the shoot timer, used to track cooldown between shots
    float getShootTimer() const; // Get the current value of the shoot timer to check if the tower is ready to shoot

    // Add shootEffect
    void initEffect(const Texture& tex, int frameWidth, int frameHeight, int totalFrames, float animSpeed);
    void startEffect();
    void updateEffect(float deltaTime);
    bool isEffectPlaying() const { return _effectPlaying; }
    const Sprite& getEffectSprite() const { return _effectSprite; }

    // Add mainTower
    void initMainTower(Texture* texture, int health, float x, float y);
    int getHealth() { return _mainTowerHealth; }
    void setHealth(int health) { _mainTowerHealth = health; }
    void decreaseHealth() { _mainTowerHealth--; if (_mainTowerHealth <= 0)  _mainTowerHealth = 0; }
    const Sprite& getMainTowerSprite() const { return _mainTowerSprite; }
};
