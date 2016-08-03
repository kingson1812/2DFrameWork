#include <AppConfig.h>
#include <GameUtility.h>
#include <stdio.h>

//Set window screen info
int Screen::m_width = 800;
int Screen::m_height = 600;
//End set

int Init(ESFRAME *esFrame)
{
	return 0;
}

void Draw(ESFRAME *esFrame)
{

}

void Update(ESFRAME *esFrame, float deltaTime)
{

}

void KeyAction(ESFRAME *esFrame, unsigned char keycode, bool isPressed)
{
	printf("key %d - %d\n",keycode,isPressed);
}

void TouchActionDown(ESFRAME *esFrame, int x, int y)
{
	printf("clicked at: %d - %d \n",x,y);
}

void TouchActionUp(ESFRAME *esFrame, int x, int y)
{
	printf("released at: %d - %d \n", x, y);
}

void TouchActionMove(ESFRAME *esFrame, int x, int y)
{
	printf("moving to %d - %d\n",x,y);
}

void CleanUp()
{

}

int main(char argv[], int argc)
{
	ESFRAME esFrame;

	InitFrame(&esFrame);

	CreateFrame(&esFrame, Screen::m_width, Screen::m_height, "Micro Magic Quest", ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esFrame) != 0)
		return -1;

	RegisterDrawFnc(&esFrame, Draw);
	RegisterUpdateFnc(&esFrame, Update);
	RegisterKeyFnc(&esFrame, KeyAction);
	RegisterMouseDownFnc(&esFrame, TouchActionDown);
	RegisterMouseUpFnc(&esFrame, TouchActionUp);
	RegisterMouseMoveFunc(&esFrame, TouchActionMove);

	MainLoop(&esFrame);

	//releasing OpenGL resources
	CleanUp();

	//leak detector
	//add visual leak here
	
	//Wait any keys for exit
	getchar();

	return 0;
}