#pragma once
#include <string>

class User {
public:
	User() = default;
	User(const std::string& name);
	User(std::uint32_t id, const std::string& name);
	User(std::uint32_t id, const std::string& name, const std::string& password);
	User(const std::string& name, const std::string& password);

public:
	uint32_t GetId() const;
	const std::string& GetName() const;
	const std::string& GetPassword() const;

	void SetId(std::uint32_t id);
	void SetName(const std::string& name);
	void SetPassword(const std::string& password);

private:
	uint32_t m_id;
	std::string m_name;
	std::string m_password;
};
