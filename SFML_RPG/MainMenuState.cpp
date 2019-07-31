#include "MainMenuState.h"

void MainMenuState::initFonts()
{

	std::cout << "\n" << "---MainMenuState initFonts  ";
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE:: Could not load font ");
	}
}

void MainMenuState::initKeybinds()
{
	std::cout << "\n" << "---MainMenuState initkeyBinds  ";

	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

}

void MainMenuState::initButtons()
{

	std::cout << "\n" << "---MainMenuState initButtons  ";
	this->buttons["GAME_STATE"]= new Button(100, 100, 150, 50,
		&this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(100, 300, 150, 50,
		&this->font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys,states)
{

	std::cout << "\n" << "MainMenuState constr : " ;
	this->initFonts();
	this->initKeybinds();
	this->initButtons();


	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
	std::cout << "\n" << "MainMenuState destr";
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState(blank)\n";
}

void MainMenuState::updateInput(const float & dt)
{
	//at this time, Close key is defined
	this->checkForQuit();

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) 
	//{
	//	
	//}



}

void MainMenuState::updateButtons()
{
	//this->gamestate_btn->update(this->mousePosView);


	//updates all the buttons in the states and handles their functionality
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}


	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys,this->states));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit =true;
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	
	this->updateButtons();

	
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
	

}

void MainMenuState::renderButtons(sf::RenderTarget * target)
{
	//this->gamestate_btn->render(target);

	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	//if target window not given,will render to default window
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);

	
	


}
