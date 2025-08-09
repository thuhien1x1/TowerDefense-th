#include "ctower.h"

ctower::ctower() : _shootTimer(0.f), _targetEnemyIdx(-1), _mainTowerHealth(5), _mainTowerTexture(nullptr) {}

int ctower::calcPathBullet() {
    return _cb.calcPathBullet(_location);
}

void ctower::init(const Texture& tex, float x, float y, int index, int itower) {
    _sprite.setTexture(tex);
    changeOrigin(index, itower, tex);
    _sprite.setScale(0.4f, 0.4f);
    _sprite.setPosition(x, y);
    _location = cpoint::fromXYToRowCol(x, y);
}

void ctower::changeOrigin(int index, int itower, const Texture& tex)
{
    switch (index) {
    case 0:
        if (itower == 2)
            _sprite.setOrigin(tex.getSize().x / 4.0f, tex.getSize().y / 1.1f);
        else
            _sprite.setOrigin(tex.getSize().x / 3.0f, tex.getSize().y);
        break;
    case 1:
        if (itower == 1 || itower == 4)
            _sprite.setOrigin(tex.getSize().x / 4.0f, tex.getSize().y / 1.1f);
        else
            _sprite.setOrigin(tex.getSize().x / 3.0f, tex.getSize().y / 1.1f);
        break;
    case 2:
        if (itower == 4 || itower == 5)
            _sprite.setOrigin(tex.getSize().x / 4.0f, tex.getSize().y / 1.1f);
        else
            _sprite.setOrigin(tex.getSize().x / 3.0f, tex.getSize().y / 1.1f);
        break;
    case 3:
        if (itower == 0 || itower == 3 || itower == 4)
            _sprite.setOrigin(tex.getSize().x / 4.0f, tex.getSize().y / 1.1f);
        else
            _sprite.setOrigin(tex.getSize().x / 3.0f, tex.getSize().y / 1.1f);
        break;
    default:
        break;
    }
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
    _effectSprite.setOrigin(_effectFrameWidth / 3.f, _effectFrameHeight);
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




