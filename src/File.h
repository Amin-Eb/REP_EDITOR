#ifndef REP_FILE_H
#define REP_FILE_H

#include "coreinc.h"
#include "Editor.h"
#include "Screen.h"

class File {
	private:
		std::fstream TheFile = {};
		std::string FileName = {};
	public:
		File(std::string FileName) : FileName(std::move(FileName)) {}
		void Save(Editor Edit, Screen& Scr, bool flag);
		bool Open(std::string Name, Editor& Edit);
};

#endif
