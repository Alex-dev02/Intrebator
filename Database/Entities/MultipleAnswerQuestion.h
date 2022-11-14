#pragma once

#include "Question.h"
#include <array>

class MultipleAnswerQuestion final : public Question {
public:
	MultipleAnswerQuestion(const std::string& question, const std::array<std::string, 4>& answers);

	const std::array<std::string, 4>& GetAnswers() const;

private:
	std::array<std::string, 4> m_answers;
};
