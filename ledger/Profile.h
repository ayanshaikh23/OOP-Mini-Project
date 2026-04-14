#ifndef PROFILE_H
#define PROFILE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Profile {
private:
    string username;
    string companyName;
    string ownerName;
    string address;
    string contactNumber;
    string email;
    string businessType;

public:
    // Constructor
    Profile(string uname) {
        username = uname;
        loadProfile();
    }

    // Destructor
    ~Profile() {}

    // Load profile from file
    void loadProfile() {
        ifstream file(username + "_profile.txt");
        if (file.is_open()) {
            getline(file, companyName);
            getline(file, ownerName);
            getline(file, address);
            getline(file, contactNumber);
            getline(file, email);
            getline(file, businessType);
            file.close();
        }
    }

    // Save profile to file
    bool saveProfile() {
        ofstream file(username + "_profile.txt");
        if (file.is_open()) {
            file << companyName   << "\n";
            file << ownerName     << "\n";
            file << address       << "\n";
            file << contactNumber << "\n";
            file << email         << "\n";
            file << businessType  << "\n";
            file.close();
            return true;
        }
        return false;
    }

    // Set full profile at once
    void setProfile(string cName, string oName, string addr,
                    string contact, string mail, string bType) {
        companyName   = cName;
        ownerName     = oName;
        address       = addr;
        contactNumber = contact;
        email         = mail;
        businessType  = bType;
        saveProfile();
    }

    // Update individual fields
    void updateCompanyName(string cName)   { companyName   = cName;   saveProfile(); }
    void updateOwnerName(string oName)     { ownerName     = oName;   saveProfile(); }
    void updateAddress(string addr)        { address       = addr;    saveProfile(); }
    void updateContact(string contact)     { contactNumber = contact; saveProfile(); }
    void updateEmail(string mail)          { email         = mail;    saveProfile(); }
    void updateBusinessType(string bType)  { businessType  = bType;   saveProfile(); }

    // Display profile
    void displayProfile() {
        cout << "\n====================================\n";
        cout << "         COMPANY PROFILE            \n";
        cout << "====================================\n";
        cout << "Company Name  : " << (companyName.empty()   ? "Not Set" : companyName)   << "\n";
        cout << "Owner Name    : " << (ownerName.empty()     ? "Not Set" : ownerName)     << "\n";
        cout << "Address       : " << (address.empty()       ? "Not Set" : address)       << "\n";
        cout << "Contact       : " << (contactNumber.empty() ? "Not Set" : contactNumber) << "\n";
        cout << "Email         : " << (email.empty()         ? "Not Set" : email)         << "\n";
        cout << "Business Type : " << (businessType.empty()  ? "Not Set" : businessType)  << "\n";
        cout << "====================================\n";
    }

    // Getters for Node.js API
    string getCompanyName()  { return companyName;   }
    string getOwnerName()    { return ownerName;     }
    string getAddress()      { return address;       }
    string getContact()      { return contactNumber; }
    string getEmail()        { return email;         }
    string getBusinessType() { return businessType;  }
};

#endif
