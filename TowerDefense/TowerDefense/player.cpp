#include "player.h"

player::player()
{
	hp = 10; gold = 50;
	for (int& s : score)
	{
		s = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		cost[i] = 10 + 10 * i;
	}
}

int player::get_score(int level)
{
	return score[level];
}

void player::setName(string name) {
	this->name = name;
}

string player::getName() {
	return name;
}
