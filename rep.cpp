#include <ncurses.h>
#include <span>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include "src/Editor.h"
#include "src/Screen.h"
#include "src/File.h"

using namespace std;

void LineUp(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep);
void LineDown(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep);
void Right(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep);
void Left(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep);
void Home(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep);
void PageUp(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep);
void PageDown(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep);
void EndPage(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep);
void Enter(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep);
void BackSpace(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep);
void Insert(char ch,int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep);

int main(int argc, char** argv) {

    auto args = std::span(argv, size_t(argc));

    int ch = 0;
    int y = 0, x = 4;
    int CurrentLine = 0;
    const int Enter_Key = 10;

    Screen RepScreen;
    RepScreen.Init();
    File RepFile(args[1]);
    Editor Rep;

    if (RepFile.Open(args[1], Rep) == false) {

        Rep.AddLine(0, " ");
    }
    RepScreen.TheEnd = min(RepScreen.TheEnd, Rep.LN - 1);
    RepScreen.PrintScr(Rep);
    move(0, 4);

    while (ch != KEY_SEND) {
        ch = getch();
        if (ch == KEY_DOWN) {
            LineDown(CurrentLine, x, y, RepScreen, RepFile, Rep);
            continue;
        }
        if (ch == KEY_UP) {
            LineUp(CurrentLine, x, y, RepScreen, RepFile, Rep);
            continue;
        }
        if (ch == KEY_LEFT) {
            Left(CurrentLine, x, y, RepScreen, RepFile, Rep);
            continue;
        }
        if (ch == KEY_RIGHT) {
            Right(CurrentLine, x, y, RepScreen, RepFile, Rep);
            continue;
        }
        if (ch == KEY_HOME) {
            Home(CurrentLine, x, y, RepScreen, RepFile, Rep);
            continue;
        }
        if (ch == KEY_NPAGE) {
            PageDown(CurrentLine, x, y, RepScreen, RepFile, Rep);
            continue;
        }
        if (ch == KEY_PPAGE) {
            PageUp(CurrentLine, x, y, RepScreen, RepFile, Rep);
            continue;
        }
        if (ch == KEY_END) {
            EndPage(CurrentLine, x, y, RepScreen, RepFile, Rep);
            continue;
        }
        if (ch == Enter_Key) {    //Enter
            Enter(CurrentLine, x, y, RepScreen, RepFile, Rep);
            continue;
        }
        if (ch == KEY_BACKSPACE) {
            BackSpace(CurrentLine, x, y, RepScreen, RepFile, Rep);
            continue;
        }
        if (ch == KEY_SHOME) {
            RepFile.Save(Rep, RepScreen, true);
            continue;
        }
        Insert((char)(ch),CurrentLine, x, y, RepScreen, RepFile, Rep);
        refresh();
    }
    RepScreen.EndScr();
    exit(0);
}


void LineUp(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep) {
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
void LineDown(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep) {
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
void Right(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep) {
    int _COLS = min((int)(Rep.Matn[CurrentLine].size()) + 4, RepScreen.row - 1);
    if (x < _COLS)
        x++;
    RepScreen.Move(y, x);
}
void Left(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep) {
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
            LineUp(CurrentLine, x, y, RepScreen, RepFile, Rep);
        }
    }
}
void Home(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep) {
    RepScreen.TheStart = 0;
    RepScreen.TheEnd = min(Rep.LN - 1, RepScreen.col - 1);
    RepScreen.PrintScr(Rep);
    x = 4, y = 0;
    CurrentLine = 0;
    RepScreen.Move(y, x);
}
void PageUp(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep) {
    RepScreen.TheStart = max(0, RepScreen.TheStart - RepScreen.col);
    RepScreen.TheEnd = min(Rep.LN - 1, RepScreen.TheStart + RepScreen.col - 1);
    CurrentLine = RepScreen.TheStart;
    x = 4, y = 0;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}
void PageDown(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep) {
    RepScreen.TheEnd = min(Rep.LN - 1, RepScreen.TheEnd + RepScreen.col);
    RepScreen.TheStart = max(0, RepScreen.TheEnd - RepScreen.col + 1);
    CurrentLine = RepScreen.TheStart;
    x = 4, y = 0;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}
void EndPage(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep) {
    RepScreen.TheEnd = Rep.LN - 1;
    RepScreen.TheStart = max(0, RepScreen.TheEnd - RepScreen.col + 1);
    CurrentLine = Rep.LN - 1;
    RepScreen.PrintScr(Rep);
    y = RepScreen.col;
    x = Rep.Matn[Rep.LN - 1].size() + 4;
    RepScreen.Move(y, x);
}
void Enter(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep) {
    Rep.AddLine(CurrentLine + 1, "");
    if (x == 4) {
        Rep.Matn[CurrentLine + 1] = Rep.Matn[CurrentLine];
        Rep.Matn[CurrentLine] = "";
    } else {
        for (int i = x - 4; i < Rep.Matn[CurrentLine].size(); i++)
            Rep.Matn[CurrentLine + 1] += Rep.Matn[CurrentLine][i];
        std::string TemperoryString("");
        for (int i = 0; i < x - 4; i++)
            TemperoryString += Rep.Matn[CurrentLine][i];
        Rep.Matn[CurrentLine] = TemperoryString;
        x = 4;
    }
    LineDown(CurrentLine, x, y, RepScreen, RepFile, Rep);
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}
void BackSpace(int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep) {
    if (x == 4) {
        if (y == 0)
            return;
        Rep.Matn[CurrentLine - 1] += Rep.Matn[CurrentLine];
        x = Rep.Matn[CurrentLine - 1].size() + 4;
        Rep.DeleteLine(CurrentLine);
        LineUp(CurrentLine, x, y, RepScreen, RepFile, Rep);
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    } else {
        Rep.DeleteCharacter(CurrentLine, x - 4 - 1);
        x--;
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    }
}
void Insert(char ch,int& CurrentLine,int& x,int& y,Screen& RepScreen,File& RepFile,Editor& Rep) {
    Rep.AddCharacter(CurrentLine, x - 4, ch);
    x++;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}