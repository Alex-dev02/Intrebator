#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>

#include <SFML/Audio.hpp>

#include "../../Logger/Debug.hpp"

class Game
{
public:
	struct User
	{
		uint32_t id;
		std::string name;
	};

public:
	Game(sf::RenderWindow &window);

	inline tgui::Gui &GetGui() { return m_gui; }
	inline void Draw() { m_gui.draw(); }
	inline void HandleEvent(sf::Event event) { m_gui.handleEvent(event); }

private:
	void CreateLoginMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateRegisterMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateMainMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateOptionsMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateMatchSelectorMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);

private:
	void CreateWaitRoomMenu(tgui::Layout windowWidth, tgui::Layout windowHeight, uint32_t numberOfPlayers);
	void CreateMapMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateNumberQuestionMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateMultipleAnswerQuestionMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);

private:
	std::string CreateAccount(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, tgui::EditBox::Ptr repeatPassword);
	std::string Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password);
	std::string JoinMatch(uint32_t numberOfPlayers);

public:
	void LeaveMatch();

private:
	tgui::Gui m_gui;

	User m_user;

	sf::RenderWindow *m_window;

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

	tgui::Group::Ptr m_loginMenu;
	tgui::Group::Ptr m_registerMenu;
	tgui::Group::Ptr m_mainMenu;

	tgui::Group::Ptr m_optionsMenu;
	tgui::Group::Ptr m_matchSelectorMenu;

	tgui::Group::Ptr m_waitRoomMenu;
	tgui::Group::Ptr m_mapMenu;
	tgui::Group::Ptr m_numberQuestionMenu;
	tgui::Group::Ptr m_multipleAnswerQuestionMenu;
};