#pragma once

#include "../Entities/Player.hpp"
#include "../Entities/Questions/Question.hpp"

#include <vector>

class Contest {
public:
	Contest() = default;
	Contest(const std::vector<std::shared_ptr<Player>>& participants, std::unique_ptr<Question> question);

	Contest(const Contest&) = delete;

	// set playerssss
	void SetQuestion(std::unique_ptr<Question> question);
private:
	std::vector<std::shared_ptr<Player>> m_participants;
	std::unique_ptr<Question> m_question;
};
