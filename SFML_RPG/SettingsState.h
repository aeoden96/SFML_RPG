#pragma once
#include "State.h"
#include "Gui.h"

class SettingsState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	GraphicsSettings& gfxSettings;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGui(); //here,bcs not every state has buttons
	void initText();

public:
	SettingsState(sf::RenderWindow* window,  GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsState();
	//Accessors


	//Functions

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);


};

