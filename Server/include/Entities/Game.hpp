#pragma once

#include "Player.hpp"

#include "Questions/MultipleAnswerQuestion.hpp"
#include "Questions/NumericQuestion.hpp"
#include "Map.hpp"

#include <memory>
#include <vector>
#include <random>

class Game {
public:
	Game() {
		//m_players = aici punem clientii, ar trebui sa facem toti playerii ca si clienti
		m_map = Map(5, 3);

		m_rounds.resize(m_players.size() * 2);

		for (auto& round : m_rounds) {
			round.resize(m_players.size());
			for (auto& turn : round) {
				turn = std::make_unique<Player>(m_players[rand() % m_players.size()]);
			}
		}
	}

	~Game() = default;

	void Run() {
		for (auto& round : m_rounds) {
			for (auto& turn : round) {

			}
		}
	}

	int GetRandomValueFrom0UpUntilN(int n);

private:
	std::vector<Player> m_players;
	Map m_map;

	using turn = std::unique_ptr<Player>;
	using round = std::vector<turn>;

	std::vector<round> m_rounds;
	std::vector<MultipleAnswerQuestion> m_multi_question;
	std::vector<NumericQuestion> m_numeric_question;
};
