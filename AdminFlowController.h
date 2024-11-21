#pragma once
#include "Admin.h"

class AdminFlowController {
private:
	Admin admin;
	enum class AdminMenuOptions { ViewPrfile = 1, AddBook, Logout, BlockCustomer, UnBlockCustomer };

public:
	void ShowMainMenu();
	void TakeControl();
	bool isAdmin(std::string const& username, std::string const& password) const;
	void ViewProfile() const;
};