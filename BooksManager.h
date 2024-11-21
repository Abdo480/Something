#pragma once
#include "Book.h"
#include <vector>
#include "ReadingHistory.h"

class BooksManager {
private:
	std::vector<Book*> books;
	const std::string fileName = "Books/books.txt";
	static BooksManager* booksManager;
	int lastID;
	BooksManager();
public:
	bool LoadDatabse();
	bool UpdateDatabase() const;
	void AddBookID(Book& book);
	void AddBookToDatabse(Book& book);
	Book* GetBookBy(int bookID);
	void FillReadingHistoriesBooks(std::vector<ReadingHistory*> readingHistories);

	static BooksManager* GetInstance();
	void SetBookID(Book& book);
	void SetReadingHistoryBookBy(ReadingHistory* readingHistory);
	void FillReadingHistoriesBooks(std::vector<ReadingHistory*> readingHistories);
	void ListSelectFromAvailableBooks(Customer* customer);
	void SetCurrentCustomer(Customer* customer);

	~BooksManager();
};