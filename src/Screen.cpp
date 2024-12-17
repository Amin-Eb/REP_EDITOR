#include "Screen.h"

using namespace std;

const int TwoDigits = 10;
const int ThreeDigits = 100;

Screen::Screen() {
    initscr();
    noecho();    //   do not show the given characters from input
    cbreak();
    keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
    mouseinterval(0);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    mvchgat(ScreenY, ScreenX, -1, A_BLINK, 1, NULL);
    start_color();
    TheEnd = COLS;
    RepSyntax.ColorMap = Scheme.Build("color.json");
    //number of lines color
    init_pair(1, COLOR_YELLOW, 10);
    //selected mode color
    init_pair(2,0, COLOR_WHITE);
    //default text color
    init_pair(3, 11 , 10);
    //highlighted tesxt color
    init_pair(4, 11, 12);
    bkgd(COLOR_PAIR(3));
    refresh();
}

void Screen::Refresh() {
    refresh();
}

void Screen::Init() {
    row = COLS;
    col = LINES - 1;
    TheEnd = LINES - 2;
    for(int i = 5; i < row; i ++) EmptyLine += " ";
}

void Screen::PrintScr(Editor Edit) {
    clear();
    RepSyntax.PrintScr(TheStart, TheEnd, Edit.Matn);
}

void Screen::PrintLine(int ScreenLine, int LineNumber,string Str[]) {
    move(ScreenLine, 4);
    printw("%s", EmptyLine.c_str());
    RepSyntax.PrintLine(LineNumber, ScreenLine, Str);
}

void Screen::PrintMessage(int ScreenLine, int LineNumber, string Str){
    move(ScreenLine, 0);
    attron(COLOR_PAIR(1));
    if (LineNumber < TwoDigits)
        printw("%c", ' ');
    if (LineNumber < ThreeDigits)
        printw("%c", ' ');
    printw("%d ", LineNumber);
    attroff(COLOR_PAIR(1));
    //for(int i = 0; i < row - Str.size(); i ++) Str += " ";
    printw("%s", Str.c_str());
    refresh();
}

void Screen::PrintChar(int ScreenLine, int Position, char Character) {
    move(ScreenLine, Position);
    printw("%c", Character);
    move(ScreenY, ScreenX);
}

void Screen::EndScr() {
    endwin();
}

void Screen::Move(int y, int x) {
    move(y, x); 
}

string Screen::Highlight(int ScreenLine, int& CurrentLine, int& x, int& y, int& x2, int& y2, Editor& Rep){
    //printw("few %d %d %d %d %d few",x, y, x2, y2, CurrentLine);
    attron(COLOR_PAIR(4));
    string RetString("");
    int yConst = y, Tmj = 0;
    for(int i = y; i <= y2; i ++, CurrentLine ++, ScreenLine ++){
        for(int j = (i == yConst? x:4); j <= (i == y2? x2 : Rep.Matn[CurrentLine].size()+3); j ++){
            move(ScreenLine, j);
            RetString += Rep.Matn[CurrentLine][j - 4];
            printw("%c", Rep.Matn[CurrentLine][j - 4]);
            Tmj = j;
        }
        RetString += '\n';
    }
    move(ScreenLine - 1, Tmj);
    CurrentLine --;
    attroff(COLOR_PAIR(4));
    return RetString;
}
