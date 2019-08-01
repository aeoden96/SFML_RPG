#pragma once

#include "MovementComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;

	//sf::RectangleShape shape; //placeholder
	MovementComponent* movementComponent;

public:
	Entity();

	virtual ~Entity();
	//Component functions
	void createSprite(sf::Texture* texture);
	void createMovementComponent(const float maxVelocity);

	//Functions
	virtual void setPosition(const float x, const float y);
	//move fn. for entity
	virtual void move(const float& dt,const float x,const float y);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

