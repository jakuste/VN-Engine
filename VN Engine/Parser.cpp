#include "stdafx.h"
#include "Engine.h"

/*
Ustawienie wartoœci zmiennej:
	[$]nazwa_zmiennej=wartosc
Zmiana wartoœci zmiennej:
	[$]nazwa_zmiennej+wartosc
	[$]nazwa_zmiennej-wartosc
	[$]nazwa_zmiennej/wartosc
	[$]nazwa_zmiennej*wartosc
Obrazek t³a:
	[@]nazwa_obrazka
Przejœcie innej sceny:
	[>]nazwa_sceny
Pytanie:
	[?]tekst_pytania;odpowiedŸ_1;odpowiedŸ_2
	[+]wykonaj_jeœli_odpowiedŸ_1; (mo¿na [$] albo [>])
	[-]wykonaj_jeœli_odpowiedŸ_2; (mo¿na [$] albo [>])
If/Else:
	[!]nazwa_zmiennej>wartoœæ;nazwa_sceny_dla_true;nazwa_sceny_dla_false
	[!]nazwa_zmiennej=wartoœæ;nazwa_sceny_dla_true;nazwa_sceny_dla_false
Tekst:
	[#]kto_mówi;co_mówi
Postaæ:
	[^]nazwa_postaci;co_zrobic
	co_zrobic:
		dodaj:
			[D];x_gdzie;y_gdzie;skala
		usun:
			[U]
		przesuñ:
			[P];x_gdzie;y_gdzie
		skaluj:
			[S];skala
		obracaj:
			[O];kierunek(-1,0 lub 1);przyrost_sinusa_na_klatke;maksymalny_kat_w_stopniach_po_ktorym_zmiana_kierunku
		ustaw_kat:
			[K];kat_w_sinusach(od -pi/2 do pi/2)
Wygrana:
	[*]
Przegrana:
	[&]
*/

void Engine::ParseText(string text)
{
	string tag = text.substr(0, 3);
	text = text.substr(3);
	if (tag.compare("[$]") == 0)
	{
		ParseVariable(text);
		ReadNextLine();
	}
	else if (tag.compare("[@]") == 0)
	{
		inGameBackground = text;
		ReadNextLine();
	}
	else if (tag.compare("[>]") == 0)
	{
		ParseScene(text);
		ReadNextLine();
	}
	else if (tag.compare("[?]") == 0)
	{
		textPosition = linePosition;
		ParseQuestion(text);
	}
	else if (tag.compare("[+]") == 0)
	{
		linePosition += 2;
		ParseAnswer(text);
		ReadNextLine();
	}
	else if (tag.compare("[-]") == 0)
	{
		linePosition += 2;
		ParseAnswer(text);
		ReadNextLine();
	}
	else if (tag.compare("[!]") == 0)
	{
		ParseIfElse(text);
		ReadNextLine();
	}
	else if (tag.compare("[#]") == 0)
	{
		textPosition = linePosition;
		ParseSpeak(text);
	}
	else if (tag.compare("[^]") == 0)
	{
		ParseActor(text);
		ReadNextLine();
	}
	else if (tag.compare("[*]") == 0)
	{
		victory = 1;
	}
	else if (tag.compare("[&]") == 0)
	{
		victory = -1;
	}
}

void Engine::ParseVariable(string text)
{
	string variableName;
	double value;
	int pos, type;
	pos = text.find('=');
	if (pos != std::string::npos) type = 0;
	else {
		pos = text.find('+');
		if (pos != std::string::npos) type = 1;
		else {
			pos = text.find('-');
			if (pos != std::string::npos) type = 2;
			else {
				pos = text.find('*');
				if (pos != std::string::npos) type = 3;
				else {
					pos = text.find('/');
					type = 4;
				}
			}
		}
	}
	variableName = text.substr(0, pos);
	string valueString = text.substr(pos + 1);
	value = std::stod(valueString);
	switch (type)
	{
	case 0:
		variables[variableName] = value;
		break;
	case 1:
		variables[variableName] += value;
		break;
	case 2:
		variables[variableName] -= value;
		break;
	case 3:
		variables[variableName] *= value;
		break;
	case 4:
		variables[variableName] /= value;
		break;
	}
}

void Engine::ParseScene(string text)
{
	gameFile.close();
	sceneFile = "data/scenes/" + text;
	gameFile.open(sceneFile, std::ios::in);
	linePosition = -1;
}

void Engine::ParseQuestion(string text)
{
	int pos = text.find(';');
	question = text.substr(0, pos);
	text = text.substr(pos + 1);
	pos = text.find(';');
	answer1 = text.substr(0, pos);
	answer2 = text.substr(pos + 1);
	std::getline(gameFile, command1);
	std::getline(gameFile, command2);
}

void Engine::ParseAnswer(string text)
{
	string tag = text.substr(0, 3);
	text = text.substr(3);
	if (tag.compare("[$]") == 0)
	{
		ParseVariable(text);
	}
	else if (tag.compare("[>]") == 0)
	{
		ParseScene(text);
	}
}

void Engine::ParseIfElse(string text)
{
	int pos, type;
	pos = text.find('=');
	if (pos != std::string::npos) type = 0;
	else {
		pos = text.find('>');
		type = 1;
	}
	string variableName = text.substr(0, pos);
	text = text.substr(pos + 1);
	pos = text.find(';');
	string valueString = text.substr(0, pos);
	double value = std::stod(valueString);
	text = text.substr(pos + 1);
	pos = text.find(';');
	string scene1 = text.substr(0, pos);
	string scene2 = text.substr(pos + 1);
	if (type == 0)
	{
		if (variables[variableName] == value) ParseScene(scene1);
		else ParseScene(scene2);
	}
	else
	{
		if (variables[variableName] > value) ParseScene(scene1);
		else ParseScene(scene2);
	}
}

void Engine::ParseSpeak(string text)
{
	int pos = text.find(';');
	talkingPerson = text.substr(0, pos);
	spokenText = text.substr(pos + 1);
}

void Engine::ParseActor(string text)
{
	int pos = text.find(';');
	string actor = text.substr(0, pos);
	text = text.substr(pos + 1);
	string tag = text.substr(0, 3);

	if (tag.compare("[D]") == 0)
	{
		text = text.substr(4);
		Actor values;
		int w, h;
		int miplevel = 0;
		glBindTexture(GL_TEXTURE_2D, images[actor]);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
		values.sizeX = w;
		values.sizeY = h;

		pos = text.find(';');
		string valueString = text.substr(0, pos);
		values.xPos = std::stod(valueString);

		text = text.substr(pos + 1);
		pos = text.find(';');
		valueString = text.substr(0, pos);
		values.yPos = std::stod(valueString);

		text = text.substr(pos + 1);
		values.scale = std::stod(text);

		visibleActors.insert(std::pair<string, Actor>(actor, values));
	}
	else if (tag.compare("[U]") == 0)
	{
		visibleActors.erase(actor);
	}
	else if (tag.compare("[P]") == 0)
	{
		text = text.substr(4);
		pos = text.find(';');
		string valueString = text.substr(0, pos);
		visibleActors[actor].xPos = std::stod(valueString);

		text = text.substr(pos + 1);
		visibleActors[actor].yPos = std::stod(text);
	}
	else if (tag.compare("[S]") == 0)
	{
		text = text.substr(4);
		visibleActors[actor].scale = std::stod(text);
	}
	else if (tag.compare("[O]") == 0)
	{
		text = text.substr(4);
		pos = text.find(';');
		string valueString = text.substr(0, pos);
		visibleActors[actor].rotDir = std::stoi(valueString);

		text = text.substr(pos + 1);
		pos = text.find(';');
		valueString = text.substr(0, pos);
		visibleActors[actor].rotSpeed = std::stod(valueString);

		text = text.substr(pos + 1);
		visibleActors[actor].rotAngle = std::stod(text);
	}
	else if (tag.compare("[K]") == 0)
	{
		text = text.substr(4);
		visibleActors[actor].rotSin = std::stod(text);
		visibleActors[actor].rot = sin(visibleActors[actor].rotSin) * visibleActors[actor].rotAngle;
	}
}

void Engine::ReadNextLine()
{
	if (!gameFile.eof())
	{
		linePosition++;
		string text;
		std::getline(gameFile, text);
		ParseText(text);
	}
	else
	{
		gameFile.close();
		InitStateVariables();
	}
}