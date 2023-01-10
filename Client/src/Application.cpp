#include "../include/Application.hpp"

Application::Application()
	: m_window(sf::VideoMode(1270, 720), "Triviador", sf::Style::Titlebar | sf::Style::Close), m_menu(m_window), m_game(m_window)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.setPosition(sf::Vector2i((desktop.width - 1270) / 2, (desktop.height - 720) / 2));
	m_window.setFramerateLimit(60);
	m_window.setVerticalSyncEnabled(true);

	if (!m_icon.loadFromFile("assets/images/icon.png"))
	{
		Debug::LogError("Game icon not found");
	}
	m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());

	if (!m_font.loadFromFile("assets/fonts/Inter-Medium.ttf"))
	{
		Debug::LogError("Could not find Inter-Medium.ttf font.");
	}
}

void Application::Run()
{
	while (m_window.isOpen())
	{
		// Event polling
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			m_menu.HandleEvent(event);

			switch (event.type)
			{
				case sf::Event::Closed:
					m_menu.LeaveMatch();
					m_window.close();
					break;

				default:
					break;
			}
		}

		// Update

		// Render
		m_window.clear(); // Clear old frame

		m_menu.Draw();

		m_window.display(); // Tell the app that the m_window is done drawing
	}
}
