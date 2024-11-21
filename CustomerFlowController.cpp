#include "CustomerFlowController.h"
#include <iostream>
#include "Helper.h"
#include <string>
#include "BookContent.h"
#include "MyExceptions.h"

bool CustomerFlowController::isValidCustomer(std::string const& username, std::string const& password) const {
	customersManager->LoadDatabse();
	return customersManager->GetCustomer(username, password);
}

BooksManager* CustomerFlowController::booksManager = BooksManager::GetInstance();
CustomersManager* CustomerFlowController::customersManager = CustomersManager::GetInstance();


CustomerFlowController::~CustomerFlowController() {
	delete customerFlowController;
}

CustomerFlowController::CustomerFlowController() : currentCustomer(nullptr){}

CustomerFlowController* CustomerFlowController::customerFlowController = nullptr;

Customer* CustomerFlowController::GetCurrentCustomer() const {
	return currentCustomer;
}

CustomerFlowController* CustomerFlowController::GetInstance() {
	if (customerFlowController == nullptr)
		customerFlowController = new CustomerFlowController();
	return customerFlowController;
}

bool CustomerFlowController::SignUp() {
	int tries = 0;

	currentCustomer = new Customer();
	std::string username, password, data;
	std::cout << "\nEnter The Following Info:\n";

	do {
		++tries;
		if (tries > 3) {
			std::cout << "\nYou exceeded the maximum number of tries.\n";
			return false;
		}

		
		std::cout << "\tUsername (No Spaces): ";
		std::cin >> username;
		while (customersManager->isUsernameUsed(username)) {
			std::cout << "\nUsername is used, try again.\n";
			std::cout << "\tEnter Username (No Spaces): ";
			std::cin >> username;
		}

		currentCustomer->SetUsername(username);

		std::cout << "\tPassword (No Spaces): ";
		std::cin >> password;
		currentCustomer->SetPassword(password);

		if (isValidCustomer(username, password)) {
			std::cout << "\nInvalid username or password, try again\n";
		}

	} while (isValidCustomer(username, password));

	std::cout << "\tName: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, data);
	currentCustomer->SetName(data);
	
	std::cout << "\tEmail: ";
	std::cin >> data;
	currentCustomer->SetEmail(data);

	while (!Helper::isValidEmail(data)) {
		std::cout << "\nInvalid Email, try again.\n";
		std::cout << "\tEnter Email: ";
		std::cin >> data;
	}

	currentCustomer->SetID(++customersManager->lastID);
	customersManager->AddCustomerToDatabase(*currentCustomer);
	ShowMainMenu();
	return true;
}

void CustomerFlowController::TakeControl(std::string const& username, std::string const& password) {
	currentCustomer = customersManager->GetCustomer(username, password);
	std::cout << "******* Welcome to the system " << currentCustomer->GetName() << " *******\n\n";

	ShowMainMenu();
}

void CustomerFlowController::ShowMainMenu() {
	int choice = 0;
	while (choice != static_cast<int>(CustomerMenuOptions::Logout)){
			std::cout << "\x1b[2J\x1b[H";
			choice = Helper::ReadMenuOption({ "View Profile", "List & Select From My Reading History", "List & Select From Available Books", "Logout"});
		if (choice == static_cast<int>(CustomerMenuOptions::ViewProfile)) {
			std::cout << "\x1b[2J\x1b[H";
			ViewProfile();
		}
		else if (choice == static_cast<int>(CustomerMenuOptions::ListSelectFromReadingHistory)) {
			std::cout << "\x1b[2J\x1b[H";
			ListSelectFromReadingHistory();
		}
		else if (choice == static_cast<int>(CustomerMenuOptions::ListSelectFromAvailableBooks)) {
			std::cout << "\x1b[2J\x1b[H";
			ListSelectFromAvailableBooks();
		}
	}
}

void CustomerFlowController::ViewProfile() const {
	std::cout << "\n\n";
	std::cout << "_______________________________________\n";
	std::cout << "Name: " << currentCustomer->GetName();
	std::cout << "\nEmail: " << currentCustomer->GetEmail();
	std::cout << "\nUser name: " << currentCustomer->GetUsername();
	std::cout << "_______________________________________\n";
	std::cout << "Press any key to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

void CustomerFlowController::ListSelectFromReadingHistory()  {
	std::vector<ReadingHistory*> readingHistories = currentCustomer->GetReadingHistories();

	if (readingHistories.size() == 0) {
		std::cout << "\nNo reading histories yet.\n";
		std::cout << "\nPress any key to continue...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
		return;
	}

	currentCustomer->DisplayReadingHistories();
	std::cout << "\nWhich Session to open?:\n";
	int readingHistoryIndex = Helper::ReadNumberInRange(1, (int)readingHistories.size());
	//readingHistories[--readingHistoryIndex]->DisplayProgress();
	Book* book = readingHistories[--readingHistoryIndex]->GetBook();

	BookContent* bookContent;
	try {
		bookContent = book->GetBookContent();
	}
	catch (DanglingException& e) {
		std::cout << "\nNot a valid object: " << e.GetMessage() << "\n";
		std::cout << "Value = " << e.what();
		std::cout << "\nMake sure to assign a content to the book object\n";
		return;
	}
	
	bookContent->ReadBook(currentCustomer, book);
}

void CustomerFlowController::ListSelectFromAvailableBooks() {
	booksManager->LoadDatabse();
	booksManager->ListSelectFromAvailableBooks(currentCustomer);
}