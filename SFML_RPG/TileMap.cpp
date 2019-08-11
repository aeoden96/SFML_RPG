#include "stdafx.h"
#include "TileMap.h"



TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	std::cout << "\n" << "TileMap KONSTR ";
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

	/*instead of pushback, we are using resize to set values in the map at once*/
	this->map.resize(this->maxSize.x , std::vector<  std::vector<Tile*>>());

	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < maxSize.y ; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}

	if (this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/grass.png"))
		std::cout << "ERROR:TILEMAP:FAILED_TO_LOAD_TILE_TEXTURE_SHEET \n";
}


TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}

//Functions

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget & target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto *z : y)
			{
				if(z != nullptr)
					z->render(target);
			}
		}
	}
}

void TileMap::addTile(const unsigned x,const unsigned y, const unsigned z)
{
	/*Take three indicies from mouse pos in the grid and add tile to that pos
	if internal tilemap array allows it*/

	if (x < this->maxSize.x &&
		y < this->maxSize.y &&
		x >= 0 && 
		y >= 0 &&
		z < this->layers &&
		z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			/*OK to add tile.*/
			this->map[x][y][z] = new Tile(x * this->gridSizeF , y* this->gridSizeF , this->gridSizeF,this->tileTextureSheet);
			std::cout << "DEBUG: ADDED TILE\n ";
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/*Take three indicies from mouse pos in the grid and remove tile to that pos
	if internal tilemap array allows it*/

	if (x < this->maxSize.x &&
		y < this->maxSize.y &&
		x >= 0 &&
		y >= 0 &&
		z < this->layers &&
		z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{
			/*OK to remove tile.*/
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
			std::cout << "DEBUG: REMOVED TILE\n ";
		}
	}

}
