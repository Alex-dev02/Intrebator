#include "crow.h"

#include "../include/Server/Server.hpp"

int main()
{
    Server server;
    auto& app = server.GetApp();
    server.Start();
}
