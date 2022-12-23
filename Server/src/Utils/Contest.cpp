#include "../../include/Utils/Contest.hpp"

void Contest::SetQuestion(std::shared_ptr<Question> question) {
	m_question = question;
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
	m_answering_time_s(0),
	m_answer("")
{}

Contest::Answer::Answer(std::shared_ptr<Player> player, uint16_t answering_time_s, const std::string& answer)
	: m_player(player),
	m_answering_time_s(answering_time_s),
	m_answer(answer)
{}

Contest::Answer::operator crow::json::wvalue() const {
	return crow::json::wvalue{
		{"player", static_cast<crow::json::wvalue>(*m_player.get())},
		{"answering_time", m_answering_time_s},
		{"answer", m_answer}
	};
}

uint8_t Contest::GetAnswersSize() {
	return m_answers.size();
}

uint8_t Contest::GetParticipantsSize() {
	return m_participants.size();
}

void Contest::SubmitAnswer(const std::string& answer, std::shared_ptr<Player> player) {
	m_answers.push_back(Answer(player, m_time - time(nullptr), answer));
}

std::vector<Contest::Answer> Contest::GetAnswers() {
	//if (m_time - time(nullptr) >= 15) // commented because of magic number 15, which must be set in a variable as a standard waiting time to answer the questions
		return m_answers;
	return {};
}

