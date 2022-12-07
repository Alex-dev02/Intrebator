#include "../include/UI.hpp"

UI::UI(sf::RenderWindow& window) {
	m_gui.setTarget(window);

	auto windowWidth = tgui::bindWidth(m_gui);
	auto windowHeight = tgui::bindHeight(m_gui);

	m_gui.setTextSize(20);

	// Login Menu
	CreateLoginMenu(windowWidth, windowHeight);

	// Register menu
	CreateRegisterMenu(windowWidth, windowHeight);

	// Main menu
	CreateMainMenu(windowWidth, windowHeight);

	m_loginMenu->setVisible(true);
	m_registerMenu->setVisible(false);
	m_mainMenu->setVisible(false);
}

void UI::CreateLoginMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
{
	m_loginMenu = tgui::Group::create();

	tgui::EditBox::Ptr editBoxUsername = tgui::EditBox::create();
	editBoxUsername->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxUsername->setPosition(windowWidth * 422 / 1270, windowHeight * 214 / 720);
	editBoxUsername->setDefaultText("Username");
	m_loginMenu->add(editBoxUsername, "Username");

	tgui::EditBox::Ptr editBoxPassword = tgui::EditBox::create();
	editBoxPassword->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxPassword->setPosition(windowWidth * 422 / 1270, windowHeight * 329 / 720);
	editBoxPassword->setPasswordCharacter('*');
	editBoxPassword->setDefaultText("Password");
	m_loginMenu->add(editBoxPassword, "Password");

	tgui::Button::Ptr loginButton = tgui::Button::create();
	loginButton->setSize(windowWidth * 204 / 1270, windowHeight * 36.48 / 720);
	loginButton->setPosition(windowWidth * 422 / 1270, windowHeight * 443.75 / 720);
	loginButton->setText("Login");
	m_loginMenu->add(loginButton);

	tgui::Button::Ptr registerButton = tgui::Button::create();
	registerButton->setSize(windowWidth * 204 / 1270, windowHeight * 36.48 / 720);
	registerButton->setPosition(windowWidth * 643 / 1270, windowHeight * 443.75 / 720);
	registerButton->setText("Register");
	m_loginMenu->add(registerButton);

	loginButton->onClick([editBoxUsername, editBoxPassword, this]() {
		Login(editBoxUsername, editBoxPassword);
		});

	registerButton->onClick([editBoxUsername, editBoxPassword, this]() {
		m_loginMenu->setVisible(false);
	m_registerMenu->setVisible(true);
		});

	m_gui.add(m_loginMenu, "LoginMenu");
}

void UI::CreateRegisterMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
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
	registerButton->setSize(windowWidth / 4, windowHeight / 6);
	registerButton->setPosition(windowWidth / 4, windowHeight * 7 / 10);
	registerButton->setText("Register");
	m_registerMenu->add(registerButton);

	tgui::Button::Ptr loginButton = tgui::Button::create();
	loginButton->setSize(windowWidth / 4, windowHeight / 6);
	loginButton->setPosition(windowWidth / 4, windowHeight * 7 / 10);
	loginButton->setText("login");
	m_registerMenu->add(loginButton);


	loginButton->onClick([editBoxUsername, editBoxPassword, this]() {
		m_registerMenu->setVisible(false);
	m_loginMenu->setVisible(true);
		});


	registerButton->onClick([editBoxUsername, editBoxPassword, editBoxRepeatPassword, this]() {
		if (editBoxPassword->getText().toStdString() == editBoxRepeatPassword->getText().toStdString()) {
			CreateAccount(editBoxUsername, editBoxPassword);
		}
		else {
			//afiseaza cv mesaj de oroare
		}
		});

	m_gui.add(m_registerMenu, "RegisterMenu");
}

void UI::CreateMainMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
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

	playButton->onClick([]() {
		Debug::Log("Play");
		});

	optionsButton->onClick([]() {
		Debug::Log("Options");
		});

	exitButton->onClick([]() {
		Debug::Log("Exit");
		});


	m_gui.add(m_mainMenu, "MainMenu");
}

void UI::CreateAccount(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password) {
	std::cout << "Username: " << username->getText().toStdString() << std::endl;
	std::cout << "Password: " << password->getText().toStdString() << std::endl;
}

void UI::Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password) {
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
