using namespace std;

class File {
   private:
    fstream TheFile = {};
    string FileName = {};

   public:
    File(string FileName) : FileName(std::move(FileName)) {}
    void Save(Editor Edit, Screen& Scr, bool flag);
    bool Open(string Name, Editor& Edit);
};

bool File::Open(string Name, Editor& Edit) {
    FileName = Name;
    TheFile.open(Name);
    if (!TheFile.is_open())
        return false;
    std::string line("");
    bool flag = 0;
    while (getline(TheFile, line)) {
        Edit.Ident[Edit.LN] = Edit.Ident[max(0,Edit.LN - 1)];
        for (auto cch : line){
            if(cch == '{')
                Edit.Ident[Edit.LN] += 4;
            if(cch == '}')
                Edit.Ident[Edit.LN] -= 4;
        }
        Edit.Matn[Edit.LN] = line;
        Edit.LN++;
        flag = 1;
    }

    TheFile.close();
    return flag;
}

void File::Save(Editor Edit, Screen& Scr, bool flag) {
    TheFile.open(FileName, ios::trunc | ios::out);
    for (int i = 0; i < Edit.LN; i++)
        TheFile << Edit.Matn[i] << "\n";
    TheFile.close();

    if (flag == false)
        return;
    Scr.PrintLine(Scr.col , 0 , "File saved succecfully!\n");
}
