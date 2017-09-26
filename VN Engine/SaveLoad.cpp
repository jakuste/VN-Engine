#include "stdafx.h"
#include "Engine.h"

void Engine::SaveGame(int slot)
{
	string filename = "saves/" + std::to_string(slot) +".txt";
	string temp;
	fstream file;
	file.open(filename, std::ios::out);
	file << textPosition << std::endl;
	file << sceneFile << std::endl;
	file << inGameBackground << std::endl;
	for (std::map<string, double>::iterator it = variables.begin(); it != variables.end(); it++)
	{
		file << it->second << std::endl;
	}
	for (std::map<string, Actor>::iterator it = visibleActors.begin(); it != visibleActors.end(); it++)
	{
		Actor values = it->second;
		file << it->first << " " << values.xPos << " " << values.yPos << " " << values.scale << " ";
		file << values.rotSpeed << " " << values.rotAngle << " " << values.rotDir << std::endl;
	}

	file.close();
}

void Engine::LoadGame(int slot)
{
	InitStateVariables();
	string filename = "saves/" + std::to_string(slot) + ".txt";
	string temp, actorName;
	fstream file;
	file.open(filename, std::ios::in);

	state = GAME;
	file >> linePosition;
	textPosition = linePosition;
	file >> sceneFile;
	file >> inGameBackground;
	for (std::map<string, double>::iterator it = variables.begin(); it != variables.end(); it++)
	{
		file >> temp;
		it->second = std::stod(temp);
	}
	while (true)
	{
		if (file >> actorName)
		{
			Actor values;
			int w, h;
			int miplevel = 0;
			glBindTexture(GL_TEXTURE_2D, images[actorName]);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
			values.sizeX = w;
			values.sizeY = h;

			file >> temp;
			values.xPos = std::stod(temp);
			file >> temp;
			values.yPos = std::stod(temp);
			file >> temp;
			values.scale = std::stod(temp);
			file >> temp;
			values.rotSpeed = std::stod(temp);
			file >> temp;
			values.rotAngle = std::stod(temp);
			file >> temp;
			values.rotDir = std::stod(temp);

			visibleActors[actorName] = values;
		}
		else break;
	}

	file.close();

	if (gameFile.is_open()) gameFile.close();
	gameFile.open(sceneFile, std::ios::in);
	for (int i = 0; i <= linePosition; i++)
	{
		std::getline(gameFile, temp);
	}
	ParseText(temp);
}

bool Engine::ExistSave(string slot)
{
	std::ifstream f("saves/" + slot + ".txt");
	return f.good();
}