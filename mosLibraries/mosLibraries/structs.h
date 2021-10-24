#pragma once
#ifndef H_STRUCTS
#define H_STRUCTS

#include <string>
#include <map>
#include <vector>

typedef struct SEV {
	int Year;
	int Month;
	int Day;

	friend bool operator< (const SEV& lDate, const SEV& rDate) {
		bool is_lessYear = lDate.Year < rDate.Year;
		bool is_lessMonth = lDate.Month < rDate.Month;
		bool is_lessDay = lDate.Day < rDate.Day;
		bool is_equal = lDate.Year == rDate.Year && lDate.Month == rDate.Month && lDate.Day == rDate.Day;
		return is_lessYear || is_lessMonth || is_lessDay;
	}
	friend bool operator<= (const SEV& lDate, const SEV& rDate) {
		bool is_lessYear = lDate.Year < rDate.Year;
		bool is_lessMonth = lDate.Month < rDate.Month;
		bool is_lessDay = lDate.Day < rDate.Day;
		bool is_equal = lDate.Year == rDate.Year && lDate.Month == rDate.Month && lDate.Day == rDate.Day;
		return is_lessYear || is_lessMonth || is_lessDay || is_equal;
	}
	friend bool operator> (const SEV& lDate, const SEV& rDate) {
		return !(lDate <= rDate);
	}
	friend bool operator>= (const SEV& lDate, const SEV& rDate) {
		return !(lDate < rDate);
	}
} Date;

class Book{
public:
	unsigned int id;
	std::string title;
	std::string author;
	unsigned int author_id;
} ;

class BookDetail : public Book {
	std::string position;
public:
	int pages;
	Date dateCreate;
	int rubric_id;
	int language_id;
	int publisher_id;
	std::string annotation; 
	std::string keyword;
};

class User{
	unsigned int id;
	std::map<Date, BookDetail> history;
	std::map<int, int> booksBYlibrary;
	std::map<int, int> libraryBYbooks;
	std::map<int, BookDetail> recommendations;
	std::map<Date, BookDetail> favourites;
	void changeRecommendations();
public:
	void setRecommendations();
	std::map<int, BookDetail> getRecommendations(const int numbRecommends);
};
#endif