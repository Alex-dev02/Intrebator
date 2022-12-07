#include <memory>
#include <string>

#include "../include/Server/Server.hpp"

int main() {
	const std::string db_name = "intrebator_db.sqlite";
	auto storage =
		std::make_shared<Database>(db_name);
	auto server = std::make_shared<Server>(storage);

	auto& app = server->GetApp();

	server->Start();
}
