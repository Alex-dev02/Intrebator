#include "../../../include/Entities/Questions/MultipleAnswerQuestion.hpp"

MultipleAnswerQuestion::MultipleAnswerQuestion(const std::string& question, const std::array<std::string, 4>& answers)
	: Question(question), m_answers(answers)
{}

const std::string& MultipleAnswerQuestion::GetFirstAnswer() const{
	return m_answers[0];
}
const std::string& MultipleAnswerQuestion::GetSecondAnswer() const{
	return m_answers[1];
}
const std::string& MultipleAnswerQuestion::GetThirdAnswer() const{
	return m_answers[2];
}
const std::string& MultipleAnswerQuestion::GetCorrectAnswer() const{
	return m_answers[3];
}

void MultipleAnswerQuestion::SetFirstAnswer(const std::string& first_answer){
	m_answers[0] = first_answer;
}
void MultipleAnswerQuestion::SetSecondAnswer(const std::string& second_answer){
	m_answers[1] = second_answer;
}
void MultipleAnswerQuestion::SetThirdAnswer(const std::string& third_answer){
	m_answers[2] = third_answer;
}
void MultipleAnswerQuestion::SetCorrectAnswer(const std::string& correct_answer){
	m_answers[3] = correct_answer;
}
