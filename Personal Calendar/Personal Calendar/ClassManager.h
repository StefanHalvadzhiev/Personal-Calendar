#pragma once
#include "Date.h"
#include "Vector.h"
#include "FileManager.h"

/// <summary>
/// Class manager that handles proper calendar execution - booking, unbooking, changing of information in dates etc.
/// </summary>

class ClassManager {
	private:
		/// Here are handled file operations
		FileManager calendarFile;

		/// Vector which stores infromation about dates
		VectorArray<CalendarDate> dates;

		/// Booking a new date chronologically
		void sortedPush(CalendarDate& dateToBePushed);

		/// Checks wheter 
		bool checkIntersection(const CalendarDate& toCheck);

		/// Loading dates from a given file.
		void loadFromFile();

		/// Interprets a string from the file as an object. Used to book new dates from a file.
		void interpretAsObjectFromFile(const char* objectLine, unsigned int lineLen);

	public:
		/// Empties the dates
		void empty();

		/// Books a new date with the given parameters.
		void book(char* date, char* startTime, char* endTime, char* name, char* note);

		/// Removes a date with the given parameters if possible.
		void unBook(char* date, char* startTime, char* endTime);

		/// Prints all duties chronologically for a given day
		void agenda(char* date);

		/// Changes information about given date. Option refers to date / start time / end time / name or note. 
		void change(char* date, char* startTime, char* option, char* newValue);

		/// Prints all dates that contain a given string in their name or note. 
		void find(char* textToFind);

		void holiday();
		void busyDays();
		void findSlot();
		void findSlotWith();
		void merge();

		/// Prints all dates chronologically.
		void print();

		/// Prints information about a date on a given position in the vector.
		void printDate(unsigned int position);

		/// Creates a new calendar file
		void createFile(char* fileName);

		/// Opens a calendar file
		void open(char* fileName);

		/// Saves the infromation from the date vector into the opened file.
		void save();

		/// Closes the opened file
		void close();

		/// Deletes a file with given name
		void deleteFile(char* fileName);

};