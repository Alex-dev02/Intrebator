#include "../../include/Entities/GenerateDateAndTime.hpp"

const std::string ReturnCurrentTimeAndDate(){
	time_t now = time(0);
	struct tm tstruct;
	char date_and_time[80];
	tstruct = *localtime(&now);
	strftime(date_and_time, sizeof(date_and_time), "%Y-%m-%d %X", &tstruct);
	return date_and_time;
}