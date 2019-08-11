#include "stdafx.h"
#include "Tile.h"



Tile::Tile(float x,float y,float gridSizeF)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setPosition(x, y);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setOutlineThickness(1.f);
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