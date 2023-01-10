#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>

#include <SFML/Audio.hpp>

#include <vector>

#include "Player.hpp"

class Game {
public:
	Game(sf::RenderWindow& window);

	inline tgui::Gui& GetGui() { return m_gui; }
	inline void Draw() { m_gui.draw(); }
	inline void HandleEvent(sf::Event event) { m_gui.handleEvent(event); }

	void CreateMapMenu();
	void CreateNumberQuestionMenu();
	void CreateMultipleAnswerQuestionMenu();

	void Update();

private:
	tgui::Gui m_gui;

	tgui::Layout m_windowWidth;
	tgui::Layout m_windowHeight;

	std::string m_state;

	Player m_localPlayer;

	std::vector<Player> m_players;

	sf::RenderWindow* m_window;

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

	tgui::Group::Ptr m_mapMenu;
	tgui::Group::Ptr m_numberQuestionMenu;
	tgui::Group::Ptr m_multipleAnswerQuestionMenu;
};
