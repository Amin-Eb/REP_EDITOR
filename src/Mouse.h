#ifndef REP_MOUSE_H
#define REP_MOUSE_H
#include "coreinc.h"
#include "Screen.h"
#include "Editor.h"
#include "NormalMode.h"

using namespace std;

class Mouse{
    public:
      MEVENT event;
      void Press(int& x,int& y,int& x2,int& y2,int& CurrentLine,Screen& RepScreen,Editor& Rep,int& mode, Normal& RepNormal);
};

#endif