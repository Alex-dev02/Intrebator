#include "../../include/Entities/User.hpp"

User::User(const std::string& name)
	: m_id(-1),
	m_name(name)
{}

User::User(std::uint32_t id, const std::string& name)
	: m_id(id),
	m_name(name)
{}

User::User(std::uint32_t id, const std::string & name, const std::string & password)
	: m_id(id),
	m_name(name),
	m_password(password)
{}

User::User(const std::string& name, const std::string& password)
	: m_id(-1), 
	m_name(name), 
	m_password(password)
{}

uint32_t User::GetId() const {
	return m_id;
}

const std::string& User::GetName() const {
	return m_name;
}

const std::string& User::GetPassword() const {
	return m_password;
}

void User::SetId(std::uint32_t id) {
	m_id = id;
}

void User::SetName(const std::string& name) {
	m_name = name;
}

void User::SetPassword(const std::string& password) {
	m_password = password;
}
