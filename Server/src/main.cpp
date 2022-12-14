#include <memory>
#include <string>

#include "../include/Server/Server.hpp"
#include "../include/Services/UserServices.hpp"

int main() {
	const std::string db_name = "intrebator_db.sqlite";
	auto storage =
		std::make_shared<Database>(InitDB::CreateStorage(db_name));
	auto server = std::make_shared<Server>(storage);
	server->InitRoutes(server);
	server->StartServer();
}
