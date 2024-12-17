#ifndef REP_SCREEN_H
#define REP_SCREEN_H
#include "coreinc.h"
#include "ColorScheme.h"
#include "Syntax.h"
#include "Editor.h"

class Screen {
   public:
    Syntax RepSyntax;
    ColorScheme Scheme;
    int row = 0, col = 0;
    int TheStart = 0, TheEnd = 0;
    int ScreenX = 0, ScreenY = 0;
	std::string EmptyLine = "";
    Screen();
    void Init();
    void PrintScr(Editor Edit);
    void PrintLine(int ScreenLine, int LineNumber, std::string Str[]);
    void PrintChar(int ScreenLine, int Position, char Character);
    void EndScr();
    void Move(int y, int x);
    void Refresh();
    void Normal(int ScreenLine, int& LineNumber, int& x, int& y, int& x2, int& y2, Editor& Rep);
    void PrintMessage(int ScreenLine, int LineNumber, std::string Str);
    std::string Highlight(int ScreenLine, int& LineNumber, int& x, int& y, int& x2, int& y2, Editor& Rep);
};
#endif
