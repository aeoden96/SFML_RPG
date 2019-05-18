#include "Game.h"

//Static functions



//Initializer functions
void Game::initWindow()
{
	this->window=new sf::RenderWindow(sf::VideoMode(800, 600), "SFML RPG");
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
	system("cls");
	std::cout << this->dt << std::endl;
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
