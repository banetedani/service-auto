#include "employee.h";

class EmployeeValidator {
private:
    Employee validatedEmployee;

public:
    EmployeeValidator();
    EmployeeValidator(Employee validatedEmployee);

    bool isValidExperience(int experience);
    bool isValidEmployee();
    bool isValidEmployee(Employee employee);
};