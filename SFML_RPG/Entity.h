#pragma once

#include "MovementComponent.h"

class Entity //EVERY ENITIY HAS ITS SPRITE
{
private:
	void initVariables();

protected:
	
	sf::Sprite sprite;

	//sf::RectangleShape shape; //placeholder
	MovementComponent* movementComponent;

public:
	Entity();

	virtual ~Entity();
	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity);

	//Functions
	virtual void setPosition(const float x, const float y);
	//move fn. for entity
	virtual void move(const float& dt,const float x,const float y);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

