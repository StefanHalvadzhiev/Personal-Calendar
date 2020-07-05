#include "Date.h"
#include <cstring>
#include <iostream>
#include "BasicTime.h"
using namespace std;

CalendarDate::CalendarDate() {
	create();
}

void CalendarDate::create() {
	name = nullptr;
	note = nullptr;
	translation = nullptr;
}

CalendarDate::CalendarDate(const CalendarDate& copyDate) {
	copy(copyDate);
}

CalendarDate::CalendarDate(const char* date, const char* startTime, const char* endTime, const char* name, const char* note) {
	Year yearBuff(date);
	Hours startTimeBuff(startTime);
	Hours endTimeBuff(endTime);
	this->date = yearBuff;
	this->startTime = startTime;
	this->endTime = endTime;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	if (note != nullptr) {
		this->note = new char[strlen(note) + 1];
		strcpy(this->note, note);
	}
	else
		this->note = nullptr;
	this->translation = nullptr;;
	
}

void CalendarDate::copy(const CalendarDate& copyDate){
	clear();
	create();

	date = copyDate.date;
	startTime = copyDate.startTime;
	endTime = copyDate.endTime;

	name = new char[strlen(copyDate.name) + 1];
	strcpy(name, copyDate.name);

	if (copyDate.note != nullptr) {
		note = new char[strlen(copyDate.note) + 1];
		strcpy(note, copyDate.note);
	}
	else
		note = nullptr;
	if (copyDate.translation != nullptr) {
		translation = new char[strlen(copyDate.translation) + 1];
		strcpy(translation, copyDate.translation);
	}
	if (translation != nullptr)
		delete[] translation;
	if (copyDate.translation != nullptr) {
		translation = new char[strlen(copyDate.translation) + 1];
		strcpy(translation, copyDate.translation);
	}
	else
		translation = nullptr;
}

void CalendarDate::clear() {
	if (name != nullptr)
		delete[] name;

	if (translation != nullptr) 
		delete[] translation;
	
	if (note != nullptr)
		delete[] note;
}

CalendarDate::~CalendarDate() {
	clear();
}

CalendarDate& CalendarDate::operator=(const CalendarDate& copyDate) {
	if (this != &copyDate) {
		copy(copyDate);
	}
	return *this;
}

char* CalendarDate::getDate(){
	return date.translateToChar();
}

char* CalendarDate::getStartTime() {
	return startTime.getHr();
}

char* CalendarDate::getEndTime() {
	return endTime.getHr();
}

char* CalendarDate::getName() {
	return name;
}

char* CalendarDate::getNote() {
	return note;
}

bool CalendarDate::operator< (const CalendarDate& rhs) {
	if (*this == rhs)
		return false;
	if (date > rhs.date)
		return false;
	if (date == rhs.date) {
		if (startTime > rhs.startTime) {
			return false;
		}
	}
	return true;
}

bool CalendarDate::operator== (const CalendarDate& rhs) {
	if (date == rhs.date && startTime == rhs.startTime && endTime == rhs.endTime)
		return true;
	return false;
}

bool CalendarDate::operator> (const CalendarDate& rhs) {
	if (*this == rhs)
		return false;
	return !(*this < rhs);
}

bool CalendarDate::operator<= (const CalendarDate& rhs) {
	if (*this == rhs)
		return true;
	return (*this < rhs);
}

bool CalendarDate::operator >= (const CalendarDate& rhs) {
	if (*this == rhs)
		return true;
	return (*this > rhs);
}

bool CalendarDate::operator != (const CalendarDate& rhs) {
	return !(*this == rhs);
}

bool CalendarDate::checkIntersection(const CalendarDate& toCheck) {
	if (date != toCheck.date)
		return false;
	if (startTime > toCheck.startTime && startTime < toCheck.endTime)
		return true;
	if (endTime > toCheck.startTime && endTime < toCheck.endTime)
		return true;
	if (startTime > toCheck.startTime && endTime < toCheck.endTime)
		return true;
	return false;
}

char* CalendarDate::translate() {
	unsigned int translationSize = 8;
	translationSize += strlen(date.translateToChar());
	translationSize += strlen(startTime.getHr());
	translationSize += strlen(endTime.getHr());
	translationSize += strlen(name);
	if (note != nullptr) {
		translationSize += strlen(note);
	}
	if (translation != nullptr)
		delete[] translation;
	translation = new char[translationSize];
	strcpy(translation, "<");
	strcat(translation, date.translateToChar());
	strcat(translation, " ");
	strcat(translation, startTime.getHr());
	strcat(translation, " ");
	strcat(translation, endTime.getHr());
	strcat(translation, " ");
	strcat(translation, name);
	if (note != nullptr) {
		strcat(translation, " ");
		strcat(translation, note);
		strcat(translation, ">");
	}
	return translation;
}