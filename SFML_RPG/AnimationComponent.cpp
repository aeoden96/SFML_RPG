#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite & sprite, sf::Texture & textureSheet)
	:sprite(sprite),textureSheet(textureSheet)
{
}

AnimationComponent::~AnimationComponent()
{
}

//Functions
void AnimationComponent::update(const float & dt)
{
}
