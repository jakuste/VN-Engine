#include "stdafx.h"
#include "Engine.h"
#include <ctime>

//Static variables
int Engine::width;
int Engine::height;
int Engine::windowXPosition;
int Engine::windowYPosition;
string Engine::windowTitle;
const int Engine::displayWidth = 800;
const int Engine::displayHeight = 600;

STATE Engine::state;
int Engine::linePosition;
fstream Engine::gameFile;
string Engine::sceneFile;
int Engine::victory;
float Engine::creditsY;

ILuint Engine::ILMenuBackgroundImage;
GLuint Engine::GLMenuBackgroundImage;
ILuint Engine::ILNewGameImage;
GLuint Engine::GLNewGameImage;
ILuint Engine::ILLoadGameImage;
GLuint Engine::GLLoadGameImage;
ILuint Engine::ILQuitGameImage;
GLuint Engine::GLQuitGameImage;

std::map<string, double> Engine::variables;
std::map<string, string> Engine::imagesFileNames;
std::map<string, ILuint> Engine::imagesDEVil;
std::map<string, GLuint> Engine::images;
std::map<string, Engine::Actor> Engine::visibleActors;
string Engine::inGameBackground;

string Engine::talkingPerson;
string Engine::spokenText;
string Engine::question;
string Engine::answer1;
string Engine::answer2;
string Engine::command1;
string Engine::command2;
int Engine::answerHover;

std::list<Engine::Particle> Engine::particlesFountains;
std::list<Engine::Particle> Engine::particlesExplosions;
std::list<Engine::Particle>::iterator Engine::particleIterator;
std::list<std::pair<float, float>> Engine::explosions;

//Functions
Engine::Engine(int argc, char **argv)
{
	srand(time(0));
	atexit(ClearMemory);
	InitWindowVariables();
	InitStateVariables();
	InitGLUT(argc, argv);
	InitGL();
	InitDEVil();
	InitGameVariables();
	LoadGameImages();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutDisplayFunc(&DrawScene);
	glutReshapeFunc(&Resize);
	glutMouseFunc(&MouseControl);
	glutPassiveMotionFunc(&MouseMotionControl);
	glutKeyboardFunc(&KeyInput);
	glutTimerFunc(5, &Animate, 1);
	glutMainLoop();
}

void Engine::ClearMemory()
{
	DeleteGameImages();
	variables.clear();
	imagesFileNames.clear();
	if (gameFile.is_open()) gameFile.close();
}