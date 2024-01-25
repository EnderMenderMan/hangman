#include "Game.h"

#include <iostream>
#include <string>
#include <fstream>
//#include <windows.h>

#include <stdio.h>
#include <conio.h>

using namespace std;

void Game::Start() {
	Init();
	Uppdate();
	End();
}
void Game::Init() {
	/*HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);*/
	cout << "Score: " << score;
	cout << "\nGame difficulaty (1-5)\n";
	difficulty = -1;
	betweenStages = 0;
	while (true)
	{
		switch (_getch())
		{
		case '1':
			difficulty = 5;
			break;
		case '2':
			difficulty = 3;
			break;
		case '3':
			difficulty = 2;
			break;
		case '4':
			difficulty = 1;
			break;
		case '5':
			difficulty = 0;
			break;
		default:
			system("CLS");
			cout << "Score: " << score;
			cout << "\nInvalid Input (needs to be 1-5)";
			break;
		}
		if (difficulty != -1)
			break;
	}
	letters = "";
	gameOn = true;
	/*while (true)
	{
		ifstream myfile("WordsFiles.txt");
		string line;
		if (myfile.is_open())
		{
			int i = 0;
			while (getline(myfile, line))
			{
				i++;
				cout << i << ": " << line << '\n';
			}
			myfile.close();
		}
		int fileInt;

		cin >> fileInt;
		if (fileInt == NULL)
		{
			fileInt = 0;
			cout << "Inavild Input";
			cin;
		}
	}*/
	ifstream defWords("DefaultWords.txt");
	if (defWords.is_open())
	{
		srand((unsigned)time(NULL));
		string tempString;
		defWords >> tempString;

		GotoLine(defWords, rand() % stoi(tempString) + 1);
		defWords >> word;

	}
	else
	{
		cout << "defWords is not open";
	}
	hiddenWord = "";
	for (char c : word) {
		hiddenWord += '_';
	}

	stages = 0;
	hangmanPic = ":)";
	Draw();
}
void Game::Uppdate() {
	while (gameOn) {
		PlayerInput();
		Draw();
	}

}
void Game::PlayerInput() {
	char key = _getch();

	bool foundKey = false;
	bool wordFilled = true;
	for (int i = 0; i < word.length();i++) {
		if (word[i] == key)
		{
			hiddenWord[i] = word[i];
			foundKey = true;
		}
		else if (hiddenWord[i] == '_')
		{
			wordFilled = false;
		}
	}
	if (wordFilled)
		gameOn = false;

	if (!foundKey)
	{

		bool contains = false;
		for (char letter : letters) {
			if (letter == key)
				contains = true;
		}
		if (!contains)
		{
			letters += key;
			UppdateStages();
		}
	}
}
void Game::UppdateStages() {
	betweenStages++;
	if (betweenStages > difficulty)
	{
		betweenStages = 0;
		stages++;
	}
	switch (stages)
	{
	case 1:
		hangmanPic = ":O";
		break;
	case 2:
		hangmanPic = ":(";
		break;
	case 3:
		hangmanPic = "x(";
		break;
	case 4:
		hangmanPic = "x(--<";
		break;
	case 5:
		hangmanPic = "x(->-<";
		gameOn = false;
		break;
	default:
		break;
	}
}
void Game::Draw() {
	system("CLS");
	cout << hangmanPic<<"\n";
	cout << hiddenWord << "\n";
	cout << "\n--letters--\n";

	for (char letter : letters) {
		cout << letter << " ";
	}

}
void Game::End() {
	system("CLS");

	if (stages >= 5)
	{
		cout << "Loser\n";
		score -= 10 * (difficulty+1);
	}
	else
	{
		cout << "Winner\n";
		score += 10 * (6 - difficulty);
	}
	cout << "the word was: " << word;
	cout << "\nscore: " << score;
	_getch();
	system("CLS");
	Start();
}
ifstream& Game::GotoLine(ifstream& file, unsigned int num) {
	file.seekg(ios::beg);
	for (int i = 0; i < num - 1; ++i) {
		file.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return file;
}