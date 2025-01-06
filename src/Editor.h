#ifndef REP_EDITOR_H
#define REP_EDITOR_H

#include "coreinc.h"

class Editor {
	public:
		int LN = 0;
		int Ident[1000];
		std::string* Matn = new std::string[1000];
		Editor();
		virtual void AddLine(int Line, std::string Str);
		virtual void AddCharacter(int Line, int Position, char Character);
		virtual void DeleteLine(int Line);
		virtual void DeleteCharacter(int Line, int Position);
};

#endif
