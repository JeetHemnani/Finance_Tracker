#include <iostream>
#include <iomanip>
#include <string>
#include <iomanip>
#include<vector>
#include<limits>
#include<fstream>
#include<sstream>
#include <stdexcept>
#include <algorithm>
const std::string FILENAME = "transactions.csv";

class Transaction {
private:
    int id;
    std::string date;
    std::string type;
    double amount;
    std::string category;
    std::string description;

public:
    Transaction(int id, const std::string& date, const std::string& type, double amount, const std::string& category, const std::string& description)
        : id(id), date(date), type(type), amount(amount), category(category), description(description) {
    }

    int getID() const { return id; }
    const std::string& getDate() const { return date; }
    const std::string& getType() const { return type; }
    double getAmount() const { return amount; }
    const std::string& getCategory() const { return category; }
    const std::string& getDescription() const { return description; }

    // --- Add the new display() method below this line ---

    // The display() method prints all transaction details to the console.
    // It is a 'const' method because it does not modify the object's state.
    // It only reads the member variables (via their getters).
    void display() const {
        std::cout << "------------------------------------------" << std::endl;
        std::cout << "Transaction ID: " << getID() << std::endl;
        std::cout << "Date:           " << getDate() << std::endl;
        std::cout << "Type:           " << getType() << std::endl;
        // Use std::fixed and std::setprecision to format the amount as currency.
        std::cout << "Amount:         $" << std::fixed << std::setprecision(2) << getAmount() << std::endl;
        std::cout << "Category:       " << getCategory() << std::endl;
        std::cout << "Description:    " << getDescription() << std::endl;
        std::cout << "------------------------------------------" << std::endl;
    }
   void setDate(const std::string& newDate) {
        date = newDate;
    }

    void setAmount(double newAmount) {
        amount = newAmount;
    }

    void setCategory(const std::string& newCategory) {
        category = newCategory;
    }

    void setDescription(const std::string& newDescription) {
        description = newDescription;
    }
};

class TransactionManager {
    private:
    std::vector<Transaction> transactions;
    int nextId;


    public:
    TransactionManager() : nextId(1) {}

    void addTransaction(const std::string& date, const std::string& type, double amount, const std::string& category, const std::string& description) {
        Transaction newTransaction(nextId, date, type, amount, category, description);

        // automatically handling memory allocation if needed.
        transactions.push_back(newTransaction);
        // creation and then increments the variable, making it ready for the next call.
        nextId++;
    }
    void viewAllTransactions() const {
        if (transactions.empty()) {
            std::cout << "\nNo transactions to display.\n" << std::endl;
            return; // Exit the method early.
        }

        std::cout << "\n========== All Transactions ==========" << std::endl;
        // Here we use the modern C++ range-based for loop.
        // For each 'transaction' object inside our 'transactions' vector...
        for (const auto& transaction : transactions) {
            transaction.display();
        }
        std::cout << "========== End of List ===========\n" << std::endl;
    }
    void saveToFile(const std::string& filename) const {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            // Use std::cerr for error messages. It's the standard stream for reporting errors.
            std::cerr << "Error: Could not open the file for writing: " << filename << std::endl;
            
            // If we can't open the file, there's nothing more to do in this function, so we exit early.
            return;
        }
        // Iterate through each Transaction object in our 'transactions' vector.
        // This is a read-only operation, so a const reference is perfect.
        for (const auto& transaction : transactions) {
            // Write the data for the current transaction to the file stream.
            // We use the stream insertion operator '<<', just like with std::cout.
            // We separate each piece of data with a comma to create the CSV format.
            outputFile << transaction.getID() << ","
                       << transaction.getDate() << ","
                       << transaction.getType() << ","
                       << transaction.getAmount() << ","
                       << transaction.getCategory() << ","
                       << transaction.getDescription() 
                       // std::endl adds a newline character and flushes the stream,
                       // ensuring this transaction is on its own line.
                       << std::endl;
        }

    }
    void loadFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        int maxId = 0;
        if (inputFile.is_open()) {
            std::string line; 
            while (std::getline(inputFile, line)) {
                std::stringstream ss(line);
                std::string idStr, date, type, amountStr, category, description;

                if (std::getline(ss, idStr, ',') &&
                    std::getline(ss, date, ',') &&
                    std::getline(ss, type, ',') &&
                    std::getline(ss, amountStr, ',') &&
                    std::getline(ss, category, ',') &&
                    std::getline(ss, description))
                {
                    try {
                        // 1. Convert string values to their proper numeric types.
                        int id = std::stoi(idStr);
                        double amount = std::stod(amountStr);

                        // 2. Use the parsed and converted data to construct a Transaction object.
                        Transaction transaction(id, date, type, amount, category, description);

                        // 3. Add the newly "rehydrated" object to the manager's vector.
                        transactions.push_back(transaction);
                        maxId = std::max(maxId, id);

                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Warning: Skipping corrupted line (invalid number format): " << line << std::endl;
                    } catch (const std::out_of_range& e) {                 
                        std::cerr << "Warning: Skipping corrupted line (number out of range): " << line << std::endl;
                    }
                }
            }

        }
        nextId = maxId + 1;
    }
    void generateSummary() const {
        if (transactions.empty()) {
            std::cout << "\nNo transactions available to generate a summary. Please add some first.\n";
            return;
        }

        // The logic for calculating and printing the summary will be implemented here
        double totalIncome = 0.0;
        double totalExpenses = 0.0;
        for (const auto& transaction : transactions) {
            // Inside this loop, 'transaction' refers to one Transaction object at a time.
            if (transaction.getType() == "income") {
                totalIncome += transaction.getAmount();
            }
            else if (transaction.getType() == "expense") {
                totalExpenses += transaction.getAmount();
            }
        }

        double netBalance = totalIncome - totalExpenses;
        std::cout << "\n========== Financial Summary ==========\n";
        std::cout << std::fixed << std::setprecision(2);

        std::cout << "Total Income:    $" << totalIncome << std::endl;
        std::cout << "Total Expenses:  $" << totalExpenses << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << "Net Balance:     $" << netBalance << std::endl;
        std::cout << "-------------------------\n" << std::endl;
    }
    std::vector<Transaction>::iterator findTransactionById(int id) {
        // `auto` deduces the type of `it` to be `std::vector<Transaction>::iterator`.
        for (auto it = transactions.begin(); it != transactions.end(); ++it) {
            // `it` is an iterator (like a pointer). We use the arrow operator `->`
            // to access the members of the Transaction object it points to.
            if (it->getID() == id) {
                return it;
            }
        }
        return transactions.end();
    }
    void deleteTransaction(const std::string& filename) {
        int idToDelete = 0;
        std::cout << "\nEnter the ID of the transaction to delete: ";
        std::cin >> idToDelete;

        if (std::cin.fail()) {
            std::cout << "[Error] Invalid ID. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        auto it = findTransactionById(idToDelete);

        if (it != transactions.end()) {
            std::cout << "\nTransaction found:\n";
            it->display(); 

            char confirmation;
            std::cout << "\nAre you sure you want to delete this transaction? (y/n): ";
            std::cin >> confirmation;

            if (confirmation == 'y' || confirmation == 'Y') {
                transactions.erase(it);
                saveToFile(filename);
                std::cout << "Transaction deleted successfully.\n";
            } else {
                std::cout << "Deletion cancelled.\n";
            }
        } 
        else {
            // If the iterator is equal to end(), the ID was not found
            std::cout << "Transaction with ID " << idToDelete << " not found.\n";
        }
    }
    void editTransaction(const std::string& filename) {
        int idToEdit = 0;
        std::cout << "\nEnter the ID of the transaction to edit: ";
        std::cin >> idToEdit;

        // Basic input validation
        if (std::cin.fail()) {
            std::cout << "[Error] Invalid ID. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        
        // Clear the rest of the line in case the user entered extra characters
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Use our helper to find the transaction. The non-const iterator 'it'
        // is the key that allows us to modify the object in place.
        auto it = findTransactionById(idToEdit);

        if (it != transactions.end()) {
            std::cout << "\nCurrent transaction details:\n";
            it->display();

            std::cout << "\nWhich field would you like to edit?\n";
            std::cout << "1. Date\n";
            std::cout << "2. Amount\n";
            std::cout << "3. Category\n";
            std::cout << "4. Description\n";
            std::cout << "0. Cancel\n";
            std::cout << "Enter your choice: ";

            int fieldChoice;
            std::cin >> fieldChoice;
            
             if (std::cin.fail()) {
                std::cout << "[Error] Invalid choice. Please enter a number.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (fieldChoice) {
                case 1: { // Edit Date
                    std::string newDate;
                    std::cout << "Enter new date (YYYY-MM-DD): ";
                    std::getline(std::cin, newDate);
                    // Use the iterator 'it' with the arrow operator '->' to call the setter
                    // on the actual object in the vector.
                    it->setDate(newDate);
                    break;
                }
                case 2: { // Edit Amount
                    double newAmount;
                    std::cout << "Enter new amount: ";
                    std::cin >> newAmount;
                    if (std::cin.fail()) {
                         std::cout << "[Error] Invalid amount. Edit cancelled.\n";
                         std::cin.clear();
                         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                         return;
                    }
                    it->setAmount(newAmount);
                    break;
                }
                case 3: { // Edit Category
                    std::string newCategory;
                    std::cout << "Enter new category: ";
                    std::getline(std::cin, newCategory);
                    it->setCategory(newCategory);
                    break;
                }
                case 4: { // Edit Description
                    std::string newDescription;
                    std::cout << "Enter new description: ";
                    std::getline(std::cin, newDescription);
                    it->setDescription(newDescription);
                    break;
                }
                case 0: { // Cancel
                    std::cout << "Edit cancelled.\n";
                    return; // Exit the function immediately, no changes are saved.
                }
                default: {
                    std::cout << "Invalid field choice. Edit cancelled.\n";
                    return; // Exit the function.
                }
            }

            // If we're here, an edit was made. Save immediately.
            saveToFile(filename);
            std::cout << "Transaction updated successfully.\n";

        } else {
            std::cout << "Transaction with ID " << idToEdit << " not found.\n";
        }
    }
    void viewByCategory(const std::string& category) const {
        std::cout << "\n--- Transactions in Category: " << category << " ---\n";
        
        bool foundOne = false;
        for (const auto& transaction : transactions) {
            if (transaction.getCategory() == category) {
                transaction.display();
                foundOne = true; 
            }
        }

        if (!foundOne) {
            std::cout << "No transactions found for this category.\n";
        }
        std::cout << "-------------------------------------------\n";
    }
    void viewByDateRange(const std::string& startDate, const std::string& endDate) const {
        std::cout << "\n--- Transactions from " << startDate << " to " << endDate << " ---\n";

        bool foundOne = false;

        for (const auto& transaction : transactions) {
            
            // This works because of the YYYY-MM-DD format.
            if (transaction.getDate() >= startDate && transaction.getDate() <= endDate) {
                transaction.display();
                foundOne = true;
            }
        }

        if (!foundOne) {
            std::cout << "No transactions found in this date range.\n";
        }
        std::cout << "---------------------------------------------------\n";
    }
};



void displayMenu() {
    std::cout << "\n===== Personal Finance Tracker =====\n";
    std::cout << "1. Add Transaction\n";
    std::cout << "2. View All Transactions\n";
    std::cout << "3. Generate Financial Summary\n";
    std::cout << "4. Edit Transaction\n";
    std::cout << "5. Delete Transaction\n";
    std::cout << "6. Filter by Category\n";
    std::cout << "7. Filter by Date Range\n";
    std::cout << "8. Exit\n"; 
    std::cout << "====================================\n";
    std::cout << "Enter your choice: ";
}
int main() {
    // 1. Instantiate the TransactionManager.
    // This creates our 'manager' object. Its constructor is called,
    // setting nextId to 1 and creating an empty vector.
    TransactionManager manager;
    manager.loadFromFile(FILENAME);
    int choice=0;
    while(true)
    {
        displayMenu();
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "\n[Error] Invalid input. Please enter a number corresponding to a menu option.\n";
            
            // 1. Clear the error flag on std::cin so we can use it again.
            std::cin.clear();
            
            // 2. Discard the rest of the line from the input buffer.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            // 3. Skip the rest of this loop iteration and start over.
            // The 'continue' statement jumps immediately to the next 'while' check.
            continue; 
        }

        
        switch (choice) {
            case 1: {
                std::string date, type, category, description;
                double amount;

                std::cout << "Enter date (YYYY-MM-DD): ";
                std::cin >> date;

                std::cout << "Enter type (income/expense): ";
                std::cin >> type;

                std::cout << "Enter amount: ";
                std::cin >> amount;

                std::cout << "Enter category: ";
                std::cin >> category;

                std::cout << "Enter description: ";
                // This is the CRUCIAL step to handle the newline character left by `std::cin >> amount;`
                // `std::cin.ignore()` discards the leftover newline from the input buffer.
                std::cin.ignore(); 
                // `std::getline` reads the entire line of text, including spaces, into the description.
                std::getline(std::cin, description);

                // With all the data collected, call the manager to do its job.
                manager.addTransaction(date, type, amount, category, description);

                std::cout << "\nTransaction added successfully!\n";
                break; 
            }
            case 2:
                manager.viewAllTransactions();
                break;
            case 3:
                std::cout << "\nGenerating financial summary...\n";
                manager.generateSummary();
                break;
            case 4:
                manager.editTransaction(FILENAME);
                break;

            case 5:
                manager.deleteTransaction(FILENAME);
                break;
            case 6: {
                std::cout << "Enter category to filter by: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string category;
                // Use std::getline to read the entire line, allowing for categories with spaces.
                std::getline(std::cin, category);
                manager.viewByCategory(category);
                break;
            }
            case 7: {
                std::cout << "Enter start date (YYYY-MM-DD): ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string startDate;
                std::getline(std::cin, startDate);
                std::cout << "Enter end date (YYYY-MM-DD): ";
                std::string endDate;
                std::getline(std::cin, endDate);
                manager.viewByDateRange(startDate, endDate);
                break;
            }
            case 8:
                manager.saveToFile(FILENAME);
                std::cout << "\nThank you for using the Personal Finance Tracker. Goodbye!\n";
                return 0;
            default:
                std::cout << "\nInvalid choice. Please try again.\n";
                break;
        }
    }
    return 0;
}




// ek kuch galat form me daal diya to vaha error aa rahah hai aur vo aage usko continue kar le raha hai like 16 march 2026 to vo aage ke 3 options ko skip kar de raha aur sabko include kar de raha