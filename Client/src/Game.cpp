#include "../include/Game.hpp"

#include <cpr/cpr.h>
#include <crow.h>

Game::Game(sf::RenderWindow& window) {
	m_window = &window;

	//m_user.name = "test"; // TODO : just for debug purposes, delete when the user assignment has been completed

	auto windowWidth = tgui::bindWidth(m_gui);
	auto windowHeight = tgui::bindHeight(m_gui);

	tgui::Picture::Ptr background = tgui::Picture::create("assets/images/background.png");
	background->setSize(windowWidth, windowHeight);

	m_gui.setTarget(window);
	m_gui.setFont(tgui::Font("assets/fonts/Inter-Medium.ttf"));
	m_gui.add(background);

	CreateLoginMenu(windowWidth, windowHeight);
	CreateRegisterMenu(windowWidth, windowHeight);

	m_menus = tgui::Group::create();
	m_menus->add(m_loginMenu);
	m_menus->add(m_registerMenu);

	m_menus->setVisible(true);

	m_loginMenu->setVisible(true);
	m_registerMenu->setVisible(false);

	m_gui.add(m_menus);
}

void Game::CreateLoginMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_loginMenu = tgui::Group::create();
	m_loginMenu->setTextSize(20);

	tgui::EditBox::Ptr editBoxUsername = tgui::EditBox::create();
	editBoxUsername->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxUsername->setPosition(windowWidth * 422 / 1270, windowHeight * 214 / 720);
	editBoxUsername->setInputValidator("[^ ]*");
	editBoxUsername->setDefaultText("Username");

	tgui::EditBox::Ptr editBoxPassword = tgui::EditBox::create();
	editBoxPassword->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxPassword->setPosition(windowWidth * 422 / 1270, windowHeight * 329 / 720);
	editBoxPassword->setInputValidator("[^ ]*");
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

	tgui::Label::Ptr errorLabel = tgui::Label::create();
	errorLabel->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	errorLabel->setPosition(windowWidth * 422 / 1270, windowHeight * 525 / 720);
	errorLabel->setText("");
	errorLabel->getRenderer()->setTextColor(tgui::Color::Red);

	m_loginMenu->add(editBoxUsername);
	m_loginMenu->add(editBoxPassword);
	m_loginMenu->add(loginButton);
	m_loginMenu->add(registerButton);
	m_loginMenu->add(errorLabel);

	editBoxUsername->onReturnKeyPress([editBoxPassword] {
		editBoxPassword->setFocused(true);
		});

	editBoxPassword->onReturnKeyPress([errorLabel, editBoxUsername, editBoxPassword, this] {
		errorLabel->setText(Login(editBoxUsername, editBoxPassword));
		});

	loginButton->onClick([errorLabel, editBoxUsername, editBoxPassword, this]() {
		errorLabel->setText(Login(editBoxUsername, editBoxPassword));
		});

	registerButton->onClick([editBoxUsername, editBoxPassword, this]() {
		m_loginMenu->setVisible(false);
	m_registerMenu->setVisible(true);
		});
}

void Game::CreateRegisterMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_registerMenu = tgui::Group::create();
	m_registerMenu->setTextSize(20);

	tgui::EditBox::Ptr editBoxUsername = tgui::EditBox::create();
	editBoxUsername->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxUsername->setPosition(windowWidth * 422 / 1270, windowHeight * 169 / 720);
	editBoxUsername->setInputValidator("[^ ]*");
	editBoxUsername->setDefaultText("Username");

	tgui::EditBox::Ptr editBoxPassword = tgui::EditBox::create();
	editBoxPassword->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxPassword->setPosition(windowWidth * 422 / 1270, windowHeight * 284 / 720);
	editBoxPassword->setInputValidator("[^ ]*");
	editBoxPassword->setPasswordCharacter('*');
	editBoxPassword->setDefaultText("Password");

	tgui::EditBox::Ptr editBoxRepeatPassword = tgui::EditBox::create();
	editBoxRepeatPassword->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	editBoxRepeatPassword->setPosition(windowWidth * 422 / 1270, windowHeight * 399 / 720);
	editBoxRepeatPassword->setInputValidator("[^ ]*");
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

	tgui::Label::Ptr errorLabel = tgui::Label::create();
	errorLabel->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	errorLabel->setPosition(windowWidth * 422 / 1270, windowHeight * 568 / 720);
	errorLabel->setText("");
	errorLabel->getRenderer()->setTextColor(tgui::Color::Red);

	m_registerMenu->add(editBoxUsername);
	m_registerMenu->add(editBoxPassword);
	m_registerMenu->add(editBoxRepeatPassword);
	m_registerMenu->add(registerButton);
	m_registerMenu->add(backButton);
	m_registerMenu->add(errorLabel);

	editBoxUsername->onReturnKeyPress([editBoxPassword] {
		editBoxPassword->setFocused(true);
		});

	editBoxPassword->onReturnKeyPress([editBoxRepeatPassword] {
		editBoxRepeatPassword->setFocused(true);
		});

	editBoxRepeatPassword->onReturnKeyPress([errorLabel, editBoxUsername, editBoxPassword, editBoxRepeatPassword, this] {
		errorLabel->setText(CreateAccount(editBoxUsername, editBoxPassword, editBoxRepeatPassword));
		});

	backButton->onClick([editBoxUsername, editBoxPassword, this]() {
		m_registerMenu->setVisible(false);
	m_loginMenu->setVisible(true);
		});


	registerButton->onClick([errorLabel, editBoxUsername, editBoxPassword, editBoxRepeatPassword, this]() {
		errorLabel->setText(CreateAccount(editBoxUsername, editBoxPassword, editBoxRepeatPassword));
		});
}

void Game::CreateMainMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_mainMenu = tgui::Group::create();

	tgui::Label::Ptr usernameLabel = tgui::Label::create();
	usernameLabel->setTextSize(80);
	usernameLabel->setPosition(windowWidth * 73 / 1270, windowHeight * 80 / 720);
	usernameLabel->setText(m_user.name);
	usernameLabel->getRenderer()->setTextColor(tgui::Color::White);
	usernameLabel->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	usernameLabel->getRenderer()->setTextOutlineThickness(2);
	usernameLabel->setTextSize(35);

	tgui::Button::Ptr playButton = tgui::Button::create();
	playButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	playButton->setPosition(windowWidth * 73 / 1270, windowHeight * 420 / 720);
	playButton->setText("Play");
	playButton->setTextSize(20);

	tgui::Button::Ptr optionsButton = tgui::Button::create();
	optionsButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	optionsButton->setPosition(windowWidth * 73 / 1270, windowHeight * 507.56 / 720);
	optionsButton->setText("Options");
	optionsButton->setTextSize(20);

	tgui::Button::Ptr exitButton = tgui::Button::create();
	exitButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	exitButton->setPosition(windowWidth * 73 / 1270, windowHeight * 595.09 / 720);
	exitButton->setText("Exit");
	exitButton->setTextSize(20);

	m_mainMenu->add(usernameLabel);
	m_mainMenu->add(playButton);
	m_mainMenu->add(optionsButton);
	m_mainMenu->add(exitButton);

	playButton->onClick([this]() {
		m_mainMenu->setVisible(false);
	m_matchSelectorMenu->setVisible(true);
		});

	optionsButton->onClick([this]() {
		m_mainMenu->setVisible(false);
	m_optionsMenu->setVisible(true);
		});

	exitButton->onClick([this]() {
		m_window->close();
		});
}

void Game::CreateMatchSelectorMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_matchSelectorMenu = tgui::Group::create();
	m_matchSelectorMenu->setTextSize(20);

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

	tgui::Label::Ptr errorLabel = tgui::Label::create();
	errorLabel->setSize(windowWidth * 425 / 1270, windowHeight * 62 / 720);
	errorLabel->setPosition(windowWidth * 422 / 1270, windowHeight * 568 / 720);
	errorLabel->setText("");
	errorLabel->getRenderer()->setTextColor(tgui::Color::Red);

	m_matchSelectorMenu->add(twoPlayerButton);
	m_matchSelectorMenu->add(threePlayerButton);
	m_matchSelectorMenu->add(fourPlayerButton);
	m_matchSelectorMenu->add(backButton);
	m_matchSelectorMenu->add(errorLabel);

	twoPlayerButton->onClick([errorLabel, this]() {
		errorLabel->setText(JoinMatch(2));
	Debug::Log("2 players");
		});

	threePlayerButton->onClick([errorLabel, this]() {
		errorLabel->setText(JoinMatch(3));
	Debug::Log("3 players");
		});

	fourPlayerButton->onClick([errorLabel, this]() {
		errorLabel->setText(JoinMatch(4));
	Debug::Log("4 players");
		});

	backButton->onClick([this]() {
		m_mainMenu->setVisible(true);
	m_matchSelectorMenu->setVisible(false);
		});
}

void Game::CreateOptionsMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
{
	m_optionsMenu = tgui::Group::create();
	m_optionsMenu->setTextSize(20);

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	backButton->setPosition(windowWidth * 73 / 1270, windowHeight * 595.09 / 720);
	backButton->setText("Back");

	// more buttons for music and stuff like that go here
	tgui::CheckBox::Ptr musicCheckbox = tgui::CheckBox::create();
	musicCheckbox->setSize(windowWidth * 56.9 / 1270, windowHeight * 56.9 / 720);
	musicCheckbox->setPosition(windowWidth * 73 / 1270, windowHeight * 420 / 720);
	musicCheckbox->setText("Music");
	musicCheckbox->setChecked(true);

	m_optionsMenu->add(backButton);
	m_optionsMenu->add(musicCheckbox);

	backButton->onClick([this]() {
		m_mainMenu->setVisible(true);
	m_optionsMenu->setVisible(false);
		});

	musicCheckbox->onCheck([this]() {
		Debug::Log("Music on");
		});

	musicCheckbox->onUncheck([this]() {
		Debug::Log("Music off");
		});

	// TODO : click events 4 each button goes here
}

void Game::CreateMapMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_mapMenu = tgui::Group::create();

	return; // 4 now

	cpr::Response r = cpr::Get(cpr::Url{ "http://127.0.0.1:8080/map" });
	auto body = crow::json::load(r.text);

	auto res = body["data"];
	auto vector_of_rows = res.lo();
	for (auto row : vector_of_rows) {
		auto vector_of_cells = row.lo();
		for (auto cell : vector_of_cells) {
			std::cout << cell["player"];
			/*
			* trebuie verificat daca playerul e altceva in afara de NONE
			* daca da, atunci ar trebui facut un auto player = cell["player"]
			* si abia apoi extreas din player datale cu player["id"]
			* sau name sau etc, asa cred
			*/
		}
	}
	// TODO : add map buttons
}

void Game::CreateNumberQuestionMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_numberQuestionMenu = tgui::Group::create();

	tgui::Button::Ptr panel = tgui::Button::create();
	panel->setEnabled(false);
	panel->setSize(windowWidth * 1037.16 / 1270, windowHeight * 185.47 / 720);
	panel->setPosition(windowWidth * 116.41 / 1270, windowHeight * 102 / 720);
	panel->setText("Question");
	panel->setTextSize(28);

	tgui::EditBox::Ptr answerBox = tgui::EditBox::create();
	answerBox->setSize(windowWidth * 446.56 / 1270, windowHeight * 79.84 / 720);
	answerBox->setPosition(windowWidth * 657.47 / 1270, windowHeight * 334.59 / 720);
	answerBox->setTextSize(20);
	answerBox->setInputValidator("[0-9]*");

	tgui::Button::Ptr submitButton = tgui::Button::create();
	submitButton->setSize(windowWidth * 177 / 1270, windowHeight * 177.03 / 720);
	submitButton->setPosition(windowWidth * 452 / 1270, windowHeight * 435 / 720);
	submitButton->setText("Submit");
	submitButton->setTextSize(20);

	// ik it looks ass but idk what else to do

	tgui::Button::Ptr number0Button = tgui::Button::create();
	number0Button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	number0Button->setPosition(windowWidth * 452 / 1270, windowHeight * 335 / 720);
	number0Button->setText("0");
	number0Button->setTextSize(20);

	tgui::Button::Ptr number1Button = tgui::Button::create();
	number1Button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	number1Button->setPosition(windowWidth * 161 / 1270, windowHeight * 532 / 720);
	number1Button->setText("1");
	number1Button->setTextSize(20);

	tgui::Button::Ptr number2Button = tgui::Button::create();
	number2Button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	number2Button->setPosition(windowWidth * 258 / 1270, windowHeight * 532 / 720);
	number2Button->setText("2");
	number2Button->setTextSize(20);

	tgui::Button::Ptr number3Button = tgui::Button::create();
	number3Button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	number3Button->setPosition(windowWidth * 355 / 1270, windowHeight * 532 / 720);
	number3Button->setText("3");
	number3Button->setTextSize(20);

	tgui::Button::Ptr number4Button = tgui::Button::create();
	number4Button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	number4Button->setPosition(windowWidth * 161 / 1270, windowHeight * 433 / 720);
	number4Button->setText("4");
	number4Button->setTextSize(20);

	tgui::Button::Ptr number5Button = tgui::Button::create();
	number5Button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	number5Button->setPosition(windowWidth * 258 / 1270, windowHeight * 433 / 720);
	number5Button->setText("5");
	number5Button->setTextSize(20);

	tgui::Button::Ptr number6Button = tgui::Button::create();
	number6Button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	number6Button->setPosition(windowWidth * 355 / 1270, windowHeight * 433 / 720);
	number6Button->setText("6");
	number6Button->setTextSize(20);

	tgui::Button::Ptr number7Button = tgui::Button::create();
	number7Button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	number7Button->setPosition(windowWidth * 161 / 1270, windowHeight * 335 / 720);
	number7Button->setText("7");
	number7Button->setTextSize(20);

	tgui::Button::Ptr number8Button = tgui::Button::create();
	number8Button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	number8Button->setPosition(windowWidth * 258 / 1270, windowHeight * 335 / 720);
	number8Button->setText("8");
	number8Button->setTextSize(20);

	tgui::Button::Ptr number9Button = tgui::Button::create();
	number9Button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	number9Button->setPosition(windowWidth * 355 / 1270, windowHeight * 335 / 720);
	number9Button->setText("9");
	number9Button->setTextSize(20);

	tgui::Button::Ptr backspaceButton = tgui::Button::create();
	backspaceButton->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	backspaceButton->setPosition(windowWidth * 549 / 1270, windowHeight * 335 / 720);
	backspaceButton->setText("Backspace");
	backspaceButton->setTextSize(20);

	m_numberQuestionMenu->add(panel);
	m_numberQuestionMenu->add(answerBox);
	m_numberQuestionMenu->add(submitButton);
	m_numberQuestionMenu->add(number0Button);
	m_numberQuestionMenu->add(number1Button);
	m_numberQuestionMenu->add(number2Button);
	m_numberQuestionMenu->add(number3Button);
	m_numberQuestionMenu->add(number4Button);
	m_numberQuestionMenu->add(number5Button);
	m_numberQuestionMenu->add(number6Button);
	m_numberQuestionMenu->add(number7Button);
	m_numberQuestionMenu->add(number8Button);
	m_numberQuestionMenu->add(number9Button);
	m_numberQuestionMenu->add(backspaceButton);

	submitButton->onClick([this, answerBox]() {
		Debug::Log(answerBox->getText().toStdString());
	// submit to the server
		});

	number0Button->onClick([this, answerBox]() {
		answerBox->setText(answerBox->getText() + "0");
		});

	number1Button->onClick([this, answerBox]() {
		answerBox->setText(answerBox->getText() + "1");
		});

	number2Button->onClick([this, answerBox]() {
		answerBox->setText(answerBox->getText() + "2");
		});

	number3Button->onClick([this, answerBox]() {
		answerBox->setText(answerBox->getText() + "3");
		});

	number4Button->onClick([this, answerBox]() {
		answerBox->setText(answerBox->getText() + "4");
		});

	number5Button->onClick([this, answerBox]() {
		answerBox->setText(answerBox->getText() + "5");
		});

	number6Button->onClick([this, answerBox]() {
		answerBox->setText(answerBox->getText() + "6");
		});

	number7Button->onClick([this, answerBox]() {
		answerBox->setText(answerBox->getText() + "7");
		});

	number8Button->onClick([this, answerBox]() {
		answerBox->setText(answerBox->getText() + "8");
		});

	number9Button->onClick([this, answerBox]() {
		answerBox->setText(answerBox->getText() + "9");
		});

	backspaceButton->onClick([this, answerBox]()
		{
			std::string text = answerBox->getText().toStdString();
	if (text.size() > 0) {
		text.pop_back();
	}
	answerBox->setText(text);
		});
}

void Game::CreateMultipleAnswerQuestionMenu(tgui::Layout windowWidth, tgui::Layout windowHeight) {
	m_multipleAnswerQuestionMenu = tgui::Group::create();

	tgui::Button::Ptr panel = tgui::Button::create();
	panel->setEnabled(false);
	panel->setSize(windowWidth * 1037.16 / 1270, windowHeight * 185.47 / 720);
	panel->setPosition(windowWidth * 116.41 / 1270, windowHeight * 102 / 720);
	panel->setText("Question");
	panel->setTextSize(28);

	tgui::Button::Ptr answer1Button = tgui::Button::create();
	answer1Button->setSize(windowWidth * 446.56 / 1270, windowHeight * 79.88 / 720);
	answer1Button->setPosition(windowWidth * 148.28 / 1270, windowHeight * 380.97 / 720);
	answer1Button->setText("Answer 1");
	answer1Button->setTextSize(20);

	tgui::Button::Ptr answer2Button = tgui::Button::create();
	answer2Button->setSize(windowWidth * 446.56 / 1270, windowHeight * 79.88 / 720);
	answer2Button->setPosition(windowWidth * 675.28 / 1270, windowHeight * 380.97 / 720);
	answer2Button->setText("Answer 2");
	answer2Button->setTextSize(20);

	tgui::Button::Ptr answer3Button = tgui::Button::create();
	answer3Button->setSize(windowWidth * 446.56 / 1270, windowHeight * 79.88 / 720);
	answer3Button->setPosition(windowWidth * 148.28 / 1270, windowHeight * 538.59 / 720);
	answer3Button->setText("Answer 3");
	answer3Button->setTextSize(20);

	tgui::Button::Ptr answer4Button = tgui::Button::create();
	answer4Button->setSize(windowWidth * 446.56 / 1270, windowHeight * 79.88 / 720);
	answer4Button->setPosition(windowWidth * 675.28 / 1270, windowHeight * 538.59 / 720);
	answer4Button->setText("Answer 4");
	answer4Button->setTextSize(20);

	m_multipleAnswerQuestionMenu->add(panel);

	m_multipleAnswerQuestionMenu->add(answer1Button);
	m_multipleAnswerQuestionMenu->add(answer2Button);
	m_multipleAnswerQuestionMenu->add(answer3Button);
	m_multipleAnswerQuestionMenu->add(answer4Button);

	int selected = NULL;

	answer1Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button]() {
		selected = 1;

	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer2Button->setEnabled(false);
	answer3Button->setEnabled(false);
	answer4Button->setEnabled(false);
		});

	answer2Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button]() {
		selected = 2;

	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer1Button->setEnabled(false);
	answer3Button->setEnabled(false);
	answer4Button->setEnabled(false);
		});

	answer3Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button]() {
		selected = 3;

	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer1Button->setEnabled(false);
	answer2Button->setEnabled(false);
	answer4Button->setEnabled(false);
		});

	answer4Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button]() {
		selected = 4;

	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer1Button->setEnabled(false);
	answer2Button->setEnabled(false);
	answer3Button->setEnabled(false);
		});
}

std::string Game::Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password) {
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:8080/user/login?name=" +
		username->getText().toStdString() +
		"&password=" +
		password->getText().toStdString() });

	auto body = crow::json::load(response.text);

	try {
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();
		auto& data = body["data"];

		if (code == 200) {

			auto windowWidth = tgui::bindWidth(m_gui);
			auto windowHeight = tgui::bindHeight(m_gui);

			m_user.id = data["player_id"].i();
			m_user.name = username->getText().toStdString();

			CreateMainMenu(windowWidth, windowHeight);
			CreateMatchSelectorMenu(windowWidth, windowHeight);
			CreateOptionsMenu(windowWidth, windowHeight);

			m_menus->add(m_mainMenu);
			m_menus->add(m_matchSelectorMenu);
			m_menus->add(m_optionsMenu);

			m_loginMenu->setVisible(false);
			m_mainMenu->setVisible(true);
			m_matchSelectorMenu->setVisible(false);
			m_optionsMenu->setVisible(false);

			return "";
		}
		else {
			return message;
		}
	}
	catch (const std::exception&) {
		return "No connection to the server";
	}
}

std::string Game::CreateAccount(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, tgui::EditBox::Ptr repeatPassword) {
	if (password->getText().toStdString() != repeatPassword->getText().toStdString()) {
		return "Passwords do not match";
	}

	auto response = cpr::Get(
		cpr::Url{ "http://localhost:8080/user/register?name=" +
		username->getText().toStdString() +
		"&password=" +
		password->getText().toStdString() });

	auto body = crow::json::load(response.text);

	try {
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();
		auto& data = body["data"];

		if (code == 200) {
			auto windowWidth = tgui::bindWidth(m_gui);
			auto windowHeight = tgui::bindHeight(m_gui);

			m_user.id = m_user.id = data["player_id"].i();
			m_user.name = username->getText().toStdString();

			CreateMainMenu(windowWidth, windowHeight);
			CreateMatchSelectorMenu(windowWidth, windowHeight);
			CreateOptionsMenu(windowWidth, windowHeight);

			m_menus->add(m_mainMenu);
			m_menus->add(m_matchSelectorMenu);
			m_menus->add(m_optionsMenu);

			m_registerMenu->setVisible(false);
			m_mainMenu->setVisible(true);
			m_matchSelectorMenu->setVisible(false);
			m_optionsMenu->setVisible(false);

			return "";
		}
		else {
			return message;
		}
	}
	catch (const std::exception&) {
		return "No connection to the server";
	}
}

std::string Game::JoinMatch(uint32_t numberOfPlayers) {
	auto response = cpr::Get(cpr::Url{ "http://localhost:8080/join_game/" + std::to_string(m_user.id) + '/' + std::to_string(numberOfPlayers) });

	auto body = crow::json::load(response.text);

	try {
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();

		if (code == 200) {
			auto windowWidth = tgui::bindWidth(m_gui);
			auto windowHeight = tgui::bindHeight(m_gui);

			m_matchSelectorMenu->setVisible(false);
			m_mainMenu->setVisible(false);

			// Map Menu
			CreateMapMenu(windowWidth, windowHeight);

			// Number Question Menu
			CreateNumberQuestionMenu(windowWidth, windowHeight);

			// Multiple Answer Question Menu
			CreateMultipleAnswerQuestionMenu(windowWidth, windowHeight);

			m_gameMenus = tgui::Group::create();
			m_gameMenus->add(m_mapMenu);
			m_gameMenus->add(m_numberQuestionMenu);
			m_gameMenus->add(m_multipleAnswerQuestionMenu);

			m_gameMenus->setVisible(true);

			m_mapMenu->setVisible(true);
			m_numberQuestionMenu->setVisible(false);
			m_multipleAnswerQuestionMenu->setVisible(false);

			m_gui.add(m_gameMenus);

			return "";
		}
		else {
			return message;
		}
	}
	catch (const std::exception&) {
		return "No connection to the server";
	}
}
