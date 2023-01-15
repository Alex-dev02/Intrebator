#include <memory>
#include <string>

#include "../include/Services/BasicDatabaseCRUD.hpp"
#include "../include/Server/Server.hpp"
#include "../include/Services/UserServices.hpp"
#include "../include/Services/GameServices.hpp"
#include "../include/Utils/InsertFromFileIntoQuestions.hpp"

void PopulateDatabase(std::shared_ptr<Database> database);

int main() {
	const std::string db_name = "intrebator_db.sqlite";
	auto storage =
		std::make_shared<Database>(InitDB::CreateStorage(db_name));
	try {
		PopulateDatabase(storage);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

	auto server = std::make_shared<Server>(storage);

	auto user_services = std::make_shared<UserServices>(storage);
	user_services->InitRoutes(server);
	auto game_services = std::make_shared<GameServices>(storage, server);
	game_services->InitRoutes();

	server->StartServer();
}

void PopulateDatabase(std::shared_ptr<Database> database) {
	try{
		BasicDatabaseCRUD crud{database};
		auto numeric_questions = ReadNumericQuestionsFromFile();
		auto multiple_questions = ReadMultipleAnswerQuestionsFromFile();

		for (const auto& n_question : numeric_questions)
			crud.Insert(n_question);

		for (const auto& m_question : multiple_questions)
			crud.Insert(m_question);
	}
	catch (const std::exception& e){
		std::cerr << e.what() << '\n';
		throw std::exception("Failed to populate the database\n");
	}
}
