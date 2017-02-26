#include "Collection.h"

Collection::Collection() : Collection("", "", CollectionType::UNKNOWN)
{}

Collection::Collection(std::string name, std::string path, CollectionType type)
{
	this->name = name;
	this->path = path;
	this->type = type;
}

Collection::~Collection()
{}

CollectionType Collection::getType()
{
	return type;
}

std::string Collection::getPath()
{
	return path;
}

std::string Collection::getName()
{
	return name;
}

std::vector<Media> Collection::getMedia()
{
	return media;
}