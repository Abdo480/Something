#include "BooksManager.h"
#include "Helper.h"
#include "BookContent.h"
#include "MyExceptions.h"
#include "ReadingHistoriesManager.h"
#include "CustomerFlowController.h"

BooksManager::BooksManager() : lastID(0) {}

BooksManager* BooksManager::booksManager = nullptr;

BooksManager::~BooksManager() {
	for (const auto& book : books) {
		delete book;
	}

	delete booksManager;
}

BooksManager* BooksManager::GetInstance() {
	if (booksManager == nullptr)
		booksManager = new BooksManager();
	return booksManager;
}

void BooksManager::FillReadingHistoriesBooks(std::vector<ReadingHistory*> readingHistories) {
	for (auto& readingHistory : readingHistories) {
		for (const auto& book : books) {
			if (book->GetID() == readingHistory->GetBookID()) {
				readingHistory->SetBook(book);
				break;
			}
		}
	}
}

void BooksManager::ListSelectFromAvailableBooks(Customer* customer) {
	if (books.size() == 0) {
		std::cout << "No books at the moment, try again later.\n";
		return;
	}

	std::cout << "\nOur Current Book Collection:\n";
	for (int i = 0; i < books.size(); ++i) {
		std::cout << "\t" << i + 1 << ": " << books[i]->GetName() << "\n";
	}

	int bookIndex;
	std::cout << "\nWhich book to read.\n";
	bookIndex =  Helper::ReadNumberInRange(1, (int)books.size());
	Book* book = books[--bookIndex];
	
	try {
		book->bookContent->SetBook(book);

	} catch (DanglingException& e) {
		std::cout << "\nNot a valid object: " << e.GetMessage() << "\n";
		std::cout << "Value = " << e.what();
		return;
	}

	book->bookContent->ReadBook(customer, book);
}

void BooksManager::FillReadingHistoriesBooks(std::vector<ReadingHistory*> readingHistories) {
	for (auto& readingHistory : readingHistories) {
		for (auto& book : books) {
			if (readingHistory->GetBookID() == book->GetID()) {
				readingHistory->SetBook(book);
			}
		}
	}
}

Book* BooksManager::GetBookBy(int bookID) {
	LoadDatabse();

	for (const auto& book : books) {
		if (book->ID == bookID) {
			return book;
		}
	}

	return nullptr;
}

void BooksManager::AddBookID(Book& book) {	book.SetID(++lastID); }

void BooksManager::AddBookToDatabse(Book& book) {
	books.push_back(&book);
	Helper::WriteLinesToFile(std::vector<std::string>(1, book.ToString()), fileName);
}

void BooksManager::SetBookID(Book& book) {
	book.ID = ++lastID;
}

void BooksManager::SetReadingHistoryBookBy(ReadingHistory* readingHistory) {
	LoadDatabse();

	for (const auto book : books) {
		if (book->GetID() == readingHistory->GetBookID())
			readingHistory->SetBook(book);
	}
}

bool BooksManager::LoadDatabse() {
	std::vector<std::string> data;
	Helper::ReadFromFile(fileName, data);
	if (books.size() != 0) {
		for (auto& book : books) {
			if (book != nullptr) {
				delete book;
			}
		}

		//Reading Histories Manager Books would be invalid, hence, should reassign them
		ReadingHistoriesManager::GetInstance()->ClearDatabase();
		books.clear();
	}

	if (data.size() == 0)
		return false;

	for (auto const& line : data) {
		Book* book = new Book();
		BookContent* bookContent = new BookContent();
		book->SetBookContent(bookContent);
		if (book->InitializeWithLine(line)) {
			books.push_back(book);
			ReadingHistoriesManager::GetInstance()->AddBookToReadingHistory(book);

			lastID = std::max(lastID, book->GetID());
		}
		else {
			delete book;
		}
	}

	
	return true;
}

bool BooksManager::UpdateDatabase() const {
	std::vector<std::string> data;
	for (const auto& book : books)
		data.push_back(book->ToString());

	if (data.size() == 0) {
		std::cout << "No books in the system yet\n";
		return false;
	}

	Helper::WriteLinesToFile(data, fileName, false);
	return true;
}