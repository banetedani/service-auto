#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
using namespace std;

class Order {
public:
    string serviceName;
    float price;
    int quantity;

    Order();
    Order(string serviceName, float price, int quantity);
    void display();
};

#endif