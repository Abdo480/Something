#include "AdminFlowController.h"
#include "Helper.h"
#include <iostream>

void AdminFlowController::TakeControl() {
	std::cout << "\n\n -- Welcome to the system, Sir." << admin.GetName() << " --\n";	
	ShowMainMenu();
}

bool AdminFlowController::isAdmin(std::string const& username, std::string const& password) const {
	return (admin.GetUsername() == username && admin.GetPassword() == password);
}

void AdminFlowController::ShowMainMenu() {
	int choice = 0;
	do {
		 choice = Helper::ReadMenuOption({ "View Profile", "Add Book", "Logout", "Block Customer", "Unblock Customer"});
		 if (choice == static_cast<int>(AdminMenuOptions::ViewPrfile)) {
			 std::cout << "\x1b[2J\x1b[H";
			 ViewProfile();
		 }
		 else if (choice == static_cast<int>(AdminMenuOptions::AddBook)) {
			 std::cout << "\x1b[2J\x1b[H";
			 admin.AddBook();
		 }
		 else if (choice == static_cast<int>(AdminMenuOptions::BlockCustomer)) {
			 std::cout << "\x1b[2J\x1b[H";
			 admin.BlockCustomer();
		 }
		 else if (choice == static_cast<int>(AdminMenuOptions::UnBlockCustomer)) {
			 std::cout << "\x1b[2J\x1b[H";
			 admin.UnBlockCustomer();
		 }

	} while (choice != static_cast<int>(AdminMenuOptions::Logout));
}

void AdminFlowController::ViewProfile() const {
	std::cout << "\n\n";
	std::cout << "_______________________________________\n";
	std::cout << "Name: " << admin.GetName();
	std::cout << "\nEmail: " << admin.GetEmail();
	std::cout << "\nUser name: " << admin.GetUsername();
	std::cout << "_______________________________________\n";
	std::cout << "Press any key to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}