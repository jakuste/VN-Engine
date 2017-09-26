#include "stdafx.h"
#include "Engine.h"

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
			if (victory == 0)
			{
				if (tempX >= 0.95f && tempX <= 1.0f)
				{
					if (tempY >= 0.0f && tempY <= 0.05f)
					{
						openSettings = !openSettings;
					}
				}
				if (openSettings)
				{
					if (tempX >= 0.7f && tempX <= 1.0f)
					{
						if (tempY >= 0.05f && tempY <= 0.10f)
						{
							state = MAIN_MENU;
							gameFile.close();
							InitStateVariables();
						}
						else if (tempY >= 0.10f && tempY <= 0.15f)
						{
							state = SAVE_WINDOW;
						}
					}
				}
			}

			if (state == GAME)
			{
				if (question.empty())
				{
					if (victory != 0) ReadNextLine();
					else
					{
						if (!(tempX >= 0.95f && tempX <= 1.0f && tempY >= 0.0f && tempY <= 0.05f))
						{
							if (!openSettings) ReadNextLine();
							else if (!(tempX >= 0.7f && tempX <= 1.0f && tempY >= 0.05f && tempY <= 0.15f)) ReadNextLine();
						}
					}
				}
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
			}
			break;
		case SAVE_WINDOW:
			if (tempX >= 0.35f && tempX <= 0.65f)
			{
				if (tempY >= 0.275f && tempY <= 0.325f)
				{
					SaveGame(1);
				}
				else if (tempY >= 0.425f && tempY <= 0.475f)
				{
					SaveGame(2);
				}
				else if (tempY >= 0.575f && tempY <= 0.625f)
				{
					SaveGame(3);
				}
				else if (tempY >= 0.725f && tempY <= 0.775f)
				{
					state = GAME;
				}
			}
			break;
		case LOAD_WINDOW:
			if (tempX >= 0.35f && tempX <= 0.65f)
			{
				if (tempY >= 0.275f && tempY <= 0.325f)
				{
					if (ExistSave("1")) LoadGame(1);
				}
				else if (tempY >= 0.425f && tempY <= 0.475f)
				{
					if (ExistSave("2")) LoadGame(2);
				}
				else if (tempY >= 0.575f && tempY <= 0.625f)
				{
					if (ExistSave("3")) LoadGame(3);
				}
				else if (tempY >= 0.725f && tempY <= 0.775f)
				{
					state = MAIN_MENU;
				}
			}
			break;
		}
	}
}

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