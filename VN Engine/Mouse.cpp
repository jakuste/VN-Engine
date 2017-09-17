#include "stdafx.h"
#include "Engine.h"

// Mouse callback routine.
void Engine::MouseControl(int button, int button_state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN)
	{
		string text;
		switch (state)
		{
		case MAIN_MENU:
			if (x >= 0.35f*width && x <= 0.65f*width)
			{
				if (y >= 0.275f*height && y <= 0.325f*height)
				{
					state = GAME;
					linePosition = 0;
					gameFile.open(sceneFile, std::ios::in);
					std::getline(gameFile, text);
					ParseText(text);
				}
				else if (y >= 0.425f*height && y <= 0.475f*height)
				{
					state = LOAD_WINDOW;
				}
				else if (y >= 0.575f*height && y <= 0.625f*height)
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
				if (x >= 0.35f*width && x <= 0.65f*width)
				{
					if (y >= 0.275f*height && y <= 0.325f*height)
					{
						ParseText(command1);
						command1.clear();
						command2.clear();
						answer1.clear();
						answer2.clear();
						question.clear();
					}
					else if (y >= 0.425f*height && y <= 0.475f*height)
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