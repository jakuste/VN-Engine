#include "stdafx.h"
#include "Engine.h"
#include <iostream>

// Drawing (display) routine.
void Engine::DrawScene()
{
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

void Engine::DisplayMainMenu()
{
	glClear(GL_COLOR_BUFFER_BIT);

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

void Engine::DisplayGame()
{
	//TODO: wyœwietlanie gry
	glClear(GL_COLOR_BUFFER_BIT);

	//T³o
	glBindTexture(GL_TEXTURE_2D, images[inGameBackground]);
	DrawImageWindow(0.0f, 0.0f, 1.0f, 1.0f);

	if (!question.empty())
	{
		//TODO: obszar i przyciski maj¹ mieæ tekst

		//Button 1 - answer1
		glBindTexture(GL_TEXTURE_2D, GLAnswerButtonImage);
		DrawImageWindow(0.35f, 0.275f, 0.3f, 0.05f);

		//Button 2 - answer2
		glBindTexture(GL_TEXTURE_2D, GLAnswerButtonImage);
		DrawImageWindow(0.35f, 0.425f, 0.3f, 0.05f);

		//Obszar z tekstem - question
		glBindTexture(GL_TEXTURE_2D, GLTextArea);
		DrawImageWindow(0.0f, 0.85f, 1.0f, 0.15f);
	}
	else
	{
		if (!talkingPerson.empty())
		{
			//Imiê mówi¹cej osoby - talkingPerson
			glBindTexture(GL_TEXTURE_2D, GLSpeakerArea);
			DrawImageWindow(0.0f, 0.8f, 0.3f, 0.05f);
		}

		//Obszar z tekstem - spokenText
		glBindTexture(GL_TEXTURE_2D, GLTextArea);
		DrawImageWindow(0.0f, 0.85f, 1.0f, 0.15f);
	}
}

void Engine::DispaySaveWindow()
{
	//TODO: wyœwietlanie okna zapisu
	glClear(GL_COLOR_BUFFER_BIT);



}

void Engine::DisplayLoadWindow()
{
	//TODO: wyœwietlanie okna wczytywania
	glClear(GL_COLOR_BUFFER_BIT);



}

// OpenGL window reshape routine.
void Engine::Resize(int w, int h)
{
	width = w;
	height = h;
	// Set viewport size to be entire OpenGL window.
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

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

void Engine::Animate(int value) {
	// Note that glutTimerFunc() calls animate() *once* after the 
	// specified msecs. Therefore, to make repeated calls, animate() 
	// must call itself again with glutTimerFunc() as below.
	glutTimerFunc(10, &Animate, 1);
	glutPostRedisplay();
}