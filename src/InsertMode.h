using namespace std;

class Insert{
    public:
        void SendKey(int ch,int& CurrentLine,int& x,int& y,Screen& RepScreen, Editor& Rep);
    private:
        void Enter(int& CurrentLine,int& x,int& y,Screen& RepScreen, Editor& Rep);
        void BackSpace(int& CurrentLine,int& x,int& y,Screen& RepScreen, Editor& Rep);
        void NewChar(char ch,int& CurrentLine,int& x,int& y,Screen& RepScreen, Editor& Rep);
};

void Insert::SendKey(int ch,int& CurrentLine,int& x,int& y,Screen& RepScreen, Editor& Rep){
    if (ch == 10) {
        Enter(CurrentLine,x,y,RepScreen,Rep);
        return;
    }
    NewChar((char)(ch),CurrentLine,x,y,RepScreen,Rep);
}
void Insert::NewChar(char ch,int& CurrentLine,int& x,int& y,Screen& RepScreen, Editor& Rep){
    Rep.AddCharacter(CurrentLine, x - 4, ch);
    x++;
    RepScreen.PrintLine(y, CurrentLine, Rep.Matn[CurrentLine]);
    move(y, x);
}
void Insert::Enter(int& CurrentLine,int& x,int& y,Screen& RepScreen, Editor& Rep){

}