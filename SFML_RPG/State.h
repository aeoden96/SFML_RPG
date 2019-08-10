#pragma once

#include "Player.h"
#include "GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

class StateData 
{
public:
	StateData()
	{

	}
	//Variables
	float gridSize;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
	GraphicsSettings* gfxSettings;
};

class State
{
private:
	
protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map<std::string,sf::Texture> textures;
	//Functions

	//EACH state has to define its own keybinds
	virtual void initKeybinds() = 0;
public:
	State(StateData* stateData);
	virtual ~State();

	
	//Accessor
	const bool& getQuit() const;
	const bool& getKeytime();
	/*needs to be defined in child classes of State*/
    void endState();
	void pauseState();
	void unpauseState();

	virtual void updateKeytime(const float& dt);
	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt)=0;
	virtual void render(sf::RenderTarget* target= NULL)=0;
};

