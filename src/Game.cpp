#include "Game.h"

#include "FakeEngine.h"

MiniGame::~MiniGame(){}

Game::Game()
	: blocksNum(cColumns * cRows)
	, blockWidth(FakeEngine::width / cColumns)
	, blockHeight(FakeEngine::height / cRows)
{
	blocks = new Rect[blocksNum];
	calcBlocks();
	mixBlocks();
}

/* virtual */ Game::~Game()
{
	delete [] blocks;
}

/* virtual */ void Game::Initialize()
{
}

/* virtual */ void Game::Click(float x, float y)
{
}

/* virtual */ bool Game::IsComplete() const
{
	return false;
}

/* virtual */ void Game::Render() const
{
	for (size_t i = 0; i < blocksNum; ++i)
	{
		Rect texRect = normalizeTexCoords(blockRect(i));
		Rect scrRect = blockRect(i);
		scrRect.left += 1;
		scrRect.top += 1;
		scrRect.right -= 1;
		scrRect.bottom -= 1;

		::Render(scrRect, cTextureId, texRect);
	}
}

void Game::calcBlocks()
{
	for (size_t row = 0; row < cRows; ++row)
	{
		for (size_t column = 0; column < cColumns; ++column)
		{
			const size_t currentBlock = column + row * cColumns;
			assert(currentBlock < blocksNum);

			blocks[currentBlock].left = column * blockWidth;
			blocks[currentBlock].top = row * blockHeight;
			blocks[currentBlock].right = (column + 1) * blockWidth;
			blocks[currentBlock].bottom = (row + 1) * blockHeight;
		}
	}
}

void Game::mixBlocks()
{
}

const Rect& Game::blockRect(int num) const
{
	return blocks[num];
}

int Game::blockNum(float x, float y) const
{
	const int row = int(y / blockHeight);
	const int column = int(x / blockWidth);
	return column + row * cColumns;
}

// преобразует из координат в пикселах в координаты [0..1]
const Rect& Game::normalizeTexCoords(const Rect & origin) const
{
	static Rect rect;
	rect.left = origin.left / FakeEngine::width;
	rect.top = origin.top / FakeEngine::height;
	rect.right = origin.right / FakeEngine::width;
	rect.bottom = origin.bottom / FakeEngine::height;

	return rect;
}
