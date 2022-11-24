#pragma once

#include "Question.hpp"

#include <array>
#include <string>

class MultipleAnswerQuestion final : public Question {
public:
	enum class Answers{
		first_answer,
		second_answer,
		third_answer,
		fourth_answer,
		correct_answer
	};
public:
	MultipleAnswerQuestion(const std::string& question, const std::array<std::string, 4>& answers);

	const std::array<std::string, 4>& GetAnswers() const;

private:
	std::array<std::string, 4> m_answers;
};
