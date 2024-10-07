#include <ncurses.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void PrintScr();
void Init();
void LineUp();
void LineDown();
void Right();
void Left();
void Home();
void PageUp();
void PageDown();
void EndPage();
void NewLine();

int ch;
int row, col, y = 0, x = 0, LN = 0, TheStart, TheEnd;
int CurrentLine = 0;
string matn[1000];

int main(int argc, char** argv) {
    Init();

    ifstream file(argv[1]);
    if (!file.is_open())
        printw("Not such a file!\n");
    string line;
    while (getline(file, line))
        matn[LN] = line.c_str(), LN++;

    mvchgat(y, x, -1, A_BLINK, 1, NULL);
    refresh();
    PrintScr();
    move(0, 0);
    refresh();

    while (true) {
        ch = getch();
        if (ch == KEY_DOWN){
            LineDown();
			continue;
		}
        if (ch == KEY_UP){
            LineUp();
			continue;
		}
        if (ch == KEY_LEFT){
            Left();
			continue;
		}
        if (ch == KEY_RIGHT){
            Right();
			continue;
		}
        if (ch == KEY_HOME){
            Home();
			continue;
		}
        if (ch == KEY_NPAGE){
            PageDown();
			continue;
		}
        if (ch == KEY_PPAGE){
            PageUp();
			continue;
		}
        if (ch == KEY_END){
            EndPage();
			continue;
		}
		if (ch == 10){//Enter
			NewLine();
			continue;
		}
        refresh();
    }
    getch();
    endwin();
}

void Init() {
    initscr();
    noecho();    //   do not show the given characters from input
    cbreak();
    keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
    row = COLS;
    col = LINES;
    TheStart = 0;
    TheEnd = LINES - 1;
}
void PrintScr() {
    clear();
    for (int i = TheStart; i <= TheEnd; i++)
        printw("%s\n", matn[i].c_str());
    refresh();
}
void LineUp() {
    if (y > 0) {
        y--;
		CurrentLine --;
    } else if (y == 0) {
        if (LN - 1 > LINES && TheStart > 0){
            TheStart--;
			TheEnd--;
			CurrentLine --;
			PrintScr();
		}
    }
    move(y, x);
}
void LineDown() {
    if (y == LN - 1)
        return;
    if (y == LINES - 1) {
        if (TheEnd < LN - 1) {
            TheStart++;
            TheEnd++;
			CurrentLine ++;
            PrintScr();
            move(y, x);
        }
    } else {
        y++;
		CurrentLine ++;
		PrintScr();
        move(y, x);
    }
}
void Right() {

    if (x < COLS - 1)
        x++;
    else if (x == COLS - 1) {
        if (y < LINES - 1)
            y++, x = 0;
        if (y == LINES - 1) {
            if (TheEnd == LN - 1)
                return;
            x = 0, LineDown();
        }
    }
    move(y, x);
}
void Left() {
    if (x > 0)
        x--, move(y, x);
    else {
        if (y > 0) {
            x = COLS - 1;
            y--;
            move(y, x);
        } else {
            if (TheStart == 0)
                return;
            x = COLS - 1;
            LineUp();
        }
    }
}
void Home() {
    TheStart = 0;
    TheEnd = min(LN - 1, LINES - 1);
    PrintScr();
    x = 0, y = 0;
    move(y, x);
}
void PageUp() {
    TheStart = max(0, TheStart - LINES);
    TheEnd = min(LN - 1, TheStart + LINES - 1);
    PrintScr();
}
void PageDown() {
    TheEnd = min(LN - 1, TheEnd + LINES);
    TheStart = max(0, TheEnd - LINES + 1);
    PrintScr();
}
void EndPage() {
    TheEnd = LN - 1;
    TheStart = max(0, TheEnd - LINES + 1);
    PrintScr();
}
void NewLine() {
	for(int i = LN; i > CurrentLine + 1; i --)
		matn[i] = matn[i-1];
	LN++;
	matn[CurrentLine + 1] = "";
	LineDown();
}
