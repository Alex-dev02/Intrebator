#pragma once

#include <memory>

#include "../Database/Database.hpp"

template<typename T>
class BasicDatabaseCRUD {
public:
	BasicDatabaseCRUD(std::shared_ptr<Database> database)
		:	m_database(database)
	{}
	std::unique_ptr<T> GetById(uint32_t id) {
		return std::move(m_database->get_pointer<T>(id));
	}
	void Insert(T data) {
		m_database->insert(data);
	}
	std::vector<T> GetAll();
	void ReplaceById(uint32_t id);

private:
	std::shared_ptr<Database> m_database;
};
