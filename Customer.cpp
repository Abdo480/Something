#include "Customer.h"
#include "Helper.h"
#include <sstream>
#include "ReadingHistory.h"
#include <iostream>
#include <cassert>
#include "MyExceptions.h"
#include "ReadingHistoriesManager.h"
#include "BooksManager.h"

Customer::Customer() : ID(-1) {}

Customer::Customer(const Customer& customer)
	: name(customer.GetName()),
	  username(customer.GetUsername()),
	  password(customer.GetPassword()),
      email(customer.GetEmail()),
	  ID(customer.GetID()) {

	for (auto* histy : customer.readingHistories) {
		if (histy)
			readingHistories.push_back(new ReadingHistory(*histy));
	}
}

void Customer::Print() const {
	std::cout << "-------------- " << ID << " ----------------\n";
	std::cout << "\nName: " << name;
	std::cout << "\nEmail: " << email;
	std::cout << "\n";
}

void Customer::DisplayReadingHistories() {
	int idx = 0;
	BooksManager::GetInstance()->FillReadingHistoriesBooks(readingHistories);
	for (const auto& readingHistory : readingHistories) {
		std::cout << ++idx << ": ";
		BooksManager::GetInstance()->SetReadingHistoryBookBy(readingHistory);
		readingHistory->PrintReadingHistory();
	}
}

std::vector<ReadingHistory*> Customer::GetReadingHistories() { return readingHistories; }

void Customer::AddReadingHistory(ReadingHistory* readingHistory) {
	if (readingHistory == nullptr)
		throw DanglingException("NullPointerException", NULL);

	for (int pos = 0; pos < readingHistories.size(); ++pos) {
		if (readingHistories[pos]->GetBookID() == readingHistory->GetBookID()) {
			delete readingHistories[pos];
			readingHistories.erase(readingHistories.begin() + pos);
			readingHistories.push_back(readingHistory);
			return;
		}
	}
	

	readingHistories.push_back(readingHistory);
}

void Customer::ReadCustomer() {
	std::cout << "\nEnter The Following info:\n";
	std::cout << "\tName: ";
	do {
		std::getline(std::cin, name);
	} while (name.empty());

	std::cout << "username (NO SPACES): ";
	std::cin >> username;

	std::cout << "password: ";
	std::cin >> password;
	
	bool emailNotValid = true;
	while (emailNotValid) {
		std::cout << "Email (NO SPACES): ";
		std::cin >> email;
		if (Helper::isValidEmail(email))
			emailNotValid = false;
		else
			std::cout << "Invalid email address, try again\n";
	}
}

bool Customer::isAuthData(std::string const& username, std::string const& password) const {
	if (username == GetUsername() && password == GetPassword())
		return true;
	return false;
}

/*
* 	std::string name;
	std::string username;
	std::string password;
	std::string email;
	int ID;
	std::vector<ReadingHistory*> readingsHistory;
*/

void Customer::ClearReadingHistoriesBooks() {
	for (const auto& readingHistory : readingHistories) {
		readingHistory->SetBook(nullptr);
	}
}

bool Customer::InitializeWithLine(std::string const& line) {
	std::vector<std::string> substrs = Helper::SplitString(line);
	if (substrs.size() != 5) {
		std::cout << "\nFile format is wrong\n";
		return false;
	}

	name = substrs[0];
	username = substrs[1];
	password = substrs[2];
	email = substrs[3];
	ID = Helper::ToInt(substrs[4]);
	return true;
}

/*
	std::string lastReadingSession;
	int lastOpenedPage;
	int numberOfPages;
	Book* book;
	Customer* customer;
	DateTime lastSession;
*/

std::string Customer::ToString() const{
	std::ostringstream oss;
	oss << name << "," << username << "," << password << "," << email << "," << ID;
	return oss.str();
}

void Customer::SetReadingHistoryBook(Book* book) {
	for (const auto& readingHistory : readingHistories)
		if (readingHistory->GetBookID() == book->GetID())
			readingHistory->SetBook(book);
}

const std::string& Customer::GetName() const{ return name; };
void Customer::SetName(std::string const& name) { this->name = name; }

const std::string& Customer::GetUsername() const { return username; };
void Customer::SetUsername(std::string const& username) { this->username = username; }

const std::string& Customer::GetPassword() const { return password; }
void Customer::SetPassword(std::string const& password) { this->password = password; }

const std::string& Customer::GetEmail() const { return email; }

void Customer::SetEmail(std::string const& email) { this->email = email; }

int Customer::GetID() const { return ID; }
void Customer::SetID(int ID) { this->ID = ID; }

Customer::~Customer() {
	for (auto const& history : readingHistories)
		if (history)
			delete history;
}