#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Function declarations
void customerMenu();
void adminMenu();
void viewMenu();
void buyItem();
void addItem();
void deleteItem();
void viewSalesHistory();

int main() {
    int choice;
    while (true) {
        cout << "Welcome to the Bakery Management Program!" << endl;
        cout << "1. Customer Menu" << endl;
        cout << "2. Admin Menu" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                customerMenu();
                break;
            case 2:
                adminMenu();
                break;
            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}

void customerMenu() {
    int choice;
    while (true) {
        cout << "Customer Menu:" << endl;
        cout << "1. View Menu" << endl;
        cout << "2. Buy Item" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                viewMenu();
                break;
            case 2:
                buyItem();
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void adminMenu() {
    int choice;
    while (true) {
        cout << "Admin Menu:" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Delete Item" << endl;
        cout << "3. View Sales History" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                deleteItem();
                break;
            case 3:
                viewSalesHistory();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void viewMenu() {
    ifstream file("inventory.csv");
    if (!file.is_open()) {
        cout << "Error opening inventory file." << endl;
        return;
    }

    string line;
    cout << "Menu:" << endl;
    cout << "Item No.\tItem Name\tPrice" << endl;
    int itemNo = 1;
    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        string itemName = line.substr(0, commaPos);
        string itemPrice = line.substr(commaPos + 1);
        cout << itemNo++ << ".\t" << itemName << "\t$" << itemPrice << endl;
    }
    file.close();
}
void buyItem() {
    ifstream file("inventory.csv");
    if (!file.is_open()) {
        cout << "Error opening inventory file." << endl;
        return;
    }

    vector<pair<string, double>> items;
    string line;
    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        string itemName = line.substr(0, commaPos);
        double itemPrice = stod(line.substr(commaPos + 1));
        items.push_back(make_pair(itemName, itemPrice));
    }
    file.close();

    int choice;
    cout << "Enter the item number to buy: ";
    cin >> choice;

    if (choice < 1 || choice > items.size()) {
        cout << "Invalid item number." << endl;
        return;
    }

    string itemName = items[choice - 1].first;
    double itemPrice = items[choice - 1].second;
    cout << "You selected: " << itemName << " - $" << itemPrice << endl;

    double payment;
    cout << "Enter payment amount: ";
    cin >> payment;

    if (payment < itemPrice) {
        cout << "Insufficient payment." << endl;
        return;
    }

    double change = payment - itemPrice;
    cout << "Receipt:" << endl;
    cout << "Item: " << itemName << endl;
    cout << "Price: $" << itemPrice << endl;
    cout << "Payment: $" << payment << endl;
    cout << "Change: $" << change << endl;

    ofstream salesFile("sales_history.csv", ios::app);
    if (salesFile.is_open()) {
        salesFile << itemName << "," << itemPrice << "," << payment << "," << change << endl;
        salesFile.close();
    } else {
        cout << "Error opening sales history file." << endl;
    }
}

void addItem() {
    ofstream file("inventory.csv", ios::app);
    if (!file.is_open()) {
        cout << "Error opening inventory file." << endl;
        return;
    }

    string itemName;
    double itemPrice;
    cout << "Enter item name: ";
    cin >> itemName;
    cout << "Enter item price: ";
    cin >> itemPrice;

    file << itemName << "," << itemPrice << endl;
    file.close();
    cout << "Item added successfully." << endl;
}

void deleteItem() {
    ifstream file("inventory.csv");
    if (!file.is_open()) {
        cout << "Error opening inventory file." << endl;
        return;
    }

    vector<string> items;
    string line;
    while (getline(file, line)) {
        items.push_back(line);
    }
    file.close();

    int choice;
    cout << "Enter the item number to delete: ";
    cin >> choice;

    if (choice < 1 || choice > items.size()) {
        cout << "Invalid item number." << endl;
        return;
    }

    items.erase(items.begin() + choice - 1);

    ofstream outFile("inventory.csv");
    if (!outFile.is_open()) {
        cout << "Error opening inventory file." << endl;
        return;
    }

    for (const string& item : items) {
        outFile << item << endl;
    }
    outFile.close();
    cout << "Item deleted successfully." << endl;
}

void viewSalesHistory() {
    ifstream file("sales_history.csv");
    if (!file.is_open()) {
        cout << "Error opening sales history file." << endl;
        return;
    }

    string line;
    cout << "Sales History:" << endl;
    cout << "Item Name\tPrice\tPayment\tChange" << endl;
    while (getline(file, line)) {
        size_t firstComma = line.find(',');
        size_t secondComma = line.find(',', firstComma + 1);
        size_t thirdComma = line.find(',', secondComma + 1);

        string itemName = line.substr(0, firstComma);
        string itemPrice = line.substr(firstComma + 1, secondComma - firstComma - 1);
        string payment = line.substr(secondComma + 1, thirdComma - secondComma - 1);
        string change = line.substr(thirdComma + 1);

        cout << itemName << "\t$" << itemPrice << "\t$" << payment << "\t$" << change << endl;
    }
    file.close();
}