#ifndef MINIGAME_H
#define MINIGAME_H

#include "MiniGameInterface.h"

class Game
	: public MiniGame
{
public:
	Game();
	virtual ~Game();

	void Initialize();
	void Click(float x, float y);
	bool IsComplete() const;
	void Render() const;
};

#endif // MINIGAME_H
