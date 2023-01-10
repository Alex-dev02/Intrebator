#include "../include/Menu.hpp"

#include <cpr/cpr.h>
#include <crow.h>

#include "../../Logger/Debug.hpp"

Menu::Menu(sf::RenderWindow& window)
	:m_windowWidth(tgui::bindWidth(m_gui)), m_windowHeight(tgui::bindHeight(m_gui))
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

	tgui::Picture::Ptr background = tgui::Picture::create("assets/images/background.png");
	background->setSize(m_windowWidth, m_windowHeight);

	m_gui.setTarget(window);
	m_gui.setFont(tgui::Font("assets/fonts/Inter-Medium.ttf"));
	m_gui.add(background);

	CreateLoginMenu();
	CreateRegisterMenu();
	CreateMainMenu();
	CreateMatchSelectorMenu();
	CreateOptionsMenu();
}

void Menu::CreateLoginMenu()
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

void Menu::CreateRegisterMenu()
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

void Menu::CreateMainMenu()
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
	m_window->close(); });

	m_gui.add(m_mainMenu);
	m_mainMenu->setVisible(false);
}

void Menu::CreateOptionsMenu()
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

void Menu::CreateMatchSelectorMenu()
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

void Menu::CreateWaitRoomMenu(uint32_t numberOfPlayers)
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

	tgui::Label::Ptr playersJoinedLabel = tgui::Label::create();
	playersJoinedLabel->setSize(m_windowWidth * 1000 / 1270, m_windowHeight * 120 / 720);
	playersJoinedLabel->setPosition(m_windowWidth * 135 / 1270, m_windowHeight * 200 / 720);
	playersJoinedLabel->getRenderer()->setTextColor(tgui::Color::White);
	playersJoinedLabel->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	playersJoinedLabel->getRenderer()->setTextOutlineThickness(1);
	playersJoinedLabel->setText("Players joined: 1 / 4");
	playersJoinedLabel->setTextSize(30);
	playersJoinedLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

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
	m_waitRoomMenu->add(playersJoinedLabel);
	m_waitRoomMenu->add(startGameButton);
	m_waitRoomMenu->add(backButton);

	startGameButton->onClick([this]()
		{
			m_clickSound.play();
	m_waitRoomMenu->setVisible(false);

	//start the game or smth
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
						if (playersJoinedLabel->getText().toStdString()[16] != std::to_string(data.size())[0]) {
							playersJoinedLabel->setText("Players joined: " + std::to_string(data.size()) + " / " + std::to_string(numberOfPlayers));
							for (auto& player : data.lo()) {
								Debug::Log(player["name"].s());
								Debug::Log(player["color"].s());
								Debug::Log(player["id"].i());
							}
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

std::string Menu::Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
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

std::string Menu::CreateAccount(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, tgui::EditBox::Ptr repeatPassword)
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

std::string Menu::JoinMatch(uint32_t numberOfPlayers)
{
	auto response = cpr::Get(cpr::Url{ "http://localhost:8080/join_game/" + std::to_string(m_localPlayer.id) + '/' + std::to_string(numberOfPlayers) });
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

			CreateWaitRoomMenu(numberOfPlayers);
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

void Menu::LeaveMatch()
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
