#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "../include/UI.hpp"

#include "../../Logger/Debug.hpp"

int main() {
	// Window
	sf::RenderWindow window(sf::VideoMode(1270, 720), "Triviador");

	UI ui(window);

	auto image = sf::Image{};
	if (!image.loadFromFile("assets/images/icon.png"))
	{
		Debug::LogError("Image not found");
	}
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

	sf::Font font;

	sf::Music music;

	if (!music.openFromFile("assets/audio/music/menu song.ogg")) {
		Debug::LogError("Error loading music");
	}
	music.setLoop(true);
	music.play();

	if (!font.loadFromFile("assets/fonts/Inter-Medium.ttf")) {
		Debug::LogError("Could not find contb.ttf font.");
	}

	// Game loop
	while (window.isOpen()) {

		// Event polling
		sf::Event event;
		while (window.pollEvent(event)) {

			ui.HandleEvent(event);

			switch (event.type) {

			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));

				ui.GetGui().setAbsoluteView(tgui::FloatRect(0, 0, event.size.width, event.size.height));

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				break;

			case sf::Event::TextEntered:
				break;

			default:
				break;
			}
		}

		// Update

		// Render
		window.clear(); // Clear old frame

		ui.Draw();

		window.display(); // Tell the app that the window is done drawing
	}

	// End of the application
	return 0;
}