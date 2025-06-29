#include "clevel.h"

int clevel::getMapValue(int row, int col) const {
    if (row < 0 || row >= cpoint::MAP_ROW || col < 0 || col >= cpoint::MAP_COL) 
        return -99;
    return _map[row][col];
}

void clevel::getFullMap(int dest[][cpoint::MAP_COL]) const {
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            dest[i][j] = _map[i][j];
}
