using namespace std;

const int TwoDigits = 10;

const int ThreeDigits = 100;
class Screen {
   public:
    int row = 0, col = 0;
    int TheStart = 0, TheEnd = 0;
    int ScreenX = 0, ScreenY = 0;
    Screen() {
        initscr();
        noecho();    //   do not show the given characters from input
        cbreak();
        keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
        mvchgat(ScreenY, ScreenX, -1, A_BLINK, 1, NULL);
        start_color();
        refresh();
    }
    void Init();
    void PrintScr(Editor Edit);
    void PrintLine(int ScreenLine, int LineNumber, string Str);
    void PrintChar(int ScreenLine, int Position, char Character);
    void EndScr();
    void Move(int y, int x);
    void Refresh();
    void Normal(int ScreenLine, int& LineNumber, int& x, int& y, int& x2, int& y2, Editor& Rep);
    string Highlight(int ScreenLine, int& LineNumber, int& x, int& y, int& x2, int& y2, Editor& Rep);
};

void Screen::Refresh() {
    refresh();
}
void Screen::Init() {
    row = COLS;
    col = LINES - 1;
    TheEnd = LINES - 2;
}
void Screen::PrintScr(Editor Edit) {
    clear();
    for (int i = TheStart, j = 0; i <= TheEnd; i++, j++) {
        move(j, 0);
        attron(COLOR_PAIR(1));
        if (i + 1 < TwoDigits)
            printw("%c", ' ');
        if (i + 1 < ThreeDigits)
            printw("%c", ' ');
        printw("%d ", i + 1);
        attroff(COLOR_PAIR(1));
        printw("%s", Edit.Matn[i].c_str());
    }
    refresh();
}

void Screen::PrintLine(int ScreenLine, int LineNumber, string Str) {
    move(ScreenLine, 0);
    attron(COLOR_PAIR(1));
    if (LineNumber < TwoDigits)
        printw("%c", ' ');
    if (LineNumber < ThreeDigits)
        printw("%c", ' ');
    printw("%d ", LineNumber);
    attroff(COLOR_PAIR(1));
    for(int i = 0; i < row - Str.size(); i ++) Str += " ";
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
    attron(COLOR_PAIR(2));
    string RetString("");
    int yConst = y;
    for(int i = y; i <= y2; i ++, CurrentLine ++, ScreenLine ++){
        for(int j = (i == yConst? x:4); j <= (i == y2? x2 : Rep.Matn[CurrentLine].size()+3); j ++){
            move(ScreenLine, j);
            RetString += Rep.Matn[CurrentLine][j - 4];
            printw("%c", Rep.Matn[CurrentLine][j - 4]);
        }
        RetString += '\n';
    }
    CurrentLine --;
    attroff(COLOR_PAIR(2));
    return RetString;
}
