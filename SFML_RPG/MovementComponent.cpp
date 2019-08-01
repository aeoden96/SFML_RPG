#include "MovementComponent.h"


//Konstr/destr
MovementComponent::MovementComponent(
	sf::Sprite& sprite,float maxVelocity , float acceleration,float deceleration)
	:sprite(sprite),maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
}


MovementComponent::~MovementComponent()
{
}

const sf::Vector2f & MovementComponent::getVelocity() const
{
	return this->velocity;
}


//Functions
//sets directional velocity
void MovementComponent::move(const float dir_x, const float dir_y,const float &dt)
{
	/*accelerating a sprite until reaches maxVelocity*/


	//acceleraton
	this->velocity.x += this->acceleration * dir_x;

	if (this->velocity.x > 0.f) //check for right 
	{
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;
	}
	else if (this->velocity.x < 0.f) //check for left
	{
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
	}

	this->velocity.y += this->acceleration * dir_y;



}

void MovementComponent::update(const float & dt)
{
	//deceletation
	if (this->velocity.x > 0.f) //check for right 
	{
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f)
	{
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	//final move
	this->sprite.move(this->velocity * dt);//uses velocity
}
