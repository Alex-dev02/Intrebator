#include "../include/Game.hpp"

Game::Game()
	: m_window(sf::VideoMode(1270, 720), "Triviador", sf::Style::Titlebar | sf::Style::Close), m_ui(m_window)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.setPosition(sf::Vector2i((desktop.width - 1270) / 2, (desktop.height - 720) / 2));
	m_window.setFramerateLimit(60);
	m_window.setVerticalSyncEnabled(true);


	if (!m_icon.loadFromFile("assets/images/icon.png")) {
		Debug::LogError("Image not found");
	}
	m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());

	if (!m_music.openFromFile("assets/audio/music/menu song.ogg")) {
		Debug::LogError("Error loading music");
	}
	m_music.setLoop(true);
	m_music.play();

	if (!m_font.loadFromFile("assets/fonts/Inter-Medium.ttf")) {
		Debug::LogError("Could not find contb.ttf font.");
	}
}

void Game::Run() {
	while (m_window.isOpen()) {

		// Event polling
		sf::Event event;
		while (m_window.pollEvent(event)) {

			m_ui.HandleEvent(event);

			switch (event.type) {

				case sf::Event::Resized:
					m_window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));

					m_ui.GetGui().setAbsoluteView(tgui::FloatRect(0, 0, event.size.width, event.size.height));

				case sf::Event::Closed:
					m_window.close();
					break;

				case sf::Event::KeyPressed:
					break;

				default:
					break;
			}
		}

		// Update

		// Render
		m_window.clear(); // Clear old frame

		m_ui.Draw();

		m_window.display(); // Tell the app that the m_window is done drawing
	}
}
