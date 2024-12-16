#ifndef REP_SYNTAX_H
#define REP_SYNTAX_H
#include "coreinc.h"

using json = nlohmann::json; 


class Syntax{
    public:
		TSParser* parser;
		TSTree* tree;
		TSNode RootNode;
		const int TwoDigits = 10;
		const int ThreeDigits = 100;
		uint32_t Ps[1000];
		std::map<std::string, int> ColorMap;
		Syntax();
		void Build(std::string Str[],int LN);
		void DfsLine(TSNode Node,int CurrentLine,int ScreenLine,std::string SourceCode[]);
		void DfsScr(TSNode Node,int TheStart,int TheEnd,std::string SourceCode[]);
		void PrintLine(int CurrentLine,int ScreenLine, std::string SourceCode[]);
		void PrintScr(int TheStart,int TheEnd, std::string SourceCode[]);

};
#endif
