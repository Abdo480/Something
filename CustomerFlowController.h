#pragma once
#include <string>
#include "Customer.h"
#include "CustomersManager.h"
#include "BooksManager.h"

class CustomerFlowController {
private:
	Customer* currentCustomer;
	static CustomersManager* customersManager;
	static BooksManager* booksManager;
	CustomerFlowController();
	static CustomerFlowController* customerFlowController;

	enum class CustomerMenuOptions{
		ViewProfile = 1, ListSelectFromReadingHistory, ListSelectFromAvailableBooks, Logout
	};

public:
	bool isValidCustomer(std::string const& username, std::string const& password) const;
	void TakeControl(std::string const& username, std::string const& password);
	void ShowMainMenu();
	bool SignUp();
	void ViewProfile() const;
	void ListSelectFromReadingHistory();
	void ListSelectFromAvailableBooks();
	Customer* GetCurrentCustomer() const;
	static CustomerFlowController* GetInstance();
	~CustomerFlowController();
};