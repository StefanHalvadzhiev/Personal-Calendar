#pragma once
#include <fstream>
using namespace std;
/// <summary>
/// Simple file managing system.
/// </summary>

class FileManager {
private:
	bool isOpen;
	bool isSaved;
	///The name of the opened file.
	char* name;

	/// Write to file.
	ofstream writeFile;

	/// Read from file.
	ifstream readFile;

	/// Checks if a string has a proper extension. If it doesn't the function concatenates a proper extension. 
	void checkFileName(char* fileName);

public:
	/// Returns the count of lines in a file.
	unsigned short getLineCount();

	/// Checks whether a file is open.
	bool checkIfOpen();

	FileManager();
	~FileManager();

	/// Empties the contents of a file.
	void emptyFile();

	///	Creates file.
	void createFile(char* fileName);

	/// Open file.
	void openFile(char* fileName);

	/// Deletes file.
	void deleteFile(char* fileName);

	/// Closes the current file.
	void closeFile();

	/// Writes string to a file.
	void writeToFile(const char* textToBeWritten);

	/// Reads all lines from a file.
	void getLines(char** parameterArr, unsigned short lineSize);
}; 
#pragma once
