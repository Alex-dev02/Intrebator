#include "../include/InputField.hpp"

InputField::InputField(int32_t size, sf::Color color, bool isSelected)
	: m_isSelected(isSelected) {
	m_textBox.setCharacterSize(size);
	m_textBox.setFillColor(color);
	if (m_isSelected) {
		m_textBox.setString("_");
	}
	else {
		m_textBox.setString("");
	}
}

void InputField::SetLimit(bool ToF, int32_t limit) { 
	m_hasLimit = ToF; 
	m_limit = limit - 1;
}

void InputField::SetSelected(bool selected) {
	m_isSelected = selected;

	if (!selected) {

		auto text = m_text.str();
		std::string newText = "";

		for (size_t i = 0; i < text.length() - 1; i++) {
			newText += text[i];
		}

		m_textBox.setString(newText);
	}
}

void InputField::TypedOn(sf::Event input) {
	if (m_isSelected) {
		sf::Keyboard::Key charTyped = input.key.code;

		if (sf::Keyboard::A < charTyped && charTyped < sf::Keyboard::Z) {
			if (m_hasLimit) {
				if (m_text.str().length() <= m_limit) {
					InputLogic(charTyped);
				}
				else {
					if (m_text.str().length() > m_limit && charTyped == sf::Keyboard::BackSpace) {
						DeleteLastCharacter();
					}
				}
			}
			else {
				InputLogic(charTyped);
			}
		}
	}
}

void InputField::InputLogic(sf::Keyboard::Key charTyped) {

	switch (charTyped) {

	case sf::Keyboard::Escape:
		break;
	case sf::Keyboard::Enter:
		break;
	case sf::Keyboard::Delete:
		if (m_text.str().length() > 0) {
			DeleteLastCharacter();
		}
		break;
	default:
		if (charTyped != sf::Keyboard::Escape) {
			m_text << charTyped;
		}
		break;
	}
	m_textBox.setString(m_text.str() + "_");
}

void InputField::DeleteLastCharacter()
{
	std::string text = m_text.str();
	std::string newText = "";

	for (size_t i = 0; i < text.length() - 1; i++) {
		newText += text[i];
	}
	m_text.str("");
	m_text << newText;

	m_textBox.setString(m_text.str());
}