#pragma once

#include<ctime>
#include<cstdlib>
#include<iostream>
#include<sstream>
#include<vector>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

enum button_states{BTN_IDLE=0, BTN_HOVER,BTN_ACTIVE};

namespace gui 
{
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
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned characterSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
		~Button();

		//accessors
		const bool isPressed() const;
		const std::string getText() const;

		//Modifiers
		void setText(const std::string text);
		//functions

		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class DropDownList {
	private:
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;
		float keytime, keytimeMax;

	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned numOfElements, const unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const bool getKeytime();
		//Functions
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};

}

