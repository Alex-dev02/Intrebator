#include "../include/Application.hpp"

#include <cpr/cpr.h>
#include <crow.h>

#include "../../Logger/Debug.hpp"

Application::Application()
	: m_window(sf::VideoMode(1270, 720), "Triviador", sf::Style::Titlebar | sf::Style::Close)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.setPosition(sf::Vector2i((desktop.width - 1270) / 2, (desktop.height - 720) / 2));
	m_window.setFramerateLimit(60);
	m_window.setVerticalSyncEnabled(true);

	if (!m_icon.loadFromFile("assets/images/icon.png"))
	{
		Debug::LogError("Game icon not found");
	}
	m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());

	if (!m_font.loadFromFile("assets/fonts/Inter-Medium.ttf"))
	{
		Debug::LogError("Could not find Inter-Medium.ttf font.");
	}

	m_windowWidth = tgui::bindWidth(m_gui);
	m_windowHeight = tgui::bindHeight(m_gui);

	if (!m_menuMusic.openFromFile("assets/audio/music/menu_song.ogg"))
	{
		Debug::LogError("Error loading menu music");
		m_window.close();
	}
	m_menuMusic.setLoop(true);

	if (!m_gameMusic.openFromFile("assets/audio/music/game_song.ogg"))
	{
		Debug::LogError("Error loading game music");
		m_window.close();
	}
	m_gameMusic.setLoop(true);

	if (!m_clickSoundBuffer.loadFromFile("assets/audio/sound_effects/click.ogg"))
	{
		Debug::LogError("Error loading click sound");
		m_window.close();
	}
	m_clickSound.setBuffer(m_clickSoundBuffer);

	if (!m_checkboxSoundBuffer.loadFromFile("assets/audio/sound_effects/checkbox.ogg"))
	{
		Debug::LogError("Error loading checkbox sound");
		m_window.close();
	}
	m_checkBoxSound.setBuffer(m_checkboxSoundBuffer);

	if (!m_correctSoundBuffer.loadFromFile("assets/audio/sound_effects/correct.ogg"))
	{
		Debug::LogError("Error loading correct sound");
		m_window.close();
	}
	m_correctSound.setBuffer(m_correctSoundBuffer);

	if (!m_incorrectSoundBuffer.loadFromFile("assets/audio/sound_effects/incorrect.ogg"))
	{
		Debug::LogError("Error loading incorrect sound");
		m_window.close();
	}
	m_incorrectSound.setBuffer(m_incorrectSoundBuffer);

	tgui::Picture::Ptr background = tgui::Picture::create("assets/images/background.png");
	background->setSize(m_windowWidth, m_windowHeight);

	m_gui.setTarget(m_window);
	m_gui.setFont(tgui::Font("assets/fonts/Inter-Medium.ttf"));
	m_gui.add(background, "background");

	CreateLoginMenu();
	CreateRegisterMenu();
	CreateMainMenu();
	CreateMatchSelectorMenu();
	CreateOptionsMenu();
}

void Application::Run()
{
	while (m_window.isOpen())
	{
		// Event polling
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			m_gui.handleEvent(event);

			switch (event.type)
			{
				case sf::Event::Closed:
					LeaveMatch();
					m_window.close();
					break;

				default:
					break;
			}
		}

		// Update
		if (m_gameStarted)
		{
			Update();
		}

		// Render
		m_window.clear(); // Clear old frame
		m_gui.draw();

		m_window.display(); // Tell the app that the m_window is done drawing
	}
}

void Application::CreateLoginMenu()
{
	m_loginMenu = tgui::Group::create();
	m_loginMenu->setTextSize(20);

	tgui::EditBox::Ptr editBoxUsername = tgui::EditBox::create();
	editBoxUsername->setSize(m_windowWidth * 425 / 1270, m_windowHeight * 62 / 720);
	editBoxUsername->setPosition(m_windowWidth * 422 / 1270, m_windowHeight * 214 / 720);
	editBoxUsername->setInputValidator("[^ ]*");
	editBoxUsername->setDefaultText("Username");

	tgui::EditBox::Ptr editBoxPassword = tgui::EditBox::create();
	editBoxPassword->setSize(m_windowWidth * 425 / 1270, m_windowHeight * 62 / 720);
	editBoxPassword->setPosition(m_windowWidth * 422 / 1270, m_windowHeight * 329 / 720);
	editBoxPassword->setInputValidator("[^ ]*");
	editBoxPassword->setPasswordCharacter('*');
	editBoxPassword->setDefaultText("Password");

	tgui::Button::Ptr loginButton = tgui::Button::create();
	loginButton->setSize(m_windowWidth * 204 / 1270, m_windowHeight * 36.48 / 720);
	loginButton->setPosition(m_windowWidth * 422 / 1270, m_windowHeight * 443.75 / 720);
	loginButton->setText("Login");

	tgui::Button::Ptr registerButton = tgui::Button::create();
	registerButton->setSize(m_windowWidth * 204 / 1270, m_windowHeight * 36.48 / 720);
	registerButton->setPosition(m_windowWidth * 643 / 1270, m_windowHeight * 443.75 / 720);
	registerButton->setText("Register");

	tgui::Label::Ptr errorLabel = tgui::Label::create();
	errorLabel->setSize(m_windowWidth * 425 / 1270, m_windowHeight * 62 / 720);
	errorLabel->setPosition(m_windowWidth * 422 / 1270, m_windowHeight * 525 / 720);
	errorLabel->setText("");
	errorLabel->getRenderer()->setTextColor(tgui::Color::Red);

	m_loginMenu->add(editBoxUsername);
	m_loginMenu->add(editBoxPassword);
	m_loginMenu->add(loginButton);
	m_loginMenu->add(registerButton);
	m_loginMenu->add(errorLabel);

	editBoxUsername->onReturnKeyPress([editBoxPassword]
		{ editBoxPassword->setFocused(true); });

	editBoxPassword->onReturnKeyPress([errorLabel, editBoxUsername, editBoxPassword, this]
		{ errorLabel->setText(Login(editBoxUsername, editBoxPassword)); });

	loginButton->onClick([errorLabel, editBoxUsername, editBoxPassword, this]()
		{
			m_clickSound.play();
	errorLabel->setText(Login(editBoxUsername, editBoxPassword)); });

	registerButton->onClick([editBoxUsername, editBoxPassword, this]()
		{
			m_clickSound.play();
	m_loginMenu->setVisible(false);
	m_registerMenu->setVisible(true); });

	m_gui.add(m_loginMenu);
	m_loginMenu->setVisible(true);
}

void Application::CreateRegisterMenu()
{
	m_registerMenu = tgui::Group::create();
	m_registerMenu->setTextSize(20);

	tgui::EditBox::Ptr editBoxUsername = tgui::EditBox::create();
	editBoxUsername->setSize(m_windowWidth * 425 / 1270, m_windowHeight * 62 / 720);
	editBoxUsername->setPosition(m_windowWidth * 422 / 1270, m_windowHeight * 169 / 720);
	editBoxUsername->setInputValidator("[^ ]*");
	editBoxUsername->setDefaultText("Username");

	tgui::EditBox::Ptr editBoxPassword = tgui::EditBox::create();
	editBoxPassword->setSize(m_windowWidth * 425 / 1270, m_windowHeight * 62 / 720);
	editBoxPassword->setPosition(m_windowWidth * 422 / 1270, m_windowHeight * 284 / 720);
	editBoxPassword->setInputValidator("[^ ]*");
	editBoxPassword->setPasswordCharacter('*');
	editBoxPassword->setDefaultText("Password");

	tgui::EditBox::Ptr editBoxRepeatPassword = tgui::EditBox::create();
	editBoxRepeatPassword->setSize(m_windowWidth * 425 / 1270, m_windowHeight * 62 / 720);
	editBoxRepeatPassword->setPosition(m_windowWidth * 422 / 1270, m_windowHeight * 399 / 720);
	editBoxRepeatPassword->setInputValidator("[^ ]*");
	editBoxRepeatPassword->setPasswordCharacter('*');
	editBoxRepeatPassword->setDefaultText("Repeat password");

	tgui::Button::Ptr registerButton = tgui::Button::create();
	registerButton->setSize(m_windowWidth * 204 / 1270, m_windowHeight * 36.48 / 720);
	registerButton->setPosition(m_windowWidth * 643 / 1270, m_windowHeight * 513.75 / 720);
	registerButton->setText("Register");

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->setSize(m_windowWidth * 204 / 1270, m_windowHeight * 36.48 / 720);
	backButton->setPosition(m_windowWidth * 422 / 1270, m_windowHeight * 513.75 / 720);
	backButton->setText("Back");

	tgui::Label::Ptr errorLabel = tgui::Label::create();
	errorLabel->setSize(m_windowWidth * 425 / 1270, m_windowHeight * 62 / 720);
	errorLabel->setPosition(m_windowWidth * 422 / 1270, m_windowHeight * 568 / 720);
	errorLabel->setText("");
	errorLabel->getRenderer()->setTextColor(tgui::Color::Red);

	m_registerMenu->add(editBoxUsername);
	m_registerMenu->add(editBoxPassword);
	m_registerMenu->add(editBoxRepeatPassword);
	m_registerMenu->add(registerButton);
	m_registerMenu->add(backButton);
	m_registerMenu->add(errorLabel);

	editBoxUsername->onReturnKeyPress([editBoxPassword]
		{ editBoxPassword->setFocused(true); });

	editBoxPassword->onReturnKeyPress([editBoxRepeatPassword]
		{ editBoxRepeatPassword->setFocused(true); });

	editBoxRepeatPassword->onReturnKeyPress([errorLabel, editBoxUsername, editBoxPassword, editBoxRepeatPassword, this]
		{ errorLabel->setText(CreateAccount(editBoxUsername, editBoxPassword, editBoxRepeatPassword)); });

	backButton->onClick([editBoxUsername, editBoxPassword, this]()
		{
			m_clickSound.play();
	m_registerMenu->setVisible(false);
	m_loginMenu->setVisible(true); });

	registerButton->onClick([errorLabel, editBoxUsername, editBoxPassword, editBoxRepeatPassword, this]()
		{
			m_clickSound.play();
	errorLabel->setText(CreateAccount(editBoxUsername, editBoxPassword, editBoxRepeatPassword)); });

	m_gui.add(m_registerMenu);
	m_registerMenu->setVisible(false);
}

void Application::CreateMainMenu()
{
	m_mainMenu = tgui::Group::create();

	tgui::Label::Ptr usernameLabel = tgui::Label::create();
	usernameLabel->setTextSize(80);
	usernameLabel->setPosition(m_windowWidth * 73 / 1270, m_windowHeight * 80 / 720);
	usernameLabel->setText(m_localPlayer.name);
	usernameLabel->getRenderer()->setTextColor(tgui::Color::White);
	usernameLabel->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	usernameLabel->getRenderer()->setTextOutlineThickness(2);
	usernameLabel->setTextSize(35);

	tgui::Button::Ptr playButton = tgui::Button::create();
	playButton->setSize(m_windowWidth * 218 / 1270, m_windowHeight * 56.9 / 720);
	playButton->setPosition(m_windowWidth * 73 / 1270, m_windowHeight * 420 / 720);
	playButton->setText("Play");
	playButton->setTextSize(20);

	tgui::Button::Ptr optionsButton = tgui::Button::create();
	optionsButton->setSize(m_windowWidth * 218 / 1270, m_windowHeight * 56.9 / 720);
	optionsButton->setPosition(m_windowWidth * 73 / 1270, m_windowHeight * 507.56 / 720);
	optionsButton->setText("Options");
	optionsButton->setTextSize(20);

	tgui::Button::Ptr exitButton = tgui::Button::create();
	exitButton->setSize(m_windowWidth * 218 / 1270, m_windowHeight * 56.9 / 720);
	exitButton->setPosition(m_windowWidth * 73 / 1270, m_windowHeight * 595.09 / 720);
	exitButton->setText("Exit");
	exitButton->setTextSize(20);

	m_mainMenu->add(usernameLabel, "usernameLabel");
	m_mainMenu->add(playButton);
	m_mainMenu->add(optionsButton);
	m_mainMenu->add(exitButton);

	playButton->onClick([this]()
		{
			m_clickSound.play();
	m_mainMenu->setVisible(false);
	m_matchSelectorMenu->setVisible(true); });

	optionsButton->onClick([this]()
		{
			m_clickSound.play();
	m_mainMenu->setVisible(false);
	m_optionsMenu->setVisible(true); });

	exitButton->onClick([this]()
		{
			m_clickSound.play();
	m_window.close(); });

	m_gui.add(m_mainMenu);
	m_mainMenu->setVisible(false);
}

void Application::CreateOptionsMenu()
{
	m_optionsMenu = tgui::Group::create();
	m_optionsMenu->setTextSize(20);

	tgui::CheckBox::Ptr musicCheckbox = tgui::CheckBox::create();
	musicCheckbox->setSize(m_windowWidth * 56.9 / 1270, m_windowHeight * 56.9 / 720);
	musicCheckbox->setPosition(m_windowWidth * 73 / 1270, m_windowHeight * 420 / 720);
	musicCheckbox->setText("Music");
	musicCheckbox->setChecked(true);

	tgui::CheckBox::Ptr sfxCheckbox = tgui::CheckBox::create();
	sfxCheckbox->setSize(m_windowWidth * 56.9 / 1270, m_windowHeight * 56.9 / 720);
	sfxCheckbox->setPosition(m_windowWidth * 73 / 1270, m_windowHeight * 507.545 / 720);
	sfxCheckbox->setText("Sfx");
	sfxCheckbox->setChecked(true);

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->setSize(m_windowWidth * 218 / 1270, m_windowHeight * 56.9 / 720);
	backButton->setPosition(m_windowWidth * 73 / 1270, m_windowHeight * 595.09 / 720);
	backButton->setText("Back");

	m_optionsMenu->add(backButton);
	m_optionsMenu->add(musicCheckbox);
	m_optionsMenu->add(sfxCheckbox);

	backButton->onClick([this]()
		{
			m_clickSound.play();
	m_mainMenu->setVisible(true);
	m_optionsMenu->setVisible(false); });

	musicCheckbox->onCheck([this]()
		{
			m_checkBoxSound.play();
	m_menuMusic.setVolume(100);
	m_gameMusic.setVolume(100); });

	musicCheckbox->onUncheck([this]()
		{
			m_checkBoxSound.play();
	m_menuMusic.setVolume(0);
	m_gameMusic.setVolume(0); });

	sfxCheckbox->onCheck([this]()
		{
			m_clickSound.setVolume(100);
	m_checkBoxSound.setVolume(100);
	m_correctSound.setVolume(100);
	m_incorrectSound.setVolume(100);
	m_checkBoxSound.play(); });

	sfxCheckbox->onUncheck([this]()
		{
			m_clickSound.setVolume(0);
	m_checkBoxSound.setVolume(0);
	m_correctSound.setVolume(0);
	m_incorrectSound.setVolume(0);
	m_checkBoxSound.play(); });

	m_gui.add(m_optionsMenu);
	m_optionsMenu->setVisible(false);
}

void Application::CreateMatchSelectorMenu()
{
	m_matchSelectorMenu = tgui::Group::create();
	m_matchSelectorMenu->setTextSize(20);

	tgui::Button::Ptr twoPlayerButton = tgui::Button::create();
	twoPlayerButton->setSize(m_windowWidth * 218 / 1270, m_windowHeight * 281 / 720);
	twoPlayerButton->setPosition(m_windowWidth * 256 / 1270, m_windowHeight * 219.5 / 720);
	twoPlayerButton->setText("2 players");

	tgui::Button::Ptr threePlayerButton = tgui::Button::create();
	threePlayerButton->setSize(m_windowWidth * 218 / 1270, m_windowHeight * 281 / 720);
	threePlayerButton->setPosition(m_windowWidth * 526 / 1270, m_windowHeight * 219.5 / 720);
	threePlayerButton->setText("3 players");

	tgui::Button::Ptr fourPlayerButton = tgui::Button::create();
	fourPlayerButton->setSize(m_windowWidth * 218 / 1270, m_windowHeight * 281 / 720);
	fourPlayerButton->setPosition(m_windowWidth * 796 / 1270, m_windowHeight * 219.5 / 720);
	fourPlayerButton->setText("4 players");

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->setSize(m_windowWidth * 218 / 1270, m_windowHeight * 56.9 / 720);
	backButton->setPosition(m_windowWidth * 73 / 1270, m_windowHeight * 595.09 / 720);
	backButton->setText("Back");

	tgui::Label::Ptr errorLabel = tgui::Label::create();
	errorLabel->setSize(m_windowWidth * 425 / 1270, m_windowHeight * 62 / 720);
	errorLabel->setPosition(m_windowWidth * 422 / 1270, m_windowHeight * 568 / 720);
	errorLabel->setText("");
	errorLabel->getRenderer()->setTextColor(tgui::Color::Red);

	m_matchSelectorMenu->add(twoPlayerButton);
	m_matchSelectorMenu->add(threePlayerButton);
	m_matchSelectorMenu->add(fourPlayerButton);
	m_matchSelectorMenu->add(backButton);
	m_matchSelectorMenu->add(errorLabel);

	twoPlayerButton->onClick([this, errorLabel]()
		{
			m_clickSound.play();
	errorLabel->setText(JoinMatch(2)); });

	threePlayerButton->onClick([this, errorLabel]()
		{
			m_clickSound.play();
	errorLabel->setText(JoinMatch(3)); });

	fourPlayerButton->onClick([this, errorLabel]()
		{
			m_clickSound.play();
	errorLabel->setText(JoinMatch(4)); });

	backButton->onClick([this]()
		{
			m_clickSound.play();
	m_mainMenu->setVisible(true);
	m_matchSelectorMenu->setVisible(false); });

	m_gui.add(m_matchSelectorMenu);
	m_matchSelectorMenu->setVisible(false);
}

void Application::CreateWaitRoomMenu(uint32_t numberOfPlayers)
{
	m_waitRoomMenu = tgui::Group::create();

	tgui::Label::Ptr waitingLabel = tgui::Label::create();
	waitingLabel->setSize(m_windowWidth * 1000 / 1270, m_windowHeight * 120 / 720);
	waitingLabel->setPosition(m_windowWidth * 135 / 1270, m_windowHeight * 62 / 720);
	waitingLabel->getRenderer()->setTextColor(tgui::Color::White);
	waitingLabel->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	waitingLabel->getRenderer()->setTextOutlineThickness(1);
	waitingLabel->setText("Waiting for other players to join");
	waitingLabel->setTextSize(30);
	waitingLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

	tgui::Button::Ptr startGameButton = tgui::Button::create();
	startGameButton->setSize(m_windowWidth * 218 / 1270, m_windowHeight * 56.9 / 720);
	startGameButton->setPosition(m_windowWidth * 73 / 1270, m_windowHeight * 507.56 / 720);
	startGameButton->setText("Start game");
	startGameButton->setTextSize(20);

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->setSize(m_windowWidth * 218 / 1270, m_windowHeight * 56.9 / 720);
	backButton->setPosition(m_windowWidth * 73 / 1270, m_windowHeight * 595.09 / 720);
	backButton->setText("Back");
	backButton->setTextSize(20);

	m_waitRoomMenu->add(waitingLabel);
	m_waitRoomMenu->add(startGameButton);
	m_waitRoomMenu->add(backButton);

	startGameButton->onClick([this]()
		{
			m_clickSound.play();
	auto response = cpr::Get(cpr::Url{ "http://localhost:8080/start_game" });
	auto body = crow::json::load(response.text);

	try {
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();

		if (code == 200) {
			Debug::Log("Game successfully started");
		}
	}
	catch (const std::exception& e) {
		Debug::Log(e.what());
	} });

	backButton->onClick([this]()
		{
			m_clickSound.play();
	LeaveMatch();
	m_waitRoomMenu->setVisible(false);
	m_matchSelectorMenu->setVisible(true); });

	m_gui.add(m_waitRoomMenu);
	m_waitRoomMenu->setVisible(false);

	return;
}

void Application::CreateMapMenu()
{
	m_mapMenu = tgui::Group::create();
	m_gui.add(m_mapMenu);
	m_mapMenu->setVisible(true);

	try
	{
		auto response = cpr::Get(cpr::Url{ "http://localhost:8080/map" });
		auto body = crow::json::load(response.text);

		std::string message = body["message"].s();
		uint32_t code = body["code"].i();
		auto data = body["data"];

		if (code == 200)
		{
			auto i = 0;
			for (auto& row : data.lo())
			{
				auto j = 0;
				for (auto& cell : row.lo())
				{
					auto& player = cell["player"];

					Debug::Log(player);

					tgui::Button::Ptr button = tgui::Button::create();
					m_mapMenu->add(button, std::to_string(i) + " " + std::to_string(j));

					button->setSize(m_windowWidth * 120 / 1270, m_windowHeight * 120 / 720);
					button->setPosition(m_windowWidth * (66 + j * 120) / 1270, m_windowHeight * (66 + i * 120) / 720);
					button->setText(std::string(cell["score"]) + "\n" + std::string(cell["type"]));
					button->setTextSize(20);

					if (player.s() != "NONE") {
						/*if (player["color"] == "RED") {
							button->getRenderer()->setBackgroundColor(tgui::Color::Red);
						}
						if (player["color"] == "GREEN") {
							button->getRenderer()->setBackgroundColor(tgui::Color::Green);
						}
						if (player["color"] == "YELLOW") {
							button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
						}
						if (player["color"] == "BLUE") {
							button->getRenderer()->setBackgroundColor(tgui::Color::Blue);
						}*/
					}

					j++;
				}
				i++;
			}
		}
		else
		{
			return;
		}
	}
	catch (const std::exception& e)
	{
		Debug::Log(e.what());
	}
}

void Application::CreateNumberQuestionMenu()
{
	m_numberQuestionMenu = tgui::Group::create();

	m_gui.add(m_numberQuestionMenu);
	m_numberQuestionMenu->setVisible(true);

	tgui::Button::Ptr panel = tgui::Button::create();
	panel->setEnabled(false);
	panel->setSize(m_windowWidth * 1037.16 / 1270, m_windowHeight * 185.47 / 720);
	panel->setPosition(m_windowWidth * 116.41 / 1270, m_windowHeight * 102 / 720);
	panel->setText("Question");
	panel->setTextSize(28);

	tgui::EditBox::Ptr answerBox = tgui::EditBox::create();
	answerBox->setSize(m_windowWidth * 446.56 / 1270, m_windowHeight * 79.84 / 720);
	answerBox->setPosition(m_windowWidth * 657.47 / 1270, m_windowHeight * 334.59 / 720);
	answerBox->setTextSize(20);
	answerBox->setInputValidator("[0-9]*");

	tgui::Button::Ptr submitButton = tgui::Button::create();
	submitButton->setSize(m_windowWidth * 177 / 1270, m_windowHeight * 177.03 / 720);
	submitButton->setPosition(m_windowWidth * 452 / 1270, m_windowHeight * 435 / 720);
	submitButton->setText("Submit");
	submitButton->setTextSize(20);

	tgui::Button::Ptr number0Button = tgui::Button::create();
	number0Button->setSize(m_windowWidth * 80 / 1270, m_windowHeight * 80 / 720);
	number0Button->setPosition(m_windowWidth * 452 / 1270, m_windowHeight * 335 / 720);
	number0Button->setText("0");
	number0Button->setTextSize(20);

	std::vector<tgui::Button::Ptr> numberButtons;

	std::vector<int> xPosition = { 161, 258, 355 };
	std::vector<int> yPosition = { 532, 433, 335 };

	for (uint8_t i = 1; i <= 3; i++)
	{
		for (auto j = 1; j <= 3; j++)
		{
			auto button = tgui::Button::create();
			button->setSize(m_windowWidth * 80 / 1270, m_windowHeight * 80 / 720);
			button->setPosition(m_windowWidth * xPosition[j - 1] / 1270, m_windowHeight * yPosition[i - 1] / 720);
			button->setText(std::to_string((i - 1) * 3 + j));
			button->setTextSize(20);

			numberButtons.push_back(button);
		}
	}

	tgui::Button::Ptr backspaceButton = tgui::Button::create();
	backspaceButton->setSize(m_windowWidth * 80 / 1270, m_windowHeight * 80 / 720);
	backspaceButton->setPosition(m_windowWidth * 549 / 1270, m_windowHeight * 335 / 720);
	backspaceButton->setText("Bksp");
	backspaceButton->setTextSize(20);

	m_numberQuestionMenu->add(panel);
	m_numberQuestionMenu->add(answerBox);
	m_numberQuestionMenu->add(submitButton);
	m_numberQuestionMenu->add(number0Button, "0");
	for (uint8_t i = 1; i <= 9; i++)
	{
		m_numberQuestionMenu->add(numberButtons[i - 1], std::to_string(i));
	}
	m_numberQuestionMenu->add(backspaceButton);

	submitButton->onClick([this, answerBox]()
		{
			m_clickSound.play();
	Debug::Log(answerBox->getText().toStdString());
	// submit to the server
		});

	for (auto i = 0; i <= 9; i++)
	{
		m_numberQuestionMenu->get<tgui::Button>(std::to_string(i))->onClick([this, answerBox, i]()
			{
				m_clickSound.play();
		answerBox->setText(answerBox->getText() + std::to_string(i)); });
	}

	backspaceButton->onClick([this, answerBox]()
		{
			m_clickSound.play();
	std::string text = answerBox->getText().toStdString();
	if (text.size() > 0) {
		text.pop_back();
	}
	answerBox->setText(text); });
}

void Application::CreateMultipleAnswerQuestionMenu()
{
	m_multipleAnswerQuestionMenu = tgui::Group::create();

	m_gui.add(m_multipleAnswerQuestionMenu);
	m_multipleAnswerQuestionMenu->setVisible(true);

	tgui::Button::Ptr panel = tgui::Button::create();
	panel->setEnabled(false);
	panel->setSize(m_windowWidth * 1037.16 / 1270, m_windowHeight * 185.47 / 720);
	panel->setPosition(m_windowWidth * 116.41 / 1270, m_windowHeight * 102 / 720);
	panel->setText("Question");
	panel->setTextSize(28);

	tgui::Button::Ptr answer1Button = tgui::Button::create();
	answer1Button->setSize(m_windowWidth * 446.56 / 1270, m_windowHeight * 79.88 / 720);
	answer1Button->setPosition(m_windowWidth * 148.28 / 1270, m_windowHeight * 380.97 / 720);
	answer1Button->setText("Answer 1");
	answer1Button->setTextSize(20);

	tgui::Button::Ptr answer2Button = tgui::Button::create();
	answer2Button->setSize(m_windowWidth * 446.56 / 1270, m_windowHeight * 79.88 / 720);
	answer2Button->setPosition(m_windowWidth * 675.28 / 1270, m_windowHeight * 380.97 / 720);
	answer2Button->setText("Answer 2");
	answer2Button->setTextSize(20);

	tgui::Button::Ptr answer3Button = tgui::Button::create();
	answer3Button->setSize(m_windowWidth * 446.56 / 1270, m_windowHeight * 79.88 / 720);
	answer3Button->setPosition(m_windowWidth * 148.28 / 1270, m_windowHeight * 538.59 / 720);
	answer3Button->setText("Answer 3");
	answer3Button->setTextSize(20);

	tgui::Button::Ptr answer4Button = tgui::Button::create();
	answer4Button->setSize(m_windowWidth * 446.56 / 1270, m_windowHeight * 79.88 / 720);
	answer4Button->setPosition(m_windowWidth * 675.28 / 1270, m_windowHeight * 538.59 / 720);
	answer4Button->setText("Answer 4");
	answer4Button->setTextSize(20);

	m_multipleAnswerQuestionMenu->add(panel);

	m_multipleAnswerQuestionMenu->add(answer1Button);
	m_multipleAnswerQuestionMenu->add(answer2Button);
	m_multipleAnswerQuestionMenu->add(answer3Button);
	m_multipleAnswerQuestionMenu->add(answer4Button);

	int selected = NULL;

	answer1Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button, this]()
		{
			m_clickSound.play();
	selected = 1;

	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer2Button->setEnabled(false);
	answer3Button->setEnabled(false);
	answer4Button->setEnabled(false); });

	answer2Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button, this]()
		{
			m_clickSound.play();
	selected = 2;

	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer1Button->setEnabled(false);
	answer3Button->setEnabled(false);
	answer4Button->setEnabled(false); });

	answer3Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button, this]()
		{
			m_clickSound.play();
	selected = 3;

	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer1Button->setEnabled(false);
	answer2Button->setEnabled(false);
	answer4Button->setEnabled(false);
		});

	answer4Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button, this]() {
		m_clickSound.play();
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

void Application::Update()
{
	auto response = cpr::Get(cpr::Url{ "http://localhost:8080/game_status" });
	auto body = crow::json::load(response.text);

	try
	{
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();

		if (code == 200)
		{
			if (m_gameState != message)
			{
				Debug::Log(message);
				if (message == "WAITING_FOR_PLAYERS")
				{
					m_players.clear();
					// make a new vector of players and put em all in the m_players vector
				}
				else if (message == "SHOW_MAP")
				{
					m_waitRoomMenu->setVisible(false);
					CreateMapMenu();
				}
				else if (message == "ANSWERING_QUESTION")
				{
					m_mapMenu->setVisible(false);
					CreateNumberQuestionMenu();
				}
				else if (message == "SHOW_RESULTS")
				{
				}
				else if (message == "PICKING_BASE")
				{
				}
				else if (message == "PICKING_CELLS")
				{
				}
				else if (message == "DUELLING")
				{
				}
				else if (message == "FINISHED")
				{
				}
				else if (message == "ERROR")
				{
				}
			}

			m_gameState = message;
		}
	}
	catch (const std::exception& e)
	{
		Debug::Log(e.what());
	}
}

std::string Application::Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:8080/user/login?name=" +
				 username->getText().toStdString() +
				 "&password=" +
				 password->getText().toStdString() });

	auto body = crow::json::load(response.text);

	try
	{
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();
		auto& data = body["data"];

		if (code == 200)
		{
			m_localPlayer.id = data["player_id"].i();
			m_localPlayer.name = username->getText().toStdString();

			m_mainMenu->get<tgui::Label>("usernameLabel")->setText(m_localPlayer.name);

			m_loginMenu->setVisible(false);
			m_mainMenu->setVisible(true);

			m_menuMusic.play();

			return "";
		}
		else
		{
			return message;
		}
	}
	catch (const std::exception&)
	{
		return "No connection to the server";
	}
}

std::string Application::CreateAccount(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, tgui::EditBox::Ptr repeatPassword)
{
	if (password->getText().toStdString() != repeatPassword->getText().toStdString())
	{
		return "Passwords do not match";
	}

	auto response = cpr::Get(
		cpr::Url{ "http://localhost:8080/user/register?name=" +
				 username->getText().toStdString() +
				 "&password=" +
				 password->getText().toStdString() });

	auto body = crow::json::load(response.text);

	try
	{
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();
		auto& data = body["data"];

		if (code == 200)
		{
			m_localPlayer.id = m_localPlayer.id = data["player_id"].i();
			m_localPlayer.name = username->getText().toStdString();

			m_mainMenu->get<tgui::Label>("usernameLabel")->setText(m_localPlayer.name);

			m_registerMenu->setVisible(false);
			m_mainMenu->setVisible(true);

			m_menuMusic.play();

			return "";
		}
		else
		{
			return message;
		}
	}
	catch (const std::exception&)
	{
		return "No connection to the server";
	}
}

std::string Application::JoinMatch(uint32_t numberOfPlayers)
{
	auto response = cpr::Get(cpr::Url{ "http://localhost:8080/join_game/" + std::to_string(m_localPlayer.id) + '/' + std::to_string(numberOfPlayers) });
	auto body = crow::json::load(response.text);

	try
	{
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();

		if (code == 200)
		{
			m_matchSelectorMenu->setVisible(false);
			m_mainMenu->setVisible(false);

			CreateWaitRoomMenu(numberOfPlayers);
			m_waitRoomMenu->setVisible(true);

			m_gameStarted = true;

			return "";
		}
		else
		{
			return message;
		}
	}
	catch (const std::exception&)
	{
		return "No connection to the server";
	}
}

void Application::LeaveMatch()
{
	auto response = cpr::Get(cpr::Url{ "http://localhost:8080/leave_game/" + std::to_string(m_localPlayer.id) });
	auto body = crow::json::load(response.text);

	try
	{
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();

		if (code == 200)
		{
			Debug::Log("left match");
		}
	}
	catch (const std::exception& e)
	{
		Debug::Log(e.what());
	}
}