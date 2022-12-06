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

	crow::SimpleApp& GetApp() const;

	void Start();

	void CreateGame();

private:
	static crow::SimpleApp m_app;
	std::vector<Game> m_games;
};
