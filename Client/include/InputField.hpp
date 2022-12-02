#pragma once

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

class InputField {
public:
	InputField() = default;

	InputField(int32_t size, sf::Color color, bool selected);

private:
	void InputLogic(sf::Keyboard::Key charTyped);
	void DeleteLastCharacter();

private:
	sf::Text m_textBox;
	std::ostringstream m_text;

	bool m_isSelected = false;
	bool m_hasLimit = false;

	int32_t limit;
};