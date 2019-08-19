#pragma once

enum TileTypes { DEFAULT= 0 , DAMAGING};

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	short type;
	bool collision;

public:
	Tile(float x, float y, float gridSizeF ,const sf::Texture& texture, const sf::IntRect& tex_rect, bool collision = false, short type = TileTypes::DEFAULT);
	Tile();
	virtual ~Tile();
	//Functions
	const std::string getAsString() const;
	void update();
	void render(sf::RenderTarget& target);
};

