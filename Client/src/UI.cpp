#include "../include/UI.hpp"
#include "../include/Network.hpp"
#include <cpr/cpr.h>

UI::UI(sf::RenderWindow& window) {
	m_window = &window;

	auto windowWidth = tgui::bindWidth(m_gui);
	auto windowHeight = tgui::bindHeight(m_gui);

	tgui::Picture::Ptr background = tgui::Picture::create("assets/images/background.png");
	background->setSize(windowWidth, windowHeight);

	m_gui.setTarget(window);
	m_gui.setFont(tgui::Font("assets/fonts/Inter-Medium.ttf"));
	m_gui.setTextSize(20);
	m_gui.add(background);

	// Login Menu
	CreateLoginMenu(windowWidth, windowHeight);

	// Register menu
	CreateRegisterMenu(windowWidth, windowHeight);

	// Main menu
	CreateMainMenu(windowWidth, windowHeight);

	// Match Selector Menu
	CreateMatchSelectorMenu(windowWidth, windowHeight);

	// Options Menu
	CreateOptionsMenu(windowWidth, windowHeight);

	m_loginMenu->setVisible(true);
	m_registerMenu->setVisible(false);
	m_mainMenu->setVisible(false);
	m_matchSelectorMenu->setVisible(false);
	m_optionsMenu->setVisible(false);
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

	m_gui.add(m_loginMenu);
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
			// TODO : afiseaza cv mesaj de oroare
		}
		});

	m_gui.add(m_registerMenu);
}

void UI::CreateMainMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_mainMenu = tgui::Group::create();

	tgui::Label::Ptr usernameLabel = tgui::Label::create();
	usernameLabel->setTextSize(80);
	usernameLabel->setPosition(windowWidth * 73 / 1270, windowHeight * 100 / 720);
	usernameLabel->setText("Username");

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

	m_mainMenu->add(usernameLabel);
	m_mainMenu->add(playButton);
	m_mainMenu->add(optionsButton);
	m_mainMenu->add(exitButton);

	playButton->onClick([this]() {
		Debug::Log("Play");
	m_mainMenu->setVisible(false);
	m_matchSelectorMenu->setVisible(true);
		});

	optionsButton->onClick([this]() {
		Debug::Log("Options");
	m_mainMenu->setVisible(false);
	m_optionsMenu->setVisible(true);
		});

	exitButton->onClick([this]() {
		Debug::Log("Exit");
	m_window->close();
		});

	m_gui.add(m_mainMenu);
}

void UI::CreateMatchSelectorMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_matchSelectorMenu = tgui::Group::create();

	tgui::Button::Ptr twoPlayerButton = tgui::Button::create();
	twoPlayerButton->setSize(windowWidth * 218 / 1270, windowHeight * 281 / 720);
	twoPlayerButton->setPosition(windowWidth * 256 / 1270, windowHeight * 219.5 / 720);
	twoPlayerButton->setText("2 players");

	tgui::Button::Ptr threePlayerButton = tgui::Button::create();
	threePlayerButton->setSize(windowWidth * 218 / 1270, windowHeight * 281 / 720);
	threePlayerButton->setPosition(windowWidth * 526 / 1270, windowHeight * 219.5 / 720);
	threePlayerButton->setText("3 players");

	tgui::Button::Ptr fourPlayerButton = tgui::Button::create();
	fourPlayerButton->setSize(windowWidth * 218 / 1270, windowHeight * 281 / 720);
	fourPlayerButton->setPosition(windowWidth * 796 / 1270, windowHeight * 219.5 / 720);
	fourPlayerButton->setText("4 players");

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	backButton->setPosition(windowWidth * 73 / 1270, windowHeight * 595.09 / 720);
	backButton->setText("Back");

	m_matchSelectorMenu->add(twoPlayerButton);
	m_matchSelectorMenu->add(threePlayerButton);
	m_matchSelectorMenu->add(fourPlayerButton);
	m_matchSelectorMenu->add(backButton);

	twoPlayerButton->onClick([]() {
		Debug::Log("2 players");
		});

	threePlayerButton->onClick([]() {
		Debug::Log("3 players");
		});

	fourPlayerButton->onClick([]() {
		Debug::Log("4 players");
		});

	backButton->onClick([this]() {
		Debug::Log("Back");
	m_mainMenu->setVisible(true);
	m_matchSelectorMenu->setVisible(false);
		});

	m_gui.add(m_matchSelectorMenu);
}

void UI::CreateOptionsMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
{
	m_optionsMenu = tgui::Group::create();

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	backButton->setPosition(windowWidth * 73 / 1270, windowHeight * 595.09 / 720);
	backButton->setText("Back");

	m_optionsMenu->add(backButton);

	backButton->onClick([this]() {
		Debug::Log("Back");
	m_mainMenu->setVisible(true);
	m_optionsMenu->setVisible(false);
		});

	m_gui.add(m_optionsMenu);
}

void UI::CreateAccount(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password) {
	Debug::Log("Registered man");
	Debug::Log("Username: " + username->getText().toStdString());
	Debug::Log("Password: " + password->getText().toStdString());

	cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:8080/user/register" },
		cpr::Body{ "name=" + username->getText().toStdString() + "&password=" + password->getText().toStdString() },
		cpr::Header{ { "Content-Type", "application/x-www-form-urlencoded" } });

	if (true) { // daca are net si reuseste sa-si faca cont
		// connect sau cv
		m_registerMenu->setVisible(false);
		m_mainMenu->setVisible(true);
		//Network::localPlayer.SetUsername(username->getText().toStdString());
	}
	else {
		//zi-le ca nu se poate accesa serveru din cine stie ce motiv
	}
}

void UI::Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password) {
	Debug::Log("Username: " + username->getText().toStdString());
	Debug::Log("Password: " + password->getText().toStdString());

	cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:8080/user/login" },
		cpr::Body{ "name=" + username->getText().toStdString() + "&password=" + password->getText().toStdString() },
		cpr::Header{ { "Content-Type", "application/x-www-form-urlencoded" } });

	if (true) { // adica daca il gasesti in baza de date sau nu
		// connect sau cv
		m_loginMenu->setVisible(false);
		m_mainMenu->setVisible(true);
		//Network::localPlayer.SetUsername(username->getText().toStdString());
	}
	else {
		//zi-le ca nu ii boon
	}
}
