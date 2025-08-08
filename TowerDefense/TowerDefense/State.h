#pragma once

#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf
{
	class RenderWindow;
}

class StateStack;
class Player;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, 
					Player& player, int& stars,
					SoundBufferHolder& sfx, MusicHolder& music,
					bool& menuMusicFlag, bool& sfxFlag,
					MusicState& musicState);

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		Player* player;
		int* victoryStars;

		SoundBufferHolder* soundBuffers;
		MusicHolder* musics;
		bool* isMusicOn;
		bool* isSoundOn;
		MusicState* currentMusic;
	};


public:
	State(StateStack& stack, Context context);
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(sf::Time dt) = 0;
	virtual bool		handleEvent(const sf::Event& event) = 0;


protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;


private:
	StateStack* mStack;
	Context				mContext;
};