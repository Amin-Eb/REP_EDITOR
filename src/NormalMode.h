using namespace std;

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

void Normal::SendKey(int ch, int& CurrentLine, int& x, int& y,
                     Screen& RepScreen, Editor& Rep) {
    if (ch == 1)
        LineUp(CurrentLine, x, y, RepScreen, Rep);
    if (ch == 2)
        LineDown(CurrentLine, x, y, RepScreen, Rep);
    if (ch == 3)
        Right(CurrentLine, x, y, RepScreen, Rep);
    if (ch == 4)
        Left(CurrentLine, x, y, RepScreen, Rep);
    if (ch == 5)
        Home(CurrentLine, x, y, RepScreen, Rep);
    if (ch == 6)
        PageUp(CurrentLine, x, y, RepScreen, Rep);
    if (ch == 7)
        PageDown(CurrentLine, x, y, RepScreen, Rep);
    if (ch == 8)
        EndPage(CurrentLine, x, y, RepScreen, Rep);
    if (ch == 9)
        Enter(CurrentLine, x, y, RepScreen, Rep);
}

void Normal::LineUp(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                    Editor& Rep) {
    if (y > 0) {
        y--;
        x = min(x, (int)(Rep.Matn[CurrentLine - 1].size()));
        x += 4;
        CurrentLine--;
    } else if (y == 0) {
        if (Rep.LN - 1 > RepScreen.col && RepScreen.TheStart > 0) {
            RepScreen.TheStart--;
            RepScreen.TheEnd--;
            x = min(x, (int)(Rep.Matn[CurrentLine - 1].size()));
            x += 4;
            CurrentLine--;
            RepScreen.PrintScr(Rep);
        }
    }
    RepScreen.Move(y, x);
}

void Normal::LineDown(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                      Editor& Rep) {
    if (y == Rep.LN - 1)
        return;
    if (y == RepScreen.col - 1) {
        if (RepScreen.TheEnd < Rep.LN - 1) {
            RepScreen.TheStart++;
            RepScreen.TheEnd++;
            x = min(x, (int)(Rep.Matn[CurrentLine + 1].size()));
            x += 4;
            CurrentLine++;
            RepScreen.PrintScr(Rep);
            RepScreen.Move(y, x);
        }
    } else {
        if (Rep.LN - 1 < RepScreen.col - 1 && y == Rep.LN - 2)
            RepScreen.TheEnd++;
        y++;
        x = min(x, (int)(Rep.Matn[CurrentLine + 1].size()));
        x += 4;
        CurrentLine++;
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    }
}

void Normal::Right(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                   Editor& Rep) {
    int _COLS = min((int)(Rep.Matn[CurrentLine].size()) + 4, RepScreen.row - 1);
    if (x < _COLS)
        x++;
    RepScreen.Move(y, x);
}

void Normal::Left(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                  Editor& Rep) {
    if (x > 4)
        x--, RepScreen.Move(y, x);
    else {
        if (y > 0) {
            x = Rep.Matn[CurrentLine - 1].size() + 4;
            y--;
            CurrentLine--;
            RepScreen.Move(y, x);
        } else {
            if (RepScreen.TheStart == 0)
                return;
            x = RepScreen.row - 1;
            LineUp(CurrentLine, x, y, RepScreen, Rep);
        }
    }
}

void Normal::Home(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                  Editor& Rep) {
    RepScreen.TheStart = 0;
    RepScreen.TheEnd = min(Rep.LN - 1, RepScreen.col - 1);
    RepScreen.PrintScr(Rep);
    x = 4, y = 0;
    CurrentLine = 0;
    RepScreen.Move(y, x);
}

void Normal::PageUp(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                    Editor& Rep) {
    RepScreen.TheStart = max(0, RepScreen.TheStart - RepScreen.col);
    RepScreen.TheEnd = min(Rep.LN - 1, RepScreen.TheStart + RepScreen.col - 1);
    CurrentLine = RepScreen.TheStart;
    x = 4, y = 0;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}

void Normal::PageDown(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                      Editor& Rep) {
    RepScreen.TheEnd = min(Rep.LN - 1, RepScreen.TheEnd + RepScreen.col);
    RepScreen.TheStart = max(0, RepScreen.TheEnd - RepScreen.col + 1);
    CurrentLine = RepScreen.TheStart;
    x = 4, y = 0;
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}

void Normal::EndPage(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                     Editor& Rep) {
    RepScreen.TheEnd = Rep.LN - 1;
    RepScreen.TheStart = max(0, RepScreen.TheEnd - RepScreen.col + 1);
    CurrentLine = Rep.LN - 1;
    RepScreen.PrintScr(Rep);
    y = RepScreen.col - 1;
    x = Rep.Matn[Rep.LN - 1].size() + 4;
    RepScreen.Move(y, x);
}

void Normal::Enter(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                   Editor& Rep) {
    LineDown(CurrentLine, x, y, RepScreen, Rep);
    x = 4;
    move(y, x);
}

//test comment