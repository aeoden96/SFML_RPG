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
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);

	//Functions
	virtual void setPosition(const float x, const float y);
	//move fn. for entity
	virtual void move(const float x,const float y,const float& dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

