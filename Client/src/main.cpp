#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "../include/Button.hpp"

int main() {

	// Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Triviador");
	sf::Font font;

	if (!font.loadFromFile("assets/Inter-Medium.ttf")) {
		std::cerr << "Could not find contb.ttf font." << std::endl;
	}


	Button play("Play", font, sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2) - sf::Vector2f(0.0f, 100.0f));
	Button options("Options", font, sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	Button exit("Exit", font, sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2) + sf::Vector2f(0.0f, 100.0f));

	sf::Event event;

	// Game loop
	while (window.isOpen()) {

		// Event polling
		while (window.pollEvent(event)) {

			switch (event.type) {

				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape) {

						window.close();

					}
					break;

				default:
					break;
			}
		}

		// Update
		play.update(event, window);
		options.update(event, window);
		exit.update(event, window);

		// Render
		window.clear(sf::Color::Blue); // Clear old frame

		window.draw(play);
		window.draw(options);
		window.draw(exit);

		// Draw your game
		window.display(); // Tell the app that the window is done drawing
	}


	// End of the application
	return 0;
}