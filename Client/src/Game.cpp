#include "../include/Game.hpp"

#include <vector>

#include <cpr/cpr.h>
#include <crow.h>

Game::Game(sf::RenderWindow& window)
{
	m_window = &window;

	if (!m_menuMusic.openFromFile("assets/audio/music/menu_song.ogg"))
	{
		Debug::LogError("Error loading menu music");
		m_window->close();
	}
	m_menuMusic.setLoop(true);

	if (!m_gameMusic.openFromFile("assets/audio/music/game_song.ogg"))
	{
		Debug::LogError("Error loading game music");
		m_window->close();
	}
	m_gameMusic.setLoop(true);

	if (!m_clickSoundBuffer.loadFromFile("assets/audio/sound_effects/click.ogg"))
	{
		Debug::LogError("Error loading click sound");
		m_window->close();
	}
	m_clickSound.setBuffer(m_clickSoundBuffer);

	if (!m_checkboxSoundBuffer.loadFromFile("assets/audio/sound_effects/checkbox.ogg"))
	{
		Debug::LogError("Error loading checkbox sound");
		m_window->close();
	}
	m_checkBoxSound.setBuffer(m_checkboxSoundBuffer);

	if (!m_correctSoundBuffer.loadFromFile("assets/audio/sound_effects/correct.ogg"))
	{
		Debug::LogError("Error loading correct sound");
		m_window->close();
	}
	m_correctSound.setBuffer(m_correctSoundBuffer);

	if (!m_incorrectSoundBuffer.loadFromFile("assets/audio/sound_effects/incorrect.ogg"))
	{
		Debug::LogError("Error loading incorrect sound");
		m_window->close();
	}
	m_incorrectSound.setBuffer(m_incorrectSoundBuffer);

	auto windowWidth = tgui::bindWidth(m_gui);
	auto windowHeight = tgui::bindHeight(m_gui);

	tgui::Picture::Ptr background = tgui::Picture::create("assets/images/background.png");
	background->setSize(windowWidth, windowHeight);

	m_gui.setTarget(window);
	m_gui.setFont(tgui::Font("assets/fonts/Inter-Medium.ttf"));
	m_gui.add(background);

	CreateLoginMenu(windowWidth, windowHeight);
	CreateRegisterMenu(windowWidth, windowHeight);
	CreateMainMenu(windowWidth, windowHeight);
	CreateMatchSelectorMenu(windowWidth, windowHeight);
	CreateOptionsMenu(windowWidth, windowHeight);
}

void Game::CreateLoginMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
{
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

void Game::CreateRegisterMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
{
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

void Game::CreateMainMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
{
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
	m_window->close(); });

	m_gui.add(m_mainMenu);
	m_mainMenu->setVisible(false);
}

void Game::CreateOptionsMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
{
	m_optionsMenu = tgui::Group::create();
	m_optionsMenu->setTextSize(20);

	tgui::CheckBox::Ptr musicCheckbox = tgui::CheckBox::create();
	musicCheckbox->setSize(windowWidth * 56.9 / 1270, windowHeight * 56.9 / 720);
	musicCheckbox->setPosition(windowWidth * 73 / 1270, windowHeight * 420 / 720);
	musicCheckbox->setText("Music");
	musicCheckbox->setChecked(true);

	tgui::CheckBox::Ptr sfxCheckbox = tgui::CheckBox::create();
	sfxCheckbox->setSize(windowWidth * 56.9 / 1270, windowHeight * 56.9 / 720);
	sfxCheckbox->setPosition(windowWidth * 73 / 1270, windowHeight * 507.545 / 720);
	sfxCheckbox->setText("Sfx");
	sfxCheckbox->setChecked(true);

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	backButton->setPosition(windowWidth * 73 / 1270, windowHeight * 595.09 / 720);
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

void Game::CreateMatchSelectorMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
{
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

	twoPlayerButton->onClick([errorLabel, this]()
		{
			m_clickSound.play();
	errorLabel->setText(JoinMatch(2));
	Debug::Log("2 players"); });

	threePlayerButton->onClick([errorLabel, this]()
		{
			m_clickSound.play();
	errorLabel->setText(JoinMatch(3));
	Debug::Log("3 players"); });

	fourPlayerButton->onClick([errorLabel, this]()
		{
			m_clickSound.play();
	errorLabel->setText(JoinMatch(4));
	Debug::Log("4 players"); });

	backButton->onClick([this]()
		{
			m_clickSound.play();
	m_mainMenu->setVisible(true);
	m_matchSelectorMenu->setVisible(false); });

	m_gui.add(m_matchSelectorMenu);
	m_matchSelectorMenu->setVisible(false);
}

void Game::CreateWaitRoomMenu(tgui::Layout windowWidth, tgui::Layout windowHeight, uint32_t numberOfPlayers)
{
	m_waitRoomMenu = tgui::Group::create();

	tgui::Label::Ptr waitingLabel = tgui::Label::create();
	waitingLabel->setSize(windowWidth * 1000 / 1270, windowHeight * 120 / 720);
	waitingLabel->setPosition(windowWidth * 135 / 1270, windowHeight * 62 / 720);
	waitingLabel->getRenderer()->setTextColor(tgui::Color::White);
	waitingLabel->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	waitingLabel->getRenderer()->setTextOutlineThickness(1);
	waitingLabel->setText("Waiting for other players to join");
	waitingLabel->setTextSize(30);
	waitingLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

	tgui::Label::Ptr playersJoinedLabel = tgui::Label::create();
	playersJoinedLabel->setSize(windowWidth * 1000 / 1270, windowHeight * 120 / 720);
	playersJoinedLabel->setPosition(windowWidth * 135 / 1270, windowHeight * 200 / 720);
	playersJoinedLabel->getRenderer()->setTextColor(tgui::Color::White);
	playersJoinedLabel->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	playersJoinedLabel->getRenderer()->setTextOutlineThickness(1);
	playersJoinedLabel->setText("Players joined: 1 / 4");
	playersJoinedLabel->setTextSize(30);
	playersJoinedLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

	tgui::Button::Ptr startGameButton = tgui::Button::create();
	startGameButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	startGameButton->setPosition(windowWidth * 73 / 1270, windowHeight * 507.56 / 720);
	startGameButton->setText("Start game");
	startGameButton->setTextSize(20);

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->setSize(windowWidth * 218 / 1270, windowHeight * 56.9 / 720);
	backButton->setPosition(windowWidth * 73 / 1270, windowHeight * 595.09 / 720);
	backButton->setText("Back");
	backButton->setTextSize(20);

	m_waitRoomMenu->add(waitingLabel);
	m_waitRoomMenu->add(playersJoinedLabel);
	m_waitRoomMenu->add(startGameButton);
	m_waitRoomMenu->add(backButton);

	startGameButton->onClick([this, windowWidth, windowHeight]()
		{
			m_clickSound.play();
	m_waitRoomMenu->setVisible(false);
	CreateMapMenu(windowWidth, windowHeight);
	// start the game o rsomethng
		});

	backButton->onClick([this]()
		{
			m_clickSound.play();
	LeaveMatch();
	m_waitRoomMenu->setVisible(false);
	m_matchSelectorMenu->setVisible(true);
		});

	m_gui.add(m_waitRoomMenu);
	m_waitRoomMenu->setVisible(false);

	std::thread thread = std::thread([this, playersJoinedLabel, numberOfPlayers]()
		{
			while (true)
			{
				cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:8080/players" });
				auto body = crow::json::load(response.text);

				try
				{
					std::string message = body["message"].s();
					uint32_t code = body["code"].i();
					auto data = body["data"];

					if (code == 200)
					{
						Debug::Log(data);
						Debug::Log(data.size());

						if (playersJoinedLabel->getText().toStdString()[16] != std::to_string(data.size())[0]) {
							playersJoinedLabel->setText("Players joined: " + std::to_string(data.size()) + " / " + std::to_string(numberOfPlayers));
						}
					}
				}
				catch (const std::exception& e)
				{
					Debug::Log(e.what());
				}
			}
		});

	thread.detach();

	return;
}

void Game::CreateMapMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
{
	m_mapMenu = tgui::Group::create();

	CreateNumberQuestionMenu(windowWidth, windowHeight);
	CreateMultipleAnswerQuestionMenu(windowWidth, windowHeight);

	m_gui.add(m_mapMenu);
	m_mapMenu->setVisible(false);

	return; // for now

	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:8080/map" });
	auto body = crow::json::load(response.text);

	try
	{
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();
		auto data = body["data"];

		for (auto& row : data.lo())
		{
			for (auto& cell : row.lo())
			{

				Debug::Log(cell["player"]);
				Debug::Log(cell["score"]);
				Debug::Log(cell["type"]);

				auto& player = cell["player"];

				Debug::Log(player["id"]);

				/*
				 * trebuie verificat daca playerul e altceva in afara de NONE
				 * daca da, atunci ar trebui facut un auto player = cell["player"]
				 * si abia apoi extreas din player datale cu player["id"]
				 * sau name sau etc, asa cred
				 */
			}
		}

		if (code == 200)
		{
			auto windowWidth = tgui::bindWidth(m_gui);
			auto windowHeight = tgui::bindHeight(m_gui);

			m_matchSelectorMenu->setVisible(false);
			m_mainMenu->setVisible(false);

			return;
		}
		else
		{
			return;
		}
	}
	catch (const std::exception&)
	{
		return;
	}
}

void Game::CreateNumberQuestionMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
{
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

	tgui::Button::Ptr number0Button = tgui::Button::create();
	number0Button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	number0Button->setPosition(windowWidth * 452 / 1270, windowHeight * 335 / 720);
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
			button->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
			button->setPosition(windowWidth * xPosition[j - 1] / 1270, windowHeight * yPosition[i - 1] / 720);
			button->setText(std::to_string((i - 1) * 3 + j));
			button->setTextSize(20);

			numberButtons.push_back(button);
		}
	}

	tgui::Button::Ptr backspaceButton = tgui::Button::create();
	backspaceButton->setSize(windowWidth * 80 / 1270, windowHeight * 80 / 720);
	backspaceButton->setPosition(windowWidth * 549 / 1270, windowHeight * 335 / 720);
	backspaceButton->setText("Backspace");
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

	m_gui.add(m_numberQuestionMenu);
	m_numberQuestionMenu->setVisible(false);
}

void Game::CreateMultipleAnswerQuestionMenu(tgui::Layout windowWidth, tgui::Layout windowHeight)
{
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
	answer4Button->setEnabled(false); });

	answer4Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button, this]()
		{
			m_clickSound.play();
	selected = 4;

	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer1Button->setEnabled(false);
	answer2Button->setEnabled(false);
	answer3Button->setEnabled(false); });

	m_gui.add(m_multipleAnswerQuestionMenu);
	m_multipleAnswerQuestionMenu->setVisible(false);
}

std::string Game::Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
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

			auto windowWidth = tgui::bindWidth(m_gui);
			auto windowHeight = tgui::bindHeight(m_gui);

			m_user.id = data["player_id"].i();
			m_user.name = username->getText().toStdString();

			m_mainMenu->get<tgui::Label>("usernameLabel")->setText(m_user.name);

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

std::string Game::CreateAccount(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, tgui::EditBox::Ptr repeatPassword)
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
			auto windowWidth = tgui::bindWidth(m_gui);
			auto windowHeight = tgui::bindHeight(m_gui);

			m_user.id = m_user.id = data["player_id"].i();
			m_user.name = username->getText().toStdString();

			m_mainMenu->get<tgui::Label>("usernameLabel")->setText(m_user.name);

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

std::string Game::JoinMatch(uint32_t numberOfPlayers)
{
	auto response = cpr::Get(cpr::Url{ "http://localhost:8080/join_game/" + std::to_string(m_user.id) + '/' + std::to_string(numberOfPlayers) });
	auto body = crow::json::load(response.text);

	try
	{
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();

		if (code == 200)
		{
			auto windowWidth = tgui::bindWidth(m_gui);
			auto windowHeight = tgui::bindHeight(m_gui);

			m_matchSelectorMenu->setVisible(false);
			m_mainMenu->setVisible(false);

			CreateWaitRoomMenu(windowWidth, windowHeight, numberOfPlayers);
			m_waitRoomMenu->setVisible(true);

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

void Game::LeaveMatch()
{
	auto response = cpr::Get(cpr::Url{ "http://localhost:8080//leave_game/" + std::to_string(m_user.id) });
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
