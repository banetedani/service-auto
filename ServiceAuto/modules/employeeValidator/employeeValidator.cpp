#include "employeeValidator.h"

EmployeeValidator::EmployeeValidator() {};

bool EmployeeValidator::isValidEmployee(Employee employee) {
  validatedEmployee = employee;
  string genderAsString(1, validatedEmployee.gender);

  return isValidFirstName(validatedEmployee.firstName) &&
      isValidLastName(validatedEmployee.lastName) &&
      isValidExperience(validatedEmployee.experience) &&
      isValidSalary(validatedEmployee.salary) &&
      isValidAge(validatedEmployee.age) &&
      isValidGender(genderAsString);
}

bool EmployeeValidator::isValidFirstName(string firstName) {
    if (firstName.length() < 2 || firstName.length() > 60) {
        throw "The first name of the employee " + getValidatedEmployeeFullName() + "needs to be between 2 and 60 characters long.";
    }

    return true;
}

bool EmployeeValidator::isValidLastName(string lastName) {
    if (lastName.length() < 2 || lastName.length() > 30) {
        throw "The last name of the employee " + getValidatedEmployeeFullName() + "needs to be between 2 and 30 characters long.";
    }

    return true;
}


bool EmployeeValidator::isValidExperience(int experience) {
    if (experience < 0 || experience > 50) {
        throw "The experience of the employee " + getValidatedEmployeeFullName() + "needs to be between 0 and 50 years.";
    }

    return true;
}

bool EmployeeValidator::isValidSalary(double salary) {
    if (salary < 1000 || salary > 25000) {
        throw "The salary of the employee " + getValidatedEmployeeFullName() + "needs to be between 1000 and 25000 EUR.";
    }

    return true;
}

bool EmployeeValidator::isValidAge(int age) {
    if (age < 18 || age > 65) {
        throw "The age of the employee " + getValidatedEmployeeFullName() + "needs to be between 18 and 65 years.";
    }

    return true;
}

bool EmployeeValidator::isValidGender(string gender) {
    if (gender.length() != 1 || (gender[0] != 'M' && gender[0] != 'F')) {
        throw "The gender of the employee " + getValidatedEmployeeFullName() + "is invalid. Valid options: M or F.";
    }

    return true;
}

string EmployeeValidator::getValidatedEmployeeFullName() {
    return validatedEmployee.firstName != "" || validatedEmployee.lastName != "" ?
        (validatedEmployee.firstName + " " + validatedEmployee.lastName + " ") : "";
}
