using namespace std;

class Screen {
    public:
        int row, col;
        int TheStart = 0, TheEnd = 0;
        int ScreenX = 0, ScreenY = 0;
        Screen(){
            initscr();
            noecho();    //   do not show the given characters from input
            cbreak();
            keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
            row = COLS;
            col = LINES;
            TheStart = 0;
            TheEnd = LINES - 1;
            ScreenX = 0;
            ScreenY = 0;
            mvchgat(ScreenY, ScreenX, -1, A_BLINK, 1, NULL);
            refresh();

        }
        void PrintScr(Editor Edit);
        void PrintLine(int ScreenLine,string Str);
        void PrintChar(int ScreenLine,int Position,char Character);
        void EndScr();
        void Move(int y,int x);
};

void Screen::PrintScr(Editor Edit){
    clear();
    for (int i = TheStart; i <= TheEnd; i++)
        printw("%s\n", Edit.Matn[i].c_str());
    move(0,0);
    refresh();
}

void Screen::PrintLine(int ScreenLine,string Str){
    move(ScreenLine, 0);
    printw("%s", Str.c_str());
    move(ScreenY, ScreenX);
}

void Screen::PrintChar(int ScreenLine,int Position,char Character){
    move(ScreenLine, Position);
    printw("%c", Character);
    move(ScreenY, ScreenX);
}

void Screen::EndScr(){
    endwin();
}

void Screen::Move(int y,int x){
    move(y, x);
}