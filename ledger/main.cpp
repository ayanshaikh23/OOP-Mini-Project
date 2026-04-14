#include <iostream>
#include <string>
#include <limits>
#include "User.h"
#include "Items.h"
#include "Transaction.h"
#include "Dashboard.h"
#include "Profile.h"

using namespace std;

// ==================== HELPER FUNCTIONS ====================

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    clearInput();
    cin.get();
}

// ==================== TRANSACTION MENU ====================

void transactionMenu(string username) {
    Items items(username);
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "        TRANSACTION MENU            \n";
        cout << "====================================\n";
        cout << "1. Add New Item\n";
        cout << "2. View My Items\n";
        cout << "3. Add New Transaction\n";
        cout << "4. View All Transactions\n";
        cout << "5. Back to Dashboard\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;
        clearInput();

        if (choice == 1) {
            string itemName;
            cout << "Enter item name (e.g. Praveen, Materials): ";
            getline(cin, itemName);

            if (items.addItem(itemName)) {
                cout << "Item '" << itemName << "' added successfully!\n";
            } else {
                cout << "Item already exists!\n";
            }

        } else if (choice == 2) {
            items.displayItems();
            pressEnterToContinue();

        } else if (choice == 3) {
            items.loadItems();
            items.displayItems();

            if (items.getItemCount() == 0) {
                cout << "Please add items first!\n";
                pressEnterToContinue();
                continue;
            }

            int itemChoice;
            cout << "Select item number: ";
            cin >> itemChoice;
            clearInput();

            vector<string> itemList = items.getItems();
            if (itemChoice < 1 || itemChoice > (int)itemList.size()) {
                cout << "Invalid choice!\n";
                continue;
            }

            string selectedItem = itemList[itemChoice - 1];

            double amount;
            cout << "Enter amount (Rs.): ";
            cin >> amount;
            clearInput();

            string txnType;
            cout << "Transaction type:\n1. Credit\n2. Debit\nEnter choice: ";
            int typeChoice;
            cin >> typeChoice;
            clearInput();
            txnType = (typeChoice == 1) ? "credit" : "debit";

            string method;
            cout << "Payment method:\n1. Cash\n2. Bank Transfer\nEnter choice: ";
            int methodChoice;
            cin >> methodChoice;
            clearInput();
            method = (methodChoice == 1) ? "cash" : "bank transfer";

            string description;
            cout << "Enter description (press Enter to skip): ";
            getline(cin, description);

            Transaction txn(username, selectedItem, amount, method, description, txnType);
            if (txn.saveTransaction()) {
                txn.displayTransaction();
                cout << "Transaction saved successfully!\n";
            } else {
                cout << "Failed to save transaction!\n";
            }
            pressEnterToContinue();

        } else if (choice == 4) {
            Transaction::viewAllTransactions(username);
            pressEnterToContinue();
        }

    } while (choice != 5);
}

// ==================== PROFILE MENU ====================

void profileMenu(string username) {
    Profile profile(username);
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "          PROFILE MENU              \n";
        cout << "====================================\n";
        cout << "1. View Profile\n";
        cout << "2. Setup / Update Profile\n";
        cout << "3. Back to Dashboard\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;
        clearInput();

        if (choice == 1) {
            profile.displayProfile();
            pressEnterToContinue();

        } else if (choice == 2) {
            string cName, oName, addr, contact, mail, bType;

            cout << "Company Name  : "; getline(cin, cName);
            cout << "Owner Name    : "; getline(cin, oName);
            cout << "Address       : "; getline(cin, addr);
            cout << "Contact Number: "; getline(cin, contact);
            cout << "Email         : "; getline(cin, mail);
            cout << "Business Type : "; getline(cin, bType);

            profile.setProfile(cName, oName, addr, contact, mail, bType);
            cout << "Profile updated successfully!\n";
            pressEnterToContinue();
        }

    } while (choice != 3);
}

// ==================== MAIN DASHBOARD MENU ====================

void mainDashboard(string username) {
    Profile profile(username);
    string companyName = profile.getCompanyName();
    if (companyName.empty()) companyName = "My Business Ledger";

    int choice;

    do {
        Dashboard dashboard(username);
        dashboard.displayDashboard(companyName);

        cout << "\n1. Transactions\n";
        cout << "2. Profile\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        clearInput();

        if (choice == 1) {
            transactionMenu(username);
        } else if (choice == 2) {
            profileMenu(username);
            // Reload company name after profile update
            Profile updatedProfile(username);
            companyName = updatedProfile.getCompanyName();
            if (companyName.empty()) companyName = "My Business Ledger";
        }

    } while (choice != 3);

    cout << "\nLogged out successfully. Goodbye!\n";
}

// ==================== MAIN FUNCTION ====================

int main() {
    int choice;

    cout << "\n====================================\n";
    cout << "   BUSINESS LEDGER SYSTEM - C++    \n";
    cout << "====================================\n";

    do {
        cout << "\n1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;
        clearInput();

        if (choice == 1) {
            string username, password;
            cout << "\n--- CREATE ACCOUNT ---\n";
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            User newUser(username, password);
            if (newUser.createAccount()) {
                cout << "Account created successfully! Please login.\n";
            } else {
                cout << "Username already exists! Try a different one.\n";
            }

        } else if (choice == 2) {
            string username, password;
            cout << "\n--- LOGIN ---\n";
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            User loginUser(username, password);
            if (loginUser.login()) {
                cout << "Login successful!\n";
                mainDashboard(username);
            } else {
                cout << "Invalid username or password!\n";
            }
        }

    } while (choice != 3);

    cout << "\nThank you for using Business Ledger System!\n";
    return 0;
}
