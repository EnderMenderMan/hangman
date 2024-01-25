#pragma once

#include <string>
using namespace std;
class Game
{
public:
	void Start();
private:
	void Init();
	void Uppdate();
	void PlayerInput();
	void UppdateStages();
	void Draw();
	void End();
	ifstream& GotoLine(ifstream& file, unsigned int num);
	std::string word;
	std::string hiddenWord;
	std::string hangmanPic;
	std::string letters;
	int stages;
	int betweenStages;
	int difficulty;
	int score = 0;
	bool gameOn;
};

