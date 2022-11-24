#pragma once
#include <string>
#

class Match{
public:
	Match(std::uint32_t id, std::string date);

public:
	const std::uint32_t& GetId() const;

	const std::string& GetDate() const;

	void SetId(std::uint32_t id);

	void SetDate(std::string date);
private:
	std::uint32_t m_id;
	std::string m_date;
};
