#include<iostream>
#include<fstream>
#include<string>
#include <ncurses.h>
#include <stdio.h>
using namespace std;

void init();

char ch;
int row, col, y = 0, x = 0;

int main(int argc,  char** argv){
	init();
    ifstream file (argv[1]);
    if(!file.is_open()) printw("Not such a file!\n");
	string line;
	while( getline(file,line) ) printw("%s\n", line.c_str());
	mvchgat(y, x, -1, A_BLINK, 1, NULL);	
	refresh();

	while(true){
		ch = getch();
	//	printw("%d",ch);
		if(ch == 4){//left
			if(x > 0) x --;
			else if(x == 0) y = max(0, y -1), x = row - 1;
			move(y, x);
		}
		if(ch == 5){//right
			if(x < row - 1) x ++;
			else if(x == row- 1) y ++, x = 0;
			move(y, x);
		}
		refresh();
	}
	getch();
	endwin();

}

void init(){
	initscr();
	noecho(); //   do not show the given characters from input
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	getmaxyx(stdscr,row,col);
}
