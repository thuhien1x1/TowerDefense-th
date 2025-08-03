#include "ctower.h"

ctower::ctower() : _shootTimer(0.f), _targetEnemyIdx(-1), _mainTowerHealth(5), _mainTowerTexture(nullptr) {}

int ctower::calcPathBullet() {
    return _cb.calcPathBullet(_location);
}

void ctower::init(const Texture& tex, float x, float y) {
    _sprite.setTexture(tex);
    _sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);
    _sprite.setScale(0.4f, 0.4f);
    _sprite.setPosition(x, y);
    _location = cpoint::fromXYToRowCol(x, y);
}

const Sprite& ctower::getSprite() const { return _sprite; }

void ctower::setLocation(const cpoint& loc) { _location = loc; }
cpoint ctower::getLocation() const { return _location; }

void ctower::resetShootTimer() { _shootTimer = 0.f; }
void ctower::addShootTimer(float dt) { _shootTimer += dt; }
float ctower::getShootTimer() const { return _shootTimer; }

int ctower::getTargetEnemyIdx() const { return _targetEnemyIdx; }
void ctower::setTargetEnemyIdx(int idx) { _targetEnemyIdx = idx; }

void ctower::setMapForBullet(cpoint map[][cpoint::MAP_COL]) {
    _cb.updateMap(map);
}

void ctower::initEffect(const Texture& tex, int frameWidth, int frameHeight, int totalFrames, float speed) {
    _effectSprite.setTexture(tex);
    _effectFrameWidth = frameWidth;
    _effectFrameHeight = frameHeight;
    _effectTotalFrames = totalFrames;
    _effectSpeed = speed;
    _effectCurrentFrame = 0;
    _effectTimer = 0.f;
    _effectPlaying = false;

    _effectFrameRect = IntRect(0, 0, _effectFrameWidth, _effectFrameHeight);
    _effectSprite.setTextureRect(_effectFrameRect);
    _effectSprite.setOrigin(_effectFrameWidth / 2.f, _effectFrameHeight / 2.f);
    _effectSprite.setScale(3.f, 3.f);
}

void ctower::startEffect() {
    if (_effectPlaying) return;
    _effectPlaying = true;
    _effectCurrentFrame = 0;
    _effectTimer = 0.f;
    _effectFrameRect.left = 0;
    _effectSprite.setTextureRect(_effectFrameRect);
    _effectSprite.setPosition(_sprite.getPosition());
}

void ctower::updateEffect(float deltaTime) {
    if (!_effectPlaying) return;

    _effectTimer += deltaTime;
    if (_effectTimer >= _effectSpeed) {
        _effectTimer -= _effectSpeed;
        _effectCurrentFrame++;

        if (_effectCurrentFrame >= _effectTotalFrames) {
            _effectPlaying = false;
            return;
        }

        _effectFrameRect.left = _effectCurrentFrame * _effectFrameWidth;
        _effectSprite.setTextureRect(_effectFrameRect);
    }
}




