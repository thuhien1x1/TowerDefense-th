#include "cmap.h"
#include <iostream>

cmap::cmap() {
    resetMapData();
    makeMapData();
}
void cmap::resetMapData() {
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            _m[i][j] = cpoint(i, j, -1); 
}

void cmap::makeMapData() {
    int map[10][15] = {
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, 0, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, 0, -1, -1, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    };
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            _m[i][j] = cpoint(i, j, map[i][j]);

    // Set start, end, curr positions for enemy
    _ce.setStart(_m[5][0]);
    _ce.setEnd(_m[4][14]);
    _ce.setCurr(_m[5][0]);
    _ce.findPath(_m, _ce.getStart(), _ce.getEnd());

    // Set tower, map for bullet
    _ctw.setLocation(_m[5][0]);
    _ctw.setMapForBullet(_m);
    _ctw.calcPathBullet();
}

void cmap::drawMap() {
    for (int i = 0; i < cpoint::MAP_ROW; i++) {
        for (int j = 0; j < cpoint::MAP_COL; j++)
            std::cout << (_m[i][j].getC() == -1 ? '+' : (_m[i][j].getC() == 0 ? '.' : ' '));
        std::cout << '\n';
    }
}
