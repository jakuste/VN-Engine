#include "stdafx.h"
#include "Engine.h"


// Keyboard input processing routine.
void Engine::KeyInput(unsigned char key, int x, int y)
{
	if (key == '1') SaveGame(1);
	if (key == '2') SaveGame(2);
	if (key == '3') SaveGame(3);
	if (key == 'q') LoadGame(1);
	if (key == 'w') LoadGame(2);
	if (key == 'e') LoadGame(3);
}