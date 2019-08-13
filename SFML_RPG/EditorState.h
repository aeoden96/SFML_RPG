#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
	public State
{
private:
	//Variables
	sf::Font font;
	sf::Text cursorText;
	PauseMenu* pmenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap *tileMap;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	//Functions
	void initVariables();
	void initBackground();
	void initPauseMenu();
	void initFonts();
	void initText();
	void initKeybinds();
	void initButtons(); //here,bcs not every state has buttons
	void initGui();
	void initTileMap();
public:
	EditorState(StateData* stateData);
	virtual ~EditorState();


	//Functions


	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui();
	void updatPauseMenuButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

