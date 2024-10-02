#include<iostream>
#include<fstream>
#include<string>
#include <ncurses.h>
#include <stdio.h>
using namespace std;

void print_scr();
void init(); 
void LINE_UP();
void LINE_DOWN();
void RIGHT();
void LEFT();
void HOME();
void PAGE_UP();
void PAGE_DOWN();
void END_PAGE();
                                                                                                                                 
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
		if(ch == 2)LINE_DOWN();
		if(ch == 3)LINE_UP();
		if(ch == 4)LEFT();
		if(ch == 5)RIGHT();
		if(ch == 6)HOME();
		if(ch == 82)PAGE_DOWN();
		if(ch == 83)PAGE_UP();
		if(ch == 104)END_PAGE();
		refresh();
	}
	getch();
	endwin();

}

void init(){
	initscr();
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
void LINE_UP(){
	if(y > 0){
		y --;
	}else if(y == 0){
		if(LN-1 > LINES && the_start > 0) the_start --, the_end --, print_scr();
	}
	move(y,x);
}
void LINE_DOWN(){	
	if(y == LN - 1) return;
	if(y == LINES - 1){
		if(the_end < LN - 1){
			the_start ++; the_end ++;
			print_scr();
			move(y, x);
		}
	}else{
		y ++;
		move(y, x);
	}
}
void RIGHT(){
	if(x < COLS-1) x ++;
	else if(x == COLS - 1){
		if(y < LINES - 1)y ++, x = 0;
		if(y == LINES -1){
			if(the_end == LN -1) return;
			x = 0, LINE_DOWN();
		}
	}
	move(y, x);
}
void LEFT(){
	if(x > 0) x --, move(y, x);
	else{
		if(y > 0){
			x = COLS - 1; y --;
			move(y, x);
		}
		else{
			if(the_start == 0) return;
			x = COLS - 1;
			LINE_UP();
		}
	}
}
void HOME(){
	the_start = 0;
	the_end = min(LN - 1, LINES - 1);
	print_scr();
	x = 0, y = 0;
	move(y, x);
}
void PAGE_UP(){
	the_start = max(0, the_start - LINES);
	the_end  = min(LN - 1, the_start + LINES - 1);
	print_scr();
}
void PAGE_DOWN(){
	the_end = min(LN - 1, the_end + LINES);
	the_start = max(0, the_end - LINES + 1);
	print_scr();
}
void END_PAGE(){
	the_end = LN - 1;
	the_start = max(0, the_end - LINES + 1);
	print_scr();
}