#include <ncurses.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <span>
#include <string>
#include "src/Editor.h"
#include "src/Screen.h"
#include "src/File.h"
#include "src/NormalMode.h"
#include "src/InsertMode.h"

using namespace std;

void LineUp(int& CurrentLine, int& x, int& y, Screen& RepScreen, File& RepFile,
            Editor& Rep);
void LineDown(int& CurrentLine, int& x, int& y, Screen& RepScreen,
              File& RepFile, Editor& Rep);
void Right(int& CurrentLine, int& x, int& y, Screen& RepScreen, File& RepFile,
           Editor& Rep);
void Left(int& CurrentLine, int& x, int& y, Screen& RepScreen, File& RepFile,
          Editor& Rep);
void Home(int& CurrentLine, int& x, int& y, Screen& RepScreen, File& RepFile,
          Editor& Rep);
void PageUp(int& CurrentLine, int& x, int& y, Screen& RepScreen, File& RepFile,
            Editor& Rep);
void PageDown(int& CurrentLine, int& x, int& y, Screen& RepScreen,
              File& RepFile, Editor& Rep);
void EndPage(int& CurrentLine, int& x, int& y, Screen& RepScreen, File& RepFile,
             Editor& Rep);
void Enter(int& CurrentLine, int& x, int& y, Screen& RepScreen, File& RepFile,
           Editor& Rep);
void BackSpace(int& CurrentLine, int& x, int& y, Screen& RepScreen,
               File& RepFile, Editor& Rep);

int main(int argc, char** argv) {
    auto args = std::span(argv, size_t(argc));
    int mode = 0;
    int ch = 0;
    int y = 0, x = 4;
    int CurrentLine = 0;
    const int Enter_Key = 10;
    const int KEY_ESC = 27;

    Screen RepScreen;
    RepScreen.Init();
    File RepFile(args[1]);
    Editor Rep;
    Normal RepNormal;
    Insert RepInsert;

    if (RepFile.Open(args[1], Rep) == false) {

        Rep.AddLine(0, " ");
    }
    RepScreen.TheEnd = min(RepScreen.TheEnd, Rep.LN - 1);
    RepScreen.PrintScr(Rep);
    move(0, 4);

    while (ch != KEY_SEND) {
        ch = getch();
        if (ch == KEY_ESC) {
            mode = 0;
            RepScreen.PrintLine(RepScreen.col, 0, "entered normal mode!");
            RepScreen.Refresh();
            continue;
        }
        if (ch == KEY_DOWN) {
            if (mode == 0 || mode == 1)
                RepNormal.SendKey(2, CurrentLine, x, y, RepScreen, Rep);
            continue;
        }
        if (ch == KEY_UP) {
            if (mode == 0 || mode == 1)
                RepNormal.SendKey(1, CurrentLine, x, y, RepScreen, Rep);
            continue;
        }
        if (ch == KEY_LEFT) {
            if (mode == 0 || mode == 1)
                RepNormal.SendKey(4, CurrentLine, x, y, RepScreen, Rep);
            continue;
        }
        if (ch == KEY_RIGHT) {
            if (mode == 0 || mode == 1)
                RepNormal.SendKey(3, CurrentLine, x, y, RepScreen, Rep);
            continue;
        }
        if (ch == KEY_HOME) {
            if (mode == 0 || mode == 1)
                RepNormal.SendKey(5, CurrentLine, x, y, RepScreen, Rep);
            continue;
        }
        if (ch == KEY_NPAGE) {
            if (mode == 0 || mode == 1)
                RepNormal.SendKey(7, CurrentLine, x, y, RepScreen, Rep);
            continue;
        }
        if (ch == KEY_PPAGE) {
            if (mode == 0 || mode == 1)
                RepNormal.SendKey(6, CurrentLine, x, y, RepScreen, Rep);
            continue;
        }
        if (ch == KEY_END) {
            if (mode == 0 || mode == 1)
                RepNormal.SendKey(8, CurrentLine, x, y, RepScreen, Rep);
            continue;
        }
        if (ch == Enter_Key) {
            if (mode == 0)
                RepNormal.SendKey(9, CurrentLine, x, y, RepScreen, Rep);
            if (mode == 1)
                RepInsert.SendKey(10, CurrentLine, x, y, RepScreen, Rep);
            continue;
        }
        if (ch == KEY_BACKSPACE) {
            if (mode == 0)
                RepNormal.SendKey(4, CurrentLine, x, y, RepScreen, Rep);
            if (mode == 1)
                RepInsert.SendKey(0, CurrentLine, x, y, RepScreen, Rep);
            continue;
        }
        if (ch == KEY_SHOME) {
            RepFile.Save(Rep, RepScreen, true);
            continue;
        }
        if (mode == 0 && (char)(ch) == 'i') {
            mode = 1;
            RepScreen.PrintLine(RepScreen.col, 0, "entered insert mode!");
            RepScreen.Refresh();
            continue;
        }
        if (mode == 1)
            RepInsert.SendKey(ch, CurrentLine, x, y, RepScreen, Rep);
    }
    RepScreen.EndScr();
    exit(0);
    exit(0);
}

//testing new branch actions 2