#include <memory>
#include <string>

#include "../include/Server/Server.hpp"
#include "../include/Services/UserServices.hpp"
#include "../include/Services/GameServices.hpp"

int main() {
	const std::string db_name = "intrebator_db.sqlite";
	auto storage =
		std::make_shared<Database>(InitDB::CreateStorage(db_name));
	auto server = std::make_shared<Server>(storage);

	auto user_services = std::make_shared<UserServices>(storage);
	user_services->InitRoutes(server);
	auto game_services = std::make_shared<GameServices>(storage, server);
	game_services->InitRoutes();

	server->StartServer();
}
