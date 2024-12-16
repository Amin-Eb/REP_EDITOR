#ifndef REP_INSERTMODE_H
#define REP_INSERTMODE_H

#include "Screen.h"
#include "Editor.h"

class Insert {
	public:
		void SendKey(int ch, int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);
	private:
		void Enter(int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);
		void BackSpace(int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);
		void NewChar(char ch, int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);
		void LineDown(int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);
		void LineUp(int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep);
};

#endif
