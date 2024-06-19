#include "order.h"

Order::Order() : serviceName(""), price(0.0), quantity(0) {}

Order::Order(string serviceName, double price, int quantity)
    : serviceName(serviceName), price(price), quantity(quantity) {}

void Order::display() {
    cout << "Service Name: " << serviceName << "\n";
    cout << "Price: " << price << "\n";
    cout << "Quantity: " << quantity << "\n";
}