#include "crow.h"
#include <memory>

#include "../include/Server/Server.hpp"
#include "../include/Database/Database.hpp"

int main() {
	std::shared_ptr<Database::Storage> storage =
		std::make_shared<Database::Storage>(InitDB::CreateStorage("intrebator_db.sqlite"));
	std::shared_ptr<Server> server = std::make_shared<Server>();

	auto& app = server->GetApp();

	server->Start();
}
