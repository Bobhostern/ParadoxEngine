#include "TileLayer.h"
#include "../lib/Log.h"

using namespace pugitmx;

std::string TileLayer::getName() const
{
	return name;
}

int TileLayer::getWidth() const
{
	return width;
}

int TileLayer::getHeight() const
{
	return height;
}

void TileLayer::addTile(Tile tl)
{
	static int currwd;
	static int currht;
	static bool first;
	if(currwd + 1 >= width)
	{
		currwd = 0;
		currht++;
		if(currht >= height)
		{
			Log::log("Invalid TMX Map file.");
		}
		tiles[currht][currwd] = tl;
	}
	else if(!first)
	{
		currwd = 0;
		currht = 0;
		tiles[currht][currwd] = tl;
		first = true;
	}
	else
	{
		tiles[currht][currwd] = tl;
		currwd++;
	}
}

std::list<Tile> TileLayer::grabTiles()
{
	std::list<Tile> tls;
	for(std::vector<std::vector<Tile> >::iterator it = tiles.begin(); it != tiles.end(); it++)
	{
		for(std::vector<Tile>::iterator itx = it->begin(); itx != it->end(); itx++)
		{
			tls.push_back(*itx);
		}
	}
	return tls;
}

void TileLayer::registerProperty(std::string key, std::string value)
{
	properties[key] = value;
}

std::string TileLayer::getProperty(std::string key) const
{
	if(properties.find(key) == properties.end())
	{
		return "";
	}
	else
	{
		return properties.find(key)->second;
	}
}
