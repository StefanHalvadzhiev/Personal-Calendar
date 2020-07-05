#include "ClassManager.h"
#include <cstring>
#include <iostream>
using namespace std;

void ClassManager::sortedPush(CalendarDate& dateToBePushed) {
	unsigned int size = dates.getSize();
	if (checkIntersection(dateToBePushed)) 
		return;
	
	for (unsigned int i = 0; i < size; i++) {
		if (dateToBePushed < dates[i]) {
			dates.pushAt(i, dateToBePushed);
			return;
		}
	}
	dates.push(dateToBePushed);
}

void ClassManager::book(char* date, char* startTime, char* endTime, char* name, char* note){
	if (!calendarFile.checkIfOpen()) {
		cout << "No file opened. Please open a file!" << endl;
		return;
	}
	Hours start(startTime);
	Hours end(endTime);
	if (start < end) {
		if (note != nullptr) {
			CalendarDate newDate(date, startTime, endTime, name, note);
			cout << newDate.translate() << endl;
			sortedPush(newDate);
		}
		else {
			CalendarDate newDate(date, startTime, endTime, name, nullptr);
			sortedPush(newDate);
		}
	}
	else
		cout << "Incorrect time. Please try again" << endl;
}

void ClassManager::unBook(char* date, char* startTime, char* endTime) {
	char filler[8] = "nothing";
	filler[7] = '\0';
	CalendarDate checkDate(date, startTime, endTime, filler, nullptr);
	unsigned int size = dates.getSize();
	for (unsigned int i = 0; i < size; i++) {
		if (checkDate == dates[i]) {
			dates.erase(i);
			return;
		}
	}
	cout << "Date not found." << endl;
}

void ClassManager::agenda(char* date){
	bool checker = false;
	unsigned int size = dates.getSize();
	for (unsigned int i = 0; i < size; i++) {
		if (strcmp(date, dates[i].getDate()) == 0) {
			cout << "-----------" << endl;
			printDate(i);
			checker = true;
		}
	}
	if (!checker)
		cout << "The date is empty." << endl;
	else
		cout << "-----------" << endl;

}

void ClassManager::change(char* date, char* startTime, char* option, char* newValue) {
	unsigned int size = dates.getSize();
	unsigned int datePos;
	bool found = false;
	for (unsigned int i = 0; i < size; i++) {
		if (strcmp(dates[i].getDate(), date) == 0 && strcmp(dates[i].getStartTime(), startTime) == 0) {
			datePos = i;
			found = true;
			break;
		}
	}

	if (found) {
		CalendarDate copy = dates[datePos];
		dates.erase(datePos);
		if (strcmp(option, "date") == 0) {
			CalendarDate toBePushed(newValue, copy.getStartTime(), copy.getEndTime(), copy.getName(), copy.getNote());
			if (!checkIntersection(toBePushed)) {
				sortedPush(toBePushed);
				return;
			}
		}

		if (strcmp(option, "starttime") == 0) {
			Hours checker;
			if (!checker.check(newValue)) {
				cout << "Invalid time" << endl;
			}
			else {
				CalendarDate toBePushed(copy.getDate(), newValue, copy.getEndTime(), copy.getName(), copy.getNote());
				if (!checkIntersection(toBePushed)) {
					sortedPush(toBePushed);
						return;
				}
			}
		}

		if (strcmp(option, "endtime") == 0) {
			Hours checker;
			if (!checker.check(newValue)) {
				cout << "Invalid time" << endl;
			}
			else {
				CalendarDate toBePushed(copy.getDate(), copy.getStartTime(), newValue, copy.getName(), copy.getNote());
				if (!checkIntersection(toBePushed)) {
					sortedPush(toBePushed);
					return;
				}
			}
		}

		if (strcmp(option, "name") == 0) {
			CalendarDate toBePushed(copy.getDate(), copy.getStartTime(), copy.getEndTime(), newValue, copy.getNote());
			if (!checkIntersection(toBePushed)) {
				sortedPush(toBePushed);
				return;
			}
		}

		if (strcmp(option, "note") == 0) {
			CalendarDate toBePushed(copy.getDate(), copy.getStartTime(), copy.getEndTime(), copy.getName(), newValue);
			if (!checkIntersection(toBePushed)) {
				sortedPush(toBePushed);
				return;
			}
		}
		sortedPush(copy);
	}
	else
		cout << "Date not found" << endl;
	
	
}

void ClassManager::find( char* textToFind) {
	cout << endl;
	bool found = false;
	unsigned int size = dates.getSize();
	char* checker;
	for (unsigned int i = 0; i < size; i++) {
		checker = strstr(textToFind, dates[i].getName());
		if (checker != nullptr) {
			found = true;
			printDate(i);
			break;
		}
		checker = strstr(textToFind, dates[i].getNote());
		if (checker != nullptr) {
			found = true;
			printDate(i);
			cout << "-----------" << endl;
		}
	}
	if (!found)
		cout << "String not found." << endl;
}
void ClassManager::holiday() {
}
void ClassManager::busyDays() {
}
void ClassManager::findSlot() {
}
void ClassManager::findSlotWith() {
}
void ClassManager::merge() {
}

void ClassManager::printDate(unsigned int position) {
	if (position > dates.getSize()) {
		cout << "There is no date at position: " << position << endl;;
		return;
	}
	cout << "Date: " << dates[position].getDate() << endl;
	cout << "Start time: " << dates[position].getStartTime() << endl;
	cout << "End time: " << dates[position].getEndTime() << endl;
	cout << "Name: " << dates[position].getName() << endl;
	if (dates[position].getNote() != nullptr)
		cout << "Note: " << dates[position].getNote() << endl;
	else
		cout << "No note added." << endl;
}

void ClassManager::print() {
	unsigned int size = dates.getSize();
	cout << "Total dates: " << size << endl;
	for (unsigned short i = 0; i < size; i++) {
		cout << "-----------" << endl;
		printDate(i);
	}
	cout << "-----------" << endl;
}

bool ClassManager::checkIntersection(const CalendarDate& toCheck) {
	unsigned int size = dates.getSize();
	for (unsigned int i = 0; i < size; i++) {
		if (dates[i] == toCheck) {
			cout << "You have entered equal dates." << endl;
			return true;
		}
		if (dates[i].checkIntersection(toCheck)) {
			cout << "Intersection of hours within the same day occured." << endl;
			return true;
		}
	}
	return false;
}

void ClassManager::interpretAsObjectFromFile(const char* objectLine, unsigned int lineLen) {
	char date[20];
	char starttime[6];
	char endtime[6];
	char name[100];
	char note[832] = { "null" };
	unsigned int lenBuffer = 0;
	unsigned int wordBuff = 0;

	for (unsigned int i = 1; i < lineLen; i++) {
		if (objectLine[i] != ' ') {
			lenBuffer++;
			date[i-1] = objectLine[i];
		}
		else {
			date[lenBuffer] = '\0';
			lenBuffer+=2;
			break;
		}
	}

	for (unsigned int i = lenBuffer; i < lineLen; i++) {
		if (objectLine[i] != ' ') {
			lenBuffer++;
			starttime[wordBuff] = objectLine[i];
			wordBuff++;
		}
		else {
			starttime[wordBuff] = '\0';
			lenBuffer++;
			break;
		}
	}
	
	wordBuff = 0;
	for (unsigned int i = lenBuffer; i < lineLen; i++) {
		if (objectLine[i] != ' ') {
			lenBuffer++;
			endtime[wordBuff] = objectLine[i];
			wordBuff++;
		}
		else {
			endtime[wordBuff] = '\0';
			lenBuffer++;
			break;
		}
	}

	wordBuff = 0;
	for (unsigned int i = lenBuffer; i < lineLen; i++) {
		if (objectLine[i] != ' ') {
			lenBuffer++;
			name[wordBuff] = objectLine[i];
			wordBuff++;
		}
		else {
			name[wordBuff] = '\0';
			lenBuffer++;
			break;
		}
	}

	wordBuff = 0;
	for (unsigned int i = lenBuffer; i < lineLen - 2; i++) {
		note[wordBuff] = objectLine[i];
		wordBuff++;
	}
	note[wordBuff] = '\0';

	if (strcmp(note, "null") == 0)
		book(date, starttime, endtime, name, nullptr);
	else
		book(date, starttime, endtime, name, note);	
}

void ClassManager::loadFromFile() {
	unsigned short lineCount = calendarFile.getLineCount();
	char** parametersFromFile = new char* [lineCount];
	for (unsigned short i = 0; i < lineCount; i++)
		parametersFromFile[i] = new char[250];
	calendarFile.getLines(parametersFromFile, 1000);
	for (unsigned short i = 0; i < lineCount; i++)
		interpretAsObjectFromFile(parametersFromFile[i], strlen(parametersFromFile[i]) + 1);

	cout << "Content loaded" << endl;
	for (unsigned short i = 0; i < lineCount; i++)
		delete[] parametersFromFile[i];
	delete[] parametersFromFile;
}

void ClassManager::save() {
	unsigned int size = dates.getSize();
	if (!calendarFile.checkIfOpen()) {
		cout << "No file opened" << endl;
		return;
	}
	calendarFile.emptyFile();
	for (unsigned int i = 0; i < size; i++)
		calendarFile.writeToFile(dates[i].translate());

	cout << "Contents saved." << endl;
}

void ClassManager::createFile(char* fileName) {
	calendarFile.createFile(fileName);
}

void ClassManager::open(char* fileName) {
	if (calendarFile.checkIfOpen()) {
		cout << "Another file already opened." << endl;
		return;
	}
	cout << "Opening file" << endl;
	calendarFile.openFile(fileName);
	loadFromFile();
}

void ClassManager::close() {
	calendarFile.closeFile();
	dates.clear();
	dates.create();
}

void ClassManager::deleteFile(char* fileName) {
	calendarFile.deleteFile(fileName);
}

void ClassManager::empty() {
	dates.clear();
}

