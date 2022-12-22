#pragma once

#include "Question.hpp"

class NumericQuestion final : public Question {
public:
	NumericQuestion() = default;
	NumericQuestion(const std::string& question, int answer);

	int GetAnswer() const;

	void SetAnswer(int answer);
private:
	int m_answer;
};
