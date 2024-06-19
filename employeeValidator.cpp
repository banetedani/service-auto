#include "employeeValidator.h"
using namespace std;

EmployeeValidator::EmployeeValidator() {};
EmployeeValidator::EmployeeValidator(Employee validatedEmployee): validatedEmployee(validatedEmployee) {};


bool EmployeeValidator::isValidEmployee() {
  isValidExperience(validatedEmployee.experience);
}

bool EmployeeValidator::isValidEmployee(Employee employee) {
  validatedEmployee = employee;

  isValidExperience(validatedEmployee.experience);
}

bool EmployeeValidator::isValidExperience(int experience) {
  if (validatedEmployee.experience < 0 || validatedEmployee.experience > 50) {
    throw "Experienta " + validatedEmployee.firstName + " " + validatedEmployee.lastName + " angajatului nu se incadreaza intre valorile permise de 0 si 50 de ani.";
  }
}


