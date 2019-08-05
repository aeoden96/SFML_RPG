#include "Button.h"



Button::Button(float x, float y, float width, float height,
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


Button::~Button()
{
}


//accessors


const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE) {
		return true;
	}
	return false;
}

//functions

void Button::update(const sf::Vector2f& mousePos)
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

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}




