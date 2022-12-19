#include "../../include/Utils/Contest.hpp"

Contest::Contest(const std::vector<std::shared_ptr<Player>>& participants, std::unique_ptr<Question> question)
	:
	m_participants(participants),
	m_question(std::move(question))
{}

void Contest::SetQuestion(std::unique_ptr<Question> question) {
	m_question = std::move(question);
}
