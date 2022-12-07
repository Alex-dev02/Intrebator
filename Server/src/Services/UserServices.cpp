#include "../../include/Services/UserServices.hpp"

UserServices::UserServices(std::shared_ptr<Database> database)
	: m_database(database)
{}

std::optional<std::unique_ptr<User>> UserServices::GetUserById(uint32_t id) {
	auto user = m_database->get_pointer<User>(id);

	return user ? std::optional<std::unique_ptr<User>>(std::move(user)) : std::nullopt;
}
