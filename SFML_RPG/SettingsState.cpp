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

void SettingsState::initGui()
{


	this->buttons["BACK"] = new gui::Button(
		60, 500, 150, 50,
		&this->font, "Back", 50,
		sf::Color(150, 150, 150, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(
		60, 600, 150, 50,
		&this->font, "Apply", 50,
		sf::Color(150, 150, 150, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::string li[] = {"1920x1080", "800x600","640x480"};

	
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(800,400,200,50,font , li ,3);
}


SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window,supportedKeys,states)
{
	std::cout << "\n" << "SettingsState constr : ";
	this->initVariables(); //no vars
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}


SettingsState::~SettingsState()
{
	std::cout << "\n" << "SettingsState destr";
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
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

void SettingsState::updateGui(const float & dt)
{


	//updates all the gui elements in the states and handles their functionality
	//Buttons
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}


	//button functionality
	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
	//apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		
	}

	//drop down lists

	for (auto &it : this->dropDownLists) {
		it.second->update(this->mousePosView,dt);
	}

	//drop down lists functionality
	//...

}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);


	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";

	
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	//this->gamestate_btn->render(target);

	for (auto &it : this->buttons) {
		it.second->render(target);
	}

	for (auto &it : this->dropDownLists) {
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	//if target window not given,will render to default window
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

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


