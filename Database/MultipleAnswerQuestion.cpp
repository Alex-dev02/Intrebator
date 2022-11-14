#include "pch.h"

#include "MultipleAnswerQuestion.h"

MultipleAnswerQuestion::MultipleAnswerQuestion(const std::string& question, const std::array<std::string, 4>& answers)
	: Question(question),
	m_answers(answers)
{}

const std::array<std::string, 4>& MultipleAnswerQuestion::GetAnswers() const {
	return m_answers;
}