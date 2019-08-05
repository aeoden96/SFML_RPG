#pragma once

#include<ctime>
#include<cstdlib>
#include<iostream>
#include<sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

enum button_states{BTN_IDLE=0, BTN_HOVER,BTN_ACTIVE};
class Button
{
private:
	
	short unsigned buttonState;
	sf::RectangleShape shape; //button basic shape
	sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x,float y, float width,float height,
		sf::Font* font,std::string text,unsigned characterSize,
		sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//accessors
	const bool isPressed() const;
	//functions

	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

