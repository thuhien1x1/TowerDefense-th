#pragma once
#include <string>

using namespace std;

class player
{
private:
	string name;
	int score[4];
	int hp;
	int gold;
	int cost[3]; // costs of 3 towers: 10 20 30 respectively
public:
	player();

	void new_hp(int h) { hp = h; } //mainTower ???
	int get_hp() { return hp; }
	void de_hp(int a) { hp -= a; }

	int get_gold() { return gold; }
	void in_gold(int a) { gold += a; }
	void de_gold(int a) { gold -= a; }
	void set_gold(int a) { gold = a; }

	int get_score(int level);
	void in_score(int level, int a) { score[level] += a; }
	void set_score(int level, int a) { score[level] = a; };

	int get_cost(int towerType) { return cost[towerType]; };

	void setName(string);
	string getName();
};

