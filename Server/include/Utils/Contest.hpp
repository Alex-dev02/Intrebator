#pragma once

#include "../Entities/Player.hpp"
#include "../Entities/Questions/Question.hpp"

#include <vector>
#include <ctime>
#include <crow.h>

class Contest {
public:
	struct Answer {
		Answer();
		Answer(std::shared_ptr<Player> player, uint16_t answering_time_s, const std::string& answer);
		std::shared_ptr<Player> m_player;
		uint16_t m_answering_time_s;
		std::string m_answer;

		operator crow::json::wvalue() const;
	};

public:
	Contest() = default;

	Contest(const Contest&) = delete;

	// set playerssss
	void SetQuestion(std::shared_ptr<Question> question);
	void AddParticipant(std::shared_ptr<Player> player);
	void SetParticipants(const std::vector<std::shared_ptr<Player>>& players);
	void ClearParticipants();
	void StartTimer();

	uint8_t GetAnswersSize();
	uint8_t GetParticipantsSize();
	std::shared_ptr<Question> CurrentQuestion();

	void SubmitAnswer(const std::string& answer, std::shared_ptr<Player> player);
	std::vector<Contest::Answer> GetAnswers();
private:
	std::time_t m_time;
	std::vector<std::shared_ptr<Player>> m_participants;
	std::shared_ptr<Question> m_question;
	std::vector<Answer> m_answers;

};
