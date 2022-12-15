#pragma once

#include "../Database/Database.hpp"
#include "../Server/Server.hpp"

class GameServices {
public:
	GameServices(std::shared_ptr<Database> database, std::shared_ptr<Server> server);
	
	void InitRoutes();

private:
	const crow::json::wvalue& JoinGame(uint32_t user_id, uint8_t room_size);

private:
	std::shared_ptr<Server> m_server;
	std::shared_ptr<Database> m_database;
	std::shared_ptr<Game> m_game;
};
