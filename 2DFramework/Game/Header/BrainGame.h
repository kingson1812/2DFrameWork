#pragma once
#include <stdio.h>

class Game 
{
public:
	Game();
	~Game();

	void Init();
	void Render();
	void Update(float deltaTime);

	static void CreateInstance();
	static Game * GetInstance();
	static void DestroyInstance();
private:
	static Game* s_instance;
};

#define GAME_INSTANCE Game::GetInstance()


