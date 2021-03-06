#include "stdafx.h"
#include "EditorState.h"

void EditorState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width, 
			this->stateData->gfxSettings->resolution.height));
	this->view.setCenter(
		this->stateData->gfxSettings->resolution.width / 2.f, 
		this->stateData->gfxSettings->resolution.height / 2.f);
}

//Initializer functions ===========================
void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(
		0, 
		0, 
		static_cast<int>(this->stateData->gridSize), 
		static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	this->cameraSpeed = 100.f;
}

void EditorState::initBackground()
{
}

void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButton("QUIT", 930.f, "Quit");
	this->pmenu->addButton("SAVE", 800.f, "Save");
	this->pmenu->addButton("LOAD", 700.f, "Load");
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
	this->sidebar.setSize(sf::Vector2f(80.f,static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50,50,50,100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(
		sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize)
	);
	this->selectorRect.setFillColor(sf::Color(255,255,255,150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(
		20.f, 20.f,500.f,500.f,
		this->stateData->gridSize,
		this->tileMap->getTileSheet(),
		this->font, "TS");
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10,"Resources/Images/Tiles/tilesheet1.png");
}

//CONSTR/DESTR ========================================

EditorState::EditorState(StateData* stateData)
	:State(stateData)
{
	std::cout << "\n" << "EditoState constr : ";
	this->initVariables();
	this->initView();
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

	//Move view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Camera_Up"))))
	{
		this->view.move(0.f, -this->cameraSpeed *dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Camera_Down"))))
	{
		this->view.move(0.f, this->cameraSpeed *dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Camera_Left"))))
	{
		this->view.move(-this->cameraSpeed *dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Camera_Right"))))
	{
		this->view.move(this->cameraSpeed *dt, 0.f);
	}


	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	//Add a tile to tilemap
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);

			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}

	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	//Remove a tile from tilemap
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
			}
			else
			{

			}
		}
	}

	//Toggle collision

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Toggle_Collision"))) && this->getKeytime())
	{
		if (this->collision)
			this->collision = false;
		else
			this->collision = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Type_Inc"))) && this->getKeytime())
	{
		//change to limit to MAX type
		this->type++;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Type_Dec"))) && this->getKeytime())
	{
		if(this->type > 0)
			this->type--;
	}

}




void EditorState::updateButtons()
{


	//updates all the buttons in the states and handles their functionality
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosWindow);
	}

}

void EditorState::updateGui(const float& dt)
{
	this->textureSelector->update(this->mousePosWindow,dt);

	if (!this->textureSelector->getActive()) //if inner mouse in inner selection, dont draw outer
	{
		//MOUSE-FOLOWING RECTANGLE selectorRect
		this->selectorRect.setTextureRect(this->textureRect);

		this->selectorRect.setPosition(
			this->mousePosGrid.x * this->stateData->gridSize, 
			this->mousePosGrid.y * this->stateData->gridSize
		);

	}

	//CURSOR TEXT
	this->cursorText.setPosition(
		this->mousePosView.x + 100.f,
		this->mousePosView.y + 20.f
	);

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y << "\n"
		<< this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n"
		<< this->textureRect.left << " " << this->textureRect.top << "\n"
		<< "Collision: " << this->collision <<
		"\n" "Type: " << this->type;


	this->cursorText.setString(ss.str());

}

void EditorState::updatPauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();

	if (this->pmenu->isButtonPressed("SAVE"))
		this->tileMap->saveToFile("text.slmp");

	if (this->pmenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("text.slmp");
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);
	if (!this->paused)//NOT PAUSED
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
	}
	else //paused
	{
		this->pmenu->update(this->mousePosWindow);
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
	if (!this->textureSelector->getActive())
	{
		target.draw(this->selectorRect);
	}

	this->textureSelector->render(target);
	target.draw(this->cursorText);

	target.draw(this->sidebar);
}

void EditorState::render(sf::RenderTarget* target)
{
	//if target window not given,will render to default window
	if (!target)
		target = this->window;

	target->setView(this->view);
	this->tileMap->render(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);
	this->renderGui(*target);

	if (this->paused)//Pause menu render
	{
		this->pmenu->render(*target);
	}
	
	



}