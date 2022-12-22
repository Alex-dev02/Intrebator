#include "../../include/Services/QuestionServices.hpp"

QuestionServices::QuestionServices(std::shared_ptr<Database> database)
	: m_database(database)
{}

void QuestionServices::InitRoutes() {
}

std::vector<std::shared_ptr<NumericQuestion>> QuestionServices::FetchQuestionForGame(uint16_t number_of_questions_to_fetch) {
	using namespace sqlite_orm;

	uint16_t number_of_numeric_questions = (rand() % number_of_questions_to_fetch) + 1 + 1; // +1 so rand doesn't return 0 and +1 because we need a numeric question for base picking
	uint16_t number_of_multiple_answer_questions = number_of_questions_to_fetch - number_of_numeric_questions;

	std::vector<std::shared_ptr<NumericQuestion>> questions;
	uint16_t stopper = 0;
	//auto numeric_questions = m_database->get_all<NumericQuestion>();

	//for (const auto& question : m_database->iterate<NumericQuestion>(order_by(sqlite_orm::random()), limit(number_of_numeric_questions))) {
	//	//questions.push_back(std::make_shared<NumericQuestion>(question));
	//}
	return questions;
}
