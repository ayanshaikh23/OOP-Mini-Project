#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class Dashboard {
private:
    string username;
    double totalBalance;
    double totalDebited;
    double totalCredited;
    int totalEntries;

public:
    // Constructor
    Dashboard(string uname) {
        username = uname;
        totalBalance  = 0.0;
        totalDebited  = 0.0;
        totalCredited = 0.0;
        totalEntries  = 0;
    }

    // Destructor
    ~Dashboard() {}

    // Load and calculate all data from file
    void loadDashboardData() {
        totalBalance  = 0.0;
        totalDebited  = 0.0;
        totalCredited = 0.0;
        totalEntries  = 0;

        ifstream file(username + "_transactions.txt");
        string line;

        while (getline(file, line)) {
            if (line.empty()) continue;

            string temp = line;
            string type   = temp.substr(0, temp.find(",")); temp = temp.substr(temp.find(",") + 1);
            string item   = temp.substr(0, temp.find(",")); temp = temp.substr(temp.find(",") + 1);
            double amount = stod(temp.substr(0, temp.find(",")));

            if (type == "credit") {
                totalCredited += amount;
                totalBalance  += amount;
            } else if (type == "debit") {
                totalDebited += amount;
                totalBalance -= amount;
            }

            totalEntries++;
        }
        file.close();
    }

    // Get greeting based on time
    string getGreeting() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int hour = ltm->tm_hour;

        if (hour < 12) return "Good Morning";
        else if (hour < 17) return "Good Afternoon";
        else return "Good Evening";
    }

    // Display dashboard
    void displayDashboard(string companyName) {
        loadDashboardData();

        cout << "\n====================================\n";
        cout << getGreeting() << ", " << username << "!\n";
        cout << "====================================\n";
        cout << "         " << companyName << "\n";
        cout << "====================================\n";
        cout << "Total Balance  : Rs. " << totalBalance  << "\n";
        cout << "Total Credited : Rs. " << totalCredited << "\n";
        cout << "Total Debited  : Rs. " << totalDebited  << "\n";
        cout << "Total Entries  :     " << totalEntries  << "\n";
        cout << "====================================\n";
    }

    // Getters for Node.js API
    double getBalance()          { return totalBalance;  }
    double getCredited()         { return totalCredited; }
    double getDebited()          { return totalDebited;  }
    int    getEntries()          { return totalEntries;  }
    string getGreetingPublic()   { return getGreeting(); }
    string getUsername()         { return username;      }
};

#endif
