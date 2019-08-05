#include "SettingsState.h"


//Initializer functions
void SettingsState::initVariables()
{
}

void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/background.jpg"))
		throw "ERROR:MAINMENUSTATE:FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	this->background.setTexture(&this->backgroundTexture);

}

void SettingsState::initFonts()
{

	std::cout << "\n" << "---MainMenuState initFonts  ";
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
	}
}

void SettingsState::initKeybinds()
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

	std::cout << "\nMainMenuState:Keybinds map: \n";
	for (auto i : this->keybinds)
	{
		std::cout << "   > " << i.first << " " << i.second << "\n";
	}


}

void SettingsState::initButtons()
{


	this->buttons["EXIT_STATE"] = new gui::Button(60, 400, 150, 50,
		&this->font, "Quit", 50,
		sf::Color(150, 150, 150, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}


SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window,supportedKeys,states)
{
	std::cout << "\n" << "SettingsState constr : ";
	this->initVariables(); //no vars
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}


SettingsState::~SettingsState()
{
	std::cout << "\n" << "SettingsState destr";
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions

void SettingsState::updateInput(const float & dt)
{
	//no keyboard buttons defined for main menu

	//exit with ESC is too fast 
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close"))))
		this->endState();*/
}

void SettingsState::updateButtons()
{


	//updates all the buttons in the states and handles their functionality
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}



	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();


	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";


}

void SettingsState::renderButtons(sf::RenderTarget& target)
{
	//this->gamestate_btn->render(target);

	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	//if target window not given,will render to default window
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

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


