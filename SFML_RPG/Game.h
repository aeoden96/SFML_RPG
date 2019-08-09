#pragma once


#include "MainMenuState.h"



class Game
{
private:
	
	
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	GraphicsSettings gfxSettings;


	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int > supportedKeys;

	//Initialization
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initStates();
	void initKeys();
public:

	//Constructors/Destructors
	Game();
	~Game();


	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void update();
	void updateSFMLEvents();

	//Render
	void render();
	
	//Core
	void run();

};

