#ifndef FILE_SCANNER_H
#define FILE_SCANNER_H

#include "File.h"

class FileScanner
{
public:
	FileScanner();
	~FileScanner();

	File* scan(std::string path, bool recursive = false);

private:


};

#endif