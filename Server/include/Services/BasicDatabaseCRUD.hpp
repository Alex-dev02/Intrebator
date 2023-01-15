#pragma once

#include <memory>
#include <optional>

#include "../Database/Database.hpp"

class BasicDatabaseCRUD {
public:
	BasicDatabaseCRUD(std::shared_ptr<Database> database)
		:	m_database(database)
	{}

	template<typename T>
	std::unique_ptr<T> GetById(uint32_t id) {
		return std::move(m_database->get_pointer<T>(id));
	}

	template<typename T>
	std::optional<int> Insert(T data) {
		try {
			return m_database->insert(data);
		}
		catch (const std::exception& e) {
			return std::nullopt;
		}
	}

	template<typename T>
	std::vector<T> GetAll() {
		std::vector<T> items;
		for (const auto& i : m_database->iterate<T>()) {
			items.push_back(i);
		}
	}

private:
	std::shared_ptr<Database> m_database;
};
