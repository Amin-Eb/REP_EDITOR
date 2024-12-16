#include "InsertMode.h"

using namespace std;

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
        Rep.Ident[CurrentLine] += 4;
    if (ch == '}')
        Rep.Ident[CurrentLine] -= 4;
}

void Insert::NewChar(char ch, int& CurrentLine, int& x, int& y,
                     Screen& RepScreen, Editor& Rep) {
    if(ch == 9){ // supporting Tab key
        for(int i = 0; i < 4; i ++){
            Rep.AddCharacter(CurrentLine, x - 4, ' ');
            RepScreen.RepSyntax.Build(Rep.Matn, Rep.LN);
            x ++;
        }
        RepScreen.PrintLine(y, CurrentLine , Rep.Matn);
        move(y, x);
        return;
    }
    Rep.AddCharacter(CurrentLine, x - 4, ch);
    x++;
    RepScreen.RepSyntax.Build(Rep.Matn, Rep.LN);
    RepScreen.PrintLine(y, CurrentLine, Rep.Matn);
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
            if(x < 4)x = 4;
            CurrentLine++;
            RepScreen.PrintScr(Rep);
            RepScreen.Move(y, x);
        }
    } else {
        y++;
        x = min(x, (int)(Rep.Matn[CurrentLine + 1].size()));
        if(x < 4)x = 4;
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
        if(x < 4)x = 4;
        CurrentLine--;
    } else if (y == 0) {
        if (RepScreen.TheStart > 0) {
            RepScreen.TheStart--;
            RepScreen.TheEnd--;
            x = min(x, (int)(Rep.Matn[CurrentLine - 1].size()));
        if(x < 4)x = 4;
            CurrentLine--;
            RepScreen.PrintScr(Rep);
        }
    }
    RepScreen.Move(y, x);
}

void Insert::Enter(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                   Editor& Rep) {
    string TemperoryString = "";
    for (int i = 0; i < Rep.Ident[CurrentLine]; i ++)
        TemperoryString += " ";


    Rep.AddLine(CurrentLine + 1, TemperoryString);
    for (int i = Rep.LN; i > CurrentLine; i--)
        Rep.Ident[i] = Rep.Ident[i - 1];
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
    }
    RepScreen.RepSyntax.Build(Rep.Matn, Rep.LN);
    LineDown(CurrentLine, x, y, RepScreen, Rep);

}

void Insert::BackSpace(int& CurrentLine, int& x, int& y, Screen& RepScreen,
                       Editor& Rep) {
    if (x == 4) {
        if (CurrentLine == 0){
            return;
        }
        x = Rep.Matn[CurrentLine - 1].size() + 4;
        Rep.Matn[CurrentLine - 1] += Rep.Matn[CurrentLine];
        Rep.DeleteLine(CurrentLine);
        RepScreen.RepSyntax.Build(Rep.Matn, Rep.LN);
        LineUp(CurrentLine, x, y, RepScreen, Rep);
        RepScreen.PrintScr(Rep);
        RepScreen.Move(y, x);
    } else {
        if( Rep.Matn[CurrentLine][x - 4 - 1] == '}')
            Rep.Ident[CurrentLine] += 4;
        if( Rep.Matn[CurrentLine][x - 4 - 1] == '{')
            Rep.Ident[CurrentLine] -= 4;

        Rep.DeleteCharacter(CurrentLine, x - 4 - 1);
        x--;
        RepScreen.RepSyntax.Build(Rep.Matn, Rep.LN);
        RepScreen.PrintLine(y, CurrentLine, Rep.Matn);
        RepScreen.Move(y, x);
    }
}
