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
	srand(time(NULL));
	selectedBlock = -1;
	calcBlocks();
	mixBlocks();
}

/* virtual */ void Game::Click(float x, float y)
{
	const int otherBlock = blockNum(x, y);
	// не двигать больше уже поставленные на место
	if (otherBlock == blocks[otherBlock])
	{
		return;
	}

	// выбрать, если ничего не выбрано
	if (-1 == selectedBlock)
	{
		selectedBlock = otherBlock;
		return;
	}
	swapBlocks(selectedBlock, otherBlock);
	selectedBlock = -1;
}

/* virtual */ bool Game::IsComplete() const
{
	for (int i = 0; i < blocksNum; ++i)
	{
		if (i != blocks[i])
		{
			return false;
		}
	}
	return true;
}

/* virtual */ void Game::Render() const
{
	for (int i = 0; i < blocksNum; ++i)
	{
		Rect texRect = normalizeTexCoords(blockRect(blocks[i]));
		Rect scrRectOrigin = blockRect(i);
		int indent;
		if (blocks[i] == i)	// правильно поставленные идут без отступа
		{
			indent = 0;
		}
		else if (blocks[i] == selectedBlock)	// выделенные с небольшим оступом
		{
			indent = 2;
		}
		else						// у всех остальных отступ большой
		{
			indent = 5;
		}

		scrRectOrigin.left += indent;
		scrRectOrigin.top += indent;
		scrRectOrigin.right -= indent;
		scrRectOrigin.bottom -= indent;

		::Render(scrRectOrigin, cTextureId, texRect);
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

			blocks[currentBlock] = currentBlock;
		}
	}
}

void Game::mixBlocks()
{
	for (int i = 0; i < blocksNum; ++i)
	{
		const int r = rand() % blocksNum;
		swapBlocks(i, r);
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

void Game::swapBlocks(const int left, const int right)
{
	if (left != right)
	{
		const int t = blocks[left];
		blocks[left] = blocks[right];
		blocks[right] = t;
	}
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
