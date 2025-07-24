#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// Utility to lowercase for case-insensitive comparison
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), tolower);
    return lowerStr;
}

// Base Product class (abstraction)
class Product {
protected:
    string name, location;
    int quantity;
    float price;
public:
    Product(string n, int q, float p, string loc) : name(n), quantity(q), price(p), location(loc) {}
    virtual void display() const = 0;
    virtual string getExtraInfo() const = 0;
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    float getPrice() const { return price; }
    void reduceQuantity(int q) { quantity -= q; }
    void increaseQuantity(int q) { quantity += q; }
    string getLocation() const { return location; }
    virtual string getCategory() const = 0;
    virtual ~Product() {}
};

// Perishable Product
class Perishable : public Product {
    string batch, expiry;
public:
    Perishable(string n, int q, float p, string loc, string b, string e) :
        Product(n, q, p, loc), batch(b), expiry(e) {
    }
    void display() const override {
        cout << name << " | Qty: " << quantity << " | Price: $" << price << " | Loc: " << location
            << " | Batch: " << batch << " | Expiry: " << expiry;
        if (quantity < 3)
            cout << " [LOW STOCK]";
        cout << endl;
    }
    string getExtraInfo() const override {
        return "Batch: " + batch + " | Expiry: " + expiry;
    }
    string getBatch() const { return batch; }
    string getExpiry() const { return expiry; }
    string getCategory() const override { return "Perishable"; }
};

// Electronic Product
class Electronic : public Product {
    string brand;
    int warranty;
public:
    Electronic(string n, int q, float p, string loc, string br, int w) :
        Product(n, q, p, loc), brand(br), warranty(w) {
    }
    void display() const override {
        cout << name << " | Qty: " << quantity << " | Price: $" << price << " | Loc: " << location
            << " | Brand: " << brand << " | Warranty: " << warranty << " Year(s)";
        if (quantity < 3)
            cout << " [LOW STOCK]";
        cout << endl;
    }
    string getExtraInfo() const override {
        return "Brand: " + brand + " | Warranty: " + to_string(warranty) + " Year(s)";
    }
    string getBrand() const { return brand; }
    int getWarranty() const { return warranty; }
    string getCategory() const override { return "Electronic"; }
};

// Order class
class Order {
public:
    string customerName;
    map<string, int> orderedItems;

    Order() : customerName("") {}
    Order(string cname) : customerName(toLower(cname)) {}
    void addItem(string item, int qty) {
        orderedItems[toLower(item)] += qty;
    }
    void removeItem(string item, int qty) {
        if (orderedItems.find(item) != orderedItems.end()) {
            orderedItems[item] -= qty;
            if (orderedItems[item] <= 0)
                orderedItems.erase(item);
        }
    }
};

// Warehouse class
class Warehouse {
    vector<Product*> inventory;
    map<string, Order> orders;

public:
    void addProduct(Product* p) {
        inventory.push_back(p);
    }

    void showInventory() {
        cout << "\n|-----------------------------------------------------------------------|" << endl;
        cout << "|                            Perishable Items                           |" << endl;
        cout << "|-----------------------------------------------------------------------|" << endl;
        cout << left << setw(5) << "|No."
            << setw(15) << "|Name"
            << setw(8) << "|Qty"
            << setw(10) << "|Price"
            << setw(10) << "|Loc"
            << setw(12) << "|Batch"
            << setw(12) << "|Expiry     |";
        cout << endl;
        cout << "|----|--------------|-------|---------|---------|-----------|-----------|" << endl;
        int i = 1;
        for (auto* p : inventory) {
            if (p->getCategory() == "Perishable") {
                Perishable* per = dynamic_cast<Perishable*>(p);
                cout << "|" << setw(4) << i++
                    << "|" << setw(14) << per->getName()
                    << "|" << setw(7) << per->getQuantity()
                    << "|$" << setw(8) << per->getPrice()
                    << "|" << setw(9) << per->getLocation()
                    << "|" << setw(11) << per->getBatch()
                    << "|" << setw(11) << per->getExpiry() << "|";
                cout << endl;
            }
        }
        cout << "|-----------------------------------------------------------------------|" << endl;

        cout << "\n|-------------------------------------------------------------------------|" << endl;
        cout << "|                            Electronics Items                            |" << endl;
        cout << "|-------------------------------------------------------------------------|" << endl;
        cout << left << setw(5) << "|No."
            << setw(15) << "|Name"
            << setw(8) << "|Qty"
            << setw(10) << "|Price"
            << setw(10) << "|Loc"
            << setw(15) << "|Brand"
            << setw(10) << "|Warranty  |";
        cout << endl;
        cout << "|----|--------------|-------|---------|---------|--------------|----------|" << endl;

        i = 1;
        for (auto* p : inventory) {
            if (p->getCategory() == "Electronic") {
                Electronic* elec = dynamic_cast<Electronic*>(p);
                cout << "|" << setw(4) << i++
                    << "|" << setw(14) << elec->getName()
                    << "|" << setw(7) << elec->getQuantity()
                    << "|$" << setw(8) << elec->getPrice()
                    << "|" << setw(9) << elec->getLocation()
                    << "|" << setw(14) << elec->getBrand()
                    << "|" << setw(5) << elec->getWarranty() << "     |";
                cout << endl;
            }
        }
        cout << "|-------------------------------------------------------------------------|" << endl;
    }

    void orderProduct() {
        string cname;
        cout << "\nEnter customer name: ";
        cin.ignore();
        getline(cin, cname);
        cname = toLower(cname);
        Order order(cname);
        float total = 0.0;

        char more = 'y';
        while (more == 'y' || more == 'Y') {
            string pname;
            int qty;
            cout << "\nEnter product name: ";
            getline(cin, pname);
            pname = toLower(pname);
            Product* selected = nullptr;

            for (auto* p : inventory)
                if (toLower(p->getName()) == pname)
                    selected = p;

            if (!selected) {
                cout << "Product not found!\n";
            }
            else {
                cout << "Enter quantity: ";
                cin >> qty;
                cin.ignore();
                if (qty > selected->getQuantity()) {
                    cout << "Not enough stock available!\n";
                }
                else {
                    float itemPrice = qty * selected->getPrice();
                    selected->reduceQuantity(qty);
                    order.addItem(selected->getName(), qty);
                    total += itemPrice;
                    cout << "Order placed for " << qty << " " << selected->getName() << "(s). Price: $" << itemPrice << endl;

                    if (selected->getQuantity() < 3)
                        cout << "Warning: " << selected->getName() << " stock is low (" << selected->getQuantity() << " remaining).\n";
                }
            }

            cout << "Add more items? (y/n): ";
            cin >> more;
            cin.ignore();
        }

        orders[cname] = order;
        cout << "\nTotal Bill for " << cname << " is: $" << total << endl;
    }

    void returnProduct() {
        string cname;
        cout << "\nEnter customer name for return: ";
        cin.ignore();
        getline(cin, cname);
        cname = toLower(cname);

        if (orders.find(cname) == orders.end()) {
            cout << "Customer not found!\n";
            return;
        }

        cout << "\nOrder for " << cname << ":\n";
        for (auto& pair : orders[cname].orderedItems)
            cout << "- " << pair.first << ": " << pair.second << endl;

        string pname;
        int qty;
        cout << "\nEnter product name to return: ";
        getline(cin, pname);
        pname = toLower(pname);
        cout << "Enter quantity to return: ";
        cin >> qty;
        cin.ignore();

        bool found = false;
        float refundAmount = 0.0;

        for (auto* p : inventory) {
            if (toLower(p->getName()) == pname) {
                if (orders[cname].orderedItems.find(pname) != orders[cname].orderedItems.end() && orders[cname].orderedItems[pname] >= qty) {
                    p->increaseQuantity(qty);
                    orders[cname].removeItem(pname, qty);
                    refundAmount = qty * p->getPrice();
                    found = true;
                }
                else {
                    cout << "Customer did not order that quantity of this product.\n";
                }
                break;
            }
        }

        if (found)
            cout << "Return processed. Amount refunded: $" << refundAmount << endl;
        else if (refundAmount == 0.0)
            cout << "Product not found in system or invalid return quantity.\n";
    }


    void showLowStock() {
        cout << "\n===== LOW STOCK ITEMS =====\n";
        bool found = false;
        for (auto* p : inventory) {
            if (p->getQuantity() < 5) {
                p->display();
                found = true;
            }
        }
        if (!found)
            cout << "All items are sufficiently stocked.\n";
    }

    void exportCSV() {
        ofstream file("Stock_Report.csv");
        if (!file) {
            cout << "Failed to export file.\n";
            return;
        }

        file << "Category,Name,Quantity,Price,Location,Batch,Expiry,Brand,Warranty\n";

        for (auto* p : inventory) {
            string category = p->getCategory();
            file << category << "," << p->getName() << "," << p->getQuantity() << "," << p->getPrice() << "," << p->getLocation() << ",";

            if (category == "Perishable") {
                Perishable* per = dynamic_cast<Perishable*>(p);
                file << per->getBatch() << "," << per->getExpiry() << ",,\n";
            }
            else if (category == "Electronic") {
                Electronic* elec = dynamic_cast<Electronic*>(p);
                file << ",," << elec->getBrand() << "," << elec->getWarranty() << "\n";
            }
        }

        file.close();
        cout << "Stock report exported to 'Stock_Report.csv'.\n";
    }

    ~Warehouse() {
        for (auto* p : inventory)
            delete p;
    }
};

// MAIN FUNCTION
int main() {
    Warehouse w;

    // Add perishable items
    w.addProduct(new Perishable("Milk", 10, 10, "P1", "B101", "2025-08-01"));
    w.addProduct(new Perishable("Egg", 5, 4, "P2", "B102", "2025-07-20"));
    w.addProduct(new Perishable("Cheese", 7, 6, "P3", "B103", "2025-09-10"));
    w.addProduct(new Perishable("Butter", 6, 5, "P4", "B104", "2025-08-15"));
    w.addProduct(new Perishable("Yogurt", 12, 5, "P5", "B105", "2025-07-25"));

    // Add electronics
    w.addProduct(new Electronic("Monitor", 5, 350, "E1", "Samsung", 2));
    w.addProduct(new Electronic("Mouse", 10, 40, "E2", "Logitech", 1));
    w.addProduct(new Electronic("Keyboard", 8, 45, "E3", "HP", 2));
    w.addProduct(new Electronic("Laptop", 3, 700, "E4", "Dell", 3));
    w.addProduct(new Electronic("Speaker", 6, 60, "E5", "JBL", 1));

    int choice;
    do {
        cout << "\n===== WAREHOUSE SYSTEM MENU =====\n";
        cout << "1. Show Inventory\n";
        cout << "2. Place Order\n";
        cout << "3. Return/Refund\n";
        cout << "4. View Low Stock Items\n";
        cout << "5. Export Stock Report (CSV)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: w.showInventory(); break;
        case 2: w.orderProduct(); break;
        case 3: w.returnProduct(); break;
        case 4: w.showLowStock(); break;
        case 5: w.exportCSV(); break;
        case 6: cout << "Exiting... Goodbye!\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
