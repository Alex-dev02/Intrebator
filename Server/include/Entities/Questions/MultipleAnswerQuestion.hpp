#pragma once

#include "Question.hpp"

#include <array>
#include <string>
#include <vector>
#include <crow/json.h>

class MultipleAnswerQuestion final : public Question {
public:
	MultipleAnswerQuestion() = default;
	MultipleAnswerQuestion(const std::string& question, const std::array<std::string, 4>& answers);

	const std::string& GetFirstAnswer() const;
	const std::string& GetSecondAnswer() const;
	const std::string& GetThirdAnswer() const;
	const std::string& GetCorrectAnswer() const;

	void SetFirstAnswer(const std::string& first_answer);
	void SetSecondAnswer(const std::string& second_answer);
	void SetThirdAnswer(const std::string& third_answer);
	void SetCorrectAnswer(const std::string& correct_answer);

	operator crow::json::wvalue() const;

private:
	std::array<std::string, 4> m_answers;
};
