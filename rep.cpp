#include <ncurses.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include "src/Editor.h"
#include "src/File.h"
#include "src/Screen.h"
using namespace std;

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
int y = 0, x = 0;
int CurrentLine = 0;

Screen RepScreen;
File RepFile;
Editor Rep;

int main(int argc, char** argv) {

    

    if ( RepFile.Open(argv[1], Rep) == false ){
        RepScreen.PrintLine(0, "Not such a file!\n");
        getch();
    }

    RepScreen.TheEnd = min(RepScreen.TheEnd, Rep.LN-1);
    RepScreen.PrintScr(Rep);

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
    RepScreen.EndScr();
}


void LineUp() {
    if (y > 0) {
        y--;
        x = min(x, (int)(Rep.Matn[CurrentLine - 1].size()));
        CurrentLine--;
    } else if (y == 0) {
        if (Rep.LN - 1 > RepScreen.col && RepScreen.TheStart > 0) {
            RepScreen.TheStart --;
            RepScreen.TheEnd --;
            x = min(x, (int)(Rep.Matn[CurrentLine - 1].size()));
            CurrentLine--;
            RepScreen.PrintScr(Rep);
        }
    }
    RepScreen.Move(y, x);
}
void LineDown() {
    if (y == Rep.LN - 1)
        return;
    if (y == RepScreen.col - 1) {
        if (RepScreen.TheEnd < Rep.LN - 1) {
            RepScreen.TheStart++;
            RepScreen.TheEnd++;
            x = min(x, (int)(Rep.Matn[CurrentLine + 1].size()));
            CurrentLine++;
            RepScreen.PrintScr(Rep);
            RepScreen.Move(y, x);
        }
    } else {
        y++;
        x = min(x, (int)(Rep.Matn[CurrentLine + 1].size()));
        CurrentLine++;
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    }
}
void Right() {
    int _COLS = min((int)(Rep.Matn[CurrentLine].size()), RepScreen.row - 1);
    if (x < _COLS)
        x++;
    RepScreen.Move(y, x);
}
void Left() {
    if (x > 0)
        x--, RepScreen.Move(y, x);
    else {
        if (y > 0) {
            x = Rep.Matn[CurrentLine - 1].size();
            y--;
            CurrentLine--;
            RepScreen.Move(y, x);
        } else {
            if (RepScreen.TheStart == 0)
                return;
            x = RepScreen.row - 1;
            LineUp();
        }
    }
}
void Home() {
    RepScreen.TheStart = 0;
    RepScreen.TheEnd = min(Rep.LN - 1, RepScreen.col - 1);
    RepScreen.PrintScr(Rep);
    x = 0, y = 0;
    CurrentLine = 0;
    RepScreen.Move(y, x);
}
void PageUp() {
    RepScreen.TheStart = max(0, RepScreen.TheStart - RepScreen.col);
    RepScreen.TheEnd = min(Rep.LN - 1, RepScreen.TheStart + RepScreen.col - 1);
    CurrentLine = RepScreen.TheStart;
    x = 0, y = 0;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}
void PageDown() {
    RepScreen.TheEnd = min(Rep.LN - 1, RepScreen.TheEnd + RepScreen.col);
    RepScreen.TheStart = max(0, RepScreen.TheEnd - RepScreen.col + 1);
    CurrentLine = RepScreen.TheStart;
    x = 0, y = 0;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}
void EndPage() {
    RepScreen.TheEnd = Rep.LN - 1;
    RepScreen.TheStart = max(0, RepScreen.TheEnd - RepScreen.col + 1);
    CurrentLine = Rep.LN - 1;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}
void Enter() {
    for (int i = Rep.LN; i > CurrentLine + 1; i--)
        Rep.Matn[i] = Rep.Matn[i - 1];
    Rep.LN++;
    Rep.Matn[CurrentLine + 1] = "";
    if (x == 0) {
        Rep.Matn[CurrentLine + 1] = Rep.Matn[CurrentLine];
        Rep.Matn[CurrentLine] = "";
    } else {
        for (int i = x; i < Rep.Matn[CurrentLine].size(); i++)
            Rep.Matn[CurrentLine + 1] += Rep.Matn[CurrentLine][i];
        string TemperoryString = "";
        for (int i = 0; i < x; i++)
            TemperoryString += Rep.Matn[CurrentLine][i];
        Rep.Matn[CurrentLine] = TemperoryString;
        x = 0;
    }
    LineDown();
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}
void BackSpace() {
    if (x == 0) {
        if (y == 0)
            return;
        x = Rep.Matn[CurrentLine - 1].size();
        Rep.Matn[CurrentLine - 1] += Rep.Matn[CurrentLine];
        Rep.Matn[CurrentLine] = "";
        LineUp();
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    } else {
        string TemperoryString = "";
        for (int i = 0; i < x - 1; i++)
            TemperoryString += Rep.Matn[CurrentLine][i];
        for (int i = x; i < Rep.Matn[CurrentLine].size(); i++)
            TemperoryString += Rep.Matn[CurrentLine][i];
        Rep.Matn[CurrentLine] = TemperoryString;
        x--;
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    }
}
void Insert(char ch){
    string TemperoryString = "";
    for (int i = 0; i < x; i ++) 
        TemperoryString += Rep.Matn[CurrentLine][i];
    TemperoryString += ch;
    for (int i = x; i < Rep.Matn[CurrentLine].size(); i ++)
        TemperoryString += Rep.Matn[CurrentLine][i];
    Rep.Matn[CurrentLine] = TemperoryString;
    x ++;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}
