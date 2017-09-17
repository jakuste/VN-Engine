#include "stdafx.h"
#include "Engine.h"
#include <ctime>

//Static variables
int Engine::width;
int Engine::height;
int Engine::windowXPosition;
int Engine::windowYPosition;
string Engine::windowTitle;

STATE Engine::state;
int Engine::linePosition;
fstream Engine::gameFile;
string Engine::sceneFile;

ILuint Engine::ILMenuBackgroundImage;
GLuint Engine::GLMenuBackgroundImage;
ILuint Engine::ILNewGameImage;
GLuint Engine::GLNewGameImage;
ILuint Engine::ILLoadGameImage;
GLuint Engine::GLLoadGameImage;
ILuint Engine::ILQuitGameImage;
GLuint Engine::GLQuitGameImage;
ILuint Engine::ILAnswerButtonImage;
GLuint Engine::GLAnswerButtonImage;
ILuint Engine::ILTextArea;
GLuint Engine::GLTextArea;
ILuint Engine::ILSpeakerArea;
GLuint Engine::GLSpeakerArea;

std::map<string, double> Engine::variables;
std::map<string, string> Engine::imagesFileNames;
std::map<string, ILuint> Engine::imagesDEVil;
std::map<string, GLuint> Engine::images;
std::map<string, Engine::ImagesValues> Engine::visibleImages;
string Engine::inGameBackground;

string Engine::talkingPerson;
string Engine::spokenText;
string Engine::question;
string Engine::answer1;
string Engine::answer2;
string Engine::command1;
string Engine::command2;

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