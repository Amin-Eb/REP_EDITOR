#ifndef REP_COLORSCHEME_H
#define REP_COLORSCHEME_H
#include "coreinc.h"
using namespace std;
using json = nlohmann::json;

class ColorScheme{
    public:
      virtual map<string,int> Build(string FileName);
    private:
      virtual void InitColor(int Number, string HexaColor);
};
#endif