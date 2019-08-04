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
			int start_frame_x, int start_frame_y,
			int frames_x, int frames_y,
			int width,int  height)
			:sprite(sprite),textureSheet(textureSheet), 
			animationTimer(animationTimer),width(width),height(height)
		{
		
			this->timer = 0.f;
			//s lijeva slike pocne od <start_frame_x * width> npr od 0, ili od 1*width
			//od vrha slike pocne od <start_frame_y * height> npr od 0 ili od 1*height
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			this->sprite.setTexture(this->textureSheet,true);//in case of error,set true?
			this->sprite.setTextureRect(this->startRect);//we want to display just the part of the texture
		}

		//Functions
		void play(const float& dt) 
		{
			this->timer += 1000.f * dt;
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

				this->sprite.setTextureRect(this->currentRect);

			}
		}
		
		void reset() {
			this->currentRect = this->startRect;
			this->timer = 0.f;
		}
	};


	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
public:
	AnimationComponent(sf::Sprite& sprite,sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	//Functions
	void addAnimation(const std::string key,
		float animationTimer,
		int start_frame_x, int start_frame_y,
		int frames_x, int frames_y,
		int width, int  height);

	/*void startAnimation(const std::string animation);
	void pauseAnimation(const std::string animation);
	void resetAnimation(const std::string animation);*/

	void play(const std::string key,const float& dt);

};

