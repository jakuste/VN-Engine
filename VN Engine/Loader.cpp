#include "stdafx.h"
#include "Engine.h"

void Engine::BindTexture(GLuint &texture)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA/*ilGetInteger(IL_IMAGE_FORMAT)*/, ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA/*ilGetInteger(IL_IMAGE_FORMAT)*/, GL_UNSIGNED_BYTE, ilGetData());
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Engine::LoadGameImages()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//Load Menu Background Image
	ILMenuBackgroundImage = LoadImage("data/img/gui/MenuBackgroudImage.jpg");
	BindTexture(GLMenuBackgroundImage);
	//Load New Game Button Image
	ILNewGameImage = LoadImage("data/img/gui/NewGameImage.png");
	BindTexture(GLNewGameImage);
	//Load Load Game Button Image
	ILLoadGameImage = LoadImage("data/img/gui/LoadGameImage.png");
	BindTexture(GLLoadGameImage);
	//Load Quit Game Button Image
	ILQuitGameImage = LoadImage("data/img/gui/QuitGameImage.png");
	BindTexture(GLQuitGameImage);

	//Load Game Images
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

	ilGenImages(1, &image);    /* Generation of one image name */
	ilBindImage(image);        /* Binding of image name */


							   /* Loading of the image filename by DevIL */
	if (success = ilLoadImage(filename))
	{
		/* Convert every colour component into unsigned byte */
		/* You can replace IL_RGB with IL_RGBA if your image contains alpha channel */

		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (!success)
		{
			return -1;
		}
	}
	else return -1;

	return image;
}