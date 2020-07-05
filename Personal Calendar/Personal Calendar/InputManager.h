#pragma once
#include "ClassManager.h"
/// <summary>
/// Class that handles user input and executes commands. 
/// </summary>
class InputManager {
private:
	///Additional classes that.
	ClassManager additionalClasses;

	///String which holds the input line.
	char* input;
	size_t inputLen;
	/// Executes command
	bool executeCommand(char** separatedCommands, const unsigned short commandCount);

	/// Returns the count of the commands given by the user.
	unsigned short getCommandWordCount(const char* input);

	/// Separates the single command line from the user into two dimensional array containing each individual command. 
	void separateWords(char** separatedCommands, const unsigned short wordCount);

	/// Concatenates string from the separated commands (usually used for names, notes, additional information..).
	void catStr(unsigned int from, unsigned int to, char** separatedCommands, char*&cpyTo);

public:
	InputManager();
	~InputManager();

	/// Receives input line from user, splits it into two dimensional array containing the separate commands and calls execution.
	bool recieveCommand(const char* userInput);
};