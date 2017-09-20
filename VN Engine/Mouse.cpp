#include "stdafx.h"
#include "Engine.h"

using namespace std;

// Mouse motion callback
void Engine::MouseMotionControl(int x, int y) {
	float fx = (x - (width / 2.0 - WIDTH_HALF) + (float)x / (width / 2.0 + WIDTH_HALF)) / WIDTH;
	float fy = (y - (height / 2.0 - HEIGHT_HALF) + (float)y / (height / 2.0 + HEIGHT_HALF)) / HEIGHT;
	switch (state)
	{
	case MAIN_MENU:
		break;
	case GAME:
		answerHover = 0;
		if (fx >= 0.0f && fx <= 1.0f)
		{
			if (fy >= 0.87f && fy <= 0.91f)
			{
				answerHover = 1;
			}
			else if (fy >= 0.92f && fy <= 0.96f)
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
// Mouse callback routine.
void Engine::MouseControl(int button, int button_state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN)
	{
		string text;
		// Przelicz piksele na pozycjê w oknie gry
		float fx = (x - (width / 2.0 - WIDTH_HALF) + (float)x / (width / 2.0 + WIDTH_HALF)) / WIDTH;
		float fy = (y - (height / 2.0 - HEIGHT_HALF) + (float)y / (height / 2.0 + HEIGHT_HALF)) / HEIGHT;
		switch (state)
		{
		case MAIN_MENU:
			if (fx >= 0.35f && fx <= 0.65f)
			{
				if (fy >= 0.275f && fy <= 0.325f)
				{
					state = GAME;
					linePosition = 0;
					gameFile.open(sceneFile, std::ios::in);
					std::getline(gameFile, text);
					ParseText(text);
				}
				else if (fy >= 0.425f && fy <= 0.475f)
				{
					state = LOAD_WINDOW;
				}
				else if (fy >= 0.575f && fy <= 0.625f)
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
				//Za³ó¿my, ¿e s¹ 2 guziki wyœwietlone (todo w draw)
				if (fx >= 0.0f && fx <= 1.0f)
				{
					if (fy >= 0.87f && fy <= 0.91f)
					{
						ParseText(command1);
						command1.clear();
						command2.clear();
						answer1.clear();
						answer2.clear();
						question.clear();
					}
					else if (fy >= 0.92f && fy <= 0.96f)
					{
						ParseText(command2);
						command1.clear();
						command2.clear();
						answer1.clear();
						answer2.clear();
						question.clear();
					}
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