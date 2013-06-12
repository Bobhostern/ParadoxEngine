#ifndef __TILE_H_
#define __TILE_H_

#include "../lib/stringh.h"
#include "square.h"

namespace pugitmx
{
	class Tile
	{
		public:
			Tile();
			Tile(int gd, std::string tlst, int x, int y) : gid(gd), tileset(tlst) {};
			int getGid() const;
			std::string getTileset() const;
		private:
			int gid;
			std::string tileset;
	};
};

#endif // __TILE_H_
