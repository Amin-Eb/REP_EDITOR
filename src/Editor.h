#ifndef REP_EDITOR_H
#define REP_EDITOR_H

#include "coreinc.h"

class Editor {
	public:
		int LN = 0;
		int Ident[1000];
		std::string* Matn = new std::string[1000];
		Editor();
		void AddLine(int Line, std::string Str);
		void AddCharacter(int Line, int Position, char Character);
		void DeleteLine(int Line);
		void DeleteCharacter(int Line, int Position);
};

#endif
