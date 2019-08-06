#include "Gui.h"


//BUTTON ===========================================================

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,unsigned characterSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor,
	short unsigned id)
	:font(font),
	textIdleColor(textIdleColor), 
	textHoverColor(textHoverColor), 
	textActiveColor(textActiveColor),
	idleColor(idleColor),
	hoverColor(hoverColor),
	activeColor(activeColor),
	outlineIdleColor(outlineIdleColor),
	outlineHoverColor(outlineHoverColor),
	outlineActiveColor(outlineActiveColor),
	id(id)

{
	std::cout << "\n" << "Button constr : " << text;
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x,y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outlineIdleColor);
	
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

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned & gui::Button::getId() const
{
	return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
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
		this->shape.setOutlineColor(outlineHoverColor);
		break;
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(outlineIdleColor);

		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(outlineActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);

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

	this->activeElement = new gui::Button(
		x, y, width, height,
		&this->font, list[default_index], 14,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 200)
	);


	for (size_t i = 0; i < numOfElements; i++)
	{
		this->list.push_back(
			new gui::Button(
				x, y + ((i+1)* height), width, height,
				&this->font,list[i], 14,
				sf::Color(255,255,255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
				i
				
			)
		);

	}
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

			if (i->isPressed() && this->getKeytime()) 
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
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
