#pragma once
#include "State.h"
#include "clevel.h"
#include "MenuState.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <iostream>
#include <fstream>

using namespace std;

class SaveManagement : public State
{
public:
	SaveManagement(StateStack& stack, Context context);

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

	void					updateOptionText();

private:
	enum fileState
	{
		SELECT_SAVE,
		Exit
	};

private:
	sf::Sprite				mBackgroundSprite;

	std::vector<sf::Text>	mOptions;
	std::size_t				mOptionIndex;

private:
	// process load file
	vector<string> savedNames;
	void scanSaveFolder();

public:
	// process save file
	struct levelResult
	{
		bool status; // isGameOver = 1, isGameWin = 1, else = 0
		int curGold; // startGold = 
		int stars; // if (!status) = 0, else = 
		int health;
		int curWave;
		vector<ctower> towers;
	};
	static vector<levelResult> playerResult;
	static void save(const string playerName);

	// Modify player's name
	static string playerName;
	static void setName(string pName);

	static bool load(string pName);
};