#include "InputManager.h"
#include <iostream>
#include <cstring>
using namespace std;

InputManager::InputManager() {
	input = new char[1000];
	inputLen = 0;
}

InputManager::~InputManager() {
	delete[] input;
}

bool InputManager::recieveCommand(const char* userInput) {
	strcpy(input, userInput);
	inputLen = strlen(input);
	unsigned short commandWordCount = getCommandWordCount(input);
	if (!commandWordCount) {
		std::cout << "No command given!" << std::endl;
		return true;
	}
	char** separatedWords = new char* [commandWordCount];
	for (unsigned short i = 0; i < commandWordCount; i++)
		separatedWords[i] = new char[100];
	if (separatedWords == nullptr) {
		std::cout << "Error allocating memory, terminating program.." << std::endl;
		return false;
	}
	separateWords(separatedWords, commandWordCount);

	bool returnStatus = executeCommand(separatedWords, commandWordCount);

	for (unsigned short i = 0; i < commandWordCount; i++)
		delete[] separatedWords[i];
	delete[] separatedWords;

	return returnStatus;
}

void InputManager::separateWords(char** separatedCommands, const unsigned short wordCount) {
	char buffer[100];
	unsigned short bufferPosition = 0;
	unsigned short wordCounter = 0;
	for (unsigned short z = 0; z < inputLen; z++) {
		if (input[z] == ' ') {
			buffer[bufferPosition] = '\0';
			strcpy(separatedCommands[wordCounter], buffer);
			bufferPosition = 0;
			wordCounter++;
			continue;
		}
		buffer[bufferPosition] = input[z];
		bufferPosition++;
	}
	buffer[bufferPosition] = '\0';
	strcpy(separatedCommands[wordCount - 1], buffer);
}

unsigned short InputManager::getCommandWordCount(const char* input) {
	unsigned short spacesCount = 0;
	for (unsigned short i = 0; i < inputLen; i++)
		if (input[i] == ' ')
			spacesCount++;
	if (inputLen == 0)
		return 0;
	if (spacesCount == 0)
		return 1;
	return spacesCount + 1;
}

bool InputManager::executeCommand(char** separatedCommands, const unsigned short commandCount) {
	if (!strcmp(separatedCommands[0], "exit")) {
		std::cout << "Terminating.." << std::endl;
		return false;
	}
	else if (!strcmp(separatedCommands[0], "book")) {
		if (commandCount > 5) {
			char* note;
			catStr(5, commandCount - 1, separatedCommands, note);
			additionalClasses.book(separatedCommands[1], separatedCommands[2], separatedCommands[3], separatedCommands[4], note);
			delete[] note;
		}
		else if (commandCount == 5)
			additionalClasses.book(separatedCommands[1], separatedCommands[2], separatedCommands[3], separatedCommands[4], nullptr);
		else
			cout << "Invalid input" << endl;
		return true;
	}
	else if (!strcmp(separatedCommands[0], "unbook")) {
		if (commandCount < 4) {
			cout << "Passed unsufficient parameters." << endl;
				return true;
		}
		additionalClasses.unBook(separatedCommands[1], separatedCommands[2], separatedCommands[3]);
		return true;
	}
	else if (!strcmp(separatedCommands[0], "agenda")) {
		if (commandCount < 2) {
			cout << "Passed unsufficient parameters." << endl;
			return true;
		}
		additionalClasses.agenda(separatedCommands[1]);
		return true;
	}
	else if (!strcmp(separatedCommands[0], "change")) {
		if (commandCount < 4) {
			cout << "Insufficient parameters" << endl;
			return true;
		}
		if (commandCount == 4) {
			additionalClasses.change(separatedCommands[1], separatedCommands[2], separatedCommands[3], nullptr);
			return true;
		}
			
		char* value;
		catStr(4, commandCount - 1, separatedCommands, value);
		additionalClasses.change(separatedCommands[1], separatedCommands[2], separatedCommands[3], value);
		return true;
	}
	else if (!strcmp(separatedCommands[0], "find")) {
		if (commandCount > 1) {
			char* textToFind;
			catStr(1, commandCount - 1, separatedCommands, textToFind);
			additionalClasses.find(textToFind);
			delete[] textToFind;
		}
		else
			cout << "No text has been added." << endl;
		return true;
	}
	else if (!strcmp(separatedCommands[0], "holiday")) {
		additionalClasses.holiday();
		return true;
	}
	else if (!strcmp(separatedCommands[0], "busydays")) {
		additionalClasses.busyDays();
		return true;
	}
	else if (!strcmp(separatedCommands[0], "findslot")) {
		additionalClasses.findSlot();
		return true;
	}
	else if (!strcmp(separatedCommands[0], "findslotwith")) {
		additionalClasses.findSlotWith();
		return true;
	}
	else if (!strcmp(separatedCommands[0], "merge")) {
		additionalClasses.merge();
		return true;
	}
	else if (!strcmp(separatedCommands[0], "print")) {
		additionalClasses.print();
		return true;
	}
	else if (!strcmp(separatedCommands[0], "createfile")) {
		if (commandCount == 1) {
			cout << "No file name written." << endl;
			return true;
		}
		additionalClasses.createFile(separatedCommands[1]);
		return true;
	}
	else if (!strcmp(separatedCommands[0], "open")) {
		if (commandCount == 1) {
			cout << "No file name written." << endl;
			return true;
		}
		additionalClasses.open(separatedCommands[1]);
		return true;
	}
	else if (!strcmp(separatedCommands[0], "save")) {
		additionalClasses.save();
		return true;
	}
	else if (!strcmp(separatedCommands[0], "close")) {
		additionalClasses.close();
		return true;
	}
	else if (!strcmp(separatedCommands[0], "delete")) {
		if (commandCount == 1) {
			cout << "No file name written." << endl;
			return true;
		}
		additionalClasses.deleteFile(separatedCommands[1]);
			return true;
	}
	else if (!strcmp(separatedCommands[0], "help")) {
		cout << "Welcome to your personal calendar! :)" << endl << endl;
		cout << "Here is how to use it:" << endl;
		cout << "1. To operate with files use: open, close, createfile, save, delete" << endl;
		cout << "2. Functions related to personal calendar: " << endl;
		cout << "2.1 Use print to print all current dates." << endl;
		cout << "2.2 Use book to create a new date." << endl;
		cout << "2.3 Use unbook to unbook a date." << endl;
		cout << "2.3 Use find to find whether a string occurs in a date's name or note." << endl;
		cout << "2.3 Use agenda to print all active dates for a given day." << endl;
		cout << "2.3 Use change to change any information about a given date (yaer date, start time, end time, name or note)." << endl;
		cout << "3. Use exit to terminate the program" << endl << endl;
		cout << "NOTE: to operatre with dates you must first open a file." << endl;
		cout << "Correct time format: 08:30, 12:02 etc." << endl;
		cout << "Correct year format: 02.12:2020, 15.05.2020" << endl;
		return true;
	}
	else {
		std::cout << "Error: Given invalid first command. Please try again!" << std::endl;
		return true;
	}
}

void InputManager::catStr(unsigned int from, unsigned int to, char** separatedCommands, char* &cpyTo) {
	unsigned int length = to - from;
	for (unsigned int i = from; i <= to; i++) 
		length += strlen(separatedCommands[i]);
	cpyTo = new char[length + 1];
	strcpy(cpyTo, separatedCommands[from]);
	if (from != to) {
		for (unsigned int i = from + 1; i <= to; i++) {
			strcat(cpyTo, " ");
			strcat(cpyTo, separatedCommands[i]);
		}
	}
}
