#ifndef BejeweledWindow_h
#define BejeweledWindow_h
#include "std_lib_facilities.h"
#include "GameBoard.h"
#include "BejeweledIO.h"
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_GIF_Image.H>

extern vector<Fl_GIF_Image*> imageVector;
void initImages(String imgPath);

class BejeweledWindow 
{
public:
	BejeweledWindow();
	~BejeweledWindow();

	void showScores();
	void showHelp();
	void showAbout();
	void newGame();
	void levelUp();
	void addScore(int s);
	PlayerScore getPlayer() const {return playerScore;}

	void updateScore();

	GameBoard* gameBoard;
	bool gameOver;

private:

	PlayerScore playerScore;

	Fl_Double_Window *mainWindow;
	Fl_Menu_Bar *menuBar;
	Fl_Box *scoreLabel;
	Fl_Box *levelLabel;
	Fl_Button *highScoreButton;
	Fl_Button *pauseButton;
	Fl_Box *scoreBox;
	Fl_Box *levelBox;
	Fl_Progress *progressBar;

	void updateLabel(Fl_Box* widget, string str);

	static Fl_Menu_Item menu_menuBar[];
	static Fl_Menu_Item *menuItemGame;
	static Fl_Menu_Item *menuItemNew;
	static Fl_Menu_Item *menuItemPause;
	static Fl_Menu_Item *menuItemExit;
	static Fl_Menu_Item *menuItemHelp;
	static Fl_Menu_Item *menuItemRules;
	static Fl_Menu_Item *menuItemAbout;
	static Fl_Menu_Item *menuItemHScores;
	
	void cb_menuItemExit_i(Fl_Menu_*, void*);
	void cb_menuItemRules_i(Fl_Menu_*, void*);
	void cb_menuItemAbout_i(Fl_Menu_*, void*);
	void cb_menuItemHScores_i(Fl_Menu_*, void*);
	void cb_highScoreButton_i(Fl_Button*, void*);
	void cb_menuItemNew_i(Fl_Menu_*, void*);

	static void cb_menuItemRules(Fl_Menu_*, void*);
	static void cb_menuItemExit(Fl_Menu_*, void*);
	static void cb_menuItemAbout(Fl_Menu_*, void*);
	static void cb_menuItemHScores(Fl_Menu_*, void*);
	static void cb_highScoreButton(Fl_Button*, void*);
	static void cb_menuItemNew(Fl_Menu_*, void*);
};

class AboutWindow 
{
public:
	AboutWindow();
protected:
	Fl_Double_Window *aboutWindow;
};

class LoseGameWindow : AboutWindow
{
public:
	LoseGameWindow();
};

class HelpWindow 
{
public:
	HelpWindow();
private:
	Fl_Double_Window *helpWindow;
};

class ScoresWindow 
{
public:
	ScoresWindow();
	ScoresWindow(PlayerScore ps);
	void writeScore(PlayerScore ps);
private:
	ScoreIO scoreIO;
	Fl_Double_Window *highScoreWindow;
};


class UserWindow 
{
public:
	UserWindow();
private:
	Fl_Double_Window *userName;
};

#endif
