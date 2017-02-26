#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <set>

enum FileType
{
	FileType_FILE,
	FileType_FOLDER,
	FileType_UNKNOWN = -1
};

class File
{
public:
	File(std::string name, std::string path, FileType type);
	~File();

	void setFiles(std::vector<File*>* files);
	const std::vector<File*>* const getFiles();
	std::string getName() const;
	std::string getPath() const;
	FileType getType() const;
	//File getFile(std::string path);

	bool isFolder() const;
	bool isFile() const;

	bool operator <(const File& file) const;
	
private:
	FileType type;
	std::string name;
	std::string path;
	std::vector<File*>* files;

};

#endif