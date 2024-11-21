#pragma once
#include <string>
#include <vector>
#include "Admin.h"
#include "Book.h"

class ReadingHistory;

class Customer {
private:
	std::string name;
	std::string username;
	std::string password;
	std::string email;
	std::vector<ReadingHistory*> readingHistories;
	int ID;

public:
	friend class Admin;
	bool isAuthData(std::string const& username, std::string const& password) const;
	bool InitializeWithLine(std::string const& line);
	std::string ToString() const;
	void ReadCustomer();
	void AddReadingHistory(ReadingHistory* readingHistory);
	void DisplayReadingHistories();
	void Print() const;
	void ClearReadingHistoriesBooks();

	//Constructors
	Customer();
	Customer(const Customer& customer);

	//Getters & setters
	std::vector<ReadingHistory*> GetReadingHistories();

	const std::string& GetName() const;
	void SetName(std::string const& name);

	const std::string& GetUsername() const;
	void SetUsername(std::string const& username);

	const std::string& GetPassword() const;
	void SetPassword(std::string const& password);

	const std::string& GetEmail() const;
	void SetEmail(std::string const& email);
	void SetReadingHistoryBook(Book* book);

	int GetID() const;
	void SetID(int ID);

	//Destructor
	~Customer();
};