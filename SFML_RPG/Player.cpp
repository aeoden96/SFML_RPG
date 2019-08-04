#include "Player.h"

//Initializer funcions

void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{
	
}

//Constructors/Destructors
Player::Player(float x,float y, sf::Texture& textureSheet)
{
	this->initVariables();

	
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite,30.f,70.f, 587.f * 0.5f * 0.65f, 707.f * 0.5f * 0.73f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(textureSheet);

	this->animationComponent->addAnimation("IDLE" , 10.f , 0, 0 ,9,0 ,587,707);
	this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 9, 1, 587, 707);
	this->animationComponent->addAnimation("ATTACK", 7.f, 0, 2, 9, 2, 587, 707);


}


Player::~Player()
{
}
//Functions
void Player::update(const float & dt)
{
	const float PLAYER_SIZE_FACTOR = 0.5f;

	this->movementComponent->update(dt);
	
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}*/

	if (this->attacking)
	{
		this->animationComponent->play("ATTACK", dt, true);
	}

	//we are defining what animation to see when player is moving in ? direction
	if (this->movementComponent->getState(IDLE)) 
		this->animationComponent->play("IDLE", dt);

	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		
		this->sprite.setOrigin(500.f, 0.f);
		this->sprite.setScale(-1.f * PLAYER_SIZE_FACTOR, 1.f *PLAYER_SIZE_FACTOR);
		this->animationComponent->play("WALK", dt ,this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(1.f *PLAYER_SIZE_FACTOR, 1.f *PLAYER_SIZE_FACTOR);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}


	this->hitboxComponent->update();  

}
