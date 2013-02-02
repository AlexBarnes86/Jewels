#ifndef SCORE_IO
#define SCORE_IO

#include "std_lib_facilities.h"

class PlayerScore
{
public:
	PlayerScore():score(0), level(1){}
	PlayerScore(string n, int l, int s): name(n), level(l), score(s){}
	
	int addScore(int nCombos){return score+=nCombos*level;}
	int levelUp(){return ++level;}

	void setName(string n){name = n;}
	string getName() const{return name;}
	int getLevel() const{return level;}
	int getScore() const{return score;}

private:
	string name;
	int level;
	int score;
};

class ScoreIO
{
public:
	ScoreIO();
	vector<PlayerScore> readScores();
	PlayerScore getScore(int idx);
	void writeScore(PlayerScore ps);
	PlayerScore getPlayer(int idx);
	int numScores(){return (int)scores.size();}

private:
	string scoreFile;
	vector<PlayerScore> scores;
};

string readHelpFile(string filename="Help.txt");

#endif