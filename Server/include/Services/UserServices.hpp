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
	std::unique_ptr<User> GetUserByName(const std::string& name);

public:
	void InitRoutes(std::shared_ptr<Server> server);

private:
	crow::json::wvalue UserRegister(const crow::request& req);
	crow::json::wvalue UserLogin(const crow::request& req);
	
private:
	std::shared_ptr<Database> m_database;
};
