#ifndef REP_INSERTMODE_H
#define REP_INSERTMODE_H

#include "Screen.h"
#include "Editor.h"

class Insert {
	public:
		void SendKey(int ch, int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);
		virtual void Enter(int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);	
		virtual void BackSpace(int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);
		virtual void NewChar(char ch, int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);
		virtual void LineDown(int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);
		virtual void LineUp(int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);
};

#endif
