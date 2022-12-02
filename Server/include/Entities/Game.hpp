#pragma once
#include "Player.hpp"
#include "Questions/MultipleAnswerQuestion.hpp"
#include "Questions/NumericQuestion.hpp"

// #include <memory>   //std::unique_ptr
#include <vector>

class Game{
public:

private:
	std::vector<Player> m_players;
	// vector<unique pointer<player>> m_moves ???
	std::vector<MultipleAnswerQuestion> m_multi_question;
	std::vector<NumericQuestion> m_numeric_question;
};
