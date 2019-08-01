#pragma once

#include<iostream>
#include<map>
#include<string>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class AnimationComponent
{
private:
	class Animation 
	{
	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		int width;
		int height;
		float timer;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& sprite,sf::Texture& textureSheet,
			float animationTimer,
			int start_x, int start_y,
			int end_x, int end_y,
			int width,int  height)
			:sprite(sprite),textureSheet(textureSheet), animationTimer(animationTimer),width(width),height(height)
		{
		

			this->startRect = sf::IntRect(start_x, start_y, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(end_x, end_y, width, height);

			this->sprite.setTexture(this->textureSheet,true);//in case of error,set true?
			this->sprite.setTextureRect(this->startRect);
		}

		//Functions
		void update(const float& dt) 
		{
			this->timer = 10.f * dt;
			//update timer
			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;
				//Animate
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else //Reset
				{
					this->currentRect.left = this->startRect.left;
				}

			}
		}
		void pause();
		void reset();
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation> animations;
public:
	AnimationComponent(sf::Sprite& sprite,sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	//Functions
	void addAnimation(const std::string key);

	void startAnimation(const std::string animation);
	void pauseAnimation(const std::string animation);
	void resetAnimation(const std::string animation);

	void update(const float& dt);

};

