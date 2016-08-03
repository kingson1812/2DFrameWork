#include <BrainGame.h>
#include <Define.h>

static Game * s_instance = NULL;

Game::Game()
{}

Game ::~Game()
{}

static void CreateInstance()
{
	s_instance = new Game();
}

static void DestroyInstance()
{
	SAFE_DEL(s_instance);
}

static Game * GetInstance()
{
	return s_instance;
}

void Game::Init()
{

}

void Game::Render()
{

}

void Game::Update(float deltaTime)
{

}