using namespace std;

class Editor {
   public:
    int LN = 0;
    string* Matn = new string[1000];
    void AddLine(int Line, string Str);
    void AddCharacter(int Line, int Position, char Character);
    void DeleteLine(int Line);
    void DeleteCharacter(int Line, int Position);
};

void Editor::AddLine(int Line, string Str) {
    for (int i = LN; i > Line; i--)
        Matn[i] = Matn[i - 1];
    Matn[Line] = Str;
    LN++;
}

void Editor::AddCharacter(int Line, int Position, char Character) {
    std::string TemperoryString("");
    for (int i = 0; i < Position; i++)
        TemperoryString += Matn[Line][i];
    TemperoryString += Character;
    for (int i = Position; i < Matn[Line].size(); i++)
        TemperoryString += Matn[Line][i];
    Matn[Line] = TemperoryString;
}

void Editor::DeleteLine(int Line) {
    for (int i = Line; i < LN; i++)
        Matn[i] = Matn[i + 1];
    LN--;
}

void Editor::DeleteCharacter(int Line, int Position) {
    std::string TemperoryString("");
    for (int i = 0; i < Position; i++)
        TemperoryString += Matn[Line][i];
    for (int i = Position + 1; i < Matn[Line].size(); i++)
        TemperoryString += Matn[Line][i];
    Matn[Line] = TemperoryString;
}