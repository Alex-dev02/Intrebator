#include "../../include/Entities/User.hpp"

User::User(const std::string& name)
	: m_id(-1),
	m_name(name)
{}

User::User(std::uint32_t id, const std::string& name)
	: m_id(id),
	m_name(name)
{}

const std::string& User::GetName() const {
	return m_name;
}

uint32_t User::GetId() const {
	return m_id;
}

void User::SetName(const std::string& name) {
	m_name = name;
}

void User::SetId(std::uint32_t id) {
	m_id = id;
}
