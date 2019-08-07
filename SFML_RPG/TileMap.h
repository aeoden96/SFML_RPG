#pragma once

#include"Tile.h"
class TileMap
{
private:
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u maxSize;
	std::vector< std::vector< std::vector<Tile> > > map; //XYZ coord

public:
	TileMap();
	virtual ~TileMap();
};

