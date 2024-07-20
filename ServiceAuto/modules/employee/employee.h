#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

using namespace std;

class Employee {
public:
    string lastName;
    string firstName;
    int experience;
    double salary;
    int age;
    char gender;

    Employee();
    Employee(string lastName, string firstName, int experience, double salary, int age, char gender);

    void display();
};

#endif