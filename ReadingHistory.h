#pragma once
#include <string>
#include "Book.h"
#include "DateTime.h"

class Customer;

//ID same as customer ID
class ReadingHistory {
private:
	int currentPage;
	int numberOfPages;
	Book* book;
	//Customer* customer;
	std::string lastSession;
	std::string bookName;
	int customerID;
	int bookID;

public:
	ReadingHistory();
	void DisplayLastReadingHistory() const;
	bool InitializeWithLine(std::string const& line);
	std::string ToString() const;
	void DisplayProgress() const;
	void PrintReadingHistory() const;

	//Getters & Setters
	int GetCustomerID();

	int GetNumberOfPages() const;
	void SetNumberOfPages(int numberOfPage);

	int GetCurrentPage() const;
	void SetCurrentPage(int currentPage);

	const std::string& GetLastSession() const;
	void SetLastSession(std::string const& lastSession);

	int GetID() const;
	void SetCustomerID(int ID);
	void SetBookName(std::string const& bookName);

	int GetBookID() const;
	Book* GetBook() const;
	void SetBook(Book* book	);
};

