#include "clevel.h"
#include <iostream>

using namespace std;

clevel::clevel(int levelID, int enemyCount, int waveCount, int towerMaxCount, int startGold) {
	_levelID = levelID;
	_enemyCount = enemyCount;
	_waveCount = waveCount;
	_towerMaxCount = towerMaxCount;
	_startGold = startGold;
	_currentLevel = 1;
}

void clevel::loadMap(sf::Texture* mainTowerTexture, sf::Texture* mapTexture, int levelId) {
	_map.makeMapData(mainTowerTexture, mapTexture, levelId);
}

void clevel::nextWave() {
	if (_currentWaveIndex + 1 < _waves.size())
		_currentWaveIndex++;
}

pair<EnemyType, int> clevel::getCurrentWaveInfo() const {
	if (_currentWaveIndex < _waves.size())
		return _waves[_currentWaveIndex];
	else
		return { HEAVY_WALKER, 0 };
}
