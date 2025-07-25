#pragma once
#include "cenemy.h"
#include "ctower.h"
#include <vector>

using namespace std;

class cmap
{
private:
    cenemy _ce;
    ctower _ctw;
    cpoint _m[cpoint::MAP_ROW][cpoint::MAP_COL];
    // Add
    cpoint _mainTowerTile;
    ctower _mainTower;
    vector <cpoint> _towerBuiltPos;
    vector <bool> _isBuilt;
    sf::Sprite _background;

public:
    cmap();

    void resetMapData();
    void makeMapData(sf::Texture* mainTowerTexture, sf::Texture* mapTexture, int levelID);

    cenemy& getEnemy() { return _ce; }
    ctower& getTower() { return _ctw; }
    cpoint(&getMap())[cpoint::MAP_ROW][cpoint::MAP_COL]{ return _m; }
    sf::Sprite& getBackground() { return _background; }

    // Add
    void setMainTowerTile(const cpoint& p) { _mainTowerTile = p; }
    cpoint getMainTowerTile() const { return _mainTowerTile; }
    ctower& getMainTower();
};
