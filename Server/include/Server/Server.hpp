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
	
public:
	void StartGame();
	std::shared_ptr<Game> GetGame() const;
	bool GameIsRunning() const;

private:
	crow::SimpleApp m_app;
	std::shared_ptr<Game> m_game;
	std::shared_ptr<Database> m_database;

	bool m_game_running;
};
