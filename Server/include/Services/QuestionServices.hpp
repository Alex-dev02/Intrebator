#pragma once

#include "../../include/Database/Database.hpp"

class QuestionServices {
public:
	QuestionServices(std::shared_ptr<Database> database);

	void InitRoutes();

private:
	std::shared_ptr<Database> m_database;

};
