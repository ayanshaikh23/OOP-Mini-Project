#  Business Ledger System

A full-stack **Business Ledger Application** built with **C++** backend, **Node.js** REST API, and **HTML/CSS/JavaScript** frontend. Designed for contractors, small business owners, and freelancers to manage their daily financial transactions efficiently.

---

##  Live Preview

> Open `login.html` in your browser after starting the Node.js server.

---

##  Project Overview

This project was built as a **C++ OOP portfolio project** that demonstrates real-world application of:
- Object-Oriented Programming in C++
- File Handling System
- REST API design with Node.js
- Frontend development with HTML/CSS/JS

The system allows a business owner to:
- Create an account and log in securely
- Manage a custom list of items (e.g. laborer names, materials)
- Record debit and credit transactions with automatic date
- View dashboard with total balance, credits, debits and entry count
- Manage company profile details

---

##  Project Structure

```
LEDGER_SYSTEM/
│
├── ledger/                        # C++ Backend
│   ├── main.cpp                   # Main program — menus and flow
│   ├── User.h                     # User class — login & register
│   ├── Items.h                    # Items class — custom item list
│   ├── Transaction.h              # Transaction class — debit/credit
│   ├── Dashboard.h                # Dashboard class — balance stats
│   ├── Profile.h                  # Profile class — company details
│   ├── users.txt                  # Stores all user credentials
│   ├── {username}_items.txt       # Per-user item list
│   ├── {username}_transactions.txt# Per-user transaction records
│   └── {username}_profile.txt     # Per-user company profile
│
└── serverfile/                    # Node.js API + Frontend
    ├── server.js                  # Express REST API server
    ├── login.html                 # Login & Register page
    ├── dashboard.html             # Main dashboard page
    ├── package.json               # Node.js dependencies
    └── node_modules/              # Installed packages
```

---

## Basics covered

| Layer        | Technology         | Purpose                            |
|--------------|--------------------|------------------------------------|
| Backend      | C++ (OOP)          | Core logic, file handling          |
| API Server   | Node.js + Express  | Bridge between frontend and C++    |
| Frontend     | HTML + CSS + JS    | User interface                     |
| Data Storage | Text Files (.txt)  | Persistent file-based storage      |

---

## C++ OOP Concepts Used

### 1. Classes & Objects
Every major feature is encapsulated in its own class:

```cpp
User user("john", "pass123");
user.createAccount();
user.login();
```

### 2. Constructors & Destructors
Each class uses constructors to initialize data and destructors for cleanup:

```cpp
class Dashboard {
public:
    Dashboard(string uname) {   // Constructor
        username = uname;
        totalBalance = 0.0;
    }
    ~Dashboard() {}             // Destructor
};
```

### 3. File Handling (fstream)
All data is saved and read using C++ file streams:

```cpp
// Writing to file
ofstream file("users.txt", ios::app);
file << username << "," << password << "\n";
file.close();

// Reading from file
ifstream file("users.txt");
string line;
while (getline(file, line)) { ... }
file.close();
```

### 4. Encapsulation
Private data members are accessed only through public member functions:

```cpp
class User {
private:
    string username;
    string password;
public:
    bool login();
    bool createAccount();
    string getUsername();
};
```

### 5. Vectors (STL)
Used in the Items class to manage a dynamic list of items:

```cpp
vector<string> itemList;
itemList.push_back(itemName);
```

### 6. Static Functions
Transaction viewing is available as a static utility function:

```cpp
static void viewAllTransactions(string username);
```

---

## Node.js API Endpoints

| Method | Route            | Description                        |
|--------|------------------|------------------------------------|
| POST   | `/login`         | Verify user credentials            |
| POST   | `/register`      | Create a new user account          |
| GET    | `/dashboard`     | Get balance, credits, debits stats |
| GET    | `/transactions`  | Get all transactions for a user    |
| POST   | `/transaction`   | Save a new transaction             |
| GET    | `/items`         | Get user's custom item list        |
| POST   | `/items`         | Add a new item to user's list      |
| GET    | `/profile`       | Get user's company profile         |
| POST   | `/profile`       | Save/update company profile        |

---

## 🗄️ Data Storage Format

### users.txt
```
Ayan,password123
ayan45,mypassword
```

### {username}_transactions.txt
```
debit,Praveen,500,cash,daily wages,12/4/2026
credit,Client A,15000,bank transfer,project payment,12/4/2026
```

### {username}_profile.txt
```
Alfa Consultancy
Ayan shaikh
123 Business Street Bharuch
9876543210
ayan@business.com
Construction
```

---

##How to Run

### Step 1 — Compile & Run C++ Backend
```bash
cd ledger
g++ main.cpp -o ledger
./ledger
```

### Step 2 — Start Node.js API Server
```bash
cd serverfile
npm install
node server.js
```

### Step 3 — Open Frontend
```
Open browser and go to: http://localhost:3000/login.html
```

---

## Features

-  Secure user registration and login
-  Automatic date on every transaction (no manual entry needed)
-  Custom item list per user — select from dropdown, no retyping
-  Debit and Credit transaction recording
-  Cash or Bank Transfer payment options
-  Optional description on each transaction
-  Dashboard with real-time balance, credited, debited, and entry count
-  Good Morning / Afternoon / Evening greeting on dashboard
-  Company profile management
-  All data stored in files — persists between sessions
-  Both terminal and web interface supported
-  Premium dark-themed iOS-style UI

---

> Built with using C++, Node.js, and HTML/CSS/JS
