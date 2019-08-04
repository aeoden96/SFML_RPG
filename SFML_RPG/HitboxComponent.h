#pragma once

#include<ctime>
#include<cstdlib>
#include<iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class HitboxComponent
{
private:
	//Variables
	sf::Sprite& sprite;
	sf::RectangleShape hitbox; //rectShape can render, float rect can not,has float rect within it
	float offset_x;
	float offset_y;

public:
	HitboxComponent(sf::Sprite& sprite,float offset_x, float offset_y,float width,float height);
	virtual ~HitboxComponent();

	//Functions
	bool checkIntersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};

