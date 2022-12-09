#include "../../include/Services/UserServices.hpp"

void UserServices::InitRoutes(std::shared_ptr<Server> server) {

}

UserServices::UserServices(std::shared_ptr<Database> database)
	: m_database(database)
{}

std::unique_ptr<User> UserServices::GetUserById(uint32_t id) {
	return std::move(m_database->get_pointer<User>(id));
}
