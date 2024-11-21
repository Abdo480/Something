#pragma once
#include <string>

class BooksManager;
class CustomersManager;
class Admin {
private:
	std::string name;
	std::string username;
	std::string password;
	std::string email;
	int ID;
	static BooksManager* booksManager;
	static CustomersManager* customersManager;

public:
	Admin();
	bool isAuthData(std::string const& username, std::string const& password) const;
	void AddBook();
	bool BlockCustomer() const;
	bool UnBlockCustomer();

	//Getters & setters
	const std::string& GetName() const;
	void SetName(std::string const& name);

	const std::string& GetUsername() const;
	void SetUsername(std::string const& username);

	const std::string& GetPassword() const;
	void SetPassword(std::string const& password);

	const std::string& GetEmail() const;
	void SetEmail(std::string const& email);

	int GetID() const;
	void SetID(int ID);
};