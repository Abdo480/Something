#include "CustomersManager.h"
#include "Helper.h"
#include <iostream>
#include "Admin.h"
#include <unordered_set>
#include "ReadingHistoriesManager.h"

bool CustomersManager::LoadDatabse() {
    blockedUsernames.clear();
    std::vector<std::string> data;
    Helper::ReadFromFile(fileName, data);
    Helper::ReadFromFile(blockedUsersFileNames, blockedUsernames);
    
    if (data.size() == 0) {
        return false;
    }

    if (customers.size() != 0) {
        for (const auto& customer : customers)
            delete customer;
        customers.clear();
    }

    for (auto const& line : data) {
        Customer* customer = new Customer();
        customer->InitializeWithLine(line);
        ReadingHistoriesManager::GetInstance()->FillReadingCustomerHistories(customer);
        lastID = std::max(lastID, customer->GetID());
        customers.push_back(customer);
    }
    return true;
}

CustomersManager* CustomersManager::customersManager = nullptr;

CustomersManager::CustomersManager() : lastID(0) {};

CustomersManager::CustomersManager(const CustomersManager& customersManager) {
    for (auto& customer : customersManager.customers) {
        if (customer)
            customers.push_back(new Customer(*customer));
    }
}

CustomersManager* CustomersManager::GetInstance() {
    if (customersManager == nullptr)
        customersManager = new CustomersManager();

    return customersManager;
}

void CustomersManager::ListCustomers() const {
    for (auto const& customer : customers)
        customer->Print();
}

//Returns false if the list is empty, and true otherwise
bool CustomersManager::ListBlockedCustomers() const {
    if (blockedUsernames.size() == 0)
        return false;

    int index = 0;
    std::cout << "\nUsernames of blocked users:\n";
    for (const auto& customer : blockedUsernames)
        std::cout << "\t" << ++index << ": " << customer << "\n";

    std::cout << "\n";
    return true;
}

std::vector<std::string> CustomersManager::GetUnblockedCustomers() {
    LoadDatabse();
    int idx = 0;
    std::vector<std::string> usernames;

    if (blockedUsernames.size() == 0) {
        for (const auto& customer : customers)
            usernames.push_back(customer->GetUsername());
    
        return usernames;
    }

    std::unordered_set<std::string> blockedSet(blockedUsernames.begin(), blockedUsernames.end());
    for (const auto& customer : customers)
        if (blockedSet.find(customer->GetUsername()) == blockedSet.end())
            usernames.push_back(customer->GetUsername());

    return usernames;
}

bool CustomersManager::RemoveCustomerFromBlackList(std::string const& username) {
    for (int i = 0; i < blockedUsernames.size(); ++i) {
        if (blockedUsernames[i] == username) {
            blockedUsernames.erase(blockedUsernames.begin() + i);
            UpdateDatabse();
            return true;
        }
    }
    return false;
}

void CustomersManager::UnBlockCustomerBy(int index) {
    std::string username = customers[index]->GetUsername();
    RemoveCustomerFromBlackList(blockedUsernames[index]);
    std::cout << "\nCustomer " << "\"" << username << "\"" << " Was Unblocked successfully.\n";
}

void CustomersManager::AddCustomerToBlackList(const std::string& username) {
    blockedUsernames.push_back(username);
    Helper::WriteLinesToFile(std::vector<std::string>(1, username), blockedUsersFileNames);
}

void CustomersManager::BlockCustomerBy(int index) {
    std::string username = customers[index]->GetUsername();
    AddCustomerToBlackList(username);
    std::cout << "\nCustomer " << "\"" << username << "\"" << " Was blocked successfully.\n";
}

void CustomersManager::AddCustomerToDatabase(Customer& customer) {
    customers.push_back(&customer);
    Helper::WriteLinesToFile(std::vector<std::string>(1, customer.ToString()), fileName);
}

bool CustomersManager::isUsernameUsed(const std::string& username) const {
    for (const auto& customer : customers)
        if (customer->GetUsername() == username)
            return true;

    return false;
}

bool CustomersManager::isBlockedCustomer(std::string const& username) {
    for (const auto& user : blockedUsernames)
        if (user == username)
            return true;

    return false;
}

bool CustomersManager::UpdateDatabse() const {
    std::vector<std::string> data;
    for (auto const& customer : customers)
        data.push_back(customer->ToString());

    if (data.size() == 0) {
        std::cout << "No customers available at the moment\n";
        return false;
    }

    Helper::WriteLinesToFile(data, fileName, false);
    Helper::WriteLinesToFile(blockedUsernames, blockedUsersFileNames, false);
    return true;
}

Customer* CustomersManager::GetCustomer(std::string const& username, std::string const& password) {
    for (auto const& customer : customers)
        if (customer->GetUsername() == username && customer->GetPassword() == password)
            return customer;
    return nullptr;
}

size_t CustomersManager::GetCustomersSize() const {
    return customers.size();
}

CustomersManager::~CustomersManager() {
    for (auto const& customer : customers)
        if (customer)
            delete customer;
}