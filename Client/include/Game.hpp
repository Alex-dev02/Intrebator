#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "../include/UI.hpp"

#include "../include/Network.hpp"

#include "../../Logger/Debug.hpp"

class Game {
public:
	Game();
	void Run();

private:
	sf::RenderWindow m_window;
	UI m_ui;
	sf::Image m_icon;
	sf::Image m_background;
	sf::Font m_font;
	sf::Music m_music;
	Network m_network;
};
