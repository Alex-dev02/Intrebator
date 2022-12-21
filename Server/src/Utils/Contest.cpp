#include "../../include/Inutils/Contest.hpp"

void Contest::SetQuestion(std::unique_ptr<Question> question) {
	m_question = std::move(question);
}

void Contest::AddParticipant(std::shared_ptr<Player> player) {
	m_participants.push_back(player);
}

void Contest::SetParticipants(const std::vector<std::shared_ptr<Player>>& players) {
	m_participants = players;
}

void Contest::ClearParticipants() {
	m_participants.clear();
}

void Contest::StartTimer() {
	m_time = time(nullptr);
}

Contest::Answer::Answer()
	: m_player(nullptr),
	m_answering_time_ms(0),
	m_answer("")
{}

Contest::Answer::Answer(std::shared_ptr<Player> player, uint16_t answering_time_ms, const std::string& answer)
	: m_player(player),
	m_answering_time_ms(answering_time_ms),
	m_answer(answer)
{}

uint8_t Contest::GetAnswersSize() {
	return m_answers.size();
}

uint8_t Contest::GetParticipantsSize() {
	return m_participants.size();
}