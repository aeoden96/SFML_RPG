#pragma once

#include "Entity.h"


class State
{
private:

protected:
	sf::RenderWindow* window;
	/*player, enemy textures, sprites ,particle textures.. */
	std::vector<sf::Texture> textures;
	bool quit;
public:
	State(sf::RenderWindow* window);
	virtual ~State();

	virtual void checkForQuit();

	const bool& getQuit() const;

	/*needs to be defined in child classes of State*/
	virtual void endState()=0;
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt)=0;
	virtual void render(sf::RenderTarget* target= NULL)=0;
};

