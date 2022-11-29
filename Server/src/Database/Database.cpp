#include "../../include/Database/Database.hpp"

Storage& Database::GetStorage() {
	return m_storage;
}

const std::string& Database::GetDatabaseName() {
	return m_database_name;
}

const std::string Database::m_database_name{"intrebator_db"};

Storage Database::m_storage {InitDB::CreateStorage(m_database_name)};
