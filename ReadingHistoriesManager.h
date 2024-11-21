#pragma once
#include "ReadingHistory.h"
#include <vector>

class ReadingHistoriesManager {
private:
	std::vector<ReadingHistory*> readingHistories;
	const std::string directoryPath = "Users/ReadingHistories/";
	std::string fileName;
	std::string fullPath;

	static ReadingHistoriesManager* readingHistoriesManager;
	ReadingHistoriesManager();

public:
	void LoadDatabase();
	void UpdateDatabase() const;
	void FillReadingCustomerHistories(Customer* customer);
	void AddReadingHistoryToDatabase(ReadingHistory* readingHistory, int userID);
	static ReadingHistoriesManager* GetInstance();
	void AddBookToReadingHistory(Book* book);
	void ClearDatabase() const;
	~ReadingHistoriesManager();
};