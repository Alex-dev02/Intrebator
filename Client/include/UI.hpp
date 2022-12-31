#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>

#include "../../Logger/Debug.hpp"

class UI {
public:
	UI(sf::RenderWindow& window);

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

private:
	tgui::Gui m_gui;

	sf::RenderWindow* m_window;

	tgui::Group::Ptr m_loginMenu;
	tgui::Group::Ptr m_registerMenu;
	tgui::Group::Ptr m_mainMenu;
	tgui::Group::Ptr m_matchSelectorMenu;
	tgui::Group::Ptr m_optionsMenu;

	tgui::Group::Ptr m_mapMenu;
	tgui::Group::Ptr m_numberQuestionMenu;
	tgui::Group::Ptr m_multipleAnswerQuestionMenu;
};