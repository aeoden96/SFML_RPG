#include "stdafx.h"
#include "EditorState.h"



//Initializer functions
void EditorState::initVariables()
{
}

void EditorState::initBackground()
{
}
void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButton("QUIT", 930.f, "Quit");
}
void EditorState::initFonts()
{

	std::cout << "\n" << "---MainMenuState initFonts  ";
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::EDITORSTATE:: Could not load font ");
	}
}

void EditorState::initKeybinds()
{
	std::cout << "\n" << "---EditorState initkeyBinds  ";

	std::ifstream ifs("Config/editorstate_keybinds.ini");

	if (ifs.is_open())
	{

		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = supportedKeys->at(key2);

		}
	}
	ifs.close();

	std::cout << "\nMainMenuState:Keybinds map: \n";
	for (auto i : this->keybinds)
	{
		std::cout << "   > " << i.first << " " << i.second << "\n";
	}


}

void EditorState::initButtons()
{

	std::cout << "\n" << "---EditorState initButtons  ";
	
}

EditorState::EditorState(StateData* stateData)
	:State(stateData)
{
	std::cout << "\n" << "EditoState constr : ";
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initPauseMenu();



}

EditorState::~EditorState()
{
	std::cout << "\n" << "MainMenuState destr";
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pmenu;

}

void EditorState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close"))))

}

void EditorState::updateButtons()
{


	//updates all the buttons in the states and handles their functionality
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

}

void EditorState::updatPauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);
	if (!this->paused)//unpaused
	{
		this->updateButtons();

	}
	else //paused
	{
		this->pmenu->update(this->mousePosView);
		this->updatPauseMenuButtons();
	}



	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";


}

void EditorState::renderButtons(sf::RenderTarget& target)
{

	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	//if target window not given,will render to default window
	if (!target)
		target = this->window;


	this->renderButtons(*target);

	this->map.render(*target);

	if (this->paused)//Pause menu render
	{
		this->pmenu->render(*target);
	}
	//REMOVE LATER
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y + 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);



}