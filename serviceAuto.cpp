#include "serviceAuto.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

ServiceAuto::ServiceAuto() : numOrders(0) {}

// File reading and writing operations

void ServiceAuto::initialize() {
    employeesManager.readEmployeesFromCSV("employees.csv");
    readOrdersFromCSV("orders.csv");
}

void ServiceAuto::readOrdersFromCSV(string filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string serviceName;
        string price;
        string quantity;

        if (getline(iss, serviceName, ',') &&
            getline(iss, price, ',') &&
            getline(iss, quantity, ',')) {
            Order ord(serviceName, stod(price), stoi(quantity));
            addOrder(ord); // Adăugarea comenzii în array-ul orders
        }
        else {
            cerr << "Error: Invalid format in CSV file" << endl;
        }
    }

    file.close();

    sortOrders();
}

void ServiceAuto::writeOrdersToCSV(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    for (int i = 0; i < numOrders; i++) {
        file << orders[i].serviceName << ','
            << orders[i].price << ','
            << orders[i].quantity << '\n';
    }

    file.close();
}

// Orders functionality

void ServiceAuto::displayAllOrders() {
    for (int i = 0; i < numOrders; i++) {
        orders[i].display();
        cout << endl;
    }
}

void ServiceAuto::searchOrderByServiceName(string serviceName) {
    bool found = false;

    for (int i = 0; i < numOrders; i++) {
        if (orders[i].serviceName == serviceName) {
            orders[i].display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Order with service name " << serviceName << " not found." << endl;
    }
}

void ServiceAuto::addOrder() {
    if (numOrders < 1500) {
        string serviceName;
        double price;
        int quantity;

        serviceName = readOrderServiceName();
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter quantity: ";
        cin >> quantity;

        bool foundOrderInsertPosition = false;
        for (int i = 0; i < numOrders; i++) {
          if (strcmp(orders[i].serviceName.c_str(), serviceName.c_str()) >= 0) {
            for (int j = numOrders + 1; j > i; j--) {
              orders[j] = orders[i];
            }

            orders[i] = Order(serviceName, price, quantity);
            foundOrderInsertPosition = true;
            break;
          }
        }

        if (!foundOrderInsertPosition) {
            orders[numOrders] = Order(serviceName, price, quantity);
        }

        numOrders++;
        writeOrdersToCSV("orders.csv");
    }
    else {
        cerr << "Error: Order array is full" << endl;
    }
}

void ServiceAuto::addOrder(const Order& order) {
    if (numOrders < 1500) {
        orders[numOrders] = order;
        numOrders++;
    }
    else {
        cerr << "Error: Order array is full" << endl;
    }
}

void ServiceAuto::deleteOrder() {
    string serviceName = readOrderServiceName();

    bool found = false;
    for (int i = 0; i < numOrders; i++) {
        if (orders[i].serviceName == serviceName) {
            for (int j = i; j < numOrders - 1; j++) {
                orders[j] = orders[j + 1];
            }
            numOrders--;
            found = true;
            cout << "Order " << serviceName << " has been deleted." << endl;
            writeOrdersToCSV("orders.csv");
            break;
        }
    }

    if (!found) {
        cout << "Order with service name " << serviceName << " not found." << endl;
    }
}

string readOrderServiceName() {
  string orderServiceName;
  cout << "Enter the name of the services: ";
  cin.ignore();
  getline(cin, orderServiceName);
}

void ServiceAuto::sortOrders() {
    sort(orders, orders + numOrders, [](Order& a, Order& b) {
        return a.serviceName < b.serviceName;
    });
}