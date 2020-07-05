#include <iostream>
#include <string>
#include "InputManager.h"
#include "Vector.h"
#include "BasicTime.h"

/*! \mainpage Personal Calendar
 *
 * This project helps poeple to manage their daily duties. <br>
 * Currently the system can book, unbook, change, find and print information about personal dates. <br>
 *
 * <br> Made by Stefan Halvadzhiev, Informatics, FN: 45678, 4th group.
 */

int main() {
	std::cout << "Use \"help\" to list all functions." << std::endl ;
	InputManager userInput;
	char* command = new char[1000];
	bool running = true;
	while (running) {
		std::cin.getline(command, 1000);
		running = userInput.recieveCommand(command);
		std::cout << std::endl;
	}
	delete[] command;
	return 0;
}