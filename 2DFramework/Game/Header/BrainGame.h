#pragma once
#include <stdio.h>
#include <Header\Object.h>
class Game 
{
public:
	Game();
	~Game();
	Object *c;
	void Init();
	void Draw();
	void Update(float deltaTime);

	static void CreateInstance();
	static Game * GetInstance();
	static void DestroyInstance();
private:
	static Game* s_instance;
};

#define GAME_INSTANCE Game::GetInstance()


