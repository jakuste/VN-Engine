#include "stdafx.h"
#include "Engine.h"

void Engine::BindTexture(GLuint &texture)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Engine::LoadGameImages()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//Wczytaj Menu Background Image
	ILMenuBackgroundImage = LoadImage("data/img/gui/MenuBackgroudImage.jpg");
	BindTexture(GLMenuBackgroundImage);
	//Wczytaj New Game Button Image
	ILNewGameImage = LoadImage("data/img/gui/NewGameImage.png");
	BindTexture(GLNewGameImage);
	//Wczytaj Load Game Button Image
	ILLoadGameImage = LoadImage("data/img/gui/LoadGameImage.png");
	BindTexture(GLLoadGameImage);
	//Wczytaj Quit Game Button Image
	ILQuitGameImage = LoadImage("data/img/gui/QuitGameImage.png");
	BindTexture(GLQuitGameImage);
	//Wczytaj Save/Load Button Image
	ILSavesImage[0] = LoadImage("data/img/gui/EmptySlotImage.png");
	BindTexture(GLSavesImage[0]);
	ILSavesImage[1] = LoadImage("data/img/gui/Save1Image.png");
	BindTexture(GLSavesImage[1]);
	ILSavesImage[2] = LoadImage("data/img/gui/Save2Image.png");
	BindTexture(GLSavesImage[2]);
	ILSavesImage[3] = LoadImage("data/img/gui/Save3Image.png");
	BindTexture(GLSavesImage[3]);
	//Wczytaj Return Button Image
	ILReturnImage = LoadImage("data/img/gui/ReturnImage.png");
	BindTexture(GLReturnImage);
	//Wczytaj Menu Button Image
	ILMenuImage = LoadImage("data/img/gui/MenuImage.png");
	BindTexture(GLMenuImage);
	//Wczytaj Save Game Button Image
	ILSaveGameImage = LoadImage("data/img/gui/SaveGameImage.png");
	BindTexture(GLSaveGameImage);
	//Wczytaj Settings Image
	ILSettingsImage = LoadImage("data/img/gui/SettingsImage.png");
	BindTexture(GLSettingsImage);

	//Wczytaj obrazki w grze
	ILuint tempIL;
	GLuint tempGL;
	for (auto const &entry : imagesFileNames)
	{
		string str = "data/img/textures/" + entry.second;
		tempIL = LoadImage(str.c_str());
		imagesDEVil.insert(std::pair<string, ILuint>(entry.first, tempIL));
		BindTexture(tempGL);
		images.insert(std::pair<string, GLuint>(entry.first, tempGL));
	}
}

void Engine::DeleteGameImages()
{
	ilDeleteImages(1, &ILMenuBackgroundImage);
	glDeleteTextures(1, &GLMenuBackgroundImage);
	ilDeleteImages(1, &ILNewGameImage);
	glDeleteTextures(1, &GLNewGameImage);
	ilDeleteImages(1, &ILLoadGameImage);
	glDeleteTextures(1, &GLLoadGameImage);
	ilDeleteImages(1, &ILQuitGameImage);
	glDeleteTextures(1, &GLQuitGameImage);
	for (int i = 0; i < 4; i++)
	{
		ilDeleteImages(1, &ILSavesImage[i]);
		glDeleteTextures(1, &GLSavesImage[i]);
	}
	ilDeleteImages(1, &ILReturnImage);
	glDeleteTextures(1, &GLReturnImage);
	ilDeleteImages(1, &ILMenuImage);
	glDeleteTextures(1, &GLMenuImage);
	ilDeleteImages(1, &ILSaveGameImage);
	glDeleteTextures(1, &GLSaveGameImage);
	ilDeleteImages(1, &ILSettingsImage);
	glDeleteTextures(1, &GLSettingsImage);


	for (auto const &entry : imagesDEVil)
		ilDeleteImages(1, &entry.second);
	for (auto const &entry : images)
		glDeleteTextures(1, &entry.second);

	images.clear();
	imagesDEVil.clear();
}

ILuint Engine::LoadImage(const char *filename)
{
	ILuint    image;
	ILboolean success;

	ilGenImages(1, &image);
	ilBindImage(image);

	if (success = ilLoadImage(filename))
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (!success) return -1;
	}
	else return -1;

	return image;
}