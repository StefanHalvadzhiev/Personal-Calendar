#include "BasicTime.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;

bool Hours::operator== (const Hours& rhs) {
	if (strcmp(hour, rhs.hour) == 0)
		return true;
	return false;
}

Hours& Hours::operator= (const char* cpyStr) {
	if (check(cpyStr)) {
		strcpy(hour, cpyStr);
		return *this;
	}
	throw;
}

bool Hours::operator<(const Hours& rhs) {
	//hrs
	char lhsHr[3];
	lhsHr[0] = hour[0];
	lhsHr[1] = hour[1];
	lhsHr[2] = '\0';
	char rhsHr[3];
	rhsHr[0] = rhs.hour[0];
	rhsHr[1] = rhs.hour[1];
	rhsHr[2] = '\0';
	// mins
	char lhsMin[3];
	lhsMin[0] = hour[3];
	lhsMin[1] = hour[4];
	lhsMin[2] = '\0';
	char rhsMin[3];
	rhsMin[0] = rhs.hour[3];
	rhsMin[1] = rhs.hour[4];
	rhsMin[2] = '\0';

	if (atoi(lhsHr) > atoi(rhsHr))
		return false;

	if (atoi(lhsHr) == atoi(rhsHr)) {
		if (atoi(lhsMin) == atoi(rhsMin)) 
			return false;
		
		if (atoi(lhsMin) > atoi(rhsMin))
			return false;

		return true;
	}
	return true;
}

bool Hours::operator!= (const Hours& rhs) {
	return !(*this == rhs);
}

bool Hours::operator >= (const Hours& rhs) {
	if (*this == rhs)
		return true;
	return (*this > rhs);
}

bool Hours::operator <= (const Hours& rhs) {
	if (*this == rhs)
		return true;
	return (*this < rhs);
}

bool Hours::operator> (const Hours& rhs) {
	if (*this == rhs)
		return false;
	return !(*this < rhs);
}

Hours::Hours() {
	create();
}

Hours::Hours(const Hours& cpyHr) {
	copy(cpyHr);
}

Hours& Hours::operator= (const Hours& cpyHr) {
	if (this != &cpyHr) {
		copy(cpyHr);
	}
	return *this;
}

void Hours::copy(const Hours& cpyHr) {
	clear();
	create();
	strcpy(hour, cpyHr.hour);
}

Hours::Hours(const char* hour) {
	this->hour = new char[6];
	if (check(hour)) {
		strcpy(this->hour, hour);
	}
	else {
		cout << "Invalid hour format. Adding default time 00:00" << endl;
		strcpy(this->hour, "00:00");
	}
}

char* Hours::getHr() {
	return hour;
}

Hours::~Hours() {
	clear();
}

void Hours::clear() {
	delete[] hour;
}

void Hours::create() {
	hour = new char[6];
}

bool Hours::check(const char* timeToBeChecked) {
	if (strlen(timeToBeChecked) > 5) // checks length
		return false;
	
	char hrBuff[3];
	hrBuff[0] = timeToBeChecked[0];
	hrBuff[1] = timeToBeChecked[1];
	hrBuff[2] = '\0';
	if (atoi(hrBuff) > 24 || atoi(hrBuff) < 0) // checks hour
		return false;

	char minBuff[3];
	minBuff[0] = timeToBeChecked[3];
	minBuff[1] = timeToBeChecked[4];
	minBuff[2] = '\0';

	if (atoi(minBuff) > 59 || atoi(minBuff) < 0) // checks mins
		return false;

	if (timeToBeChecked[2] != ':') // checks double dots
		return false;
	return true;
}

//-----------------------------------//

Year::Year() {
	year = 0;
	month = 1;
	day = 1;
}

Year::~Year() {
	if (translation != nullptr)
		delete[] translation;
}

bool Year::check(const int nyear, const unsigned int nmonth, const unsigned int nday) {
	if (nmonth > 12 || nday == 0 || nmonth == 0)
		return false;
	if (nday > dayCnt[nmonth - 2] && nmonth > 2)
		return false;
	if (nmonth == 2) {
		if (isLeap(year)) {
			if (nday > 29)
				return false;
			else
				return true;
		}
		else {
			if (nday > 28)
				return false;
			return true;
		}
	}
	if (nmonth == 1 && day > dayCnt[0])
		return false;
	return true;
}

bool Year::isLeap(int year) {
	if (year % 4 == 0) {
		if (year % 100 == 0) {
			if (year % 400 == 0)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}

Year::Year(const int nyear, const unsigned int nmonth, const unsigned int nday) {
	if (check(nyear, nmonth, nday)) {
		year = nyear;
		month = nmonth;
		day = nday;
	}
	else {
		useDefault();
	}
}

void Year::copy(const Year& cpy) {
	year = cpy.year;
	month = cpy.month;
	day = cpy.day;
}

Year::Year(const Year& cpyYear) {
	copy(cpyYear);
}

Year& Year::operator= (const Year& cpyYear) {
	if (this != &cpyYear) {
		copy(cpyYear);
	}
	return *this;
}

bool Year::operator<(const Year& rhs) {
	if (*this == rhs)
		return false;
	if (rhs.year > year)
		return true;
	if (rhs.year == year) {
		if (rhs.month > month)
			return true;
		if (rhs.month == month) {
			if (rhs.day > day)
				return true;
		}
	}
	return false;
}

bool Year::operator> (const Year& rhs) {
	if (*this == rhs)
		return false;
	return !(*this < rhs);
}

bool Year::operator== (const Year& rhs) {
	if (year == rhs.year && month == rhs.month && day == rhs.day)
		return true;
	return false;
}

bool Year::operator!= (const Year& rhs) {
	return !(*this == rhs);
}

bool Year::operator>=(const Year& rhs) {
	if (*this == rhs)
		return true;
	return (*this > rhs);
}

bool Year::operator<= (const Year& rhs) {
	if (*this == rhs)
		return true;
	return (*this < rhs);
}

Year::Year(const char* nYear) {
	unsigned int length = strlen(nYear);
	if (length <= 6) {
		useDefault();
		return;
	}
	else {
		char d[3] = { nYear[0], nYear[1], '\0' };
		char m[3] = { nYear[3], nYear[4], '\0' };
		if (nYear[2] != '.' && nYear[5] != '.') {
			useDefault();
			return;
		}
		unsigned int yearLen = length - 6;
		char y[10];
		for (unsigned int i = 0; i < yearLen; i++) {
			y[i] = nYear[6 + i];
		}
		y[yearLen + 1] = '\0';

		if (check(atoi(y), atoi(m), atoi(d)) == false) {
			cout << atoi(y) << endl;
			cout << atoi(m) << endl;
			cout << atoi(d) << endl;
			useDefault();
			return;
		}
		this->year = atoi(y);
		this->month = atoi(m);
		this->day = atoi(d);
	}
}

void Year::useDefault(){
	cout << "Incorrect date. Using default date" << endl;
	year = 1;
	month = 1;
	day = 1;
}

char* Year::translateToChar() {
	if (translation != nullptr)
		delete[] translation;
	translation = new char[17];
	char buffer[10];
	if (day < 10) {
		strcpy(translation, "0");
		strcat(translation, itoa(day, buffer, 10));
	}
	else
		strcpy(translation, itoa(day, buffer, 10));
	strcat(translation, ".");
	if(month < 10)
		strcat(translation, "0");
	strcat(translation, itoa(month, buffer, 10));
	strcat(translation, ".");
	strcat(translation, itoa(year, buffer, 10));
	return translation;
}