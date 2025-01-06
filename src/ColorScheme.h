#ifndef REP_COLORSCHEME_H
#define REP_COLORSCHEME_H
#include "coreinc.h"
using namespace std;
using json = nlohmann::json;

class ColorScheme{
    public:
      map<string,int> Build(string FileName);
    private:
      void InitColor(int Number, string HexaColor);
};
#endif