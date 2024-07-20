#include "employee.h"

Employee::Employee() :
  lastName(""),
  firstName(""),
  experience(0),
  salary(0.0),
  age(0),
  gender(' ') {}

Employee::Employee(string lastName, string firstName, int experience, double salary, int age, char gender)
    : lastName(lastName), firstName(firstName), experience(experience), salary(salary), age(age), gender(gender) {}

void Employee::display() {
    cout << "Name: " << lastName << " " << firstName << "\n";
    cout << "Experience: " << experience << " years\n";
    cout << "Salary: " << salary << "\n";
    cout << "Age: " << age << " years\n";
    cout << "Gender: " << gender << "\n";
}
