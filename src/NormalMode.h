#ifndef REP_NORMALMODE_H
#define REP_NORMALMODE_H

#include "coreinc.h"
#include "Screen.h"
#include "Editor.h"

class Normal {
   public:
    void SendKey(int ch, int& CurrentLine, int& x, int& y, Screen& RepScreen,
                 Editor& Rep);

   private:
    void LineUp(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep);
    void LineDown(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                  Editor& Rep);
    void Right(int& CurrentLine, int& x, int& y, Screen& RepScreen,
               Editor& Rep);
    void Left(int& CurrentLine, int& x, int& y, Screen& RepScreen, Editor& Rep);
    void Home(int& CurrentLine, int& x, int& y, Screen& RepScreen, Editor& Rep);
    void PageUp(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep);
    void PageDown(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                  Editor& Rep);
    void EndPage(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                 Editor& Rep);
    void Enter(int& CurrentLine, int& x, int& y, Screen& RepScreen,
               Editor& Rep);
};

#endif
