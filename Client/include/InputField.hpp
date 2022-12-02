#pragma once

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

class InputField {
public:
	InputField() = default;

	InputField(int32_t size, sf::Color color, bool selected);

	inline void SetFont(sf::Font& font) { m_textBox.setFont(font); }
	inline void SetPosition(const sf::Vector2f& pos) { m_textBox.setPosition(pos); }
	inline void SetLimit(bool ToF) { m_hasLimit = ToF; }
	void SetLimit(bool ToF, int32_t limit);

	void SetSelected(bool selected);

	inline std::string GetText() { return m_text.str(); }

	inline void DrawTo(sf::RenderWindow& window) { window.draw(m_textBox); }

	void TypedOn(sf::Event input);

private:
	void InputLogic(sf::Keyboard::Key charTyped);
	void DeleteLastCharacter();

private:
	sf::Text m_textBox;
	std::ostringstream m_text;

	bool m_isSelected = false;
	bool m_hasLimit = false;
	int32_t m_limit = 0;
};