#include "Gui.h"


//BUTTON ===========================================================

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,unsigned characterSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
	:font(font),
	textIdleColor(textIdleColor), 
	textHoverColor(textHoverColor), 
	textActiveColor(textActiveColor),
	idleColor(idleColor),
	hoverColor(hoverColor),
	activeColor(activeColor)

{
	std::cout << "\n" << "Button constr : " << text;
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x,y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);
	
	//this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(characterSize);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f)  - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f)  - this->text.getGlobalBounds().height 
	);
}

gui::Button::~Button()
{
}

//accessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE) {
		return true;
	}
	return false;
}

const std::string& gui::Button::getText() const
{
	return this->text.getString();
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

//functions
void gui::Button::update(const sf::Vector2f& mousePos)
{
	/*update bools for hover/pressed   */

	//idle
	this->buttonState = BTN_IDLE;

	//hover
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;
		//pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_ACTIVE;
		}
	}


	switch (this->buttonState) {
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		break;
	}

	//std::cout << "\n"<< this->buttonState << "\n";
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}


//DROP DOWN LIST ====================================================

gui::DropDownList::DropDownList(float x,float y, float width, float height, sf::Font& font, std::string list[], unsigned numOfElements,const unsigned default_index)
	:font(font),showList(false),keytimeMax(1.f),keytime(0.f)
{
	//unsigned numOfElements = sizeof(list) / sizeof(std::string);

	for (size_t i = 0; i < numOfElements; i++)
	{
		this->list.push_back(
			new gui::Button(
				x , y + (i* height) , width, height,
				&this->font,list[i], 12,
				sf::Color(255,255,255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
			)
		);

	}
	this->activeElement = new Button(*this->list[default_index]);
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;

	/*for(auto &i : list)
		delete i;*/

	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}

//Accessors
const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

//Functions
void gui::DropDownList::updateKeytime(const float& dt)
{
	if (this->keytime < keytimeMax)
	{
		this->keytime += 10.f * dt;
	}
	
}

void gui::DropDownList::update(const sf::Vector2f & mousePos, const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePos);

	//show/hide list
	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if(this->showList)
			this->showList = false;
		else
			this->showList = true;
	}
	
	if (this->showList) 
	{

		for (auto &i : this->list)
		{
			i->update(mousePos);
		}
	}

	

}

void gui::DropDownList::render(sf::RenderTarget & target)
{
	this->activeElement->render(target);

	if (this->showList)
	{

		for (auto &i : this->list)
		{
			i->render(target);
		}
	}
}
