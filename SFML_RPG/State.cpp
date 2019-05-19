#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
	this->window = window;
	this->quit = false;
	this->supportedKeys = supportedKeys;
}


State::~State()
{
}

const bool & State::getQuit() const
{
	return this->quit;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition());

}


void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close"))))
	{
		this->quit = true;
	}
}

