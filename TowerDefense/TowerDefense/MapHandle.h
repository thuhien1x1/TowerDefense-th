#pragma once
#include <iostream>
#include <cmath>
#include "cmap.h"

using namespace std;

class MapHandle {
public:
    static void setCmap1(cmap& map, int a, int b, int C);
    static void setCmap2(cmap& map, int a, int b, int C);
    static void setCmap3(cmap& map, int a, int b, int C);
    static void setCmap4(cmap& map, int a, int b, int C);
    static pair <int, int> getTowerdes1(int a, int b);
    static pair <int, int> getTowerdes2(int a, int b);
    static pair <int, int> getTowerdes3(int a, int b);
    static pair <int, int> getTowerdes4(int a, int b);

    static void setCmap(int index, cmap& map, int a, int b, int C);
    static pair <int, int> getTowerdes(int index, int a, int b);

};