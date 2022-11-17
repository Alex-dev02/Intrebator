#include "crow.h"

#include "../include/Utils/Server.hpp"

int main()
{
    Server server;
    auto& app = server.GetApp();

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
        });

    server.Start();
}
