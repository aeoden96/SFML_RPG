#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE:: Could not load font ");
	}
}

void MainMenuState::initKeybinds()
{

	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{

		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = supportedKeys->at(key2);

		}
	}
	ifs.close();

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	:State(window, supportedKeys)
{
	this->initFonts();
	this->initKeybinds();
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::endState()
{
	std::cout << "Ending menu state\n";
}

void MainMenuState::updateInput(const float & dt)
{
	//at this time, Close key is defined
	this->checkForQuit();

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) 
	//{
	//	
	//}



}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	
	system("cls");
	std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";

}

void MainMenuState::render(sf::RenderTarget* target)
{
	//if target window not given,will render to default window
	if (!target)
		target = this->window;

	target->draw(this->background);
	


}
