#pragma once

#include <string>
#include <TGUI/Color.hpp>

class Player {
public:
	uint32_t id = -1;
	std::string name = "Test name";
	tgui::Color color = tgui::Color::Black;
};
