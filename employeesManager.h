#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "employee.h"
using namespace std;

class EmployeesManager {
private:
    Employee employees[50];
    int numEmployees;

    void sortEmployees();

public:
    void readEmployeesFromCSV(string filename);
    void writeEmployeesToCSV(string filename);
    void displayAllEmployees();
    void searchEmployeeByName(string lastName, string firstName);
    void addAnEmployee();
    void updateEmployee();
    void deleteEmployee();
    string readEmployeeFirstName();
    string readEmployeeLastName();
}