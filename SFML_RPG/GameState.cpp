#include "GameState.h"



GameState::GameState(sf::RenderWindow* window)
	:State(window)
{

}


GameState::~GameState()
{
}


void GameState::endState()
{
	std::cout << "Ending game state\n";
}

void GameState::updateKeybinds(const float & dt)
{
	this->checkForQuit();


}


void GameState::update(const float& dt)
{
	this->updateKeybinds(dt);

	this->player.update(dt);

}

void GameState::render(sf::RenderTarget* target)
{
	if (target)
	{
		this->player.render(target);
	}
	else
	{
		this->player.render(this->window);
	}

}
