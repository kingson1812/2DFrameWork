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

private:
	static void DestroyInstance();
	static Game* s_instance;
};


