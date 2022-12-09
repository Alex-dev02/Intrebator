#pragma once
#include <string>

class User {
public:
	User() = default;
	User(const std::string& name);
	User(std::uint32_t id, const std::string& name);

public:
	const std::string& GetName() const;
	uint32_t GetId() const;

	void SetId(std::uint32_t id);
	void SetName(const std::string& name);

private:
	uint32_t m_id;
	std::string m_name;
};
