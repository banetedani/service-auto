#ifndef ORDERS_MANAGER_H
#define ORDERS_MANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "./../order/order.h"
#include "./../orderValidator/orderValidator.h"
using namespace std;

enum OrderFieldToValidate {
    ORDER_SEVICE_NAME,
    ORDER_PRICE,
    ORDER_QUANTITY
};

class OrdersManager {
private:
    static const unsigned maxOrders = 1500;
    const string ordersFileName = "./ServiceAuto/resources/orders.csv";

    Order orders[maxOrders];
    int numOrders;

    void sortOrders();
    string readOrderField(string message, OrderFieldToValidate fieldToValidate);

public:
    OrdersManager();

    void readOrdersFromCSV();
    void readOrdersFromCSV(string filename);
    void writeOrdersToCSV();
    void writeOrdersToCSV(string filename);
    void displayAllOrders();
    void searchOrderByServiceName();
    void addOrder();
    void deleteOrder();
};

#endif