#pragma once
#include "State.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Utility.h"
#include "ctower.h"
#include "cbullet.h"
#include "cenemy.h"
#include "clevel.h"
#include "cmap.h"
#include "MapHandle.h"
#include <vector>
#include <map>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp>

using namespace std;
using namespace sf;

class GameState : public State
{
public:
    GameState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(Time dt);
    virtual bool handleEvent(const Event& event);

private:
    Event event;

    void loadLevel(int index);
    void spawnEnemies();
    int calStars();

    Sprite backgroundSprite;

    Font font;
    Text hpText, gold;

    vector<cenemy> enemies;
    vector<ctower> towers;
    vector<cbullet> bullets;
    vector<clevel> levels;

    cmap* curMap;
    int currentLevelIndex;
    int waveIndex;
    int mainTowerMaxHealth;
    float TOWER_RANGE;

    bool isGameOver;
    bool isGameWin;
    bool isWaitingForNextLevel = false;
    bool showEndButtons = false;
    bool hasPressedPlay = false;

    map<EnemyType, EnemyAnimationData> enemyData;
    Texture* backgroundTexture[4];
    Texture* towerTexture[6];
    Texture* bulletTexture[6];
    Texture* mainTowerTexture;
    Texture* shootEffectTexture;

    // UI
    Sprite pauseButton;
    Sprite commingWave;
    Sprite upgradeButton;
    Sprite towerChoosingButtons[3];
    Sprite towerChoosingCircle;


    // Tower Infos
    Texture* infoTexture[6];
    Sprite infoSprite[6];
    bool showInfo = false;
    int selectedinfo;

    // Icon appear when click
    bool isChoosingTower = false;
    cpoint selectedTile;  // cliked pixel
};