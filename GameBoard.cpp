#include "GameBoard.h"
#include <time.h>

int CurrentSelection::row = -999;
int CurrentSelection::col = -999;
int score = 0;

Jewel::Jewel(int cc)
{
	switch(cc)
	{
		case 1: c = FL_RED; break;
		case 2: c = FL_BLUE; break;
		case 3: c = FL_YELLOW; break;
		case 4: c = FL_GREEN; break;
		case 5: c = FL_WHITE; break;
		case 6: c = FL_MAGENTA; break;
		case 7: c = FL_CYAN; break;
		default: c = Fl_Color(cc);
	}
}

int Jewel::as_int() const 
{
	switch(c)
	{
	case FL_RED: return 1;
	case FL_BLUE: return 2;
	case FL_YELLOW: return 3;
	case FL_GREEN: return 4;
	case FL_WHITE: return 5;
	case FL_MAGENTA: return 6;
	case FL_CYAN: return 7;
	default: return c;
	}
}

void Tile::operator=(Tile& tile)
{
	clr = tile.clr;
	r = tile.r;
	c = tile.c;
	marked = tile.marked;
}

GameBoard::GameBoard()
	:comboColor(-1), comboDir(Direction::UNDEFINED), numColors(7)
{
	for(int i = 0; i < GAME_ROWS; ++i)
		for(int j = 0; j < GAME_COLS; ++j)
		{
			board[i][j] = new Tile(Jewel((rand()%numColors)+1));
		}

	while(findMatches()!=0) removeMatches();
}

GameBoard::GameBoard(Fl_Group& gb)
	:comboColor(0), comboDir(Direction::UNDEFINED), numColors(7)
{
	for(int r=0; r<GAME_ROWS; r++)
	{
		for (int c=0; c<GAME_COLS; c++)
		{
			board[r][c] = new Tile(c*50+190, r*50+35, 50, 50, Jewel((rand()%numColors)+1), r, c);
			board[r][c]->callback((Fl_Callback*)cb_TileButton);
			gb.add(board[r][c]);
		}
	}

	while(findMatches()!=0) removeMatches();
	
	gb.end();
	gb.show();
}

void Tile::draw()
{
	//draw the boxes just incase the images didnt load properly
	fl_draw_box(FL_UP_BOX, x(), y(), w(), h(), clr.as_Fl_Color());
	if(marked)
		imageVector[(int)imageVector.size()-1]->draw(x(), y());//typecast to remove warning
	else
		imageVector[clr.as_int()+3]->draw(x(), y());//magic number 3 is for the first set of images in the game
}

GameBoard::~GameBoard()
{
	for(int i = 0; i < GAME_ROWS; i++)
		for(int j = 0; j < GAME_COLS; j++)
			if(board[i][j])
				delete board[i][j];
}

void GameBoard::display()
{
	cout << "   ";
	for(int i = 0; i < GAME_ROWS; i++)
		cout << i << ' ';

	cout << "\n\n";

	for(int i = 0; i < GAME_ROWS; ++i)
	{
		cout << i << "  ";
		for(int j = 0; j < GAME_COLS; ++j)
			cout << board[i][j]->clr << ' ';
		cout << endl;
	}
	cout << endl;
}

void GameBoard::displayMarks()
{
	cout << "   ";
	for(int i = 0; i < GAME_ROWS; i++)
		cout << i << ' ';

	cout << "\n\n";

	for(int i = 0; i < GAME_ROWS; ++i)
	{
		cout << i << "  ";
		for(int j = 0; j < GAME_COLS; ++j)
			cout << (board[i][j]->marked?'M':'0') << ' ';
		cout << endl;
	}
}

void GameBoard::displayCombos()
{
	for(unsigned int i = 0; i < combos.size(); i++)
		cout << combos[i] << endl;
	if(combos.size()>0) cout << endl;
}

int GameBoard::findMatches()
{
	for(int i = 0; i < GAME_ROWS; ++i)
		for(int j = 0; j < GAME_COLS; ++j)
			findMatches(i, j, board[i][j]->clr);
	
	if(combos.size()>0)
	{
		display();
		displayCombos();
	}

	return (int)combos.size();
}

void GameBoard::findMatches(int r, int c, Jewel clr)
{
	int combo = 0;
	for(int i = r; i < GAME_ROWS; ++i)
	{
		if(board[i][c]->clr!=clr)
			break;
		++combo;
	}
	if(combo>2)
	{
		markTiles(r, c, clr, Direction::S, combo);
		ostringstream ss;
		ss << "Color: " << clr << " ["<<r<<"]["<<c<<"] Dir: " <<Direction::S;
		combos.push_back(ss.str());
	}
	combo = 0;
	for(int i = c; i < GAME_COLS; ++i)
	{
		if(board[r][i]->clr!=clr)
			break;
		++combo;
	}
	if(combo>2)
	{
		markTiles(r, c, clr, Direction::E, combo);
		ostringstream ss;
		ss << "Color: " << clr << " ["<<r<<"]["<<c<<"] Dir: " <<Direction::E;
		combos.push_back(ss.str());
	}
}

void GameBoard::markTiles(int r, int c, Jewel clr, Direction dir, int count)
{
	switch(int(dir))
	{
	case Direction::E:
		for(int i = c; i < c+count; i++)
			board[r][i]->marked = true;
		break;
	case Direction::S:
		for(int i = r; i < r+count; i++)
			board[i][c]->marked = true;
		break;
	}	
}

bool GameBoard::possibleMatches()
{
	for(int r = 0; r < GAME_ROWS; r++)
		for(int c = 0; c < GAME_COLS; c++)
		{
			if(board[r][c]->marked)
				continue;

			Jewel clr = board[r][c]->clr;

			if(r>=1 && board[r-1][c]->clr == clr)
				if(possibleMatchPair(r-1, c, clr, Direction::N)) return true;

			if(r>=2 && board[r-2][c]->clr == clr)
				if(possibleMatchGap(r-1, c, clr, Direction::N)) return true;
			
			if(c<GAME_COLS-1 && board[r][c+1]->clr == clr)
				if(possibleMatchPair(r, c+1, clr, Direction::E)) return true;

			if(c<GAME_COLS-2 && board[r][c+2]->clr == clr)
				if(possibleMatchGap(r, c+1, clr, Direction::E)) return true;

			if(r<GAME_ROWS-1 && board[r+1][c]->clr == clr)
				if(possibleMatchPair(r+1, c, clr, Direction::S)) return true;

			if(r<GAME_ROWS-2 && board[r+2][c]->clr == clr)
				if(possibleMatchGap(r+1, c, clr, Direction::S)) return true;

			if(c>=1 && board[r][c-1]->clr == clr)
				if(possibleMatchPair(r, c-1, clr, Direction::W)) return true;

			if(c>=2 && board[r][c-2]->clr == clr)
				if(possibleMatchGap(r, c-1, clr, Direction::W)) return true;
		}

	return false;
}

bool GameBoard::possibleMatchGap(int r, int c, Jewel clr, Direction dir)
{
	//if we are looking at a gap the current [r][c] element should be "on" the gap itself
	if(dir == Direction::N || dir == Direction::S)
	{
		if(c>=1 && board[r][c-1]->clr == clr)
			return true;
		else if(c<GAME_COLS-1 && board[r][c+1]->clr == clr)
			return true;
	}
	else if(dir == Direction::E || dir == Direction::W)
	{
		if(r>=1 && board[r-1][c]->clr == clr)
			return true;
		else if(r<GAME_ROWS-1 && board[r+1][c]->clr == clr)
			return true;
	}

	return false;
}

bool GameBoard::possibleMatchPair(int r, int c, Jewel clr, Direction dir)
{
	if(dir == Direction::N)
	{
		if(r>=2 && board[r-2][c]->clr == clr)
			return true;
		else if(r>=1 && c<GAME_COLS-1 && board[r-1][c+1]->clr == clr)
			return true;
		else if(r>=1 && c>=1 && board[r-1][c-1]->clr == clr)
			return true;
	}
	else if(dir == Direction::S)		
	{
		if(r<GAME_ROWS-2 && board[r+2][c]->clr == clr)
			return true;
		else if(r<GAME_ROWS-1 && c<GAME_COLS-1 && board[r+1][c+1]->clr == clr)
			return true;
		else if(r<GAME_ROWS-1 && c>=1 && board[r+1][c-1]->clr == clr)
			return true;
	}
	else if(dir == Direction::E)
	{
		if(c<GAME_COLS-2 && board[r][c+2]->clr == clr)
			return true;
		else if(c<GAME_COLS-1 && r<GAME_ROWS-1 && board[r+1][c+1]->clr == clr)
			return true;
		else if(c<GAME_COLS-1 && r>=1 && board[r-1][c+1]->clr == clr)
			return true;
	}
	else if(dir == Direction::W)
	{
		if(c>=2 && board[r][c-2]->clr == clr)
			return true;
		else if(c>=1 && r<GAME_ROWS-1 && board[r+1][c-1]->clr == clr)
			return true;
		else if(c>=1 && r>=1 && board[r-1][c-1]->clr == clr)
			return true;
	}

	return false;
}

int GameBoard::legalMove(int r, int c, Direction dir)
{
	//perform range checking - very important in this situation
	if(r<0||r>=GAME_ROWS||c<0||c>=GAME_COLS) return 0;
	if(r==0 && dir==Direction::N) return 0;
	else if(r==GAME_ROWS-1 && dir==Direction::S) return 0;
	else if(c==0 && dir==Direction::W) return 0;
	else if(c==GAME_COLS-1 && dir==Direction::E) return 0;

	int swapR = r;
	int swapC = c;

	switch(int(dir))
	{
	case Direction::N: swapR--; break;
	case Direction::E: swapC++; break;
	case Direction::S: swapR++; break;
	case Direction::W: swapC--; break;
	}

	cout << "Swapping: " << r << ", " << c << " color: " << board[r][c]->clr << " With " << swapR << ", " << swapC << " color: " << board[swapR][swapC]->clr << endl;
	swap(board[r][c]->clr, board[swapR][swapC]->clr);
	//cout << "\nScore:\t" << score << endl;
	display();

	if(findMatches()) //not necessary to check all, but for now
	{
		combos.clear();
		int comboCount = 0;
		while(findMatches()!=0) 
		{
			comboCount++;
			update();
			Fl::wait();
			time_t endTime, curTime;
			time(&endTime);
			endTime+=1;//seconds
			while(time(&curTime) && curTime < endTime);//do nothing but wait
			removeMatches();
		}
		return comboCount;
	}
	else
	{
		swap(board[r][c]->clr, board[swapR][swapC]->clr);
		return 0;
	}
}

void GameBoard::removeMatches()
{
	int rowIndex = 0;

	for(int c = 0; c < GAME_COLS; c++)
		for(int r = GAME_ROWS-1; r >= 0; r--)
		{
			if(board[r][c]->marked)
			{
				rowIndex = r;
				while(rowIndex>=0 && board[rowIndex][c]->marked)
					rowIndex--;
				if(rowIndex==-1)
					board[r][c]->clr = Jewel(rand()%numColors+1);
				else
				{
					board[r][c]->clr = board[rowIndex][c]->clr;
					board[rowIndex][c]->marked = true;
				}

				board[r][c]->marked = false;
			}
		}

		combos.clear();
}

void GameBoard::update()
{	
	score+=10;
	for(int r = 0; r < GAME_ROWS; ++r)
		for(int c = 0; c < GAME_COLS; ++c)
		{
			board[r][c]->redraw();
		}
}