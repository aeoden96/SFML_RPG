#pragma once

#include <ctime>
#include <cstdlib>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"


class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	//Initialization
	void initWindow();
public:

	//Constructors/Destructors
	Game();
	~Game();


	//Functions
	void update();
	void render();
	void run();
	void updateSFMLEvents();

};

