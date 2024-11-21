#pragma once
#include <string>
#include <sstream>
#include <ctime>
#include "DateTime.h"

class BookContent;

class Book {
private:
	std::string name;
	std::string authorName;
	int ID;
	BookContent* bookContent;
	DateTime publishedDateTime;
	void Read();

public:
	friend class Admin;
	friend class BooksManager;
	bool InitializeWithLine(std::string const& line);
	std::string ToString();
	//Constructors
	Book();

	//Setters & getters
	const std::string& GetName() const;
	void SetName(std::string const& name);

	const std::string& GetAuthorName() const;
	void SetAuthorName(std::string const& authorName);

	int GetID() const;
	void SetID(int ID);

	BookContent* GetBookContent();
	void SetBookContent(BookContent* bookContent);
	~Book();
};
