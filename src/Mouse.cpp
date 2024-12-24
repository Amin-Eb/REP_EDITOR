#include "Mouse.h"
using namespace std;

void Mouse::Press(int& x,int& y,int& x2,int& y2,int& CurrentLine,Screen& RepScreen,Editor& Rep,int &mode,Normal& RepNormal){
    if(getmouse(&event) == OK){
        auto TimeStart = chrono::high_resolution_clock::now();
        if(event.bstate == 65536)
            RepNormal.SendKey(1, CurrentLine, x, y, RepScreen, Rep);
        if(event.bstate == 2097152)
            RepNormal.SendKey(2, CurrentLine, x, y, RepScreen, Rep);
        if(event.bstate & BUTTON1_PRESSED){
            char ch = getch();
            y2 = event.y;
            x2 = event.x;
            CurrentLine = RepScreen.TheStart + y2;
            if(event.y >= Rep.LN){
                x2 = Rep.Matn[Rep.LN - 1].size() + 4;
                y2 = Rep.LN - 1;
                CurrentLine = Rep.LN - 1;
            }
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
                            if(event.y >= Rep.LN){
                                x = Rep.Matn[Rep.LN - 1].size() + 4;
                                y = Rep.LN - 1;
                                CurrentLine = Rep.LN - 1;
                            }
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
                            if(event.y >= Rep.LN){
                                x = Rep.Matn[Rep.LN - 1].size() + 4;
                                y = Rep.LN - 1;
                                CurrentLine = Rep.LN - 1;
                                return;
                            }
                            RepScreen.Highlight(y2, CurrentLine,x2 , y2, x, y, Rep);
                            break;
                        }
                    }
                }
            }
            
        }
        return;
    }
}