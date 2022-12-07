#pragma once

#include "crow.h"
#include "../Entities/Game.hpp"

#include <vector>

class Server {
public:

	Server() = default;
	Server(Server&) = delete;
	Server(Server&&) = delete;
	~Server() = default;

	crow::SimpleApp& GetApp();

	void Start();

	void CreateGame();

private:
	crow::SimpleApp m_app;
	std::vector<Game> m_games;
};
