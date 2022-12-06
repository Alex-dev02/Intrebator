#include "crow.h"

#include "../include/Server/Server.hpp"
#include "../include/Database/Database.hpp"

int main() {
	Storage storage = Database::GetStorage();

	Server server;
	auto& app = server.GetApp();

	server.Start();
}
