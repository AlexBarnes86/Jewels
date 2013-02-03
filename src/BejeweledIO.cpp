#include "BejeweledIO.h"
#include <stdlib.h>

ScoreIO::ScoreIO()
	: scoreFile("HighScores.txt")	
{
	readScores();
}

vector<PlayerScore> ScoreIO::readScores()
{
	string HighScores = "HighScores.txt";
	ifstream ist(HighScores.c_str());
	if(!ist)
		cout << "High Score File Not Found!" << endl;
	
	string temp;
	string name;
	int score;
	int level;

	while(getline(ist, temp))
	{
		istringstream strInput(temp);
		strInput>>name>>level>>score;
		PlayerScore pscore(name, level, score);
		scores.push_back(pscore);
		cout << "Score pushed back: Name: " << name << ' ' << level << ' ' << score << endl;
	}

	ist.close();
	return scores;
}

void ScoreIO::writeScore(PlayerScore ps)
{
	string HighScores = "HighScores.txt";
	ofstream ost(HighScores.c_str());
	if(!ost)
		cout << "High Score File Not Found!\n" << endl;
	
	bool scoreMadeIt = false;
	for (unsigned int i=0; i<scores.size(); i++)
	{
		int temp = scores[i].getScore();
		if(!scoreMadeIt && ps.getScore()>=temp)
		{
			cout << "Writing: " <<  ps.getName() << " " << ps.getLevel() << " " << ps.getScore() << endl;
			ost << ps.getName() << " " << ps.getLevel() << " " << ps.getScore() << endl;
			scoreMadeIt = true;
		}
		else
		{
			cout << "Writing: " << scores[i].getName() << " " << scores[i].getLevel() << " " << scores[i].getScore() << endl;
			ost << scores[i].getName() << " " << scores[i].getLevel() << " " << scores[i].getScore() << endl;
		}
	}

	ost.close();
}

string readHelpFile(string filename)
{
	ifstream ist(filename.c_str());
	if(!ist)
		return "Help file not found!";
	
	string temp;
	string helpFile;
	while(getline(ist, temp))
	{
		helpFile+=temp+'\n';
	}

	ist.close();
	return helpFile;
}

PlayerScore ScoreIO::getPlayer(int idx)
{
	return scores[idx];
}