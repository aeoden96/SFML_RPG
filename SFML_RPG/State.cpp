#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{

	std::cout << "\n" << "State constr";

	this->window = window;
	this->quit = false;
	this->states = states;
	this->supportedKeys = supportedKeys;
	this->paused = false;

}	


State::~State()
{
	std::cout << "\n" << "State destr \n \n"; 

}

const bool & State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

}


