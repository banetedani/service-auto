#include "./ordersManager.h"

OrdersManager::OrdersManager(): numOrders(0) {};

void OrdersManager::readOrdersFromCSV() {
    readOrdersFromCSV(ordersFileName);
}

void OrdersManager::readOrdersFromCSV(string filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    unsigned currentReadLine = 1;
    while (getline(file, line)) {
        if (numOrders >= maxOrders) {
            cerr << "Error: You reached the maximum number of " << maxOrders << " orders. File reading stopped." << endl;
            break;
        }

        istringstream iss(line);
        string serviceName;
        string price;
        string quantity;

        if (getline(iss, serviceName, ',') &&
            getline(iss, price, ',') &&
            getline(iss, quantity, ','))
        {
            OrderValidator orderValidator;
            Order order(serviceName, stof(price), stoi(quantity));

            try {
                if (orderValidator.isValidOrder(order)) {
                    orders[numOrders] = order;
                    numOrders++;
                }
            }
            catch (string error) {
                cerr << "Error: " << error << " (line " << currentReadLine << ")" << endl;
            }
        }
        else {
            cerr << "Error: Invalid format in orders CSV file. (line " << currentReadLine << ")" << endl;
        }

        currentReadLine++;
    }

    file.close();

    OrdersManager::sortOrders();
}

void OrdersManager::writeOrdersToCSV() {
    writeOrdersToCSV(ordersFileName);
}

void OrdersManager::writeOrdersToCSV(string filename) {
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

void OrdersManager::displayAllOrders() {
    cout << endl;
    for (int i = 0; i < numOrders; i++) {
        orders[i].display();
        cout << endl;
    }
}

void OrdersManager::searchOrderByServiceName() {
    cin.ignore();
    string serviceName = readOrderField("Enter the name of the order service: ", ORDER_SEVICE_NAME);
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

void OrdersManager::addOrder() {
    if (numOrders < maxOrders) {
        Order newOrder;

        /* It seems that we need to clear the cin buffer (with cin.ignore()) for the first field only, after the cout
           was done. If we try to clear it before reading other fields, it will remove the first character entered. */
        cin.ignore();
        newOrder.serviceName = readOrderField("Enter the name of the order service: ", ORDER_SEVICE_NAME);
        newOrder.price = stof(readOrderField("Enter price: ", ORDER_PRICE));
        newOrder.quantity = stoi(readOrderField("Enter quantity: ", ORDER_QUANTITY));

        bool foundOrderInsertPosition = false;
        for (int i = 0; i < numOrders; i++) {
            if (orders[i].serviceName.compare(newOrder.serviceName) >= 0) {
                for (int j = numOrders + 1; j > i; j--) {
                    orders[j] = orders[j - 1];
                }

                orders[i] = newOrder;
                foundOrderInsertPosition = true;
                break;
            }
        }

        if (!foundOrderInsertPosition) {
            orders[numOrders] = newOrder;
        }

        numOrders++;

        writeOrdersToCSV();
    }
    else {
        cerr << "Error: You reached the maximum number of " << maxOrders << " orders." << endl;
    }
}

void OrdersManager::deleteOrder() {
    cin.ignore();
    string serviceName = readOrderField("Enter the name of the order service: ", ORDER_SEVICE_NAME);

    bool found = false;
    for (int i = 0; i < numOrders; i++) {
        if (orders[i].serviceName == serviceName) {
            for (int j = i; j < numOrders - 1; j++) {
                orders[j] = orders[j + 1];
            }
            numOrders--;
            found = true;
            cout << "Order " << serviceName << " has been deleted." << endl;
            writeOrdersToCSV();
            break;
        }
    }

    if (!found) {
        cout << "Order with service name " << serviceName << " not found." << endl;
    }
}

void OrdersManager::sortOrders() {
    sort(orders, orders + numOrders, [](Order& a, Order& b) {
        return a.serviceName < b.serviceName;
    });
}

string OrdersManager::readOrderField(string message, OrderFieldToValidate fieldToValidate) {
    OrderValidator orderValidator;
    string input;
    bool isFieldValid = false;

    while (!isFieldValid) {
        cout << message;
        getline(cin, input);

        try {
            switch (fieldToValidate) {
            case ORDER_SEVICE_NAME:
                isFieldValid = orderValidator.isValidServiceName(input);
                break;
            case ORDER_PRICE:
                isFieldValid = orderValidator.isValidPrice(stof(input));
                break;
            case ORDER_QUANTITY:
                isFieldValid = orderValidator.isValidQuantity(stoi(input));
                break;
            }
        }
        catch (string error) {
            cerr << error << endl;
        }

        if (isFieldValid) {
            return input;
        }
    }
}