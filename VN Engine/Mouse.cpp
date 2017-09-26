#include "stdafx.h"
#include "Engine.h"

// Mouse callback routine.
void Engine::MouseControl(int button, int button_state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN)
	{
		string text;
		float tempX = (x - (width - displayWidth) / 2.0) / displayWidth;
		float tempY = (y - (height - displayHeight) / 2.0) / displayHeight;
		switch (state)
		{
		case MAIN_MENU:
			if (tempX >= 0.35f && tempX <= 0.65f)
			{
				if (tempY >= 0.275f && tempY <= 0.325f)
				{
					state = GAME;
					linePosition = 0;
					textPosition = 0;
					gameFile.open(sceneFile, std::ios::in);
					std::getline(gameFile, text);
					ParseText(text);
				}
				else if (tempY >= 0.425f && tempY <= 0.475f)
				{
					state = LOAD_WINDOW;
				}
				else if (tempY >= 0.575f && tempY <= 0.625f)
				{
					exit(0);
				}
			}
			break;
		case GAME:
			//TODO: Dodaæ obs³ugê wejœcia do okna zapisu
			if (question.empty())
				ReadNextLine();
			else
			{
				if (tempY >= 0.87f && tempY <= 0.91f)
				{
					string command = command1;
					command1.clear();
					command2.clear();
					answer1.clear();
					answer2.clear();
					question.clear();
					ParseText(command);
				}
				else if (tempY >= 0.92f && tempY <= 0.96f)
				{
					string command = command2;
					command1.clear();
					command2.clear();
					answer1.clear();
					answer2.clear();
					question.clear();
					ParseText(command);
				}
			}
			break;
		case SAVE_WINDOW:
			//TODO: Dodaæ zapis stanu gry i powrót do poprzedniego stanu (do GAME), stan gry musi zawieraæ wartoœci zmiennych, wyœwietlane postacie i efekty, obecn¹ pozycjê w tekœcie, wybran¹ scenê
			break;
		case LOAD_WINDOW:
			//TODO: Dodaæ wczytywanie stanu gry
			break;
		}
	}


	//TODO: tymczasowe do cofania do menu
	if (button == GLUT_RIGHT_BUTTON && button_state == GLUT_DOWN) {
		state = MAIN_MENU;
		gameFile.close();
		InitStateVariables();
	}
}

// Mouse motion callback
void Engine::MouseMotionControl(int x, int y) 
{
	float tempX = (x - (width - displayWidth) / 2.0) / displayWidth;
	float tempY = (y - (height - displayHeight) / 2.0) / displayHeight;
	switch (state)
	{
	case MAIN_MENU:
		break;
	case GAME:
		answerHover = 0;
		if (tempX >= 0.0f && tempX <= 1.0f)
		{
			if (tempY >= 0.87f && tempY <= 0.91f)
			{
				answerHover = 1;
			}
			else if (tempY >= 0.92f && tempY <= 0.96f)
			{
				answerHover = 2;
			}
		}
		break;
	case SAVE_WINDOW:
		break;
	case LOAD_WINDOW:
		break;
	}
}