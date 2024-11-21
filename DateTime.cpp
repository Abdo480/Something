#include "DateTime.h"
#include <sstream>
#pragma warning(disable : 4996)

DateTime::DateTime() : month(-1), day(-1), year(-1), hour(-1), minute(-1), second(-1) {}

std::string DateTime::ToString() const {
	std::ostringstream oss;
	oss << month << year << "-" << month << "-" << day << " " << hour << ":" << minute << ":" << second;
	return oss.str();
}

void DateTime::SetTime(std::time_t& time) {
	std::tm* localTime = std::localtime(&time);

	year = localTime->tm_year + 1900;  // tm_year is years since 1900
	month = localTime->tm_mon + 1;     // tm_mon is 0-11
	day = localTime->tm_mday;
	hour = localTime->tm_hour;
	minute = localTime->tm_min;
	second = localTime->tm_sec;
}

void DateTime::print() const {
	std::cout << year << "-" << month << "-" << day << "-" << hour << "-" << minute << second << "\n";
}