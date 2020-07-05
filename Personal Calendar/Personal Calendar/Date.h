#pragma once
#include "BasicTime.h"

/// <summary>
/// This class containts all the information about a personal date
/// </summary>

class CalendarDate {
	private: 
		Year date;
		Hours startTime;
		Hours endTime;
		char* name;
		char* note;

		///String which is defined filled and passed when a translation for a calendar file is needed. 
		char* translation = nullptr;

		/// Copy function.
		void copy(const CalendarDate& copyDate);

		/// Clears name, note and translation.
		void clear();

		/// Creates defaults values for name, note and translation.
		void create();

	public:
		CalendarDate();
		CalendarDate(const char *date, const char* startTime, const char* endTime,const  char* name, const char* note);
		~CalendarDate();
		CalendarDate(const CalendarDate& copyDate);
		CalendarDate& operator=(const CalendarDate& copyDate);

		/// Returns a string containing the year date.
		char* getDate();

		/// Returns a string containing the start time of a personal date.
		char* getStartTime();

		/// Returns a string containing the end time of a personal date.
		char* getEndTime();

		/// Returns a string containing the name of a personal date.
		char* getName();

		/// Returns a string containing the note of a personal date. Nullptr is returned if the note of a personal date is not added.
		char* getNote();

		///@see all of the operators below are used for comaprison of personal dates (comparing their years and hours). 
		bool operator< (const CalendarDate& rhs);
		bool operator> (const CalendarDate& rhs);
		bool operator<= (const CalendarDate& rhs);
		bool operator>= (const CalendarDate& rhs);
		bool operator== (const CalendarDate& rhs);
		bool operator!= (const CalendarDate& rhs);

		///Checks whether hour intersection occurs between the current date and another one.
		bool checkIntersection(const CalendarDate& toCheck);

		///Translates all the information about the object into a string that is used to store the information in a file.
		char* translate();
};
