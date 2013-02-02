#pragma warning (disable: 4482)
#pragma warning (disable: 4311)
#pragma warning (disable: 4312)
#include "std_lib_facilities.h"
#include "fltk.h"

extern vector<Fl_GIF_Image*> imageVector;

enum Direction{N, E, S, W, UNDEFINED = -1};

struct Jewel
{
	Jewel(int cc);
	int as_int() const;
	Fl_Color as_Fl_Color() const {return c;}

private:
	Fl_Color c;
};

inline bool operator==(const Jewel& lhs, const Jewel& rhs)
{
	return lhs.as_int() == rhs.as_int();
}

inline bool operator!=(const Jewel& lhs, const Jewel& rhs)
{
	return lhs.as_int() != rhs.as_int();
}

inline ostream& operator<<(ostream& os, const Jewel& c)
{
	return os<<c.as_int();
}

struct CurrentSelection
{
	static int row;
	static int col;

private:
	CurrentSelection();//dont want to create any instances
};

class Tile: public Fl_Button
{
public:
	Tile()
		:Fl_Button(0, 0, 0, 0, 0), clr(0), marked(false){}
	Tile(Jewel c)
		:Fl_Button(0, 0, 0, 0, 0), clr(c), marked(false){}
	Tile(int xx, int yy, int ww, int hh, Jewel cc, int row, int col)
		:Fl_Button(xx, yy, ww, hh, 0), clr(cc), marked(false), r(row), c(col){color(clr.as_Fl_Color());}
	
	Jewel clr;
	bool marked;//for deletion
	
	friend void cb_TileButton(Tile* tile, void* v);
	void operator=(Tile& tile);

private:
	int r, c; //for use with the callback

protected:
	void draw();//do we want to tell it how to draw itself?
};

void cb_TileButton(Tile* tile, void* v);

class GameBoard
{
public:
	static const int GAME_ROWS = 8;
	static const int GAME_COLS = 8;
	
	GameBoard();
	GameBoard(Fl_Group& gb);
	~GameBoard();
	
	void display();
	void displayMarks();
	void displayCombos();

	int findMatches();
	bool possibleMatches();
	int legalMove(int r, int c, Direction dir);

	void update();

	Tile* getTile(int r, int c){return board[r][c];}

private:
	bool possibleMatchPair(int r, int c, Jewel color, Direction dir);
	bool possibleMatchGap(int r, int c, Jewel color, Direction dir);
	void findMatches(int r, int c, Jewel color);
	void markTiles(int r, int c, Jewel color, Direction dir, int count);
	void removeMatches();
	
	(Tile*) board[GAME_ROWS][GAME_COLS];
	int numColors;
	vector<String> combos;
	Direction comboDir;
	Jewel comboColor;
};

typedef void (idleCallback)(void*);
inline void idleFunction(void*){}

/*****************************************************************

MEMBER FUNCTIONS
----------------
Name: GameBoard() - Default constructor
Task: Fills the board with gems and removes all initial
	  "combos" from the game board. if it creates a board with no
 	  possible moves it tries again

Name: display()
Returns: void
Task: display the game board in text
	  used in debugging for displaying the game board in text

Name: displayMarks()
Returns: void
Task: display current matches
	  used in debugging for displaying "combos", gems that appear in
	  a combo are displayed as 'M', all others are displayed as 0's

Name: displayCombos()
Returns: void
Task: outputs the location of current combos
	  used in debugging to make finding the combos a little easier

Name: findMatches()
Returns: int
Task: returns the number of combos found and marks them for removal

Name: possibleMatches()
Returns: bool
Task: returns true if any possible moves exist.

Name: legalMove(int r, int c, Direction dir)
Params: r - row
		c - column
		dir - direction of desired move
Returns: bool
Task: if the move is legal it will swap the gems and call findMatches()
	  otherwise the gems will not be moved

Name: possibleMatchPair(int r, int c, Color color, Direction dir)
Params:	r - row
		c - column
		color - color of the currently searched combo
		dir - direction that the algorithm is currently searching in
Returns: bool
Task: Helper function to possibleMatches()

Name: possibleMatchGap(int r, int c, Color color, Direction dir)
Params:	r - row
		c - column
		color - color of the currently searched combo
		dir - direction that the algorithm is currently searching in
Returns: bool
Task: Helper function to possibleMatches()

Name: findMatches(int r, int c, Color color)
Params: r - row
		c - column
		color - current combo color
Returns: void
Task: mark combos for removal if any are found
	  for debugging purposes it adds combos it finds to the combos vector

	void 
Name: markTiles(int r, int c, Color color, Direction dir, int count)
Params: r - row
		c - column
		color - color of the combo to be marked
		dir - direction of the combo
		count - number of gems in the combo
Returns: void
Task: mark combo'd tiles for removal

Name: removeMatches()
Returns: void
Task: remove marked tiles from the board and shifts gems from above down

MEMBER VARIABLES
----------------

static const int GAME_ROWS = 8;		fixed number of rows in our game for the board
static const int GAME_COLS = 8;		fixed number of columns in our game for the board
Tile board[GAME_ROWS][GAME_COLS];	the game board itself implemented as a 2D Array (could do better)
int numColors;						how many different gem types are in the game

vector<String> combos;				used for text based debugging
Direction comboDir;					used for text based debugging
Color comboColor;					used for text based debugging
*/