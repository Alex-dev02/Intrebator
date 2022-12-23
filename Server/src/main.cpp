#include <memory>
#include <string>

#include "../include/Server/Server.hpp"
#include "../include/Services/UserServices.hpp"
#include "../include/Services/GameServices.hpp"
#include "../include/Utils/InsertFromFileIntoQuestions.hpp"

void PopulateDatabase(std::shared_ptr<Database> database);

int main() {
	const std::string db_name = "intrebator_db.sqlite";
	auto storage =
		std::make_shared<Database>(InitDB::CreateStorage(db_name));
	
	PopulateDatabase(storage);

	auto server = std::make_shared<Server>(storage);

	auto user_services = std::make_shared<UserServices>(storage);
	user_services->InitRoutes(server);
	auto game_services = std::make_shared<GameServices>(storage, server);
	game_services->InitRoutes();

	server->StartServer();
}

void PopulateDatabase(std::shared_ptr<Database> database) {
	try{
		auto numeric_questions = ReadNumericQuestionsFromFile();
		auto multiple_questions = ReadMultipleAnswerQuestionsFromFile();

		for (const auto& n_question : numeric_questions)
			database->insert<NumericQuestion>(n_question);

		for (const auto& m_question : multiple_questions)
			database->insert<MultipleAnswerQuestion>(m_question);
	}
	catch (const std::exception& e){
		std::cerr << e.what() << '\n';
		std::cerr << "Failed to populate database\n";
	}
}
