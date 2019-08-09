#include "stdafx.h"
#include "Game.h"

//Static functions




//Initializer functions
void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;
	
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");
}




void Game::initWindow()
{
	/*Creates SFML window*/

	
	if(this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution, 
			this->gfxSettings.title,
			sf::Style::Fullscreen , 
			this->gfxSettings.contextSettings
		);
	else 
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close, 
			this->gfxSettings.contextSettings
		);

	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.vsync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supportedKeys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value) 
		{
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();

	std::cout << "SupportedKeys map: \n";
	for (auto i: this->supportedKeys)
	{
		std::cout << "   > " << i.first << " " << i.second << "\n";
	}




}

void Game::initStates()
{
	std::cout << "\n" << "Game --- init states";
	this->states.push(new MainMenuState(this->window, &this->supportedKeys,&this->states));//need to send adress of states stack
	//this->states.push(new GameState(this->window,&this->supportedKeys));
}



//Constructors
Game::Game()
{
	std::cout << "\n" << "Game --- constr \n";
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStates();

}

//Destructors
Game::~Game()
{
	std::cout << "\n" << "Game --- destr";
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
		

}

//Functions

void Game::endApplication()
{
	std::cout << "\nEnding app function (blank)";
}

void Game::updateDt()
{
	/*Updates dt variable with time it takes to update and render one frame*/
	this->dt = this->dtClock.restart().asSeconds();
	
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty()) 
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{

			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Application end
	else 
	{
		//insted of destructor 
		this->endApplication();
		this->window->close();

	}



}

void Game::render()
{
	this->window->clear();

	//Render items

	if (!this->states.empty())
		this->states.top()->render(this->window);
	


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
