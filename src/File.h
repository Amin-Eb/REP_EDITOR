using namespace std;

class File {
    public:
        fstream TheFile;
        string FileName;
        void Save(Editor Edit);
        void Open(string Name);
        void Close();
};

void File::Open(string Name){
    FileName = Name;
    TheFile.open(Name);
}

void File::Close(){
    TheFile.close();
}

void File::Save(Editor Edit){
    TheFile.open(FileName, ios::trunc);
    for(int i = 0 ; i < Edit.LN ; i ++)
        TheFile << Edit.Matn[i] << "\n";
    TheFile.close();
}