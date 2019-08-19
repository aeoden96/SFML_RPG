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
	std::string textureFile;
	sf::Texture tileTextureSheet;
	//now we can have null pointers in entire map

	void clear();

public:
	TileMap(float gridSize,unsigned width,unsigned hight, std::string textureFile);
	virtual ~TileMap();

	//Accessors 
	const sf::Texture* getTileSheet() const;

	//Functions 
	void saveToFile(const std::string fileName);
	void loadFromFile(const std::string fileName);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& tex_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void update();
	void render(sf::RenderTarget& target);


};

