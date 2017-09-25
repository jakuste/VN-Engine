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
	static void MouseMotionControl(int x, int y);
	static void KeyInput(unsigned char key, int x, int y);

	static void DrawImage(float imageX, float imageY, float imageWidth, float imageHeight);
	static void DrawImageWindow(float imageX, float imageY, float imageWidth, float imageHeight);
	static void DrawActor(float imageX, float imageY, float imageWidth, float imageHeight, float rot);
	static void DrawActors();
	static void DrawText(float posX, float posY, string text, bool endingFont = false);
	static void DrawTextWindow(float posX, float posY, string text, bool endingFont = false);
	static void DisplayMainMenu();
	static void DisplayGame();
	static void DispaySaveWindow();
	static void DisplayLoadWindow();
	static void DrawTextArea();
	static void DrawSpeakerOrQuestionArea();
	static void DrawButton(int buttonNumber, float buttonX, float buttonY, float buttonWidth, float buttonHeight);
	static void DrawButtonWindow(int buttonNumber, float buttonX, float buttonY, float buttonWidth, float buttonHeight);
	static void DrawEndingPanel();
	static void DrawClosingCredits();

	static void ParseText(string text);
	static void ParseVariable(string text);
	static void ParseScene(string text);
	static void ParseQuestion(string text);
	static void ParseAnswer(string text);
	static void ParseIfElse(string text);
	static void ParseSpeak(string text);
	static void ParseActor(string text);
	static void ReadNextLine();

	static ILuint LoadImage(const char *filename);

	static float NRand();

	static void AnimateParticles();
	static void AddParticleExplosion(float xPos, float yPos);
	static void AddParticleFountain(int position);
	static void DrawParticles();

	struct Actor {
		float xPos = 0.0;		// pozycja x (srodek);
		float yPos = 0.0;		// pozycja y (dol);
		float sizeX = 0.0;		// szerokosc x (na boki od posX)
		float sizeY = 0.0;		// wysokosc y (w gore od posY)
		float scale = 0.0;
		float rot = 0.0;		// aktualny kat obrotu
		float rotSin = 0.0;		// aktualny sinus obrotu (-pi/2 do pi/2)
		float rotSpeed = 0.0f;	// przyrost sinusa na klatke
		float rotAngle = 0.0f;	// maksymalny obrot (stopnie)
		int rotDir = 0;			// 1 = clockwise, -1 = counter clockwise
	};

	struct Particle {
		GLfloat lifetime;					// czas zycia
		GLfloat maximum_lifetime;           // czas smierci
		GLfloat r, g, b;					// skladowe koloru 
		GLfloat xPos, yPos;					// pozycja czastki (x,y)
		GLfloat xspeed, yspeed;				// predkosc czastki
		GLfloat xAcc, yAcc;					// przyspieszenie czastki
		float angle;
	};

	//GLUT Variables
	int static width;
	int static height;
	int static windowXPosition;
	int static windowYPosition;
	string static windowTitle;
	const static int displayWidth;
	const static int displayHeight;

	//Engine Variables
	static STATE state;
	static int linePosition;
	static fstream gameFile;
	static string sceneFile;
	static int victory;
	static float creditsY;

	static ILuint ILMenuBackgroundImage;
	static GLuint GLMenuBackgroundImage;
	static ILuint ILNewGameImage;
	static GLuint GLNewGameImage;
	static ILuint ILLoadGameImage;
	static GLuint GLLoadGameImage;
	static ILuint ILQuitGameImage;
	static GLuint GLQuitGameImage;


	static std::map<string, double> variables;
	static std::map<string, string> imagesFileNames;
	static std::map<string, ILuint> imagesDEVil;
	static std::map<string, GLuint> images;
	static std::map<string, Actor> visibleActors;
	static string inGameBackground;

	static string talkingPerson;
	static string spokenText;
	static string question;
	static string answer1;
	static string answer2;
	static string command1;
	static string command2;
	static int answerHover;

	static std::list<Particle> particlesFountains;
	static std::list<Particle> particlesExplosions;
	static std::list<Particle>::iterator particleIterator;
	static std::list<std::pair<float, float>> explosions;
};