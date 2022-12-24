#include "../../../include/Entities/Questions/MultipleAnswerQuestion.hpp"

#include <algorithm>
#include <random>

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

MultipleAnswerQuestion::operator crow::json::wvalue() const {
	std::vector<crow::json::wvalue> answers = {
		crow::json::wvalue{GetFirstAnswer()},
		crow::json::wvalue{GetSecondAnswer()},
		crow::json::wvalue{GetThirdAnswer()},
		crow::json::wvalue{GetCorrectAnswer()}
	};

	auto rng = std::default_random_engine{};
	std::shuffle(answers.begin(), answers.end(), rng);

	return crow::json::wvalue{
		{"question", GetQuestion()},
		{"answers", answers}
	};
}

