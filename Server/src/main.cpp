#include "crow.h"

#include "../include/Utils/Server.hpp"

void n();

int main()
{
    Server server;
    auto& app = server.GetApp();
    n();
    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
        });

    server.Start();
}

void n() {
    Server server;
    auto& app = server.GetApp();
    CROW_ROUTE(app, "/user")([]() {
        return "Hello user";
        });
}
