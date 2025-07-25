#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "ctower.h"
#include "cbullet.h"
#include "cenemy.h"
#include "clevel.h"
#include "cmap.h"
#include <vector>
#include <map>

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

    Sprite backgroundSprite;

    Font font;
    Text hpText, gold, gameOver, gameWin;

    vector<cenemy> enemies;
    vector<ctower> towers;
    vector<cbullet> bullets;
    vector<clevel> levels;

    cmap* curMap;
    int currentLevelIndex;
    int waveIndex = 0;
    float TOWER_RANGE;

    bool isGameOver;
    bool isGameWin;
    bool isWaitingForNextLevel = false;
    bool showEndButtons = false;
    bool hasPressedPlay = false;

    map<EnemyType, EnemyAnimationData> enemyData;
    Texture* backgroundTexture[4];
    Texture* towerTexture;
    Texture* bulletTexture;
    Texture* mainTowerTexture;
    Texture* shootEffectTexture;
};