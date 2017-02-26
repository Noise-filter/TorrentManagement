#ifndef COLLECTION_H
#define COLLECTION_H

#include "Media.h"

#include <string>
#include <vector>

enum CollectionType
{
	TV,
	MOVIE,
	UNKNOWN = -1
};

class Collection
{
public:
	Collection();
	Collection(std::string name, std::string path, CollectionType type);
	~Collection();

	CollectionType getType();
	std::string getPath();
	std::string getName();
	std::vector<Media> getMedia();

protected:
	CollectionType type;
	std::string path;
	std::string name;
	std::vector<Media> media;

};

#endif