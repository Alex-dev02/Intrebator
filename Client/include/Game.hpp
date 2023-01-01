#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>

#include "../include/User.hpp"

#include "../../Logger/Debug.hpp"

class Game {
public:
	Game(sf::RenderWindow& window);

	inline tgui::Gui& GetGui() { return m_gui; }
	inline void Draw() { m_gui.draw(); }
	inline void HandleEvent(sf::Event event) { m_gui.handleEvent(event); }

private:
	void CreateLoginMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateRegisterMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateMainMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateMatchSelectorMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateOptionsMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);

private:
	void CreateMapMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateNumberQuestionMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);
	void CreateMultipleAnswerQuestionMenu(tgui::Layout windowWidth, tgui::Layout windowHeight);

private:
	std::string CreateAccount(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, tgui::EditBox::Ptr repeatPassword);
	std::string Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password);
	std::string JoinMatch(uint32_t numberOfPlayers);

private:
	tgui::Gui m_gui;

	User m_user; // we'll use this 1 l8r

	sf::RenderWindow* m_window;

	tgui::Group::Ptr m_menus;

	tgui::Group::Ptr m_loginMenu;
	tgui::Group::Ptr m_registerMenu;
	tgui::Group::Ptr m_mainMenu;

	tgui::Group::Ptr m_matchSelectorMenu;
	tgui::Group::Ptr m_optionsMenu;

	tgui::Group::Ptr m_gameMenus;

	tgui::Group::Ptr m_mapMenu;
	tgui::Group::Ptr m_numberQuestionMenu;
	tgui::Group::Ptr m_multipleAnswerQuestionMenu;
};