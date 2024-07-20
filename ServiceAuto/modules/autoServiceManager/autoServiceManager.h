#ifndef SERVICE_AUTO_MANAGER_H
#define SERVICE_AUTO_MANAGER_H

#include "./../employeesManager/employeesManager.h"
#include "./../ordersManager/ordersManager.h"

class AutoServiceManager {
public:
    EmployeesManager employeesManager;
    OrdersManager ordersManager;

    AutoServiceManager();
    
    void initialize();
    void displayMainMenu(AutoServiceManager autoServiceManager);
};

#endif