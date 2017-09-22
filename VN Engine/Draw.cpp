#include "stdafx.h"
#include "Engine.h"
#include <iostream>

void Engine::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	switch (state)
	{
	case MAIN_MENU:
		DisplayMainMenu();
		break;
	case GAME:
		DisplayGame();
		break;
	case SAVE_WINDOW:
		DispaySaveWindow();
		break;
	case LOAD_WINDOW:
		DisplayLoadWindow();
		break;
	}
	glPopMatrix();
	glutSwapBuffers();
}

void Engine::DrawImage(float imageX, float imageY, float imageWidth, float imageHeight)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(imageX, imageY, 0.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(imageX, imageY + imageHeight, 0.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(imageX + imageWidth, imageY + imageHeight, 0.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(imageX + imageWidth, imageY, 0.0f);
	glEnd();
}

void Engine::DrawImageWindow(float imageX, float imageY, float imageWidth, float imageHeight)
{
	DrawImage(imageX*width, imageY*height, imageWidth*width, imageHeight*height);
}

void Engine::DrawActor(float imageX, float imageY, float imageWidth, float imageHeight, float rot)
{
	glPushMatrix();
	glTranslatef(imageX, imageY, 0.0);
	glRotatef(rot, 0.0, 0.0, 1.0);
	glTranslatef(-imageX, -imageY, 0.0);
	DrawImage(imageX - imageWidth / 2.0,
		imageY - imageHeight,
		imageWidth, imageHeight);
	glPopMatrix();
}

void Engine::DrawActors()
{
	for (auto const &mapElement : visibleActors)
	{
		Actor actor = mapElement.second;
		glBindTexture(GL_TEXTURE_2D, images[mapElement.first]);
		DrawActor(actor.xPos, actor.yPos, actor.sizeX * actor.scale, actor.sizeY * actor.scale, actor.rot);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Engine::DrawText(float posX, float posY, string text, bool endingFont) {
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(posX, posY + 0.01 * displayHeight);
	glDisable(GL_TEXTURE_2D);
	if (endingFont)
	{
		for (unsigned int i = 0; i < text.length(); ++i) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text.at(i));
		}
	}
	else
	{
		for (unsigned int i = 0; i < text.length(); ++i) {
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text.at(i));
		}
	}

	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void Engine::DrawTextWindow(float posX, float posY, string text, bool endingFont)
{
	DrawText(posX*width, posY*height, text, endingFont);
}

void Engine::DisplayMainMenu()
{
	//T³o
	glBindTexture(GL_TEXTURE_2D, GLMenuBackgroundImage);
	DrawImageWindow(0.0f, 0.0f, 1.0f, 1.0f);

	//Button 1 (Nowa gra)
	glBindTexture(GL_TEXTURE_2D, GLNewGameImage);
	DrawImageWindow(0.35f, 0.275f, 0.3f, 0.05f);

	//Button 2 (Wczytaj grê)
	glBindTexture(GL_TEXTURE_2D, GLLoadGameImage);
	DrawImageWindow(0.35f, 0.425f, 0.3f, 0.05f);

	//Button 3 (WyjdŸ z gry)
	glBindTexture(GL_TEXTURE_2D, GLQuitGameImage);
	DrawImageWindow(0.35f, 0.575f, 0.3f, 0.05f);
}

void Engine::DrawTextArea()
{
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f*width, 0.78f*height);
	glVertex2f(1.0f*width, 0.78f*height);
	glColor4f(0.0f, 0.0f, 0.0f, 0.9f);
	glVertex2f(1.0f*width, (0.82f)*height);
	glVertex2f(0.0f*width, (0.82f)*height);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f((0.0f)*width, (0.82f)*height);
	glVertex2f((0.0f)*width, (1.0f)*height);
	glVertex2f((1.0f)*width, (1.0f)*height);
	glVertex2f((1.0f)*width, (0.82f)*height);
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void Engine::DrawSpeakerOrQuestionArea()
{
	glLineWidth(2.0);

	glBegin(GL_LINES);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glVertex2f((0.0f)*width, (0.85f)*height);
	glVertex2f((0.5f)*width, (0.85f)*height);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f((0.5f)*width, (0.85f)*height);
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glVertex2f((0.95f)*width, (0.85f)*height);
	glEnd();

	glColor4f(1.0, 1.0, 1.0, 1.0);
}

void Engine::DrawButton(int buttonNumber, float buttonX, float buttonY, float buttonWidth, float buttonHeight)
{
	if (answerHover == buttonNumber) glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	else glColor4f(0.5f, 0.0f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex2f(buttonX, buttonY);
	glVertex2f(buttonX + buttonWidth, buttonY);
	glVertex2f(buttonX + buttonWidth, buttonY + buttonHeight);
	glVertex2f(buttonX, buttonY + buttonHeight);
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void Engine::DrawButtonWindow(int buttonNumber, float buttonX, float buttonY, float buttonWidth, float buttonHeight)
{
	DrawButton(buttonNumber, buttonX*width, buttonY*height, buttonWidth*width, buttonHeight*height);
}

void Engine::DrawEndingPanel()
{
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
	glVertex2f(0.0f, height);
	glVertex2f(width, height);
	glVertex2f(width, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void Engine::DrawClosingCredits()
{
	if(creditsY >= 0.45) DrawTextWindow(0.4f, creditsY, "Tworcy programu:");
	if (creditsY >= 0.35)DrawTextWindow(0.4f, creditsY + 0.1f, "Jakub Steuer");
	if (creditsY >= 0.3) DrawTextWindow(0.4f, creditsY + 0.15f, "Michal A. Wilk");
	if (creditsY >= 0.25)DrawTextWindow(0.4f, creditsY + 0.2f, "Michal Kudela");
}

void Engine::DisplayGame()
{
	//T³o
	glBindTexture(GL_TEXTURE_2D, images[inGameBackground]);
	DrawImageWindow(0.0f, 0.0f, 1.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	DrawActors();

	if (!question.empty())
	{
		//Obszar z tekstem
		DrawTextArea();
		DrawSpeakerOrQuestionArea();
		DrawTextWindow(0.01f, 0.82f, question);

		//Przycisk 1
		DrawButtonWindow(1, 0.0f, 0.87f, 1.0f, 0.04f);
		DrawTextWindow(0.01f, 0.89f, answer1);

		//Przycisk 2
		DrawButtonWindow(2, 0.0f, 0.92f, 1.0f, 0.04f);
		DrawTextWindow(0.01f, 0.94f, answer2);
	}
	else
	{
		//Obszar z tekstem
		DrawTextArea();
		DrawTextWindow(0.01f, 0.89f, spokenText);

		if (!talkingPerson.empty())
		{
			//Imiê mówi¹cej osoby
			DrawSpeakerOrQuestionArea();
			DrawTextWindow(0.01f, 0.82f, talkingPerson);
		}
	}

	if (victory != 0)
	{
		DrawEndingPanel();
		if (victory == 1) DrawTextWindow(0.42f, 0.4f, "Wygrales!", true);
		else DrawTextWindow(0.42f, 0.4f, "Przegrales!", true);

		//TODO: Animacja cz¹steczkowa na ekranie koñca gry, jakieœ wybuchy jak fajerwerki

		DrawClosingCredits();
	}

	glDisable(GL_BLEND);
}

void Engine::DispaySaveWindow()
{
	//TODO: wyœwietlanie okna zapisu



}

void Engine::DisplayLoadWindow()
{
	//TODO: wyœwietlanie okna wczytywania


}

void Engine::Resize(int w, int h)
{
	if (w < displayWidth || h < displayHeight)
	{
		glutReshapeWindow(displayWidth, displayHeight);
	}
	else
	{
		width = w;
		height = h;
		// Set viewport size to be entire OpenGL window.
		glViewport((width - displayWidth) / 2.0, (height - displayHeight) / 2.0, displayWidth, displayHeight);

		// Set matrix mode to projection.
		glMatrixMode(GL_PROJECTION);

		// Clear current projection matrix to identity.
		glLoadIdentity();

		// Specify the orthographic (or perpendicular) projection, 
		// i.e., define the viewing box.
		glOrtho(0.0, w, h, 0.0, 0.0, 10.0);
		//glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 100.0); 

		// Set matrix mode to modelview.
		glMatrixMode(GL_MODELVIEW);

		// Clear current modelview matrix to identity.
		glLoadIdentity();
	}
}

void Engine::Animate(int value) {
	for (auto &mapElement : visibleActors)
	{
		if (mapElement.second.rotDir != 0)
		{
			// Animacja obrotu aktora
			if (abs(mapElement.second.rotSin) >= 1.57f)
			{
				mapElement.second.rotDir *= -1;
			}
			mapElement.second.rotSin += mapElement.second.rotSpeed * mapElement.second.rotDir;
			mapElement.second.rot = sin(mapElement.second.rotSin) * mapElement.second.rotAngle;
		}
	}

	if (victory != 0) creditsY -= 0.001f;

	//TODO: Animacja cz¹steczkowa na ekranie koñca gry, jakieœ wybuchy jak fajerwerki

	glutTimerFunc(10, &Animate, 1);
	glutPostRedisplay();
}