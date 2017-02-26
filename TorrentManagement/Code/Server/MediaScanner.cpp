#include "MediaScanner.h"

#include "dirent.h"

#include <iostream>

using namespace std;

MediaScanner::MediaScanner()
{}

MediaScanner::~MediaScanner()
{}

void printContent(std::string path, int& count);

void MediaScanner::scan(Collection& collection)
{
	vector<Media> media = collection.getMedia();
	string path = collection.getPath();
	CollectionType type = collection.getType();

	int count = 0;
	printContent("C:\\", count);
	cout << "Number of files: " << count << endl;
}

void printContent(std::string path, int& count)
{
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
				// cout << ent->d_name << endl;
				count++;
				break;
			case DT_DIR:
				if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
				{
					// cout << ent->d_name << endl;
					printContent(path + "\\" + ent->d_name, count);
				}
				break;
			default:
				break;
			}
		}
		closedir(dirStream);
	}
	else
	{
		cout << "Cannot open directory: " << path << endl;
	}
}