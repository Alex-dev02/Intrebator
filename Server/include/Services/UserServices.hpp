#pragma once

#include <optional>
#include <memory>

#include "../Entities/User.hpp"
#include "../Database/Database.hpp"

class UserServices {
public:
	UserServices(std::shared_ptr<Database> database);
	std::unique_ptr<User> GetUserById(uint32_t id);

private:
	std::shared_ptr<Database> m_database;
};
