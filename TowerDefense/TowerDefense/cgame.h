#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <filesystem>

#include "cpoint.h"
#include "cmap.h"
#include "cenemy.h"
#include "cbullet.h"
#include "ctower.h"
#include "player.h"

using namespace sf;
using namespace std;

struct explosion {
    Sprite sprite;
    float timer = 0.f;
};


class cgame {
private:
    RenderWindow window;

    Texture backgroundTexture[4], mainTowerTexture, explosionTexture, menuTexture;
    Texture towerTexture[3];
    Texture bulletTexture[3];
    Texture enemyTexture[3];
    Texture infoTexture[3];
    Sprite backgroundSprite, mainTowerSprite;

    Font font;
    Text hpText, gameOverText, gameWin, gold;

    vector<cenemy> enemies;
    vector<ctower> towers;
    vector<cbullet> bullets;
    vector<explosion> explosions;

    cmap map;
    bool isGameOver;
    int mainTowerHealth;
    float enemySpeed;
    float TOWER_RANGE;

    player p;
    int level;
    int attacks;

public:
    cgame();
    void run();

    void processSaveFile();
    bool processLoadFile(const std::string& player);
    void playContinue();

    string playerName;
    int getLevel() { return level; };
    int setLevel(int l) { level = l; };
    void levelManagement();

private:
    void handleEvents();

    void updateEnemies(float dt);
    void updateTower(float dt);
    void updateTest(float dt);
    void updateMap(int index);

    void render(float dt);

    void spawnEnemies(int number, int type, int health);

    Sprite infoSprite[3];
    bool showInfo = false;
    int selectedinfo;

    bool isChoosingTower = false;
    cpoint selectedTile;  // cliked pixel
    Sprite towerIcons[3];  // 4 icon tower
};
