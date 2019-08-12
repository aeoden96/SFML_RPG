#include "stdafx.h"
#include "Tile.h"



Tile::Tile(float x,float y,float gridSizeF, const sf::Texture& texture, const sf::IntRect& tex_rect)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setPosition(x, y);
	//this->shape.setOutlineColor(sf::Color::Black);
	//this->shape.setOutlineThickness(1.f);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(tex_rect);

}

Tile::Tile()
{
}


Tile::~Tile()
{
}



//Functions
void Tile::update()
{
}

void Tile::render(sf::RenderTarget & target)
{
	target.draw(this->shape);
}