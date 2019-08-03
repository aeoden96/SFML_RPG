#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite & sprite, sf::Texture & textureSheet)
	:sprite(sprite),textureSheet(textureSheet),lastAnimation(NULL)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto &i : this->animations)
		delete i.second;
}


//Functions
void AnimationComponent::addAnimation(
	const std::string key , 
	float animationTimer,
	int start_frame_x, int start_frame_y,
	int frames_x, int frames_y,
	int width, int  height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet,
		animationTimer, start_frame_x, start_frame_y,
		frames_x, frames_y, width, height);
}

void AnimationComponent::play(const std::string key, const float & dt)
{

	//resetting animation sequence every time another animation comes ( etc. idle -> moving )
	if (this->lastAnimation != this->animations[key])
	{
		if (this->lastAnimation == NULL)
		{
			this->lastAnimation = this->animations[key];
		}
		else
		{
			this->lastAnimation->reset();
			this->lastAnimation= this->animations[key];

		}
	}
	this->animations[key]->play(dt);
}
