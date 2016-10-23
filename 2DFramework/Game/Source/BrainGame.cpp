#include <BrainGame.h>
#include <Define.h>

Game * Game::s_instance = NULL;

Game::Game()
{}

Game ::~Game()
{}

void Game::CreateInstance()
{
	s_instance = new Game();
}

void Game::DestroyInstance()
{
	SAFE_DEL(s_instance);
}

Game * Game::GetInstance()
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