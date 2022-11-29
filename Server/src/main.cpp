#include "crow.h"

#include "../include/Server/Server.hpp"
#include "../include/Database/Database.hpp"

int main() {
    const std::string db_name = "db_test";
    Storage storage = Database::GetStorage();

    Server server;
    auto& app = server.GetApp();
    server.Start();
}
