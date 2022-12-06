#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>

#include "../../Logger/Debug.hpp"

class UI
{
public:
	UI(sf::RenderWindow& window) {
		m_gui.setTarget(window);

		auto windowWidth = tgui::bindWidth(m_gui);
		auto windowHeight = tgui::bindHeight(m_gui);

		m_gui.setTextSize(20);

		// Login Menu
		{
			m_loginMenu = tgui::Group::create();

			tgui::EditBox::Ptr editBoxUsername = tgui::EditBox::create();
			editBoxUsername->setSize(windowWidth / 2, windowHeight / 8);
			editBoxUsername->setPosition(windowWidth / 6, windowHeight / 6);
			editBoxUsername->setDefaultText("Username");
			m_loginMenu->add(editBoxUsername, "Username");

			tgui::EditBox::Ptr editBoxPassword = tgui::EditBox::create();
			editBoxPassword->setSize(windowWidth / 2, windowHeight / 8);
			editBoxPassword->setPosition(windowWidth / 6, windowHeight * 5 / 12);
			editBoxPassword->setPasswordCharacter('*');
			editBoxPassword->setDefaultText("Password");
			m_loginMenu->add(editBoxPassword, "Password");

			tgui::Button::Ptr loginButton = tgui::Button::create();
			loginButton->setSize(windowWidth / 4, windowHeight / 6);
			loginButton->setPosition(windowWidth / 4, windowHeight * 7 / 10);
			loginButton->setText("Login");
			m_loginMenu->add(loginButton);

			loginButton->onClick([editBoxUsername, editBoxPassword, this]() {
				login(editBoxUsername, editBoxPassword);
				});

			m_gui.add(m_loginMenu, "LoginMenu");
		}

		// Register menu
		{
			m_registerMenu = tgui::Group::create();

			tgui::EditBox::Ptr editBoxUsername = tgui::EditBox::create();
			editBoxUsername->setSize(windowWidth * 2 / 3, windowHeight / 8);
			editBoxUsername->setPosition(windowWidth / 6, windowHeight / 6);
			editBoxUsername->setDefaultText("Username");
			m_registerMenu->add(editBoxUsername, "Username");

			tgui::EditBox::Ptr editBoxPassword = tgui::EditBox::create();
			editBoxPassword->setSize(windowWidth * 2 / 3, windowHeight / 8);
			editBoxPassword->setPosition(windowWidth / 6, windowHeight * 5 / 12);
			editBoxPassword->setPasswordCharacter('*');
			editBoxPassword->setDefaultText("Password");
			m_registerMenu->add(editBoxPassword, "Password");

			tgui::EditBox::Ptr editBoxRepeatPassword = tgui::EditBox::create();
			editBoxRepeatPassword->setSize(windowWidth * 2 / 3, windowHeight / 8);
			editBoxRepeatPassword->setPosition(windowWidth / 6, windowHeight * 5 / 12);
			editBoxRepeatPassword->setPasswordCharacter('*');
			editBoxRepeatPassword->setDefaultText("Repeat password");
			m_registerMenu->add(editBoxRepeatPassword, "Repeatpassword");

			tgui::Button::Ptr registerButton = tgui::Button::create();
			registerButton->setSize(windowWidth / 2, windowHeight / 6);
			registerButton->setPosition(windowWidth / 4, windowHeight * 7 / 10);
			registerButton->setText("Register");
			m_registerMenu->add(registerButton);

			registerButton->onClick([editBoxUsername, editBoxPassword, editBoxRepeatPassword, this]() {
				if (editBoxPassword->getText().toStdString() == editBoxRepeatPassword->getText().toStdString()) {
					createAccount(editBoxUsername, editBoxPassword);
				}
				else {
					//afiseaza cv mesaj de oroare
				}
				});

			m_gui.add(m_registerMenu, "RegisterMenu");
		}


		// Main menu
		{
			m_mainMenu = tgui::Group::create();

			tgui::Button::Ptr playButton = tgui::Button::create();
			playButton->setSize(windowWidth / 2, windowHeight / 6);
			playButton->setPosition(windowWidth / 4, windowHeight * 1 / 10);
			playButton->setText("Play");
			m_mainMenu->add(playButton);

			tgui::Button::Ptr optionsButton = tgui::Button::create();
			optionsButton->setSize(windowWidth / 2, windowHeight / 6);
			optionsButton->setPosition(windowWidth / 4, windowHeight * 4 / 10);
			optionsButton->setText("Options");
			m_mainMenu->add(optionsButton);

			tgui::Button::Ptr exitButton = tgui::Button::create();
			exitButton->setSize(windowWidth / 2, windowHeight / 6);
			exitButton->setPosition(windowWidth / 4, windowHeight * 7 / 10);
			exitButton->setText("Exit");
			m_mainMenu->add(exitButton);

			m_gui.add(m_mainMenu, "MainMenu");
		}



		m_loginMenu->setVisible(true);
		m_registerMenu->setVisible(false);
		m_mainMenu->setVisible(false);
	}

	tgui::Gui& GetGui() {
		return m_gui;
	}

	void Draw() {
		m_gui.draw();
	}

	void HandleEvent(sf::Event event) {
		m_gui.handleEvent(event);
	}

private:
	void createAccount(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password) {
		std::cout << "Username: " << username->getText().toStdString() << std::endl;
		std::cout << "Password: " << password->getText().toStdString() << std::endl;
	}

	void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password) {
		std::cout << "Username: " << username->getText().toStdString() << std::endl;
		std::cout << "Password: " << password->getText().toStdString() << std::endl;

		if (true) { // adica daca il gasesti in baza de date sau nu
			// connect sau cv
			m_loginMenu->setVisible(false);
			m_mainMenu->setVisible(true);
		}
		else {
			//zi-le ca nu ii boon
		}
	}

private:
	tgui::Gui m_gui;

	tgui::Group::Ptr m_loginMenu;
	tgui::Group::Ptr m_registerMenu;
	tgui::Group::Ptr m_mainMenu;
};