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

	void Start();
public:
	void InitRoutes(std::shared_ptr<Server> server);
private:
	void CreateGame();
private:

	crow::SimpleApp m_app;
	std::vector<Game> m_games;
	std::shared_ptr<Database> m_database;
};
