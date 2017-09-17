#pragma once
#include "stdafx.h"
#include "Types.h"

class Engine
{
public:
	Engine(int argc, char **argv);
private:
	static void ClearMemory();
	static void InitWindowVariables();
	static void InitStateVariables();
	static void InitGLUT(int argc, char **argv);
	static bool InitDEVil();
	static void InitGL();
	static void InitGameVariables();
	static void BindTexture(GLuint &texture);
	static void LoadGameImages();
	static void DeleteGameImages();
	static void DrawScene();
	static void Resize(int w, int h);
	static void Animate(int value);
	static void MouseControl(int button, int state, int x, int y);
	static void KeyInput(unsigned char key, int x, int y);

	static void DrawImage(float imageX, float imageY, float imageWidth, float imageHeight);
	static void DrawImageWindow(float imageX, float imageY, float imageWidth, float imageHeight);
	static void DisplayMainMenu();
	static void DisplayGame();
	static void DispaySaveWindow();
	static void DisplayLoadWindow();

	static void ParseText(string text);
	static void ParseVariable(string text);
	static void ParseScene(string text);
	static void ParseQuestion(string text);
	static void ParseAnswer(string text);
	static void ParseIfElse(string text);
	static void ParseSpeak(string text);
	static void ReadNextLine();

	static ILuint LoadImage(const char *filename);

	struct ImagesValues {
		int xPos;
		int yPos;
		int scale;
	};
public:
	//GLUT Variables
	int static width;
	int static height;
	int static windowXPosition;
	int static windowYPosition;
	string static windowTitle;

	//Engine Variables
	static STATE state;
	static int linePosition;
	static fstream gameFile;
	static string sceneFile;

	static ILuint ILMenuBackgroundImage;
	static GLuint GLMenuBackgroundImage;
	static ILuint ILNewGameImage;
	static GLuint GLNewGameImage;
	static ILuint ILLoadGameImage;
	static GLuint GLLoadGameImage;
	static ILuint ILQuitGameImage;
	static GLuint GLQuitGameImage;
	static ILuint ILAnswerButtonImage;
	static GLuint GLAnswerButtonImage;
	static ILuint ILTextArea;
	static GLuint GLTextArea;
	static ILuint ILSpeakerArea;
	static GLuint GLSpeakerArea;


	static std::map<string, double> variables;
	static std::map<string, string> imagesFileNames;
	static std::map<string, ILuint> imagesDEVil;
	static std::map<string, GLuint> images;
	static std::map<string, ImagesValues> visibleImages;
	static string inGameBackground;

	static string talkingPerson;
	static string spokenText;
	static string question;
	static string answer1;
	static string answer2;
	static string command1;
	static string command2;
};