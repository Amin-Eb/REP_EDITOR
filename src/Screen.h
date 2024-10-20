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
};

void Screen::Init() {
    row = COLS;
    col = LINES - 1;
    TheEnd = LINES - 2;
}
void Screen::PrintScr(Editor Edit) {
    clear();
    for (int i = TheStart, j = 0; i <= TheEnd; i++ , j ++) {
        move(j, 0);
        init_pair(1, COLOR_YELLOW, 0);
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
    init_pair(1, COLOR_YELLOW, 0);
    attron(COLOR_PAIR(1));
    if (LineNumber < TwoDigits)
        printw("%c", ' ');
    if (LineNumber < ThreeDigits)
        printw("%c", ' ');
    printw("%d ", LineNumber);
    attroff(COLOR_PAIR(1));
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