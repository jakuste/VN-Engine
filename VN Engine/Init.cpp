#include "stdafx.h"
#include "Engine.h"
#include <fstream>

void Engine::InitWindowVariables()
{
	width = displayWidth;
	height = displayHeight;
	windowXPosition = 100;
	windowYPosition = 100;
	windowTitle = "Game Engine";
}

void Engine::InitStateVariables()
{
	state = MAIN_MENU;
	linePosition = 0;
	sceneFile = "data/scenes/scene01.txt";
	question.clear();
	visibleActors.clear();
	victory = 0;
	creditsY = 1.0f;
}

void Engine::InitGLUT(int argc, char **argv)
{
	// Initialize GLUT.
	glutInit(&argc, argv);

	// Set display mode as single-buffered and RGB color.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Set OpenGL window size.
	glutInitWindowSize(width, height);

	// Set position of OpenGL window upper-left corner.
	glutInitWindowPosition(windowXPosition, windowYPosition);

	// Create OpenGL window with title.
	glutCreateWindow(windowTitle.c_str());

	// Initialize GLEW.
	glewInit();
}

void Engine::InitGL()
{
	glViewport(0, 0, width, height); // use a screen size of WIDTH x HEIGHT
	glEnable(GL_TEXTURE_2D);     // Enable 2D texturing

	glMatrixMode(GL_PROJECTION);     // Make a simple 2D projection on the entire window
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, 0.0, 10.0);

	glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to object modeling

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
}

bool Engine::InitDEVil()
{
	/* Initialization of DevIL */
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		printf("Wrong DevIL version!\n");
		return false;
	}
	ilInit();
	return true;
}

void Engine::InitGameVariables()
{
	fstream file;
	string fileName, variableName;
	//1.Wczytanie z pliku variables.txt nazw zmiennych
	file.open("data/init/variables.txt", std::ios::in);
	while (file >> variableName)
	{
		variables.insert(std::pair<string, double>(variableName, 0.0));
	}
	file.close();
	//2.Wczytanie z pliku images.txt par "nazwa_obrazka nazwa_pliku"
	file.open("data/init/images.txt", std::ios::in);
	while (file >> variableName >> fileName)
	{
		imagesFileNames.insert(std::pair<string, string>(variableName, fileName));
	}
	file.close();
}