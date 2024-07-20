#include "autoServiceManager.h"

AutoServiceManager::AutoServiceManager() {}

// File reading and writing operations

void AutoServiceManager::initialize() {
    employeesManager.readEmployeesFromCSV();
    ordersManager.readOrdersFromCSV();
}

void AutoServiceManager::displayMainMenu(AutoServiceManager autoServiceManager) {
    int choice = 0;

    do {
        cout << "Menu:\n";
        cout << "1. Display all orders alphabeticaly\n";
        cout << "2. Display all employees alphabetically\n";
        cout << "3. Search for an employee\n";
        cout << "4. Search for an order\n";
        cout << "5. Add an employee\n";
        cout << "6. Add an order\n";
        cout << "7. Delete an employee\n";
        cout << "8. Delete an order\n";
        cout << "9. Update employee data\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            autoServiceManager.ordersManager.displayAllOrders();
        }
              break;
        case 2: {
            autoServiceManager.employeesManager.displayAllEmployees();
        }
              break;
        case 3: {
            autoServiceManager.employeesManager.searchEmployeeByName();
        }
              break;
        case 4: {
            autoServiceManager.ordersManager.searchOrderByServiceName();
        }
              break;
        case 5: {
            autoServiceManager.employeesManager.addAnEmployee();
        }
              break;
        case 6: {
            autoServiceManager.ordersManager.addOrder();
        }
              break;
        case 7: {
            autoServiceManager.employeesManager.deleteEmployee();
        }
              break;
        case 8: {
            autoServiceManager.ordersManager.deleteOrder();
        }
              break;
        case 9: {
            autoServiceManager.employeesManager.updateEmployee();
        }
              break;
        case 0: {
            cout << "Exiting ...\n";
            break;
        default:
            cout << "Invalid choice. Please try again. \n";
        }
        }
    } while (choice != 0);
}