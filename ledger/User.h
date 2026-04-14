#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class User {
private:
    string username;
    string password;

public:
    // Constructor
    User(string uname, string pwd) {
        username = uname;
        password = pwd;
    }

    // Destructor
    ~User() {}

    // Check if username already exists
    bool userExists(string uname) {
        ifstream file("users.txt");
        string line;

        while (getline(file, line)) {
            string savedUser = line.substr(0, line.find(","));
            if (savedUser == uname) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    // Save new user to file
    bool createAccount() {
        if (userExists(username)) {
            return false; // User already exists
        }

        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << username << "," << password << "\n";
            file.close();
            return true;
        }
        return false;
    }

    // Check login credentials
    bool login() {
        ifstream file("users.txt");
        string line;

        while (getline(file, line)) {
            string savedUser = line.substr(0, line.find(","));
            string savedPass = line.substr(line.find(",") + 1);

            if (savedUser == username && savedPass == password) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    string getUsername() {
        return username;
    }
};

#endif
