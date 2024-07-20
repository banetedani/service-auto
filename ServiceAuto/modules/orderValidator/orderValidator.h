#ifndef ORDER_VALIDATOR_H
#define ORDER_VALIDATOR_H

#include "./../order/order.h"
using namespace std;

class OrderValidator {
private:
	Order validatedOrder;

	string getOrderServiceName();

public:
	OrderValidator() {}

	bool isValidServiceName(string serviceName);
	bool isValidPrice(float price);
	bool isValidQuantity(int quantity);

	bool isValidOrder(Order order);
};

#endif