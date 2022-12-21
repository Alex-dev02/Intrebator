#pragma once
#include <string>

class DateGenerator{
public:
	struct Date {
		Date() = default;
		Date(const std::string& date);
		std::string date;
	};

public:
	static const Date& GetCurrentTimeAndDate();
};
