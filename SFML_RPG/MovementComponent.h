#pragma once

#include<ctime>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<stack>
#include<map>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class MovementComponent //IS SPRITE DEPENDENT
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Init functions

public:
	MovementComponent(sf::Sprite& sprite,float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();
	//Accessors

	const sf::Vector2f& getVelocity() const;

	//Functions
	void move(const float x, const float y, const float &dt);
	void update(const float& dt);

};

