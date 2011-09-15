#ifndef MINIGAME_H
#define MINIGAME_H

#include "MiniGameInterface.h"

class Game
	: public MiniGame
{
public:
	Game();
	~Game();

	void Initialize();
	void Click(float x, float y);
	bool IsComplete() const;
	void Render() const;

private:
	void calcBlocks();
	void mixBlocks();
	const Rect & blockRect(const int num) const;
	int blockNum(const float x, const float y) const;
	const Rect & normalizeTexCoords(const Rect & origin) const;

	const int blocksNum;
	const float blockWidth;
	const float blockHeight;
	Rect * blocksCoords;
	int * blocks;

	int selectedBlock; // -1 for none
};

#endif // MINIGAME_H
