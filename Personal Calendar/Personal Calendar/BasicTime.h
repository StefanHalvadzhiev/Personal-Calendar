#pragma once

/// <summary>
/// This class can hold clock time hours ranging from 00:00 to 23:59.
/// Proper way to use the class - 08:05 not 8:5.
/// </summary>

class Hours {
	private:
		char* hour;
		void clear();
		void create();
		void copy(const Hours& cpyHr);
	public:
		Hours();

		///Constructor that gets a string as a parameter
		Hours(const char* hour);
		~Hours();

		Hours(const Hours& cpyHr);

		Hours& operator= (const Hours& cpyHr);
		Hours& operator= (const char* cpyStr);
		/// @note All of the operators below are used for hour comparison. To examplify: 08:30 < 10:00 ; 08:30 >= 08:30
		bool operator<  (const Hours& rhs);
		bool operator>  (const Hours& rhs);
		bool operator<= (const Hours& rhs);
		bool operator>= (const Hours& rhs);
		bool operator== (const Hours& rhs); 
		bool operator!= (const Hours& rhs);
		/// Checks if a given time is correct
		bool check(const char* timeToBeChecked);

		/// Returns hour 
		char* getHr();
};

/// <summary>
/// This class can hold days.
/// Proper way to use the class - 01.12.2020, 18.04.2021 etc.
/// </summary>
class Year {
	private:
		int year;
		unsigned int month;
		unsigned int day;

		/// String containing the date information that is being returned with a speicific function.
		char* translation = nullptr;

		/// This array contains the count of days from january to december excluding february.
		const unsigned int dayCnt[11] = { 31, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		void copy(const Year& year);

		///Checks whether a given year is a leap year or not.
		bool isLeap(int year);

		///Adds default date when needed.
		void useDefault();
	public:

		Year();
		~Year();

		///Constructor that takes string as a parameter and interprets it as a year.
		Year(const char* nYear);
		Year(const int nyear, const unsigned int nmonth, const unsigned int nday);
		Year(const Year& cpyYear);

		///@note All of the operators below are for comparison. To exemplify: 01.03.2020 < 03.03.2020, 01.01.2020 <= 01.01.2020 etc.
		Year& operator= (const Year& cpyYear);
		bool operator<  (const Year& rhs);
		bool operator>  (const Year& rhs);
		bool operator<= (const Year& rhs);
		bool operator>= (const Year& rhs);
		bool operator== (const Year& rhs);
		bool operator!= (const Year& rhs);
		/// Checks whether a given date is correct. To exemplify 29.02.1900 / 33.14.2020 / 17.22.2929 are not a correct dates.
		bool check(const int year, const unsigned int month, const unsigned int day);

		/// Returns a string containing the date.
		char* translateToChar();
};