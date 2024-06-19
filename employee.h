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
    char sex;

    Employee();
    Employee(string lastName, string firstName, int experience, double salary, int age, char sex);
    void display();
};