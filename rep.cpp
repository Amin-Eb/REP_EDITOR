#include<iostream>
#include<fstream>
#include<string>
#include <ncurses.h>
#include <stdio.h>
using namespace std;

void init(); print_scr();                                                                                                                                  
char ch;
int row, col, y = 0, x = 0, LN = 0,the_start, the_end;
string matn[1000];

int main(int argc,  char** argv){
	init();
    ifstream file (argv[1]);
    if(!file.is_open()) printw("Not such a file!\n");
	string line;
	while(getline(file,line)) matn[LN] = line.c_str(),LN++;
	mvchgat(y, x, -1, A_BLINK, 1, NULL);	
	refresh();
	print_scr();
	move(0,0);
	refresh();
	while(true){
		ch = getch();
//		printw("%d",ch);
		if(ch == 2){//down
			if(y == LINES - 1){
				if(the_end != LN - 1){
					the_start ++; the_end ++;
					print_scr();
					x = 0;
					move(y,x);
				}

			}else y++, move(y, x);
		}
		if(ch == 3){//up
			if(y > 0){
				y --;
			}else if(y == 0){
				x = 0;
				if(LN-1 > LINES && the_start > 0) the_start --, the_end --, print_scr();
			}
			move(y,x);
		}
		if(ch == 4){//left
			if(x > 0) x --;
			else if(x == 0) y = max(0, y -1), x = row - 1;
			move(y, x);
		}
		if(ch == 5){//right
			if(x < COLS- 1) x ++;
			else if(x == COLS - 1){
				if(y < LINES - 1)y ++, x = 0;
			}
			move(y, x);
		}
		refresh();
	}
	getch();
	endwin();

}

void init(){
	initscr();
//	cbreak();
	noecho(); //   do not show the given characters from input
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	row = COLS;
	col = LINES;
	the_start = 0;
	the_end = LINES - 1;
}
void print_scr(){
	clear();
	for(int i = the_start; i <= the_end; i ++) printw("%s\n", matn[i].c_str());
	refresh();
}
