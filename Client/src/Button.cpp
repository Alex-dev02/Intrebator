#include "../include/Button.hpp"

Button::Button(std::string text, sf::Font& font, sf::Vector2f position) 
	:m_fontSize(12) {

	m_buttonColorNormal = sf::Color(255, 255, 255);
	m_buttonColorHover = sf::Color(190, 190, 190);
	m_buttonColorClicked = sf::Color(30, 30, 30);

	//set position
	m_position = position;

	//set initial state
	m_state = State::Normal;

	//set up text
	m_text.setString(text);
	m_text.setFont(font);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
	m_text.setFillColor(m_textColorNormal);
	
	//set some defauts
	m_borderRadius = 5.0f;
	m_borderThickness = 0.0f;
	m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.5f);

	m_shape.setSize(m_size);
	m_shape.setOutlineThickness(m_borderThickness);
	m_shape.setOutlineColor(m_borderColor);

	m_shape.setOrigin(m_shape.getGlobalBounds().width / 2, m_shape.getGlobalBounds().height / 2);
	m_shape.setPosition(m_position);

	sf::Vector2f textPosition = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y - m_shape.getGlobalBounds().height / 4);

	m_text.setPosition(textPosition);
}

void Button::SetSize(uint32_t size) {
	m_fontSize = size;

	m_text.setCharacterSize(m_fontSize);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);

	m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, (m_text.getGlobalBounds().height + m_text.getGlobalBounds().height) * 1.5f);
	
	m_shape.setSize(m_size);
	m_shape.setOutlineThickness(m_borderThickness);
	m_shape.setOutlineColor(m_borderColor);
}

void Button::SetText(std::string text) {
	m_text.setString(text);
}

void Button::SetFont(sf::Font& font) {
	m_text.setFont(font);
}

void Button::update(sf::Event& e, sf::RenderWindow& window) {
	sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);

	bool mouseInButton = m_mousePosition.x >= m_shape.getPosition().x - m_shape.getGlobalBounds().width / 2
		&& m_mousePosition.x <= m_shape.getPosition().x + m_shape.getGlobalBounds().width / 2
		&& m_mousePosition.y >= m_shape.getPosition().y - m_shape.getGlobalBounds().height / 2
		&& m_mousePosition.y <= m_shape.getPosition().y + m_shape.getGlobalBounds().height / 2;

	if (e.type == sf::Event::MouseMoved)
	{
		if (mouseInButton)
		{
			m_state = Button::State::Hover;
		}
		else
		{
			m_state = Button::State::Normal;
		}
	}

	if (e.type == sf::Event::MouseButtonPressed)
	{
		switch (e.mouseButton.button)
		{
			case sf::Mouse::Left:
			{
				if (mouseInButton)
				{
					m_state = Button::State::Clicked;
				}

				else
				{
					m_state = Button::State::Normal;
				}
			}
			break;
		}
	}

	if (e.type == sf::Event::MouseButtonReleased)
	{
		switch (e.mouseButton.button)
		{
			case sf::Mouse::Left:
			{
				if (mouseInButton)
				{
					m_state = Button::State::Hover;
				}
				else
				{
					m_state = Button::State::Normal;
				}
			}
		}
	}

	switch (m_state)
	{
		case Button::State::Normal:
			m_shape.setFillColor(m_buttonColorNormal);
			m_text.setFillColor(m_textColorNormal);

			break;

		case Button::State::Hover:
			m_shape.setFillColor(m_buttonColorHover);
			m_text.setFillColor(m_textColorHover);

			break;

		case Button::State::Clicked:
			m_shape.setFillColor(m_buttonColorClicked);
			m_text.setFillColor(m_textColorClicked);

			break;

		default:
			break;
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_shape);
	target.draw(m_text);
}