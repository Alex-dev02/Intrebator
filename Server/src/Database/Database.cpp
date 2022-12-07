#include "../../include/Database/Database.hpp"

Database::Database(const std::string& database_name)
	: m_database_name(database_name),
	m_storage(InitDB::CreateStorage(database_name))
{}

Database::Storage& Database::GetStorage() {
	return m_storage;
}
const std::string& Database::GetDatabaseName() {
	return m_database_name;
}
