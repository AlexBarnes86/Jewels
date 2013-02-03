/*
*Name: Alex Barnes
*UIN: ****07272
*Class: ENGR 112-205
*Date: 4-05-06
*
*FileName: BejeweledMain.cpp
*Version: 1.5
*Description:
*/

#include "std_lib_facilities.h"
#include "BejeweledWindow.h"
#include "GameBoard.h"
#include <time.h>

string getImagePath(); 

int main(int argc, char** argv) {
	srand((unsigned)time(NULL));
	initImages(getImagePath());
	BejeweledWindow* bw = new BejeweledWindow();

	string mainArg;

	if(argc == 1) {
		mainArg = string(argv[0]);
	}
	
	if(mainArg == "-debug") {
		int r, c;
		char dir;
		GameBoard gb;

		while(gb.possibleMatches()) {
			gb.display();
			cout << "Move (r, c, dir): ";
			cin >> r >> c >> dir;
			switch(dir) {
				case 'n':
				case 'N': if(!gb.legalMove(r, c, N))cout<<"\aIllegal move!\n\n"; break;
				case 'e':
				case 'E': if(!gb.legalMove(r, c, E))cout<<"\aIllegal move!\n\n"; break;
				case 's':
				case 'S': if(!gb.legalMove(r, c, S))cout<<"\aIllegal move!\n\n"; break;
				case 'w':
				case 'W': if(!gb.legalMove(r, c, W))cout<<"\aIllegal move!\n\n"; break;
				case '~': goto endloop; //bad practice
				default: cout << "Illegal direction!\n";
			}
		}endloop: //bad practice, but simple use and very small scope
		
		return 0;
	}
	else {
		return Fl::run();
	}
}

string getImagePath() {
	ifstream ist("imagePath.txt");
	string path;
	if(!ist)
		return "images/";//"C:/Documents and Settings/shannaa/Desktop/Bejeweled/GUI/Images"
	getline(ist, path);
	ist.close();
	return path;//path;
}
