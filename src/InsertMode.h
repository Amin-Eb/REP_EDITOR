using namespace std;

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

void Insert::SendKey(int ch, int& CurrentLine, int& x, int& y,
                     Screen& RepScreen, Editor& Rep) {
    if (ch == 10) {
        Enter(CurrentLine, x, y, RepScreen, Rep);
        return;
    }
    if (ch == 0) {
        BackSpace(CurrentLine, x, y, RepScreen, Rep);
        return;
    }
    NewChar((char)(ch), CurrentLine, x, y, RepScreen, Rep);
    if (ch == '{')
        Rep.Ident[CurrentLine] ++;
    if (ch == '}')
        Rep.Ident[CurrentLine] --;

    // :()
}

void Insert::NewChar(char ch, int& CurrentLine, int& x, int& y,
                     Screen& RepScreen, Editor& Rep) {
    Rep.AddCharacter(CurrentLine, x - 4, ch);
    x++;
    RepScreen.PrintLine(y, CurrentLine + 1, Rep.Matn[CurrentLine]);
    move(y, x);
}

void Insert::LineDown(int& CurrentLine, int& x, int& y, Screen& RepScreen,
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

void Insert::LineUp(int& CurrentLine, int& x, int& y, Screen& RepScreen,
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

void Insert::Enter(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                   Editor& Rep) {
    string TemperoryString = "";
    Rep.Ident[CurrentLine + 1] = Rep.Ident[CurrentLine];
    for (int i = 0; i < Rep.Ident[CurrentLine]; i ++)
        TemperoryString += " ";
    Rep.AddLine(CurrentLine + 1, TemperoryString);
    if (x == 4) {
        Rep.Matn[CurrentLine + 1] = Rep.Matn[CurrentLine];
        Rep.Matn[CurrentLine] = "";
    } else {
        for (int i = x - 4; i < Rep.Matn[CurrentLine].size(); i++)
            Rep.Matn[CurrentLine + 1] += Rep.Matn[CurrentLine][i];
        TemperoryString = "";
        for (int i = 0; i < x - 4; i++)
            TemperoryString += Rep.Matn[CurrentLine][i];
        Rep.Matn[CurrentLine] = TemperoryString;
        x = 4;
    }
    LineDown(CurrentLine, x, y, RepScreen, Rep);
    RepScreen.PrintScr(Rep);
    RepScreen.Move(y, x);
}

void Insert::BackSpace(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                       Editor& Rep) {
    if (x == 4) {
        if (y == 0)
            return;
        Rep.Matn[CurrentLine - 1] += Rep.Matn[CurrentLine];
        x = Rep.Matn[CurrentLine - 1].size() + 4;
        Rep.DeleteLine(CurrentLine);
        LineUp(CurrentLine, x, y, RepScreen, Rep);
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    } else {
        Rep.DeleteCharacter(CurrentLine, x - 4 - 1);
        x--;
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    }
}
