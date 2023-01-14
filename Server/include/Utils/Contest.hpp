#pragma once

#include "../Entities/Player.hpp"
#include "../Entities/Questions/Question.hpp"

#include <vector>
#include <ctime>
#include <crow.h>
#include <variant>

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

	struct EvaluatedAnswer {
		EvaluatedAnswer() = default;

		std::shared_ptr<Player> m_player;
		std::variant<bool, float> m_is_correct_or_margin_error;
	};

public:
	Contest() = default;

	Contest(const Contest&) = delete;

	// set playerssss
	void SetQuestion(std::shared_ptr<Question> question);
	void AddParticipant(std::shared_ptr<Player> player);
	void SetParticipants(const std::vector<std::shared_ptr<Player>>& players);
	void ClearParticipants();
	void ClearContestData();
	void StartTimer();

	uint8_t GetAnswersSize();
	uint8_t GetParticipantsSize();
	std::shared_ptr<Question> CurrentQuestion();

	void SubmitAnswer(const std::string& answer, std::shared_ptr<Player> player);
	std::vector<Contest::Answer> GetAnswers();
	crow::json::wvalue GetResult(uint32_t player_id);
	crow::json::wvalue GetResults();
	std::vector<EvaluatedAnswer> GetEvaluatedAnswers();
	const std::vector<std::shared_ptr<Player>>& GetParticipants() const;

private:
	std::optional<std::vector<EvaluatedAnswer>> GetEvaluatedAnswersForNumericQuestion();
	std::optional<std::vector<EvaluatedAnswer>> GetEvaluatedAnswersForMultipleQuestion();
	float GetMarginErrorForAnswer(int given_answer, int correct_answer);
	bool UsedPowerup(const Player::Powerups& powerupName);

private:
	std::time_t m_time;
	std::vector<std::shared_ptr<Player>> m_participants;
	std::shared_ptr<Question> m_question;
	std::vector<Answer> m_answers;

};
