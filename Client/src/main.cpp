#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

//#include "../include/Button.hpp"
//#include "../include/InputField.hpp"

#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>

#include "../../Logger/Debug.hpp"



void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
{
	std::cout << "Username: " << username->getText().toStdString() << std::endl;
	std::cout << "Password: " << password->getText().toStdString() << std::endl;
}

void loadWidgets(tgui::Gui& gui)
{
	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	auto windowWidth = tgui::bindWidth(gui);
	auto windowHeight = tgui::bindHeight(gui);



	// Create the username edit box
	tgui::EditBox::Ptr editBoxUsername = std::make_shared<tgui::EditBox>();
	editBoxUsername->setSize(windowWidth * 2 / 3, windowHeight / 8);
	editBoxUsername->setPosition(windowWidth / 6, windowHeight / 6);
	editBoxUsername->setDefaultText("Username");
	gui.add(editBoxUsername, "Username");

	// Create the password edit box
	tgui::EditBox::Ptr editBoxPassword = std::make_shared<tgui::EditBox>();
	editBoxPassword->setSize(windowWidth * 2 / 3, windowHeight / 8);
	editBoxPassword->setPosition(windowWidth / 6, windowHeight * 5 / 12);
	editBoxPassword->setPasswordCharacter('*');
	editBoxPassword->setDefaultText("Password");
	gui.add(editBoxPassword, "Password");

	// Create the login button
	tgui::Button::Ptr button = std::make_shared<tgui::Button>();
	button->setSize(windowWidth / 2, windowHeight / 6);
	button->setPosition(windowWidth / 4, windowHeight * 7 / 10);
	button->setText("Login");
	gui.add(button);

	// Call the login function when the button is pressed

	button->onClick([editBoxUsername, editBoxPassword]() {
		login(editBoxUsername, editBoxPassword);
		});
}



int main() {
	// Window
	sf::RenderWindow window(sf::VideoMode(1270, 720), "Triviador");

	tgui::Gui menu(window);

	try {
		loadWidgets(menu);
	}
	catch (const tgui::Exception e) {
		Debug::LogError(e.what());
	}

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

	tgui::Button play("Play");
	tgui::Button options("Play");
	tgui::Button exit("Play");

	play.setPosition(tgui::Layout2d(window.getSize().x / 2, window.getSize().y / 2) - tgui::Layout2d(0.0f, 100.0f));
	options.setPosition(tgui::Layout2d(window.getSize().x / 2, window.getSize().y / 2));
	exit.setPosition(tgui::Layout2d(window.getSize().x / 2, window.getSize().y / 2) + tgui::Layout2d(0.0f, 100.0f));

	play.onClick([&window]() {
		Debug::Log("play");
		});


	options.onClick([&window]() {
		Debug::Log("options");
		});


	exit.onClick([&window]() {
		window.close();
		});

	/*Button play("Play", font, sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2) - sf::Vector2f(0.0f, 100.0f));
	Button options("Options", font, sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	Button exit("Exit", font, sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2) + sf::Vector2f(0.0f, 100.0f));

	InputField inputField(20, sf::Color::White, true);

	inputField.SetFont(font);
	inputField.SetPosition(sf::Vector2f(100.0f, 100.0f));*/

	// Game loop
	while (window.isOpen()) {

		// Event polling
		sf::Event event;
		while (window.pollEvent(event)) {

			menu.handleEvent(event);

			switch (event.type) {

			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));

				menu.setAbsoluteView(tgui::FloatRect(0, 0, event.size.width, event.size.height));

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				break;

			case sf::Event::TextEntered:
				//inputField.TypedOn(event);
				break;

			default:
				break;
			}
		}

		// Update





		// Render
		window.clear(); // Clear old frame

		menu.draw();

		window.display(); // Tell the app that the window is done drawing
	}

	// End of the application
	return 0;
}