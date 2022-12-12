#pragma once

#include <optional>
#include <memory>

#include "../Entities/User.hpp"
#include "../Database/Database.hpp"
#include "../Server/Server.hpp"

class UserServices {
public:
	UserServices(std::shared_ptr<Database> database);
	std::unique_ptr<User> GetUserById(uint32_t id);

public:
	void InitRoutes(std::shared_ptr<Server> server);

private:
	const crow::json::wvalue& UserRegister(const crow::request& req);
	const crow::json::wvalue& UserLogIn(const crow::request& req);
	
	
	const crow::json::wvalue& CrowResponseStatusAndMessage(int status, const std::string& message);

private:
	std::shared_ptr<Database> m_database;
};
