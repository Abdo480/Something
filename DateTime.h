#pragma once
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

class DateTime {
private:
	int month;
	int day;
	int year;
	int hour;
	int minute;
	int second;

public:
	DateTime();
	std::string ToString() const;
	void SetTime(std::time_t& time);
	void print() const;
};