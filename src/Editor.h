using namespace std;

class Editor {
    public:
        int LN = 0;
        int TheStart = 0;
        int TheEnd = 0;
        string matn[1000];
        void AddLine(int Line);
        void AddCharacter(int Line,int Position,char Character);
        void DeleteLine(int Line,string Str);
        void DeleteCharacter(int Line,int Position);
};

void Editor::AddLine(int Line, string Str){
    for (int i = LN; i > Line ; i--)
        matn[i] = matn[i - 1];
    matn[Line] = Str;
    LN ++;
}

void Editor::AddCharacter(int Line,int Position,char Character){
    string TemperoryString = "";
    for(int i = 0; i < Position; i ++) 
        TemperoryString += matn[Line][i];
    TemperoryString += Character;
    for(int i = Position; i < matn[Line].size(); i ++) 
        TemperoryString += matn[Line][i];
    matn[Line] = TemperoryString;
}

void Editor::DeleteLine(int Line){
    for(int i = Line; i < LN; i ++)
        matn[i] = matn[i + 1];
    LN --;          
}

void Editor::DeleteCharacter(int Line,int Position){
    string TemperoryString = "";
    for(int i = 0; i < Position; i ++)
        TemperoryString += matn[Line][i];
    for(int i = Position + 1; i < matn[Line].size(); i ++)
        TemperoryString += matn[Line][i];
    matn[Line] = TemperoryString;
}