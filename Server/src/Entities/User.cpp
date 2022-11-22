#include "../../include/Entities/User.hpp"

User::User(unsigned int id, const std::string& name)
	: m_id(id),
	m_name(name)
{}

const std::string& User::GetName() const {
	return m_name;
}

unsigned int User::GetId() const {
	return m_id;
}

void User::SetName(const std::string& name) {
	m_name = name;
}

void User::SetId(std::uint32_t id) {
	m_id = id;
}
