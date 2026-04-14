# Business Ledger System - C++

## Project Structure

```
ledger/
├── main.cpp          → Main file, all menus and program flow
├── User.h            → User class (create account, login)
├── Items.h           → Items class (add/view custom items)
├── Transaction.h     → Transaction class (add/view transactions)
├── Dashboard.h       → Dashboard class (balance, credits, debits)
├── Profile.h         → Profile class (company details)
└── README.md         → This file
```

## How to Compile

```bash
g++ main.cpp -o ledger
./ledger
```

## Classes Used

| Class       | Responsibility                              |
|-------------|---------------------------------------------|
| User        | Create account, login verification          |
| Items       | Add custom items, load dropdown list        |
| Transaction | Record debit/credit, view all transactions  |
| Dashboard   | Calculate balance, credits, debits, entries |
| Profile     | Store and update company details            |

## Files Generated at Runtime

Each user gets their own set of data files:

| File                        | Contents                    |
|-----------------------------|-----------------------------|
| users.txt                   | All usernames and passwords |
| {username}_items.txt        | User's custom items list    |
| {username}_transactions.txt | User's all transactions     |
| {username}_profile.txt      | User's company profile      |

## Features

- Create Account and Login system
- Auto date on every transaction (no manual entry)
- Custom items list per user (dropdown style selection)
- Debit / Credit transactions
- Cash or Bank Transfer payment options
- Optional description on transactions
- Dashboard showing Total Balance, Credited, Debited, Entries
- Good Morning / Afternoon / Evening greeting
- Company Profile management
- All data saved to files (persists between sessions)

## OOP Concepts Used

- Classes and Objects
- Constructors and Destructors
- File Handling (ifstream, ofstream)
- Encapsulation (private/public)
- Static functions
- Vectors

## Built for LinkedIn & GitHub Portfolio Project
