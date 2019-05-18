#pragma once

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include<stack>
#include<map>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"


class State
{

private:
	sf::RenderWindow* window;
	/*player, enemy textures, sprites ,particle textures.. */
	std::vector<sf::Texture> textures;
public:
	State(sf::RenderWindow* window);
	virtual ~State();

	virtual void endState() = 0;

	/*needs to be defined in child classes of State*/
	virtual void update(const float& dt)=0;
	virtual void render(sf::RenderTarget* target= nullptr)=0;
};

