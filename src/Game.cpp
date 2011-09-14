#include "Game.h"

#include "FakeEngine.h"

MiniGame::~MiniGame(){}

Game::Game()
{
}

Game::~Game()
{
}

void Game::Initialize()
{
}

void Game::Click(float x, float y)
{
}

bool Game::IsComplete() const
{
	return false;
}

void Game::Render() const
{
	static const struct Rect scr = {0, 0, FakeEngine::width, FakeEngine::height};
	static const struct Rect tex = {0, 0, 1, 1};
	::Render(scr, cTextureId, tex);
}
