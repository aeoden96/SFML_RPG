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

#include "Button.h"

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape container;
	std::map<std::string, Button*>  buttons;

	//Private functions

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();
	//Accessor
	std::map<std::string, Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key,float y, const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

