#include "stdafx.h"
#include "EditorState.h"

//Initializer functions ===========================
void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(
		0, 
		0, 
		static_cast<int>(this->stateData->gridSize), 
		static_cast<int>(this->stateData->gridSize));
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

void EditorState::initText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y + 20);
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

	std::cout << "\n" << "---EditorState initButtons ---empty ";
	
}

void EditorState::initGui()
{
	this->selectorRect.setSize(
		sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize)
	);
	this->selectorRect.setFillColor(sf::Color(255,255,255,150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(20.f, 20.f,500.f,500.f,this->tileMap->getTileSheet());
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
	
}

//CONSTR/DESTR ========================================

EditorState::EditorState(StateData* stateData)
	:State(stateData)
{
	std::cout << "\n" << "EditoState constr : ";
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText(); //we need initFonts for this
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();// we need initTileMap for this



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

	delete this->tileMap;

	delete this->textureSelector;

}

//UPDATE ===============================================

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

void EditorState::updateEditorInput(const float & dt)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	//Add a tile to tilemap
	{
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y,0,this->textureRect);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	//Remove a tile from tilemap
	{
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}

	//change texture
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->getKeytime())
	{
		if (this->textureRect.left < 100)
		{
			this->textureRect.left += 100;
		}
	}

}

void EditorState::updateButtons()
{


	//updates all the buttons in the states and handles their functionality
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

}

void EditorState::updateGui()
{
	//MOUSE-FOLOWING RECTANGLE selectorRect
	this->selectorRect.setTextureRect(this->textureRect);

	this->selectorRect.setPosition(
		this->mousePosGrid.x * this->stateData->gridSize, 
		this->mousePosGrid.y * this->stateData->gridSize
	);

	//CURSOR TEXT
	this->cursorText.setPosition(
		this->mousePosView.x + 100.f,
		this->mousePosView.y + 20.f
	);

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y << "\n" 
		<< this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n"
		<< this->textureRect.left << " " << this->textureRect.top;
	this->cursorText.setString(ss.str());

	this->textureSelector->update();
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
	if (!this->paused)//NOT PAUSED
	{
		this->updateButtons();
		this->updateGui();
		this->updateEditorInput(dt);
	}
	else //paused
	{
		this->pmenu->update(this->mousePosView);
		this->updatPauseMenuButtons();
	}



	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";


}

//RENDER===================================================

void EditorState::renderButtons(sf::RenderTarget& target)
{

	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget & target)
{
	target.draw(this->selectorRect);
	this->textureSelector->render(target);
	target.draw(this->cursorText);
}

void EditorState::render(sf::RenderTarget* target)
{
	//if target window not given,will render to default window
	if (!target)
		target = this->window;


	this->tileMap->render(*target);

	this->renderButtons(*target);
	this->renderGui(*target);

	if (this->paused)//Pause menu render
	{
		this->pmenu->render(*target);
	}
	
	



}