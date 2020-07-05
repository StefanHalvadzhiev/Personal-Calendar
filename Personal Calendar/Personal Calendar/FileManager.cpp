#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "InputManager.h"
#include <stdio.h>
#include<conio.h>
using namespace std;

FileManager::FileManager() {
	isSaved = false;
	isOpen = false;
	name = new char[100];
}

FileManager::~FileManager() {
	delete[] name;
}

void FileManager::createFile(char* fileName) {
	char* bufferName = new char[strlen(fileName) + 5];
	strcpy(bufferName, fileName);
	checkFileName(bufferName);
	ofstream newFile;
	newFile.open(bufferName);
	if (newFile.fail()) {
		cout << "Error creating file." << endl;
		return;
	}
	newFile.close();
	cout << "Successfully created new file." << endl;
	delete[] bufferName;
}

void FileManager::openFile(char* fileName) {
	if (isOpen) {
		cout << "Another file already opened." << endl;
		return;
	}
	checkFileName(fileName);
	name = strcpy(name, fileName);
	writeFile.open(fileName, ios_base::app);
	readFile.open(fileName);
	if (writeFile.fail() || readFile.fail()) {
		cout << "Error opening file!" << endl;
		closeFile();
		isOpen = false;
		return;
	}
	cout << "Opened " << fileName << endl;
	isOpen = true;
}

void FileManager::closeFile() {
	writeFile.close();
	readFile.close();
	isOpen = false;
	cout << "Closed " << name << endl;
}

void FileManager::checkFileName(char* fileName) {
	if (!strstr(fileName, ".txt"))
		strcat(fileName, ".txt");
}

void FileManager::deleteFile(char* fileName) {
	char* bufferName = new char[strlen(fileName) + 5];
	strcpy(bufferName, fileName);
	checkFileName(bufferName);
	if (remove(bufferName))
		cout << "Error deleting file.." << endl;
	else
		cout << "File deleted successfully!" << endl;
	delete[] bufferName;
}

void FileManager::writeToFile(const char* textToBeWritten) {
	writeFile << textToBeWritten << endl;
}

bool FileManager::checkIfOpen() {
	if (isOpen)
		return true;
	return false;
}

void FileManager::getLines(char** parameterArr, unsigned short lineSize) {
	unsigned short counter = 0;
	char buffer[400];
	readFile.clear();
	readFile.seekg(0, ios::beg);
	while (!readFile.eof()) {
		readFile.getline(buffer, 400);
		if (strcmp(buffer, "") != 0) {
			strcpy(parameterArr[counter], buffer);
			counter++;
		}
	}
}

unsigned short FileManager::getLineCount() {
	unsigned short count = 0;
	char* line = new char[250];
	while (!readFile.eof()) {
		readFile.getline(line, 250);
		if (strcmp(line, "") != 0)
			count++;
	}
	delete[] line;
	return count;
}

void FileManager::emptyFile() {
	writeFile.close();
	writeFile.open(name, std::ofstream::trunc);
}