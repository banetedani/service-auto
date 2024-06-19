#include <iostream>
#include <string>

using namespace std;

class Order {
public:
    string serviceName;
    double price;
    int quantity;

    Order();
    Order(string serviceName, double price, int quantity);
    void display();
};