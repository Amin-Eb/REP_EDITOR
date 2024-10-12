#include <ncurses.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include "src/Editor.h"
#include "src/Screen.h"
#include "src/File.h"

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
int y = 0, x = 4;
int CurrentLine = 0;

Screen RepScreen;
File RepFile;
Editor Rep;

int main(int argc, char** argv) {

    if (RepFile.Open(argv[1], Rep) == false) {
        RepFile.FileName = argv[1];
        Rep.AddLine(0, " ");
    }
    RepScreen.TheEnd = min(RepScreen.TheEnd, Rep.LN - 1);
    RepScreen.PrintScr(Rep);
    move(0, 4);

    while (ch != KEY_SEND) {
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
        if (ch == KEY_SHOME) {
            RepFile.Save(Rep, RepScreen, true);
            continue;
        }
        Insert(ch);
        refresh();
    }
    RepScreen.EndScr();
    exit(0);
}


void LineUp() {
    if (y > 0) {
        y--;
        x = min(x, (int)(Rep.Matn[CurrentLine - 1].size()));
        x += 4;
        CurrentLine--;
    } else if (y == 0) {
        if (Rep.LN - 1 > RepScreen.col && RepScreen.TheStart > 0) {
            RepScreen.TheStart--;
            RepScreen.TheEnd--;
            x = min(x, (int)(Rep.Matn[CurrentLine - 1].size()));
            x += 4;
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
            x += 4;
            CurrentLine++;
            RepScreen.PrintScr(Rep);
            RepScreen.Move(y, x);
        }
    } else {
        if (Rep.LN - 1 < RepScreen.col - 1 && y == Rep.LN - 2)
            RepScreen.TheEnd++;
        y++;
        x = min(x, (int)(Rep.Matn[CurrentLine + 1].size()));
        x += 4;
        CurrentLine++;
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    }
}
void Right() {
    int _COLS = min((int)(Rep.Matn[CurrentLine].size()) + 4, RepScreen.row - 1);
    if (x < _COLS)
        x++;
    RepScreen.Move(y, x);
}
void Left() {
    if (x > 4)
        x--, RepScreen.Move(y, x);
    else {
        if (y > 0) {
            x = Rep.Matn[CurrentLine - 1].size() + 4;
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
    x = 4, y = 0;
    CurrentLine = 0;
    RepScreen.Move(y, x);
}
void PageUp() {
    RepScreen.TheStart = max(0, RepScreen.TheStart - RepScreen.col);
    RepScreen.TheEnd = min(Rep.LN - 1, RepScreen.TheStart + RepScreen.col - 1);
    CurrentLine = RepScreen.TheStart;
    x = 4, y = 0;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}
void PageDown() {
    RepScreen.TheEnd = min(Rep.LN - 1, RepScreen.TheEnd + RepScreen.col);
    RepScreen.TheStart = max(0, RepScreen.TheEnd - RepScreen.col + 1);
    CurrentLine = RepScreen.TheStart;
    x = 4, y = 0;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}
void EndPage() {
    RepScreen.TheEnd = Rep.LN - 1;
    RepScreen.TheStart = max(0, RepScreen.TheEnd - RepScreen.col + 1);
    CurrentLine = Rep.LN - 1;
    RepScreen.PrintScr(Rep);
    y = RepScreen.col;
    x = Rep.Matn[Rep.LN - 1].size() + 4;
    RepScreen.Move(y, x);
}
void Enter() {
    Rep.AddLine(CurrentLine + 1, "");
    if (x == 4) {
        Rep.Matn[CurrentLine + 1] = Rep.Matn[CurrentLine];
        Rep.Matn[CurrentLine] = "";
    } else {
        for (int i = x - 4; i < Rep.Matn[CurrentLine].size(); i++)
            Rep.Matn[CurrentLine + 1] += Rep.Matn[CurrentLine][i];
        string TemperoryString = "";
        for (int i = 0; i < x - 4; i++)
            TemperoryString += Rep.Matn[CurrentLine][i];
        Rep.Matn[CurrentLine] = TemperoryString;
        x = 4;
    }
    LineDown();
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}
void BackSpace() {
    if (x == 4) {
        if (y == 0)
            return;
        Rep.Matn[CurrentLine - 1] += Rep.Matn[CurrentLine];
        x = Rep.Matn[CurrentLine - 1].size() + 4;
        Rep.DeleteLine(CurrentLine);
        LineUp();
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    } else {
        Rep.DeleteCharacter(CurrentLine, x - 4 - 1);
        x--;
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    }
}
void Insert(char ch) {
    Rep.AddCharacter(CurrentLine, x - 4, ch);
    x++;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}