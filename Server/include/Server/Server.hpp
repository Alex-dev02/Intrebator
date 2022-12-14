#pragma once

#include "crow.h"
#include "../Entities/Game.hpp"
#include "../Database/Database.hpp"

#include <vector>

class Server {
public:
	Server(std::shared_ptr<Database> database);
	Server(Server&) = delete;
	Server(Server&&) = delete;
	~Server() = default;

	crow::SimpleApp& GetApp();

	void StartServer();
	void StartGame();
public:
	void InitRoutes(std::shared_ptr<Server> server);

private:
	crow::SimpleApp m_app;
	Game m_game;
	std::shared_ptr<Database> m_database;

	bool m_game_running;
};
