#pragma once

#include "Question.hpp"

class NumericQuestion final : public Question {
public:
	NumericQuestion(const std::string& question, int answer);

	int GetAnswer() const;
private:
	int m_answer;
};
