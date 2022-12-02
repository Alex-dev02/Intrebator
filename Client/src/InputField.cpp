#include "../include/InputField.hpp"

InputField::InputField(int32_t size, sf::Color color, bool isSelected)
	: m_isSelected(isSelected) {
	m_textBox.setCharacterSize(size);
	m_textBox.setFillColor(color);
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
			m_text << static_cast<char>(charTyped);
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