#include "Game.h"

#include "FakeEngine.h"

MiniGame::~MiniGame(){}

Game::Game()
	: blocksNum(cColumns * cRows)
	, blockWidth(FakeEngine::width / cColumns)
	, blockHeight(FakeEngine::height / cRows)
{
	blocksCoords = new Rect[blocksNum];
	blocks = new int[blocksNum];
}

/* virtual */ Game::~Game()
{
	delete [] blocks;
	delete [] blocksCoords;
}

/* virtual */ void Game::Initialize()
{
	calcBlocks();
	mixBlocks();
	selectedBlock = -1;
}

/* virtual */ void Game::Click(float x, float y)
{
	if (-1 == selectedBlock)
	{
		selectedBlock = blockNum(x, y);
		return;
	}

	const int otherBlock = blockNum(x, y);

	if (otherBlock != selectedBlock)
	{
		int beforeS = blocks[selectedBlock];
		int beforeO = blocks[otherBlock];


		int t = blocks[selectedBlock];
		blocks[selectedBlock] = blocks[otherBlock];
		blocks[otherBlock] = t;

		int afterS = blocks[selectedBlock];
		int afterO = blocks[otherBlock];
		selectedBlock = -1;
	}
	selectedBlock = -1;
}

/* virtual */ bool Game::IsComplete() const
{
	return false;
}

/* virtual */ void Game::Render() const
{
	for (int i = 0; i < blocksNum; ++i)
	{
		Rect texRect = normalizeTexCoords(blockRect(blocks[i]));
		const Rect scrRectOrigin = blockRect(i);
		Rect scrRect;
		if (blocks[i] == selectedBlock)
		{
			scrRect.left = scrRectOrigin.left - 1;
			scrRect.top = scrRectOrigin.top - 1;
			scrRect.right = scrRectOrigin.right + 1;
			scrRect.bottom = scrRectOrigin.bottom + 1;
		}
		else
		{
			scrRect.left = scrRectOrigin.left + 3;
			scrRect.top = scrRectOrigin.top + 3;
			scrRect.right = scrRectOrigin.right - 3;
			scrRect.bottom = scrRectOrigin.bottom - 3;
		}

		::Render(scrRect, cTextureId, texRect);
	}
}

void Game::calcBlocks()
{
	for (int row = 0; row < cRows; ++row)
	{
		for (int column = 0; column < cColumns; ++column)
		{
			const int currentBlock = column + row * cColumns;
			assert(currentBlock < blocksNum);

			blocksCoords[currentBlock].left = column * blockWidth;
			blocksCoords[currentBlock].top = row * blockHeight;
			blocksCoords[currentBlock].right = (column + 1) * blockWidth;
			blocksCoords[currentBlock].bottom = (row + 1) * blockHeight;
		}
	}
}

void Game::mixBlocks()
{
	for (int i = 0; i < blocksNum; ++i)
	{
		blocks[i] = i;
	}
}

const Rect& Game::blockRect(int num) const
{
	return blocksCoords[blocks[num]];
}

int Game::blockNum(float x, float y) const
{
	const int row = int(y / blockHeight);
	const int column = int(x / blockWidth);
	return column + row * cColumns;
}

// преобразует из координат в пикселах в координаты [0..1]
// причём (0, 0) - верхний левый угол картинки, а не нижний
const Rect& Game::normalizeTexCoords(const Rect & origin) const
{
	static Rect rect;
	rect.left = origin.left / FakeEngine::width;
	rect.top = (FakeEngine::height - origin.top) / FakeEngine::height;
	rect.right = origin.right / FakeEngine::width;
	rect.bottom = (FakeEngine::height - origin.bottom) / FakeEngine::height;
	return rect;
}
