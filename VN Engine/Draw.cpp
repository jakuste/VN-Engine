#include "stdafx.h"
#include "Engine.h"
#include <iostream>
#define FONT_CENTER 0.01 // offset font to draw in the middle of posY instead of above

// Drawing (display) routine.
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
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(imageX, imageY, 0.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(imageX, imageY + imageHeight, 0.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(imageX + imageWidth, imageY + imageHeight, 0.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(imageX + imageWidth, imageY, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void Engine::DrawText(float posX, float posY, string text) {
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(posX, posY + FONT_CENTER);
	glDisable(GL_TEXTURE_2D);
	for (int i = 0; i < text.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text.at(i));
	}
	glPopMatrix();
}

void Engine::DisplayMainMenu()
{
	//T³o
	glBindTexture(GL_TEXTURE_2D, GLMenuBackgroundImage);
	DrawImage(0.0f, 0.0f, 1.0f, 1.0f);

	//Button 1 (Nowa gra)
	glBindTexture(GL_TEXTURE_2D, GLNewGameImage);
	DrawImage(0.35f, 0.275f, 0.3f, 0.05f);

	//Button 2 (Wczytaj grê)
	glBindTexture(GL_TEXTURE_2D, GLLoadGameImage);
	DrawImage(0.35f, 0.425f, 0.3f, 0.05f);

	//Button 3 (WyjdŸ z gry)
	glBindTexture(GL_TEXTURE_2D, GLQuitGameImage);
	DrawImage(0.35f, 0.575f, 0.3f, 0.05f);
}

void Engine::DisplayGame()
{
	//TODO: wyœwietlanie gry

	//T³o
	glBindTexture(GL_TEXTURE_2D, images[inGameBackground]);
	DrawImage(0.0f, 0.0f, 1.0f, 1.0f);

	//Aktor
	

	// Rysowanie aktora
	if (actor.visible) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();
		glTranslatef(actor.posX, actor.posY, 0.0);
		glRotatef(actor.rot, 0.0, 0.0, 1.0);
		glTranslatef(-actor.posX, -actor.posY, 0.0);
		glBindTexture(GL_TEXTURE_2D, images[actor.image]);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		DrawImage(actor.posX - (actor.sizeX / 2.0),
			actor.posY - actor.sizeY,
			actor.sizeX, actor.sizeY);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glPopMatrix();
		glDisable(GL_BLEND);
	}
	
	if (!question.empty())
	{
		//TODO: obszar i przyciski maj¹ mieæ tekst
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
		glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(0.0f, 0.78f);
		glVertex2f(1.0f, 0.78f);
		glColor4f(0.0f, 0.0f, 0.0f, 0.9f);
		glVertex2f(1.0f, (0.82f));
		glVertex2f(0.0f, (0.82f));
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f((0.0f), (0.82f));
		glVertex2f((0.0f), (1.0f));
		glVertex2f((1.0f), (1.0f));
		glVertex2f((1.0f), (0.82f));
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glLineWidth(2.0);
		glBegin(GL_LINES);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex2f((0.0f), (0.85f));
		glVertex2f((0.5f), (0.85f));
		glEnd();
		glBegin(GL_LINES);
		glVertex2f((0.5f), (0.85f));
		glColor4f(1.0, 1.0, 1.0, 0.0);
		glVertex2f((0.95f), (0.85f));
		glEnd();
		DrawText(0.01f, 0.82f, question);
		//Button 1 - answer1
		if (answerHover == 1) {
			glBegin(GL_QUADS);
			glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
			glVertex2f(0.0f, 0.87f);
			glVertex2f(1.0f, 0.87f);
			glVertex2f(1.0f, 0.91f);
			glVertex2f(0.0f, 0.91f);
			glEnd();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
		DrawText(0.01f, 0.89f, answer1);
		//Button 2 - answer2
		if (answerHover == 2) {
			glBegin(GL_QUADS);
			glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
			glVertex2f(0.0f, 0.92f);
			glVertex2f(1.0f, 0.92f);
			glVertex2f(1.0f, 0.96f);
			glVertex2f(0.0f, 0.96f);
			glEnd();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	
		}
		glDisable(GL_BLEND);
		DrawText(0.01f, 0.94f, answer2);
	}
	else
	{
		//Obszar z tekstem - spokenText
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
			glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
			glVertex2f(0.0f, 0.78f);
			glVertex2f(1.0f, 0.78f);
			glColor4f(0.0f, 0.0f, 0.0f, 0.9f);
			glVertex2f(1.0f, (0.82f));
			glVertex2f(0.0f, (0.82f));	
		glEnd();
		glBegin(GL_QUADS);
			glVertex2f((0.0f), (0.82f));
			glVertex2f((0.0f), (1.0f));
			glVertex2f((1.0f), (1.0f));
			glVertex2f((1.0f), (0.82f));
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glDisable(GL_BLEND);
		DrawText(0.01f, 0.89f, spokenText);

		if (!talkingPerson.empty())
		{
			//Imiê mówi¹cej osoby - talkingPerson
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glVertex2f((0.0f), (0.85f));
				glVertex2f((0.5f), (0.85f));
			glEnd();
			glBegin(GL_LINES);
				glVertex2f((0.5f), (0.85f));
				glColor4f(1.0, 1.0, 1.0, 0.0);
				glVertex2f((0.95f), (0.85f));
			glEnd();
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glDisable(GL_BLEND);
			DrawText(0.01f, 0.82f, talkingPerson);
		}
	}
}

void Engine::DispaySaveWindow()
{
	//TODO: wyœwietlanie okna zapisu
	



}

void Engine::DisplayLoadWindow()
{
	//TODO: wyœwietlanie okna wczytywania



}

// OpenGL window reshape routine.
void Engine::Resize(int w, int h)
{
	width = w;
	height = h;
	// Set viewport size to be entire OpenGL window.
	glViewport((width/2.0)-WIDTH_HALF, (height / 2.0) - HEIGHT_HALF, WIDTH, HEIGHT);

	// Set matrix mode to projection.
	glMatrixMode(GL_PROJECTION);

	// Clear current projection matrix to identity.
	glLoadIdentity();

	// Specify the orthographic (or perpendicular) projection, 
	// i.e., define the viewing box.
	glOrtho(0.0, 1.0, 1.0, 0.0, 0.0, 10.0);
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

	// Animacja obrotu aktora
	if (abs(actor.rotSin) >= 1.57f) {
		actor.rotDir *= -1;
	}
	actor.rotSin += actor.rotSpeed * actor.rotDir;
	actor.rot = sin(actor.rotSin) * actor.rotAngle;
	//
	glutTimerFunc(10, &Animate, 1);
	glutPostRedisplay();
}