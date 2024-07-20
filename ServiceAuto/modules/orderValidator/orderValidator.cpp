#include "orderValidator.h"

bool OrderValidator::isValidOrder(Order order) {
	validatedOrder = order;

	return isValidServiceName(order.serviceName) &&
		isValidPrice(order.price) &&
		isValidQuantity(order.quantity);
}

bool OrderValidator::isValidServiceName(string serviceName) {
	if (serviceName.length() < 2 || serviceName.length() > 100) {
		throw "The order service name " + getOrderServiceName() + "must be between 2 and 100 characters.";
	}

	return true;
}

bool OrderValidator::isValidPrice(float price) {
	if (price < 0 || price > 10000) {
		throw "The price for the order " + getOrderServiceName() + "must be between 0 and 10000.";
	}

	return true;
}

bool OrderValidator::isValidQuantity(int quantity) {
	if (quantity < 1 || quantity > 15) {
		throw "The quantity for the order " + getOrderServiceName() + "must be between 1 and 15.";
	}

	return true;
}

string OrderValidator::getOrderServiceName() {
	return validatedOrder.serviceName != "" ? '\"' + validatedOrder.serviceName + "\" " : "";
}