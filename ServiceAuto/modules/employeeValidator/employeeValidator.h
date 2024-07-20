#ifndef EMPLOYEE_VALIDATOR_H
#define EMPLOYEE_VALIDATOR_H

#include "./../employee/employee.h"
using namespace std;

class EmployeeValidator {
private:
    Employee validatedEmployee;

    string getValidatedEmployeeFullName();

public:
    EmployeeValidator();

    bool isValidFirstName(string firstName);
    bool isValidLastName(string lastName);
    bool isValidExperience(int experience);
    bool isValidSalary(double salary);
    bool isValidAge(int age);
    bool isValidGender(string gender);

    bool isValidEmployee(Employee employee);
};

#endif