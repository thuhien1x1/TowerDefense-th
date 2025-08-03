#include "MapHandle.h"


// MAP 1
void MapHandle::setCmap1(cmap& map, int a, int b, int C) // a = row || b = col
{
    if (a >= 14 && a <= 16 && b >= 6 && b <= 9) {
        for (int i = 14; i <= 16; ++i) {
            for (int j = 6; j <= 9; ++j) {
                map.getMap()[i][j].setC(C);
            }
        }
    }

    else if (a >= 22 && a <= 24 && b >= 12 && b <= 15) {
        for (int i = 22; i <= 24; ++i) {
            for (int j = 12; j <= 15; ++j) {
                map.getMap()[i][j].setC(C);
            }
        }
    }

    else if (a >= 15 && a <= 18 && b >= 26 && b <= 28) {
        for (int i = 15; i <= 18; ++i) {
            for (int j = 26; j <= 28; ++j) {
                map.getMap()[i][j].setC(C);
            }
        }
    }

    else if (a >= 4 && a <= 6 && b >= 30 && b <= 33) {
        for (int i = 4; i <= 6; ++i) {
            for (int j = 30; j <= 33; ++j) {
                map.getMap()[i][j].setC(C);
            }
        }
    }

    else if (a >= 12 && a <= 14 && b >= 35 && b <= 38) {
        for (int i = 12; i <= 14; ++i) {
            for (int j = 35; j <= 38; ++j) {
                map.getMap()[i][j].setC(C);
            }
        }
    }
}

pair<int, int> MapHandle::getTowerdes1(int a, int b)
{
    if (a >= 14 && a <= 16 && b >= 6 && b <= 9)
        return { 16, 8 };
    else if (a >= 22 && a <= 24 && b >= 12 && b <= 15)
        return { 25, 13 };
    else if (a >= 15 && a <= 18 && b >= 26 && b <= 28)
        return { 16, 27 };
    else if (a >= 4 && a <= 6 && b >= 30 && b <= 33)
        return { 5, 31 };
    else if (a >= 12 && a <= 14 && b >= 35 && b <= 38)
        return { 13, 36 };

    return { -1, -1 };
}

// MAP 2
void MapHandle::setCmap2(cmap& map, int a, int b, int C)
{
    if (a >= 14 && a <= 16 && b >= 6 && b <= 9) {
        for (int i = 14; i <= 16; ++i)
            for (int j = 6; j <= 9; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 16 && a <= 19 && b >= 20 && b <= 22) {
        for (int i = 16; i <= 19; ++i)
            for (int j = 20; j <= 22; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 22 && a <= 24 && b >= 9 && b <= 12) {
        for (int i = 22; i <= 24; ++i)
            for (int j = 9; j <= 12; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 5 && a <= 7 && b >= 23 && b <= 26) {
        for (int i = 5; i <= 7; ++i)
            for (int j = 23; j <= 26; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 16 && a <= 19 && b >= 28 && b <= 30) {
        for (int i = 16; i <= 19; ++i)
            for (int j = 28; j <= 30; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 14 && a <= 16 && b >= 36 && b <= 39) {
        for (int i = 14; i <= 16; ++i)
            for (int j = 36; j <= 39; ++j)
                map.getMap()[i][j].setC(C);
    }
}

pair<int, int> MapHandle::getTowerdes2(int a, int b)
{
    if (a >= 14 && a <= 16 && b >= 6 && b <= 9)
        return { 15, 8 };
    else if (a >= 16 && a <= 19 && b >= 20 && b <= 22)
        return { 17, 21 };
    else if (a >= 22 && a <= 24 && b >= 9 && b <= 12)
        return { 23, 10 };
    else if (a >= 5 && a <= 7 && b >= 23 && b <= 26)
        return { 6, 24 };
    else if (a >= 16 && a <= 19 && b >= 28 && b <= 30)
        return { 17, 29 };
    else if (a >= 14 && a <= 16 && b >= 36 && b <= 39)
        return { 15, 37 };

    return { -1, -1 };
}

// MAP 3
void MapHandle::setCmap3(cmap& map, int a, int b, int C)
{
    if (a >= 14 && a <= 16 && b >= 5 && b <= 8) {
        for (int i = 14; i <= 16; ++i)
            for (int j = 5; j <= 8; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 22 && a <= 24 && b >= 16 && b <= 19) {
        for (int i = 22; i <= 24; ++i)
            for (int j = 16; j <= 19; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 2 && a <= 4 && b >= 25 && b <= 28) {
        for (int i = 2; i <= 4; ++i)
            for (int j = 25; j <= 28; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 2 && a <= 4 && b >= 37 && b <= 40) {
        for (int i = 2; i <= 4; ++i)
            for (int j = 37; j <= 40; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 15 && a <= 18 && b >= 39 && b <= 41) {
        for (int i = 15; i <= 18; ++i)
            for (int j = 39; j <= 41; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 8 && a <= 11 && b >= 11 && b <= 13) {
        for (int i = 8; i <= 11; ++i)
            for (int j = 11; j <= 13; ++j)
                map.getMap()[i][j].setC(C);
    }
}

pair<int, int> MapHandle::getTowerdes3(int a, int b)
{
    if (a >= 14 && a <= 16 && b >= 5 && b <= 8)
        return { 15, 6 };
    else if (a >= 22 && a <= 24 && b >= 16 && b <= 19)
        return { 23, 17 };
    else if (a >= 2 && a <= 4 && b >= 25 && b <= 28)
        return { 3, 26 };
    else if (a >= 2 && a <= 4 && b >= 37 && b <= 40)
        return { 3, 38 };
    else if (a >= 15 && a <= 18 && b >= 39 && b <= 41)
        return { 16, 40 };
    else if (a >= 8 && a <= 11 && b >= 11 && b <= 13)
        return { 9, 12 };

    return { -1, -1 };
}

// MAP 4
void MapHandle::setCmap4(cmap& map, int a, int b, int C)
{
    if (a >= 9 && a <= 12 && b >= 9 && b <= 11) {
        for (int i = 9; i <= 12; ++i)
            for (int j = 9; j <= 11; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 20 && a <= 22 && b >= 7 && b <= 10) {
        for (int i = 20; i <= 22; ++i)
            for (int j = 7; j <= 10; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 11 && a <= 13 && b >= 18 && b <= 21) {
        for (int i = 11; i <= 13; ++i)
            for (int j = 18; j <= 21; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 18 && a <= 21 && b >= 20 && b <= 22) {
        for (int i = 18; i <= 21; ++i)
            for (int j = 20; j <= 22; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 16 && a <= 19 && b >= 35 && b <= 37) {
        for (int i = 16; i <= 19; ++i)
            for (int j = 35; j <= 37; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 6 && a <= 8 && b >= 35 && b <= 38) {
        for (int i = 6; i <= 8; ++i)
            for (int j = 35; j <= 38; ++j)
                map.getMap()[i][j].setC(C);
    }
    else if (a >= 14 && a <= 16 && b >= 41 && b <= 44) {
        for (int i = 14; i <= 16; ++i)
            for (int j = 41; j <= 44; ++j)
                map.getMap()[i][j].setC(C);
    }
}

pair<int, int> MapHandle::getTowerdes4(int a, int b)
{
    if (a >= 9 && a <= 12 && b >= 9 && b <= 11)
        return { 10, 10 };
    else if (a >= 20 && a <= 22 && b >= 7 && b <= 10)
        return { 21, 8 };
    else if (a >= 11 && a <= 13 && b >= 18 && b <= 21)
        return { 12, 19 };
    else if (a >= 18 && a <= 21 && b >= 20 && b <= 22)
        return { 19, 21 };
    else if (a >= 16 && a <= 19 && b >= 35 && b <= 37)
        return { 17, 36 };
    else if (a >= 6 && a <= 8 && b >= 35 && b <= 38)
        return { 7, 36 };
    else if (a >= 14 && a <= 16 && b >= 41 && b <= 44)
        return { 15, 42 };

    return { -1, -1 };
}


// Main Handle
void MapHandle::setCmap(int index, cmap& map, int a, int b, int C)
{
    if (index == 0) {
        setCmap1(map, a, b, C);
        return;
    }

    else if (index == 1) {
        setCmap2(map, a, b, C);
        return;
    }

    else if (index == 2) {
        setCmap3(map, a, b, C);
        return;
    }

    setCmap4(map, a, b, C);
}

pair<int, int> MapHandle::getTowerdes(int index, int a, int b)
{
    if (index == 0) {
        return getTowerdes1(a, b);
    }

    else if (index == 1) {
        return getTowerdes2(a, b);
    }

    else if (index == 2) {
        return getTowerdes3(a, b);
    }

    return getTowerdes4(a, b);
}
