#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main() {

	// Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Triviador");
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


		// Render
		window.clear(sf::Color::Blue); // Clear old frame


		// Draw your game
		window.display(); // Tell the app that the window is done drawing
	}


	// End of the application
	return 0;
}