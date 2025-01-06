#ifndef REP_NORMALMODE_H
#define REP_NORMALMODE_H

#include "coreinc.h"
#include "Screen.h"
#include "Editor.h"

class Normal {
   public:
    void SendKey(int ch, int& CurrentLine, int& x, int& y, Screen& RepScreen,
                   Editor& Rep);
                 
    virtual void LineUp(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep);
    virtual void LineDown(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                  Editor& Rep);
    virtual void Right(int& CurrentLine, int& x, int& y, Screen& RepScreen,
               Editor& Rep);
    virtual void Left(int& CurrentLine, int& x, int& y, Screen& RepScreen, Editor& Rep);
    virtual void Home(int& CurrentLine, int& x, int& y, Screen& RepScreen, Editor& Rep);
    virtual void PageUp(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep);
    virtual void PageDown(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                  Editor& Rep);
    virtual void EndPage(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                 Editor& Rep);
    virtual void Enter(int& CurrentLine, int& x, int& y, Screen& RepScreen,
               Editor& Rep);
};

#endif
