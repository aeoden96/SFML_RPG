#include "Player.h"

//Initializer funcions

void Player::initVariables()
{
}

void Player::initComponents()
{
	
}

//Constructors/Destructors
Player::Player(float x,float y, sf::Texture& textureSheet)
{
	this->initVariables();

	
	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(textureSheet);

	this->animationComponent->addAnimation("IDLE_LEFT" , 100.f , 0, 0 ,9,0 ,587,707);
	this->animationComponent->addAnimation("WALK_LEFT", 100.f, 0, 1, 9, 1, 587, 707);


}


Player::~Player()
{
}
//Functions
void Player::update(const float & dt)
{
	this->movementComponent->update(dt);
	


	//we are defining what animation to see when player is moving in ? direction
	if (this->movementComponent->getState(IDLE)) 
		this->animationComponent->play("IDLE_LEFT", dt);
	else if(this->movementComponent->getState(MOVING_RIGHT))
		this->animationComponent->play("WALK_LEFT",dt);

}
