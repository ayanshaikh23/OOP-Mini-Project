#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Items {
private:
    string username;
    vector<string> itemList;

public:
    // Constructor
    Items(string uname) {
        username = uname;
        loadItems();
    }

    // Destructor
    ~Items() {}

    // Load items from file
    void loadItems() {
        itemList.clear();
        ifstream file(username + "_items.txt");
        string line;

        while (getline(file, line)) {
            if (!line.empty()) {
                itemList.push_back(line);
            }
        }
        file.close();
    }

    // Add new item
    bool addItem(string itemName) {
        for (string item : itemList) {
            if (item == itemName) return false; // Already exists
        }

        ofstream file(username + "_items.txt", ios::app);
        if (file.is_open()) {
            file << itemName << "\n";
            file.close();
            itemList.push_back(itemName);
            return true;
        }
        return false;
    }

    // Get all items
    vector<string> getItems() {
        return itemList;
    }

    // Display all items
    void displayItems() {
        cout << "\n--- Your Items ---\n";
        if (itemList.empty()) {
            cout << "No items found. Please add items first.\n";
            return;
        }
        for (int i = 0; i < (int)itemList.size(); i++) {
            cout << i + 1 << ". " << itemList[i] << "\n";
        }
    }

    int getItemCount() {
        return itemList.size();
    }
};

#endif
