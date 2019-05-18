#pragma once

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include<vector>

class State
{

private:
	/*player, enemy textures, sprites ,particle textures.. */
	std::vector<sf::Texture> textures;
public:
	State();
	virtual ~State();

	/*needs to be defined in child classes of State*/
	virtual void update()=0;
	virtual void render()=0;
};

