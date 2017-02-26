#include "File.h"

File::File(std::string name, std::string path, FileType type)
	: name(name), path(path), type(type), files(NULL)
{
}

File::~File()
{
	delete files;
}

void File::setFiles(std::vector<File*>* files)
{
	this->files = files;
}

const std::vector<File*>* const File::getFiles()
{
	return files;
}

std::string File::getName() const
{
	return name;
}

std::string File::getPath() const
{
	return path;
}

FileType File::getType() const
{
	return type;
}

bool File::isFolder() const
{
	return (type == FileType_FOLDER);
}

bool File::isFile() const
{
	return (type == FileType_FILE);
}

bool File::operator <(const File& file) const
{
	// List folders first then files
	if (this->getType() > file.getType()) return true;
	if (this->getType() < file.getType()) return false;

	// Then sort on names
	return (this->name < file.name);
}