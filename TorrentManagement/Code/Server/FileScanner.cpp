#include "FileScanner.h"

#include "dirent.h"

using namespace std;

FileScanner::FileScanner()
{}

FileScanner::~FileScanner()
{}

File* FileScanner::scan(std::string path, bool recursive)
{
	int index = path.find_last_of("/\\");
	std::string name = path.substr(index+1, path.size() - 1);
	File* file = new File(name, path, FileType_FOLDER);

	vector<File*>* files = new vector<File*>;

	DIR* dirStream = opendir(path.c_str());
	if (dirStream != NULL)
	{
		dirent* ent;
		while ((ent = readdir(dirStream)) != NULL)
		{
			switch (ent->d_type)
			{
			case DT_LNK:
			case DT_REG:
				files->push_back(new File(ent->d_name, path + ent->d_name, FileType_FILE));
				break;
			case DT_DIR:
				if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
				{
					if (recursive)
					{
						files->push_back(scan(path + "\\" + ent->d_name, recursive));
					}
					else
					{
						files->push_back(new File(ent->d_name, path + ent->d_name, FileType_FOLDER));
					}
				}
				break;
			default:
				break;
			}
		}
		closedir(dirStream);
	}

	file->setFiles(files);

	return file;
}