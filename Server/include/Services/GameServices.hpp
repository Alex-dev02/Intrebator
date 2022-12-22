#pragma once

#include "../Database/Database.hpp"
#include "../Server/Server.hpp"
#include "../Services/UserServices.hpp"

class GameServices {
public:
	GameServices(std::shared_ptr<Database> database, std::shared_ptr<Server> server);
	
	void InitRoutes();

private:
	crow::json::wvalue JoinGame(uint32_t user_id, uint8_t room_size);
	crow::json::wvalue LeaveGame(uint32_t user_id);
	crow::json::wvalue StartGame();
	crow::json::wvalue CheckGameStatus();
	crow::json::wvalue SubmitAnswerForCurrentQuestion(const crow::request& req);
private:
	std::shared_ptr<Server> m_server;
	std::shared_ptr<Database> m_database;
	std::shared_ptr<UserServices> m_user_services;
	std::shared_ptr<Game> m_game;
};
