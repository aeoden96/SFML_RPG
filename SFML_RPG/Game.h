#pragma once

#include "State.h"


class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	//Initialization
	void initWindow();
public:

	//Constructors/Destructors
	Game();
	~Game();


	//Functions
	void updateDt();
	void update();
	void render();
	void run();
	void updateSFMLEvents();

};

