#pragma once



enum button_states{BTN_IDLE=0, BTN_HOVER,BTN_ACTIVE};

namespace gui 
{
	class Button
	{
	private:

		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape; //button basic shape
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned characterSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineIdleColor = sf::Color::Transparent , sf::Color outlineHoverColor = sf::Color::Transparent, sf::Color outlineActiveColor = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		//accessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//Accessors
		
		//functions

		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class DropDownList {
	private:
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;
		float keytime, keytimeMax;

	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned numOfElements, const unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const unsigned short& getActiveElementId() const ;
		//Functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};

}

