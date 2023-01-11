#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "Player.hpp"

class Application
{
public:
	Application();
	void Run();

private:
	void CreateLoginMenu();
	void CreateRegisterMenu();
	void CreateMainMenu();
	void CreateOptionsMenu();
	void CreateMatchSelectorMenu();

	void CreateWaitRoomMenu(uint32_t numberOfPlayers);

	void CreateMapMenu();
	void CreateNumberQuestionMenu();
	void CreateMultipleAnswerQuestionMenu();

	void Update();

private:
	std::string CreateAccount(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, tgui::EditBox::Ptr repeatPassword);
	std::string Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password);
	std::string JoinMatch(uint32_t numberOfPlayers);

private:
	void LeaveMatch();

private:
	sf::RenderWindow m_window;

	sf::Image m_icon;
	sf::Image m_background;
	sf::Font m_font;

private:
	tgui::Gui m_gui;
	tgui::Layout m_windowWidth;
	tgui::Layout m_windowHeight;

	std::string m_gameState;

	Player m_localPlayer;

	std::vector<Player> m_players;

	sf::Music m_menuMusic;
	sf::Music m_gameMusic;

	sf::SoundBuffer m_clickSoundBuffer;
	sf::SoundBuffer m_checkboxSoundBuffer;
	sf::SoundBuffer m_correctSoundBuffer;
	sf::SoundBuffer m_incorrectSoundBuffer;

	sf::Sound m_clickSound;
	sf::Sound m_checkBoxSound;
	sf::Sound m_correctSound;
	sf::Sound m_incorrectSound;

	bool m_gameStarted = false;

private:
	tgui::Group::Ptr m_loginMenu;
	tgui::Group::Ptr m_registerMenu;
	tgui::Group::Ptr m_mainMenu;

	tgui::Group::Ptr m_optionsMenu;
	tgui::Group::Ptr m_matchSelectorMenu;

	tgui::Group::Ptr m_waitRoomMenu;

private:
	tgui::Group::Ptr m_mapMenu;
	tgui::Group::Ptr m_numberQuestionMenu;
	tgui::Group::Ptr m_multipleAnswerQuestionMenu;
};
