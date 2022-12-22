#pragma once

#include "../../include/Database/Database.hpp"

class QuestionServices {
public:
	QuestionServices(std::shared_ptr<Database> database);

	void InitRoutes();

public:
	std::vector<std::shared_ptr<NumericQuestion>> FetchQuestionForGame(uint16_t number_of_questions_to_fetch);

private:
	std::shared_ptr<Database> m_database;

};
