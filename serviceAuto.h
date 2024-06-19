#include "employeesManager.h"
#include "order.h"

class ServiceAuto {
private:
    // TODO: separate orders logic in "ordersManager.h/.cpp" as done with employees
    Order orders[1500];
    int numOrders;

    void readOrdersFromCSV(string filename);
    void writeOrdersToCSV(string filename);

    void sortOrders();

public:
    EmployeesManager employeesManager;

    ServiceAuto();
    
    void initialize();

    // TODO: separate orders logic in "ordersManager.h/.cpp" as done with employees
    void displayAllOrders();
    void searchOrderByServiceName(string serviceName);
    void addOrder();
    void addOrder(const Order& order);
    void deleteOrder();
    string readOrderServiceName();
};

