using namespace std;

class File {
    private:
        fstream TheFile = {};
        string FileName = {};

    public:
        File(string FileName):FileName(std::move(FileName)){}
        void Save(Editor Edit, Screen Scr, bool flag);
        bool Open(string Name, Editor& Edit);
};

bool File::Open(string Name, Editor& Edit) {
    FileName = Name;
    TheFile.open(Name);
    if (!TheFile.is_open())
        return false;
    std::string line("");
    while (getline(TheFile, line)) {
        Edit.Matn[Edit.LN] = line;
        Edit.LN++;
    }
    TheFile.close();
    return true;
}

void File::Save(Editor Edit, Screen Scr, bool flag) {
    TheFile.open(FileName, ios::trunc | ios::out);
    clear();
    for (int i = 0; i < Edit.LN; i++)
        TheFile << Edit.Matn[i] << "\n";
    TheFile.close();

    if (flag == false)
        return;
    Scr.PrintLine(0, 1, "File saved succecfully!\n");
    Scr.PrintLine(1, 2, "Press Space key for continue :)");
}