#pragma once

#include <memory>

#include "../Database/Database.hpp"

template<typename T>
class BasicDatabaseCRUD {
public:
	BasicDatabaseCRUD(std::shared_ptr<Database> database)
		:	m_database(database)
	{}
	T GetById(uint32_t id);
	std::vector<T> GetAll();
	void ReplaceById(uint32_t id);

private:
	std::shared_ptr<Database> m_database;
};
