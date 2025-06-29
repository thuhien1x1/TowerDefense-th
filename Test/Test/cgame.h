#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "cpoint.h"
#include "cmap.h"
#include "cenemy.h"
#include "cbullet.h"
#include "ctower.h"

using namespace sf;
using namespace std;

class cgame {
private:
    RenderWindow window;
    Texture backgroundTexture, towerTexture, enemyTexture, bulletTexture, mainTowerTexture;
    Sprite backgroundSprite, mainTowerSprite;
    Font font;
    Text hpText, gameOverText;

    vector<cenemy> enemies;
    vector<ctower> towers;
    vector<cbullet> bullets;

    cmap map;
    bool isGameOver;
    int mainTowerHealth;
    float enemySpeed;
    float TOWER_RANGE;

public:
    cgame();
    void run();

private:
    void handleEvents();
    void update(float dt);
    void render();
    void spawnEnemies();
};
