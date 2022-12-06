#pragma once

#include <string>

#include "../Inutils/GenerateDateAndTime.hpp"

class Match{
public:
	Match(std::uint32_t id, const std::string& date);

public:
	std::uint32_t GetId() const;
	const std::string& GetDate() const;

	void SetId(std::uint32_t id);
	void SetDate(const std::string& date);

private:
	std::uint32_t m_id;
	DateGenerator::Date m_date;
};
