#include "BejeweledWindow.h"
#include "../BejeweledIO.h"
#include "Fl/fl_ask.h"
#include <iostream>
#include <string.h>

vector<Fl_GIF_Image*> imageVector;

void initImages(String imgPath)
{
	imageVector.push_back(new Fl_GIF_Image((imgPath+"Score.gif").c_str()));
	imageVector.push_back(new Fl_GIF_Image((imgPath+"Level.gif").c_str()));
	imageVector.push_back(new Fl_GIF_Image((imgPath+"High Scores.gif").c_str()));
	imageVector.push_back(new Fl_GIF_Image((imgPath+"Pause.gif").c_str()));

	imageVector.push_back(new Fl_GIF_Image((imgPath+"Blue.gif").c_str()));
	imageVector.push_back(new Fl_GIF_Image((imgPath+"Green.gif").c_str()));
	imageVector.push_back(new Fl_GIF_Image((imgPath+"Yellow.gif").c_str()));
	imageVector.push_back(new Fl_GIF_Image((imgPath+"Orange.gif").c_str()));
	imageVector.push_back(new Fl_GIF_Image((imgPath+"Red.gif").c_str()));
	imageVector.push_back(new Fl_GIF_Image((imgPath+"White.gif").c_str()));
	imageVector.push_back(new Fl_GIF_Image((imgPath+"Purple.gif").c_str()));
	imageVector.push_back(new Fl_GIF_Image((imgPath+"Explosion.gif").c_str()));
}

void BejeweledWindow::cb_menuItemNew_i(Fl_Menu_*, void*)
{
	newGame();
}

void BejeweledWindow::cb_menuItemNew(Fl_Menu_* o, void* v)
{
	((BejeweledWindow*)(o->parent()->user_data()))->cb_menuItemNew_i(o,v);
}

void BejeweledWindow::cb_menuItemExit_i(Fl_Menu_*, void*)
{
	mainWindow->hide();
}

void BejeweledWindow::cb_menuItemExit(Fl_Menu_* o, void* v)
{
	((BejeweledWindow*)(o->parent()->user_data()))->cb_menuItemExit_i(o,v);
}

void BejeweledWindow::cb_menuItemRules_i(Fl_Menu_*, void*)
{
	showHelp();
}
void BejeweledWindow::cb_menuItemRules(Fl_Menu_* o, void* v) 
{
	((BejeweledWindow*)(o->parent()->user_data()))->cb_menuItemRules_i(o,v);
}

void BejeweledWindow::cb_menuItemAbout_i(Fl_Menu_*, void*)
{
	showAbout();
}

void BejeweledWindow::cb_menuItemAbout(Fl_Menu_* o, void* v)
{
	((BejeweledWindow*)(o->parent()->user_data()))->cb_menuItemAbout_i(o,v);
}

void BejeweledWindow::cb_menuItemHScores_i(Fl_Menu_*, void*)
{
	showScores();
}

void BejeweledWindow::cb_menuItemHScores(Fl_Menu_* o, void* v) 
{
	((BejeweledWindow*)(o->parent()->user_data()))->cb_menuItemHScores_i(o,v);
}

Fl_Menu_Item BejeweledWindow::menu_menuBar[] = {
	{"&Game", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 2},
	{"&New", 0,  (Fl_Callback*)BejeweledWindow::cb_menuItemNew, 0, 0, FL_NORMAL_LABEL, 0, 14, 2},
	{"&Pause", 0,  0, 0, 1, FL_NORMAL_LABEL, 0, 14, 2},
	{"E&xit", 0,  (Fl_Callback*)BejeweledWindow::cb_menuItemExit, 0, 0, FL_NORMAL_LABEL, 0, 14, 2},
	{0,0,0,0,0,0,0,0,0},
	{"&Help", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 2},
	{"Game Rules", 0,  (Fl_Callback*)BejeweledWindow::cb_menuItemRules, 0, 0, FL_NORMAL_LABEL, 0, 14, 63},
	{"&About", 0,  (Fl_Callback*)BejeweledWindow::cb_menuItemAbout, 0, 0, FL_NORMAL_LABEL, 0, 14, 2},
	{"High Scores", 0,  (Fl_Callback*)BejeweledWindow::cb_menuItemHScores, 0, 0, FL_NORMAL_LABEL, 0, 14, 2},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0}
};

Fl_Menu_Item* BejeweledWindow::menuItemGame = BejeweledWindow::menu_menuBar + 0;
Fl_Menu_Item* BejeweledWindow::menuItemNew = BejeweledWindow::menu_menuBar + 1;
Fl_Menu_Item* BejeweledWindow::menuItemPause = BejeweledWindow::menu_menuBar + 2;
Fl_Menu_Item* BejeweledWindow::menuItemExit = BejeweledWindow::menu_menuBar + 3;
Fl_Menu_Item* BejeweledWindow::menuItemHelp = BejeweledWindow::menu_menuBar + 5;
Fl_Menu_Item* BejeweledWindow::menuItemRules = BejeweledWindow::menu_menuBar + 6;
Fl_Menu_Item* BejeweledWindow::menuItemAbout = BejeweledWindow::menu_menuBar + 7;
Fl_Menu_Item* BejeweledWindow::menuItemHScores = BejeweledWindow::menu_menuBar + 8;

void BejeweledWindow::cb_highScoreButton_i(Fl_Button*, void*) 
{
	showScores();
}

void BejeweledWindow::cb_highScoreButton(Fl_Button* o, void* v)
{
	((BejeweledWindow*)(o->parent()->user_data()))->cb_highScoreButton_i(o,v);
}

BejeweledWindow::BejeweledWindow() 
	:gameOver(false)
{
	mainWindow = new Fl_Double_Window(600, 480, "Bejeweled");
    mainWindow->color(FL_FOREGROUND_COLOR);
    mainWindow->user_data((void*)(this));
    
	menuBar = new Fl_Menu_Bar(0, 0, 600, 25, "Game Rules");
    menuBar->color(FL_FOREGROUND_COLOR);
    menuBar->labelcolor(FL_GREEN);
    menuBar->menu(menu_menuBar);

    scoreLabel = new Fl_Box(25, 65, 150, 40);
    levelLabel = new Fl_Box(20, 193, 155, 37);

	highScoreButton = new Fl_Button(10, 330, 175, 45);
    highScoreButton->color(FL_GRAY0);
    highScoreButton->selection_color(FL_FOREGROUND_COLOR);
    highScoreButton->callback((Fl_Callback*)cb_highScoreButton);

    pauseButton = new Fl_Button(10, 385, 175, 50);
    pauseButton->color(FL_FOREGROUND_COLOR);

    progressBar = new Fl_Progress(190, 442, 400, 30);
    progressBar->box(FL_PLASTIC_UP_BOX);
    progressBar->color(FL_GRAY0);
    progressBar->selection_color((Fl_Color)6);

	scoreBox = new Fl_Box(5, 120, 180, 55);
	updateLabel(scoreBox, "0");
    scoreBox->box(FL_PLASTIC_DOWN_FRAME);
    scoreBox->color((Fl_Color)41);
    scoreBox->labelfont(1);
    scoreBox->labelsize(51);
    scoreBox->labelcolor(FL_GREEN);

    levelBox = new Fl_Box(70, 250, 45, 60, "1");
    levelBox->box(FL_PLASTIC_DOWN_FRAME);
    levelBox->color((Fl_Color)41);
    levelBox->labelfont(1);
    levelBox->labelsize(50);
    levelBox->labelcolor(FL_GREEN);

    mainWindow->size_range(600, 480, 600, 480);
    mainWindow->end();

	scoreLabel->image(imageVector[0]);
	levelLabel->image(imageVector[1]);
	highScoreButton->image(imageVector[2]);
	pauseButton->image(imageVector[3]);

	gameBoard = new GameBoard(*mainWindow);
	mainWindow->show();
}

void BejeweledWindow::showScores() 
{
	ScoresWindow sw;
}

void BejeweledWindow::showHelp() 
{
	HelpWindow hw;
}

void BejeweledWindow::showAbout() 
{
	AboutWindow aw;
}

void BejeweledWindow::newGame() 
{
	//UserWindow();
	if(gameBoard)
	{
		for(int r = 0; r < gameBoard->GAME_ROWS; r++)
			for(int c = 0; c < gameBoard->GAME_COLS; c++)
				mainWindow->remove(gameBoard->getTile(r, c));
		delete gameBoard;
	}
	gameBoard = new GameBoard(*mainWindow);
	gameBoard->update();
	playerScore = PlayerScore();
	updateScore();
	gameOver = false;
}

UserWindow::UserWindow()
{
	userName = new Fl_Double_Window(200, 150, "UserName");
	userName->color(FL_FOREGROUND_COLOR);
	userName->user_data((void*)(this));

	Fl_Input *input = new Fl_Input(10,10,100,50,"User Name: ");
	//userName->set_output();

	userName->end();
	userName->show();
}

BejeweledWindow::~BejeweledWindow() 
{
	if(gameBoard)
		delete gameBoard;

	for(unsigned int i = 0; i < imageVector.size(); i++)
		if(imageVector[i] != 0)
			delete imageVector[i];
}

AboutWindow::AboutWindow()
{
	aboutWindow = new Fl_Double_Window(290, 170, "About");
    aboutWindow->color(FL_FOREGROUND_COLOR);
    aboutWindow->user_data((void*)(this));

	{ 
		Fl_Box* o = new Fl_Box(45, 59, 85, 20, "Created By:");
		o->color(FL_GREEN);
		o->labelcolor(FL_GREEN);
		o->align(133|FL_ALIGN_INSIDE);
	}{ 
		Fl_Box* o = new Fl_Box(124, 59, 159, 20, "Shanna Andrews");
		o->color(FL_GREEN);
		o->labelcolor(FL_GREEN);
	}{ 
		Fl_Box* o = new Fl_Box(124, 79, 159, 20, "Alex Barnes");
		o->color(FL_GREEN);
		o->labelcolor(FL_GREEN);
    }{ 
		Fl_Box* o = new Fl_Box(124, 99, 159, 20, "Dhivya Padmanabhan");
		o->color(FL_GREEN);
		o->labelcolor(FL_GREEN);
    }{ 
		Fl_Box* o = new Fl_Box(28, 134, 105, 20, "ENGR 112-205");
		o->color(FL_GREEN);
		o->labelcolor(FL_GREEN);
    }{ 
		Fl_Box* o = new Fl_Box(158, 134, 110, 20, "April 2006");
		o->color(FL_GREEN);
		o->labelcolor(FL_GREEN);
    }{ 
		Fl_Box* o = new Fl_Box(68, 11, 175, 40, "Bejeweled");
		o->box(FL_UP_FRAME);
		o->color(FL_GREEN);
		o->labelfont(1);
		o->labelsize(30);
		o->labelcolor(FL_GREEN);
    }

	aboutWindow->end();
	aboutWindow->show();
}

LoseGameWindow::LoseGameWindow()
{
	aboutWindow->resize(aboutWindow->x(), aboutWindow->y(), aboutWindow->w(), aboutWindow->h()+50);
	Fl_Box* o = new Fl_Box(68, aboutWindow->h()-45, 175, 40, "You Lose!");
	o->box(FL_UP_FRAME);
	o->color(FL_GREEN);
	o->labelfont(1);
	o->labelsize(30);
	o->labelcolor(FL_RED);
	aboutWindow->add(o);
	aboutWindow->end();
	aboutWindow->show();
}

HelpWindow::HelpWindow() 
{
	helpWindow = new Fl_Double_Window(400, 300, "Rules and Controls");
	helpWindow->color(FL_FOREGROUND_COLOR);
	helpWindow->user_data((void*)(this));
	
	Fl_Multiline_Output *textDisplayHelp = new Fl_Multiline_Output(0, 0, 400, 300);
	textDisplayHelp->box(FL_BORDER_BOX);
	textDisplayHelp->color(FL_WHITE);
	textDisplayHelp->labelcolor((Fl_Color)5);
	textDisplayHelp->value(readHelpFile().c_str());//from BejeweledIO
	textDisplayHelp->set_output();

	helpWindow->end();
	helpWindow->show();
}

ScoresWindow::ScoresWindow()
{
	highScoreWindow = new Fl_Double_Window(300, 400, "HighScores");
	highScoreWindow->color(FL_GRAY0);
	highScoreWindow->user_data((void*)(this));
	highScoreWindow->align(FL_ALIGN_CENTER);

	ostringstream oss;
	oss<<"\n\n\nPlace\tScore\n\n";

	for(int i = 0; i < scoreIO.numScores(); i++)
	{
		PlayerScore tPlayer = scoreIO.getPlayer(i);
		oss<<i+1<<":\t"<<tPlayer.getName()<<"\t"<<tPlayer.getScore()<<"\n";
	}

	cout << oss.str();

	Fl_Multiline_Output *textDisplayHelp = new Fl_Multiline_Output(0, 0, 400, 300);
	textDisplayHelp->box(FL_BORDER_BOX);
	textDisplayHelp->color(FL_WHITE);
	textDisplayHelp->labelcolor((Fl_Color)5);
	textDisplayHelp->value(oss.str().c_str());//from BejeweledIO
	textDisplayHelp->set_output();

	highScoreWindow->end();
	highScoreWindow->show();
}

ScoresWindow::ScoresWindow(PlayerScore ps)
{
	writeScore(ps);
	ScoresWindow();
}

void cb_TileButton(Tile* tile, void* v)
{
	int r = tile->r;
	int c = tile->c;

	BejeweledWindow* bj = (BejeweledWindow*)(tile->parent()->user_data());
	GameBoard* gb = bj->gameBoard;//not picking up the correct value

	cout << "[" << r << "][" << c << "] Clicked!\n";
	if(((CurrentSelection::col == c-1 || CurrentSelection::col == c+1) && CurrentSelection::row == r ) || 
	   ((CurrentSelection::row == r-1 || CurrentSelection::row == r+1) && CurrentSelection::col == c ))
	{	
		Direction d;
		if(r<CurrentSelection::row)
			d = Direction::N;
		else if(c>CurrentSelection::col)
			d = Direction::E;
		else if(r>CurrentSelection::row)
			d = Direction::S;
		else if(c<CurrentSelection::col)
			d = Direction::W;

		bj->addScore(gb->legalMove(CurrentSelection::row, CurrentSelection::col, d));
		bj->updateScore();
		CurrentSelection::row = CurrentSelection::col = -999;
	}
	else
	{
		CurrentSelection::row = r;
		CurrentSelection::col = c;
	}
	if(CurrentSelection::row==-999 || CurrentSelection::col==-999)
		cout << "Current Row: None\nCurrent Column: None\n";
	else
		cout << "Current Row: " << CurrentSelection::row << "\nCurrent Column: " << CurrentSelection::col << endl;

	if(!gb->possibleMatches() && !bj->gameOver)
	{
		cout << "You Lose!\n";
		LoseGameWindow w;
		ScoresWindow sw(bj->getPlayer());
		bj->gameOver = true;
	}
	gb->update();
}

void ScoresWindow::writeScore(PlayerScore ps)
{
	//userwindow
	const char* chAry = fl_input("Please enter your first name: ");
	string name;
	if(chAry!=NULL)
		name = string(chAry);
	else
		name = "Unkown";

	/*trim(name);
	if(name.length()==0)
		name = "Unkown";*///why isnt there an std trim, that makes no sense!

	string fname;
	istringstream iss(name);
	iss>>fname;

	ps.setName(fname);
	scoreIO.writeScore(ps);
}

//the text for a widget label MUST reside in the free store for it to work in FLTK
void BejeweledWindow::updateLabel(Fl_Box* widget, string str)
{
	static string statStr;
	statStr = str;

	int tempX, tempY, tempW, tempH;
	if(widget)
	{
		tempX = widget->x();
		tempY = widget->y();
		tempW = widget->w();
		tempH = widget->h();
		mainWindow->remove(widget);
		delete widget;
	}
	widget = new Fl_Box(tempX, tempY, tempW, tempH, statStr.c_str());

	widget->box(FL_PLASTIC_DOWN_FRAME);
    widget->color((Fl_Color)41);
    widget->labelfont(1);
    widget->labelsize(51);
    widget->labelcolor(FL_GREEN);

	mainWindow->add(widget);
	mainWindow->end();
	mainWindow->redraw();
	/*if(widget->label())
		delete widget->label();
	char* chAry = new char[str.length()+1];
	for(unsigned int i = 0; i < str.length(); i++)
		chAry[i] = str[i];
	chAry[str.length()]='\0';

	widget->label(chAry);
	//widget->redraw();*/
}

void BejeweledWindow::updateScore()
{
	ostringstream oss;
	oss<<playerScore.getScore();
	updateLabel(scoreBox, oss.str());
}

void BejeweledWindow::levelUp()
{
}

void BejeweledWindow::addScore(int s)
{
	//cout << "adding: " << s << " combos to score\n";
	playerScore.addScore(s);
}