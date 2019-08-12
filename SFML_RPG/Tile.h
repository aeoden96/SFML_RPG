#pragma once


class Tile
{
private:

protected:
	sf::RectangleShape shape;
public:
	Tile(float x, float y, float gridSizeF ,const sf::Texture& texture, const sf::IntRect& tex_rect);
	Tile();
	virtual ~Tile();
	//Functions

	void update();
	void render(sf::RenderTarget& target);
};

