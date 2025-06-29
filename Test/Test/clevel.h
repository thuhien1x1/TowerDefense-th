#pragma once
#include "cpoint.h"

class clevel
{
private:
	int _enemyHealth;
	int _enemyCount;
	int _waveCount;
	int _mainTowerHealth;
	float _towerAttackRate; // Time between shots
	int _towerMaxCount;
	int _map[cpoint::MAP_ROW][cpoint::MAP_COL];

public:
	clevel(int enemyHealth, int enemyCount, int enemyWave, double mainTowerAttackRate, int towerMaxCount);

	int getEnemyHealth() const { return _enemyHealth; }
	int getEnemyCount() const { return _enemyCount; }
	int getWaveCount() const { return _waveCount; }
	int getEnemyMainTowerHealth() const { return _mainTowerHealth; }
	float getTowerAttackRate() const { return _towerAttackRate; }
	int getTowerMaxCount() const { return _towerMaxCount; }

	int getMapValue(int row, int col) const; // Get the value at a specific tile, quickly check a tile
	void getFullMap(int dest[][cpoint::MAP_COL]) const; // Use to get the entire map at once to reset the game map
};

