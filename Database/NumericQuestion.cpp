#include "pch.h"

#include "NumericQuestion.h"

NumericQuestion::NumericQuestion(const std::string& question, int answer)
	: Question(question),
	m_answer(answer)
{}

int NumericQuestion::GetAnswer() const {
	return m_answer;
}
