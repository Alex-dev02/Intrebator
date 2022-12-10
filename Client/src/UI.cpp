#include "../include/UI.hpp"

UI::UI(sf::RenderWindow& window) {
	m_window = &window;
	m_gui.setTarget(window);

	auto windowWidth = tgui::bindWidth(m_gui);
	auto windowHeight = tgui::bindHeight(m_gui);

	m_gui.setTextSize(20);

	tgui::Picture::Ptr background = tgui::Picture::create("assets/images/background.png");

	//put the image in the center of the screen
	background->setSize(windowWidth, windowHeight);
	background->setPosition(windowWidth / 1270, windowHeight / 720);

	m_gui.add(background);

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

void UI::CreateLoginMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_loginMenu = tgui::Group::create();

	tgui::EditBox::Ptr editBoxUsername = tgui::EditBox::create();
	editBoxUsername->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxUsername->setPosition(windowWidth * 422 / 1270, windowHeight * 214 / 720);
	editBoxUsername->setDefaultText("Username");

	tgui::EditBox::Ptr editBoxPassword = tgui::EditBox::create();
	editBoxPassword->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxPassword->setPosition(windowWidth * 422 / 1270, windowHeight * 329 / 720);
	editBoxPassword->setPasswordCharacter('*');
	editBoxPassword->setDefaultText("Password");

	tgui::Button::Ptr loginButton = tgui::Button::create();
	loginButton->setSize(windowWidth * 204 / 1270, windowHeight * 36.48 / 720);
	loginButton->setPosition(windowWidth * 422 / 1270, windowHeight * 443.75 / 720);
	loginButton->setText("Login");

	tgui::Button::Ptr registerButton = tgui::Button::create();
	registerButton->setSize(windowWidth * 204 / 1270, windowHeight * 36.48 / 720);
	registerButton->setPosition(windowWidth * 643 / 1270, windowHeight * 443.75 / 720);
	registerButton->setText("Register");

	m_loginMenu->add(editBoxUsername);
	m_loginMenu->add(editBoxPassword);
	m_loginMenu->add(loginButton);
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

void UI::CreateRegisterMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_registerMenu = tgui::Group::create();

	tgui::EditBox::Ptr editBoxUsername = tgui::EditBox::create();
	editBoxUsername->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxUsername->setPosition(windowWidth * 422 / 1270, windowHeight * 169 / 720);
	editBoxUsername->setDefaultText("Username");

	tgui::EditBox::Ptr editBoxPassword = tgui::EditBox::create();
	editBoxPassword->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxPassword->setPosition(windowWidth * 422 / 1270, windowHeight * 284 / 720);
	editBoxPassword->setPasswordCharacter('*');
	editBoxPassword->setDefaultText("Password");

	tgui::EditBox::Ptr editBoxRepeatPassword = tgui::EditBox::create();
	editBoxRepeatPassword->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxRepeatPassword->setPosition(windowWidth * 422 / 1270, windowHeight * 399 / 720);
	editBoxRepeatPassword->setPasswordCharacter('*');
	editBoxRepeatPassword->setDefaultText("Repeat password");

	tgui::Button::Ptr registerButton = tgui::Button::create();
	registerButton->setSize(windowWidth * 204 / 1270, windowHeight * 36.48 / 720);
	registerButton->setPosition(windowWidth * 643 / 1270, windowHeight * 513.75 / 720);
	registerButton->setText("Register");

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->setSize(windowWidth * 204 / 1270, windowHeight * 36.48 / 720);
	backButton->setPosition(windowWidth * 422 / 1270, windowHeight * 513.75 / 720);
	backButton->setText("Back");

	m_registerMenu->add(editBoxUsername);
	m_registerMenu->add(editBoxPassword);
	m_registerMenu->add(editBoxRepeatPassword);
	m_registerMenu->add(registerButton);
	m_registerMenu->add(backButton);

	backButton->onClick([editBoxUsername, editBoxPassword, this]() {
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

void UI::CreateMainMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_mainMenu = tgui::Group::create();

	tgui::Button::Ptr playButton = tgui::Button::create();
	playButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	playButton->setPosition(windowWidth * 73 / 1270, windowHeight * 420 / 720);
	playButton->setText("Play");

	tgui::Button::Ptr optionsButton = tgui::Button::create();
	optionsButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	optionsButton->setPosition(windowWidth * 73 / 1270, windowHeight * 507.56 / 720);
	optionsButton->setText("Options");

	tgui::Button::Ptr exitButton = tgui::Button::create();
	exitButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	exitButton->setPosition(windowWidth * 73 / 1270, windowHeight * 595.09 / 720);
	exitButton->setText("Exit");

	m_mainMenu->add(playButton);
	m_mainMenu->add(optionsButton);
	m_mainMenu->add(exitButton);

	playButton->onClick([]() {
		Debug::Log("Play");
		});

	optionsButton->onClick([]() {
		Debug::Log("Options");
		});


	exitButton->onClick([this]() {
		Debug::Log("Exit");
	m_window->close();
		});

	m_gui.add(m_mainMenu, "MainMenu");
}

void UI::CreateAccount(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password) {
	Debug::Log("Registered man");
	Debug::Log("Username: " + username->getText().toStdString());
	Debug::Log("Password: " + password->getText().toStdString());

	if (true) { // daca are net si reuseste sa-si faca cont
		// connect sau cv
		m_registerMenu->setVisible(false);
		m_mainMenu->setVisible(true);
	}
	else {
		//zi-le ca nu se poate accesa serveru din cine stie ce motiv
	}
}

void UI::Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password) {
	Debug::Log("Username: " + username->getText().toStdString());
	Debug::Log("Password: " + password->getText().toStdString());

	if (true) { // adica daca il gasesti in baza de date sau nu
		// connect sau cv
		m_loginMenu->setVisible(false);
		m_mainMenu->setVisible(true);
	}
	else {
		//zi-le ca nu ii boon
	}
}
