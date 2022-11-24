#include <ctime>

#include "../../include/Entities/GenerateDateAndTime.hpp"

DateGenerator::Date::Date(const std::string& date)
	: date(date)
{}

const DateGenerator::Date& DateGenerator::ReturnCurrentTimeAndDate(){
	time_t now = time(0);
	tm currenttime;
	char date_and_time[40];

	localtime_s(&currenttime, &now);
	strftime(date_and_time, sizeof(date_and_time), "%Y-%m-%d %X", &currenttime);

	return Date(date_and_time);
}
