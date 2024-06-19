#include <iostream>
#include "serviceAuto.h"
using namespace std;

void displayMainMenu(ServiceAuto serviceAuto) {
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
      cin >> choice;

      switch (choice) {
        case 1: {
            serviceAuto.displayAllOrders();
        }
        break;
        case 2: {
            serviceAuto.employeesManager.displayAllEmployees();
        }
        break;
        case 3: {
            string lastName = serviceAuto.employeesManager.readEmployeeLastName();
            string firstName = serviceAuto.employeesManager.readEmployeeFirstName();
            serviceAuto.employeesManager.searchEmployeeByName(lastName, firstName);
        }
        break;
        case 4: {
            string orderServiceName = serviceAuto.readOrderServiceName();
            serviceAuto.searchOrderByServiceName(orderServiceName);
        }
        break;
        case 5: {
            serviceAuto.employeesManager.addAnEmployee();
        }
        break;
        case 6: {
            serviceAuto.addOrder();
        }
        break;
        case 7: {
            serviceAuto.employeesManager.deleteEmployee();
        }
        break;
        case 8: {
            serviceAuto.deleteOrder();
        }
        break;
        case 9: {
            serviceAuto.employeesManager.updateEmployee();
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

int main() {
    ServiceAuto serviceAuto;
    serviceAuto.initialize();
    
    displayMainMenu(serviceAuto);

    return 0;
}