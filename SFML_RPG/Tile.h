#pragma once


class Tile
{
private:

protected:
	sf::RectangleShape shape;
public:
	Tile(float x, float y, float gridSizeF ,sf::Texture& texture);
	Tile();
	virtual ~Tile();
	//Functions

	void update();
	void render(sf::RenderTarget& target);
};

