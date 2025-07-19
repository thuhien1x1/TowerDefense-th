/*
#pragma once
#include "cenemy.h"
#include "ctower.h"

class cmap
{
    cenemy _ce;
    ctower _ctw;
    cpoint _m[cpoint::MAP_ROW][cpoint::MAP_COL];
public:
    cmap();

    void resetMapData();
    void makeMapData();
    void drawMap();

    cenemy& getEnemy() { return _ce; }
    ctower& getTower() { return _ctw; }
    cpoint(&getMap())[cpoint::MAP_ROW][cpoint::MAP_COL]{ return _m; }
};
*/

#pragma once
#include "cenemy.h"
#include "ctower.h"

class cmap
{
    cenemy _ce;
    ctower _ctw;
    cpoint _m[cpoint::MAP_ROW][cpoint::MAP_COL];
public:
    cmap();

    /*   void resetMapData();*/
    void makeMapData();
    void makeMap2Data();
    void makeMap3Data();
    void makeMap4Data();
    void ChooseMap(int index);
    cenemy& getEnemy() { return _ce; }
    ctower& getTower() { return _ctw; }
    cpoint(&getMap())[cpoint::MAP_ROW][cpoint::MAP_COL]{ return _m; }


};
