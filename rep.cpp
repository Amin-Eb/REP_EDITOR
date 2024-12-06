#include <ncurses.h>
#include <cstring>
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
#include "src/ClipBoard.h"

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
    // 0 normal /1 insert /2 selected
    int mode = 0;
    int ch = 0;
    int y = 0, x = 4;
    int y2, x2;
    int CurrentLine = 0;
    string SelectedString;
    const int Enter_Key = 10;
    const int KEY_ESC = 27;
    MEVENT event;

    Screen RepScreen;
    RepScreen.Init();
    File RepFile(args[1]);
    Editor Rep;
    Normal RepNormal;
    Insert RepInsert;
    ClipBoard RepClip;
    init_pair(1, COLOR_YELLOW, 0);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    if (RepFile.Open(args[1], Rep) == false) {
        Rep.AddLine(0, "");
    }

    RepScreen.TheEnd = min(RepScreen.TheEnd, Rep.LN - 1);
    RepScreen.PrintScr(Rep);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    while (ch != KEY_SEND) {
        ch = getch();
        if(mode == 2){
            if(ch == 'y'){
                continue;
            }
            if(ch == 'd'){
                continue;
            }
            RepScreen.PrintScr(Rep);
            mode = 0;
        }
        if(ch == KEY_MOUSE) {
            if(getmouse(&event) == OK){
                if(event.bstate == 65536)
                    RepNormal.SendKey(1, CurrentLine, x, y, RepScreen, Rep);
                if(event.bstate == 2097152)
                    RepNormal.SendKey(2, CurrentLine, x, y, RepScreen, Rep);
                if(event.bstate & BUTTON1_CLICKED){
                    if(event.x < 4)
                        event.x = 4;
                    if(event.x > Rep.Matn[CurrentLine].size() + 4)
                        event.x = Rep.Matn[CurrentLine].size() + 4;
                    move(event.y, event.x);
                    y = event.y;
                    x = event.x;
                    refresh();
                    CurrentLine = RepScreen.TheStart + event.y;
                    continue;
                }
                if(event.bstate & BUTTON1_PRESSED){
                    if(event.x < 4 || event.x > Rep.Matn[CurrentLine].size() + 4)
                        continue;
                    ch = getch();
                    y2 = event.y;
                    x2 = event.x;
                    CurrentLine = RepScreen.TheStart + event.y;
                    while(true){
                        if(getmouse(&event) == OK){
                            if(event.bstate & BUTTON1_RELEASED){  
                                y = event.y;
                                x = event.x;
                                RepScreen.Highlight(y2, CurrentLine,x2 , y2, x, y, Rep);
                                break;
                            }
                        }
                    }
                    mode = 2;
                }
                continue;
            }
        }
        if (ch == KEY_ESC) {
            mode = 0;
            RepScreen.PrintScr(Rep);
            RepScreen.PrintLine(RepScreen.col, 0, "entered normal mode!");      
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
}
