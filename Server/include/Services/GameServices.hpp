#pragma once

#include "../Database/Database.hpp"
#include "../Server/Server.hpp"

class GameServices {
public:
	GameServices(std::shared_ptr<Database> database);
	
	void InitRoutes(std::shared_ptr<Server> server);

private:
	const std::pair<bool, const crow::json::wvalue&>& CreateGame(uint32_t user_id);

private:
	std::shared_ptr<Database> m_database;
};
