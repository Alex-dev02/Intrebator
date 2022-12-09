#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "../include/UI.hpp"

#include "../include/Network.hpp"

#include "../../Logger/Debug.hpp"

class Game {
public:

	Game()
		: window(sf::VideoMode(1270, 720), "Triviador"), ui(window)
	{
		if (!icon.loadFromFile("assets/images/icon.png")) {
			Debug::LogError("Image not found");
		}
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		if (!music.openFromFile("assets/audio/music/menu song.ogg")) {
			Debug::LogError("Error loading music");
		}
		music.setLoop(true);
		music.play();

		if (!font.loadFromFile("assets/fonts/Inter-Medium.ttf")) {
			Debug::LogError("Could not find contb.ttf font.");
		}
	}

	void Run() {
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
	}

private:
	sf::RenderWindow window;
	UI ui;
	sf::Image icon;
	sf::Font font;
	sf::Music music;
	Network network;
};
