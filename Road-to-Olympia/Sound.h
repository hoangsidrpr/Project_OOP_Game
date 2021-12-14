#ifndef _SOUND_H_
#define _SOUND_H_

#include "Console_Game.h"

class Sound {
public:
	void InGame();
	void CharacterStep();
	void Crash();
	void Lose();
	void Victory();
};

#endif // !_SOUND_H_

