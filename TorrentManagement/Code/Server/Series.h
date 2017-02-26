#ifndef SERIES_H
#define SERIES_H

#include "Media.h"

#include <vector>

class Series : public Media
{
public:

private:
	std::vector<Media> seasons;

};

#endif