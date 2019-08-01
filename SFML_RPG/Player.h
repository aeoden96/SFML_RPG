#pragma once

#include "Entity.h"
class Player :
	public Entity
{
private:
	//Variables


	//Initializer funcions
	void initVariables();
	void initComponents();

public:
	Player(float x, float y, sf::Texture& textureSheet);
	virtual ~Player();

	//Functions
	virtual void update(const float& dt);
};

