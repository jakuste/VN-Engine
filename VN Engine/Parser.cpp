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
dodaj;x_gdzie;y_gdzie;z_gdzie;skala
usun
przesuñ;x_gdzie;y_gdzie;z_gdzie
skaluj;skala
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
		ParseSpeak(text);
	}
	else if (tag.compare("[^]") == 0)
	{
		//TODO: Obs³uga zmian dla postaci
		ReadNextLine();
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
	linePosition = 0;
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
		std::getline(gameFile, text);
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