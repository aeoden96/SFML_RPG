#include "Game.h"

//Static functions



//Initializer functions
void Game::initWindow()
{
	/*Creates SFML windows using options from window.ini file*/

	std::ifstream ifs("Config/window.ini");

	std::string title = "None";
	sf::VideoMode window_bounds(800,600);
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;

	if (ifs.is_open()) 
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}

	ifs.close();

	this->window=new sf::RenderWindow(window_bounds,title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

//Constructors



Game::Game()
{
	this->initWindow();
}

//Destructors
Game::~Game()
{
	delete this->window;
}

//Functions

void Game::updateDt()
{
	/*Updates dt variable with time it takes to update and render one frame*/
	this->dt = this->dtClock.restart().asSeconds();
	
}

void Game::update()
{
	this->updateSFMLEvents();

	int sum = 0;

}

void Game::render()
{
	this->window->clear();

	//Render items


	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}
