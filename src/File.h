using namespace std;

class File {
    public:
        fstream TheFile;
        string FileName;
        void Save(Editor Edit);
        bool Open(string Name, Editor& Edit);
};

bool File::Open(string Name, Editor& Edit){
    FileName = Name;
    TheFile.open(Name);
    if (!TheFile.is_open()) return false;
    string line;
    while (getline(TheFile, line)){
        Edit.Matn[Edit.LN] = line;
        Edit.LN ++;
    }
    TheFile.close();
    return true;
}

void File::Save(Editor Edit){
    TheFile.open(FileName, ios::trunc);
    for(int i = 0 ; i < Edit.LN ; i ++)
        TheFile << Edit.Matn[i] << "\n";
    TheFile.close();
}