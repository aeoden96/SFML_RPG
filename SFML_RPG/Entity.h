#pragma once

#include<ctime>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<stack>
#include<map>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Entity
{
private:
	void initVariables();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;

	//sf::RectangleShape shape; //placeholder
	float movementSpeed;

public:
	Entity();

	virtual ~Entity();
	//Component functions
	void createSprite(sf::Texture* texture);

	//Functions
	virtual void setPosition(const float x, const float y);
	//move fn. for entity
	virtual void move(const float& dt,const float x,const float y);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

