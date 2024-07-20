#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "./../employee/employee.h"
#include "./../employeeValidator/employeeValidator.h"
using namespace std;

enum EmployeeFieldToValidate {
    EMPLOYEE_LAST_NAME,
    EMPLOYEE_FIRST_NAME,
    EMPLOYEE_EXPERIENCE,
    EMPLOYEE_SALARY,
    EMPLOYEE_AGE,
    EMPLOYEE_GENDER
};

class EmployeesManager {
private:
    static const unsigned maxEmployees = 50;
    const string employeesFileName = "./ServiceAuto/resources/employees.csv";

    Employee employees[maxEmployees];
    int numEmployees = 0;

    void sortEmployees();
    string readEmployeeField(string message, EmployeeFieldToValidate fieldToValidate);
    string readEmployeeField(string message, EmployeeFieldToValidate fieldToValidate, bool allowEmptyField);

public:
    void readEmployeesFromCSV();
    void readEmployeesFromCSV(string filename);
    void writeEmployeesToCSV();
    void writeEmployeesToCSV(string filename);
    void displayAllEmployees();
    void searchEmployeeByName();
    void addAnEmployee();
    void updateEmployee();
    void deleteEmployee();
};

#endif