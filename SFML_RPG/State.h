#pragma once

#include "Entity.h"


class State
{
private:
	
protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	bool quit;
	std::map<std::string, int> keybinds;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::vector<sf::Texture> textures;
	//Functions

	//EACH state has to define its own keybinds
	virtual void initKeybinds() = 0;
public:
	State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	virtual void checkForQuit();

	const bool& getQuit() const;

	/*needs to be defined in child classes of State*/
	virtual void endState()=0;
	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt)=0;
	virtual void render(sf::RenderTarget* target= NULL)=0;
};

