#pragma once

#include"Tile.h"
class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u maxSize;
	std::vector< std::vector< std::vector<Tile* > > > map; //XYZ coord 
	//now we can have null pointers in entire map

public:
	TileMap(float gridSize,unsigned width,unsigned hight);
	virtual ~TileMap();

	//Functions 
	void update();
	void render(sf::RenderTarget& target);

	void addTile(const unsigned x, const unsigned y, const unsigned z);
	void removeTile();
};

