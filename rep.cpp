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
void Enter();
void BackSpace();
void Insert(char ch);

int ch;
int row, col, y = 0, x = 0, LN = 0, TheStart, TheEnd;
int CurrentLine = 0;
string matn[1000];

int main(int argc, char** argv) {
    Init();

    ifstream file(argv[1]);
    if (!file.is_open()){
        printw("Not such a file!\n");
        refresh();
    }
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
        if (ch == KEY_DOWN) {
            LineDown();
            continue;
        }
        if (ch == KEY_UP) {
            LineUp();
            continue;
        }
        if (ch == KEY_LEFT) {
            Left();
            continue;
        }
        if (ch == KEY_RIGHT) {
            Right();
            continue;
        }
        if (ch == KEY_HOME) {
            Home();
            continue;
        }
        if (ch == KEY_NPAGE) {
            PageDown();
            continue;
        }
        if (ch == KEY_PPAGE) {
            PageUp();
            continue;
        }
        if (ch == KEY_END) {
            EndPage();
            continue;
        }
        if (ch == 10) {    //Enter
            Enter();
            continue;
        }
        if (ch == KEY_BACKSPACE) {
            BackSpace();
            continue;
        }
        Insert(ch);
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
        x = min(x, (int)(matn[CurrentLine - 1].size()));
        CurrentLine--;
    } else if (y == 0) {
        if (LN - 1 > LINES && TheStart > 0) {
            TheStart--;
            TheEnd--;
            x = min(x, (int)(matn[CurrentLine - 1].size()));
            CurrentLine--;
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
            x = min(x, (int)(matn[CurrentLine + 1].size()));
            CurrentLine++;
            PrintScr();
            move(y, x);
        }
    } else {
        y++;
        x = min(x, (int)(matn[CurrentLine + 1].size()));
        CurrentLine++;
        PrintScr();
        move(y, x);
    }
}
void Right() {
    int _COLS = min((int)(matn[CurrentLine].size()), COLS - 1);
    if (x < _COLS)
        x++;
    move(y, x);
}
void Left() {
    if (x > 0)
        x--, move(y, x);
    else {
        if (y > 0) {
            x = matn[CurrentLine - 1].size();
            y--;
            CurrentLine--;
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
    CurrentLine = 0;
    move(y, x);
}
void PageUp() {
    TheStart = max(0, TheStart - LINES);
    TheEnd = min(LN - 1, TheStart + LINES - 1);
    CurrentLine = TheStart;
    x = 0, y = 0;
    PrintScr();
    move(y, x);
}
void PageDown() {
    TheEnd = min(LN - 1, TheEnd + LINES);
    TheStart = max(0, TheEnd - LINES + 1);
    CurrentLine = TheStart;
    x = 0, y = 0;
    PrintScr();
    move(y, x);
}
void EndPage() {
    TheEnd = LN - 1;
    TheStart = max(0, TheEnd - LINES + 1);
    CurrentLine = LN - 1;
    PrintScr();
    move(y, x);
}
void Enter() {
    for (int i = LN; i > CurrentLine + 1; i--)
        matn[i] = matn[i - 1];
    LN++;
    matn[CurrentLine + 1] = "";
    if (x == 0) {
        matn[CurrentLine + 1] = matn[CurrentLine];
        matn[CurrentLine] = "";
    } else {
        for (int i = x; i < matn[CurrentLine].size(); i++)
            matn[CurrentLine + 1] += matn[CurrentLine][i];
        string TemperoryString = "";
        for (int i = 0; i < x; i++)
            TemperoryString += matn[CurrentLine][i];
        matn[CurrentLine] = TemperoryString;
        x = 0;
    }
    LineDown();
    PrintScr();
    move(y, x);
}
void BackSpace() {
    if (x == 0) {
        if (y == 0)
            return;
        x = matn[CurrentLine - 1].size();
        matn[CurrentLine - 1] += matn[CurrentLine];
        matn[CurrentLine] = "";
        LineUp();
        PrintScr();
        move(y, x);
    } else {
        string TemperoryString = "";
        for (int i = 0; i < x - 1; i++)
            TemperoryString += matn[CurrentLine][i];
        for (int i = x; i < matn[CurrentLine].size(); i++)
            TemperoryString += matn[CurrentLine][i];
        matn[CurrentLine] = TemperoryString;
        x--;
        PrintScr();
        move(y, x);
    }
}
void Insert(char ch){
    string TemperoryString = "";
    for (int i = 0; i < x; i ++) 
        TemperoryString += matn[CurrentLine][i];
    TemperoryString += ch;
    for (int i = x; i < matn[CurrentLine].size(); i ++)
        TemperoryString += matn[CurrentLine][i];
    matn[CurrentLine] = TemperoryString;
    x ++;
    PrintScr();
    move(y, x);
}