#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"

class Button : public sf::Drawable {

public:
	enum State
	{
		Normal, Hover, Clicked
	};

public:
	Button() = default;
	Button(std::string text, sf::Font& font, sf::Vector2f position);

	~Button() = default;

	inline void SetTextColorNormal(sf::Color color) { m_textColorNormal = color; }
	inline void SetTextColorHover(sf::Color color) { m_textColorHover = color; }
	inline void SetTextColorClicked(sf::Color color) { m_textColorClicked = color; }

	inline void SetButtonColorNormal(sf::Color color) { m_buttonColorNormal = color; }
	inline void SetButtonColorHover(sf::Color color) { m_buttonColorHover = color; }
	inline void SetButtonColorClicked(sf::Color color) { m_buttonColorClicked = color; }

	inline void SetBorderColor(sf::Color color) { m_borderColor = color; }

	inline void SetBorderThickness(float t) { m_borderThickness = t; }
	inline void SetBorderRadius(float r) { m_borderRadius = r; }

	inline void SetPosition(sf::Vector2f position) { m_position = position; }

	void SetSize(uint32_t size);
	void SetText(std::string text);
	void SetFont(sf::Font& font);

	inline sf::Vector2f GetPosition() { return m_position; }
	inline sf::Vector2f GetDimensions() { return sf::Vector2f(m_shape.getGlobalBounds().width, m_shape.getGlobalBounds().height); }

	inline sf::Uint32 GetState() { return m_state; }

	void update(sf::Event& e, sf::RenderWindow& window);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	sf::Color m_buttonColorNormal;
	sf::Color m_buttonColorHover;
	sf::Color m_buttonColorClicked;

	sf::Color m_textColorNormal;
	sf::Color m_textColorHover;
	sf::Color m_textColorClicked;

	sf::Color m_borderColor;

	float m_borderThickness;
	float m_borderRadius;

	sf::Vector2f m_size;
	sf::Vector2f m_position;

	State m_state;

	sf::RectangleShape m_shape;

	sf::Font m_font;
	uint32_t m_fontSize;

	sf::Text m_text;
};
