# 💰 Personal Finance Tracker

![Language](https://img.shields.io/badge/Language-C%2B%2B11-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Cross--Platform-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/Status-Active-brightgreen.svg)

A comprehensive, console-based personal finance tracker built in **C++**. Manage your income and expenses with full CRUD operations, persistent CSV storage, financial summaries, and powerful filtering — all from your terminal.

---

## Preview

```
========================================
     PERSONAL FINANCE TRACKER
========================================
 1. Add Transaction
 2. View All Transactions
 3. Edit Transaction
 4. Delete Transaction
 5. Financial Summary
 6. Filter by Category
 7. Filter by Date Range
 8. Exit
========================================
Enter your choice:
```

---

## Features

- **Full CRUD Operations** — Create, Read, Update, and Delete transactions with ease
- **Data Persistence** — All data is automatically saved to and loaded from `transactions.csv`
- **Financial Summary** — Instantly view total income, total expenses, and net balance
- **Filter by Category** — Narrow down transactions by category (e.g., Food, Rent, Salary)
- **Filter by Date Range** — View transactions within any custom date range
- **Input Validation** — Robust error handling to prevent invalid entries
- **Modular OOP Design** — Clean architecture with separated `Transaction` and `TransactionManager` classes

---

## Tech Stack

| Component | Details |
|-----------|---------|
| Language | C++ (C++11 or later) |
| Paradigm | Object-Oriented Programming (OOP) |
| Storage | Local CSV file (`transactions.csv`) |
| Libraries | `iostream`, `fstream`, `sstream`, `vector`, `string`, `iomanip`, `limits`, `algorithm` |
| Compiler | g++ / clang++ |

---

##  Getting Started

### Prerequisites
- A C++ compiler (g++ or clang++)
- Terminal / Command Prompt


##  How It Works

1. On startup, the app loads all saved transactions from `transactions.csv`
2. You interact through a numbered menu in the console
3. Any changes (add, edit, delete) are immediately saved back to the CSV file
4. On exit, all data is safely persisted for the next session

---

## CSV Data Format

Transactions are stored in a simple, human-readable format:

```
ID,Date,Type,Amount,Category,Description
1,2024-01-15,Income,50000,Salary,Monthly salary
2,2024-01-18,Expense,1200,Food,Grocery shopping
3,2024-01-20,Expense,500,Transport,Fuel
```

---

## Future Improvements

- [ ] Export summary report as a `.txt` or `.pdf` file
- [ ] Monthly spending charts (ASCII-based)
- [ ] Budget limits with alerts
- [ ] Multiple user profile support
- [ ] Sort transactions by date, amount, or category



> *Built as a personal project to demonstrate C++ fundamentals, OOP design, and file handling.*
