#include "src/coreinc.h"
#include "src/ColorScheme.h"
#include "src/Syntax.h"
#include "src/Editor.h"
#include "src/Screen.h"
#include "src/File.h"
#include "src/NormalMode.h"
#include "src/InsertMode.h"


using namespace std;
using json = nlohmann::json;

int main(int argc, char** argv) {
    vector<std::string> args(argv, argv + argc);   
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

    if (RepFile.Open(args[1], Rep) == false) {
        Rep.AddLine(0, "");
    }
    
    RepScreen.RepSyntax.Build(Rep.Matn, Rep.LN);
    RepScreen.PrintScr(Rep);
    move(0, 4);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    
    while (ch != KEY_SEND) {
        ch = getch();
        if(mode == 2){
            RepScreen.PrintScr(Rep);
            move(y, x);
            mode = 0;
            continue;
        }
        if(ch == KEY_MOUSE) {
            if(getmouse(&event) == OK){
                auto TimeStart = chrono::high_resolution_clock::now();
                if(event.bstate == 65536)
                    RepNormal.SendKey(1, CurrentLine, x, y, RepScreen, Rep);
                if(event.bstate == 2097152)
                    RepNormal.SendKey(2, CurrentLine, x, y, RepScreen, Rep);
                if(event.bstate & BUTTON1_PRESSED){
                    ch = getch();
                    y2 = event.y;
                    x2 = event.x;
                    CurrentLine = RepScreen.TheStart + y2;
                    if(event.x < 4)
                        x2 = 4;
                    if(event.x > Rep.Matn[CurrentLine].size() + 4)
                        x2 = Rep.Matn[CurrentLine].size() + 4;
                    while(true){
                        if(getmouse(&event) == OK){
                            if(event.bstate & BUTTON1_RELEASED){  
                                auto TimeEnd = chrono::high_resolution_clock::now();
                                auto ElapsedTime = chrono::duration<double, std::milli>(TimeEnd - TimeStart).count();
                                if(ElapsedTime < 200){
                                    y = event.y;
                                    x = event.x;
                                    CurrentLine = RepScreen.TheStart + y;
                                    if(event.x < 4)
                                        x = 4;
                                    if(event.x > Rep.Matn[CurrentLine].size() + 4)
                                        x = Rep.Matn[CurrentLine].size() + 4;
                                    move(28, 0);
                                    move(y, x);
                                    refresh();
                                    break;
                                }
                                else{
                                    mode = 2;
                                    y = event.y;
                                    x = event.x;
                                    int TCurrentLine = RepScreen.TheStart + y;
                                    if(event.x < 4)
                                        x = 4;
                                    if(event.x > Rep.Matn[TCurrentLine].size() + 4)
                                        x = Rep.Matn[TCurrentLine].size() + 4;
                                    RepScreen.Highlight(y2, CurrentLine,x2 , y2, x, y, Rep);
                                    break;
                                }
                            }
                        }
                    }
                    
                }
                continue;
            }
        }
        if (ch == KEY_ESC) {
            mode = 0;
            RepScreen.PrintScr(Rep);
            RepScreen.PrintMessage(RepScreen.col, 0, "entered normal mode!");      
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
            RepScreen.PrintMessage(RepScreen.col, 0, "entered insert mode!");
            RepScreen.Refresh();
            continue;
        }
        if (mode == 1)
            RepInsert.SendKey(ch, CurrentLine, x, y, RepScreen, Rep);
    }
    RepScreen.EndScr();
    exit(0);
}
