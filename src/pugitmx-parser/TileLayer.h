#ifndef __TILELAYER_H_
#define __TILELAYER_H_

#include "../lib/stringh.h"
#include "Tile.h"
#include <vector>
#include <list>
#include <map>

namespace pugitmx
{
	class TileLayer
	{
		public:
			TileLayer(std::string nme, int wd, int ht) : name(nme), width(wd), height(ht) 
			{
				tiles.resize(height);
				for(int i = 0; i < tiles.size(); i++)
				{
					tiles[i].resize(width);
				}
			};
			std::string getName() const;
			int getWidth() const;
			int getHeight() const;
			void addTile(Tile);
			std::list<Tile> grabTiles();
			void registerProperty(std::string, std::string);
			std::string getProperty(std::string) const;
		private:
			std::string name;
			int width;
			int height;
			std::map<std::string, std::string> properties;
			std::vector<std::vector<Tile> > tiles;
	};
};

#endif // __TILELAYER_H_
