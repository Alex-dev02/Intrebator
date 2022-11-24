#include "../../../include/Entities/Questions/NumericQuestion.hpp"

NumericQuestion::NumericQuestion(const std::string& question, int answer)
	: Question(question),
	m_answer(answer)
{}

int NumericQuestion::GetAnswer() const {
	return m_answer;
}
