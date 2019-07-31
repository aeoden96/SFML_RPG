#include "Game.h"

//Static functions




//Initializer functions
void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;
	this->fullscreen = false;
}


void Game::initWindow()
{
	/*Creates SFML windows using options from window.ini file*/

	std::ifstream ifs("Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds=sf::VideoMode::getDesktopMode();

	bool fullscreen = false;
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open()) 
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}

	ifs.close();


	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level; //ant_level and atribute_flags only relevant in con_settings,rest is for opengl
	
	if(this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title,sf::Style::Fullscreen , windowSettings);
	else 
		this->window = new sf::RenderWindow(window_bounds, title,sf::Style::Titlebar | sf::Style::Close, windowSettings);

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
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


	for (auto i: this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
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
	std::cout << "\n" << "Game --- constr";
	this->initVariables();
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
