#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Transaction {
private:
    string username;
    string itemName;
    double amount;
    string paymentMethod; // "cash" or "bank transfer"
    string description;
    string date;
    string type; // "credit" or "debit"

public:
    // Constructor
    Transaction(string uname, string item, double amt,
                string method, string desc, string txnType) {
        username = uname;
        itemName = item;
        amount = amt;
        paymentMethod = method;
        description = desc;
        type = txnType;
        date = getAutoDate();
    }

    // Destructor
    ~Transaction() {}

    // Auto generate current date
    string getAutoDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        string day   = to_string(ltm->tm_mday);
        string month = to_string(1 + ltm->tm_mon);
        string year  = to_string(1900 + ltm->tm_year);

        return day + "/" + month + "/" + year;
    }

    // Save transaction to file
    bool saveTransaction() {
        ofstream file(username + "_transactions.txt", ios::app);
        if (file.is_open()) {
            file << type << ","
                 << itemName << ","
                 << amount << ","
                 << paymentMethod << ","
                 << description << ","
                 << date << "\n";
            file.close();
            return true;
        }
        return false;
    }

    // Display transaction details
    void displayTransaction() {
        cout << "\n--- Transaction Recorded ---\n";
        cout << "Date        : " << date << "\n";
        cout << "Item        : " << itemName << "\n";
        cout << "Amount      : Rs. " << amount << "\n";
        cout << "Type        : " << type << "\n";
        cout << "Payment Via : " << paymentMethod << "\n";
        cout << "Description : " << (description.empty() ? "N/A" : description) << "\n";
        cout << "----------------------------\n";
    }

    // View all transactions for a user
    static void viewAllTransactions(string username) {
        ifstream file(username + "_transactions.txt");
        string line;
        int count = 1;

        cout << "\n========== ALL TRANSACTIONS ==========\n";
        if (!file.is_open()) {
            cout << "No transactions found.\n";
            return;
        }

        while (getline(file, line)) {
            if (line.empty()) continue;

            string temp = line;
            string type    = temp.substr(0, temp.find(",")); temp = temp.substr(temp.find(",") + 1);
            string item    = temp.substr(0, temp.find(",")); temp = temp.substr(temp.find(",") + 1);
            string amount  = temp.substr(0, temp.find(",")); temp = temp.substr(temp.find(",") + 1);
            string method  = temp.substr(0, temp.find(",")); temp = temp.substr(temp.find(",") + 1);
            string desc    = temp.substr(0, temp.find(",")); temp = temp.substr(temp.find(",") + 1);
            string date    = temp;

            cout << count++ << ". [" << date << "] "
                 << item << " | Rs." << amount
                 << " | " << type
                 << " | " << method
                 << " | " << (desc.empty() ? "N/A" : desc) << "\n";
        }
        cout << "======================================\n";
        file.close();
    }
};

#endif
