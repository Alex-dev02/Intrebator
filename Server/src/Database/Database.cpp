#include "../../include/Database/Database.hpp"

const std::string Database::m_database_name{"intrebator_db"};

Storage Database::m_storage {InitDB::CreateStorage(m_database_name)};
