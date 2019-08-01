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
		
	}
	else if (this->velocity.x < 0.f) //check for left
	{
		
	}

	this->velocity.y += this->acceleration * dir_y;



}

void MovementComponent::update(const float & dt)
{
	/*
	Decelerates the sprite and controls max velocity.
	Moves the sprite.
	*/
	if (this->velocity.x > 0.f) //check for positive x 
	{
		//maxVelocity check x positive
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration x positive
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;

	}
	else if (this->velocity.x < 0.f)//check for negative x 
	{
		//maxVelocity check x negative
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
		//Deceleration x negative
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) //check for positive y 
	{
		//maxVelocity check y positive
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration y positive
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;

	}
	else if (this->velocity.y < 0.f)//check for negative y 
	{
		//maxVelocity check y negative
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;
		//Deceleration y negative
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//final move
	this->sprite.move(this->velocity * dt);//uses velocity
}
