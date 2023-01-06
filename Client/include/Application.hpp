#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "../include/Game.hpp"

#include "../../Logger/Debug.hpp"

class Application
{
public:
	Application();
	void Run();

private:
	sf::RenderWindow m_window;
	Game m_game;
	sf::Image m_icon;
	sf::Image m_background;
	sf::Font m_font;
};
