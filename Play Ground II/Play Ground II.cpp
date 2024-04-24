#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Employee {
private:
    string lastName;
    string firstName;
    int experience;
    double salary;
    int age;
    char sex;
public:
    Employee() {}
    Employee(string lastName, string firstName, int experience, double salary, int age, char sex){}

    string getLastName() { return lastName; }
    string getFirstName() { return firstName; }
    int getExperience() { return experience; }
    double getSalary() { return salary; }
    int getAge() { return age; }
    char getSex() { return sex; }

    void display() {
        cout << "Name: " << lastName << " " << firstName << "\n";
        cout << "Experience: " << experience << " years\n";
        cout << "Salary: " << salary << "\n";
        cout << "Age: " << age << " years\n";
        cout << "Sex: " << sex << "\n";
    }
};

class Order {
private:
    string serviceName;
    double price;
    int quantity;
public:
    Order() {}
    Order(string sn, double p, int q) : serviceName(sn), price(p), quantity(q) {}

    string getServiceName() { return serviceName; }
    double getPrice() { return price; }
    int getQuantity() { return quantity; }

    void display() {
        cout << "Service Name: " << serviceName << "\n";
        cout << "Price: " << price << "\n";
        cout << "Quantity: " << quantity << "\n";
    }
};

class ServiceAuto {
private:
    Employee employees[100];
    Order orders[100];
    int numEmployees;
    int numOrders;

public:
    ServiceAuto() : numEmployees(0), numOrders(0) {}

    void readEmployeesFromCSV(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            cout << "Read line: " << line << endl; // Afișează conținutul fiecărei linii citite
            istringstream iss(line);
            string lastName, firstName;
            string experience, age;
            string salary;
            string sex; // Variabila temporara pentru citirea sexului
            if (getline(iss, lastName, ',') &&
                getline(iss, firstName, ',') &&
                getline(iss, experience, ',') &&
                getline(iss, salary, ',') &&
                getline(iss, age, ',') &&
                getline(iss, sex, ',') )
              {

                Employee emp(lastName, firstName, stoi(experience), stod(salary), stoi(age), sex[0]);
                addEmployee(emp); // Adăugarea angajatului în array
            }
            else {
                cerr << "Error: Invalid format in CSV file" << endl;
            }
        }

        file.close();

        // Actualizarea numărului de angajați
        cout << "Number of employees read: " << numEmployees << endl;
    }
    void readOrdersFromCSV(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string serviceName;
            double price;
            int quantity;
            if (getline(iss, serviceName, ',') && (iss >> price >> quantity)) {
                Order ord(serviceName, price, quantity);
                addOrder(ord); // Adăugarea comenzii în array-ul orders
            }
            else {
                cerr << "Error: Invalid format in CSV file" << endl;
            }
        }

        file.close();
    }

    void displayAllOrdersAlphabetically() {
        // Sortarea comenzilor după denumirea serviciului în ordine alfabetică (bubble sort)
        for (int i = 0; i < numOrders - 1; ++i) {
            for (int j = 0; j < numOrders - i - 1; ++j) {
                if (orders[j].getServiceName() > orders[j + 1].getServiceName()) {
                    // Schimbarea pozițiilor comenzilor în array
                    Order temp = orders[j];
                    orders[j] = orders[j + 1];
                    orders[j + 1] = temp;
                }
            }
        }

        // Afisarea comenzilor in ordine alfabetica
        cout << "All Orders (Alphabetically):\n";
        for (int i = 0; i < numOrders; ++i) {
            orders[i].display(); // Afisarea comenzii
            cout << endl;
        }
    }

    void displayAllEmployeesAlphabetically() {
        // Sortarea angajatilor după nume în ordine alfabetică (bubble sort)
        for (int i = 0; i < numEmployees - 1; ++i) {
            for (int j = 0; j < numEmployees - i - 1; ++j) {
                if (employees[j].getLastName() > employees[j + 1].getLastName()) {
                    // Schimbarea pozițiilor angajatilor în array
                    Employee temp = employees[j];
                    employees[j] = employees[j + 1];
                    employees[j + 1] = temp;
                }
            }
        }

        // Afisarea angajatilor in ordine alfabetica
        cout << "All Employees (Alphabetically):\n";
        for (int i = 0; i < numEmployees; ++i) {
            employees[i].display(); // Afisarea angajatului
            cout << endl;
        }
    }

    void searchEmployee(string name) {
        bool found = false;
        for (int i = 0; i < numEmployees; ++i) {
            if (employees[i].getLastName() == name || employees[i].getFirstName() == name) {
                found = true;
                cout << "Employee found:\n";
                employees[i].display();
                break;
            }
        }
        if (!found) {
            cout << "Employee with name " << name << " not found.\n";
        }
    }


    void searchOrder(string serviceName) {
        bool found = false;
        for (int i = 0; i < numOrders; ++i) {
            if (orders[i].getServiceName() == serviceName) {
                found = true;
                cout << "Order found:\n";
                orders[i].display();
                break;
            }
        }
        if (!found) {
            cout << "Order with service name " << serviceName << " not found.\n";
        }
    }


    void addEmployee(Employee emp) {
        if (numEmployees < 100) { // Verificare dacă există spațiu disponibil în array
            employees[numEmployees] = emp; // Adăugarea angajatului la sfârșitul array-ului
            numEmployees++; // Incrementarea numărului de angajați
            cout << "Employee added successfully.\n";
        }
        else {
            cerr << "Error: Maximum number of employees reached.\n";
        }
    }


    void addOrder(Order ord) {
        if (numOrders < 100) { // Verificare dacă există spațiu disponibil în array
            orders[numOrders] = ord; // Adăugarea comenzii la sfârșitul array-ului
            numOrders++; // Incrementarea numărului de comenzi
            cout << "Order added successfully.\n";
        }
        else {
            cerr << "Error: Maximum number of orders reached.\n";
        }
    }


    void deleteEmployee(string name) {
        bool found = false;
        for (int i = 0; i < numEmployees; ++i) {
            if (employees[i].getLastName() == name || employees[i].getFirstName() == name) {
                found = true;
                // Stergerea angajatului prin mutarea elementelor de la dreapta la stânga
                for (int j = i; j < numEmployees - 1; ++j) {
                    employees[j] = employees[j + 1];
                }
                numEmployees--; // Decrementarea numărului de angajați
                cout << "Employee " << name << " deleted successfully.\n";
                break;
            }
        }
        if (!found) {
            cerr << "Error: Employee with name " << name << " not found.\n";
        }
    }


    void deleteOrder(string serviceName) {
        bool found = false;
        for (int i = 0; i < numOrders; ++i) {
            if (orders[i].getServiceName() == serviceName) {
                found = true;
                // Muta elementele la stanga pentru a suprascrie comanda stearsa
                for (int j = i; j < numOrders - 1; ++j) {
                    orders[j] = orders[j + 1];
                }
                numOrders--; // Scade numarul de comenzi
                cout << "Order with service name \"" << serviceName << "\" deleted successfully.\n";
                break;
            }
        }
        if (!found) {
            cerr << "Error: Order with service name \"" << serviceName << "\" not found.\n";
        }
    }

    void updateEmployeeData(string name) {
        bool found = false;
        Employee updatedEmployees[100]; // Arrayul temporar in care sa memoram datele actualizate
        int numUpdatedEmployees = 0;

        for (int i = 0; i < numEmployees; ++i) {
            if (employees[i].getLastName() == name || employees[i].getFirstName() == name) {
                found = true;
                cout << "Enter updated employee details for " << name << ":\n";
                // Obținem date actualizate ale angajaților din datele introduse de utilizator
                string newLastName, newFirstName;
                int newExperience, newAge;
                double newSalary;
                char newSex;
                cout << "Last Name: ";
                cin >> newLastName;
                cout << "First Name: ";
                cin >> newFirstName;
                cout << "Experience: ";
                cin >> newExperience;
                cout << "Salary: ";
                cin >> newSalary;
                cout << "Age: ";
                cin >> newAge;
                cin.ignore();
                cout << "Sex (M/F): ";
                cin >> newSex;

                // Creiam un nou Employee cu datele actualizate
                Employee updatedEmp(newLastName, newFirstName, newExperience, newSalary, newAge, newSex);
                updatedEmployees[numUpdatedEmployees] = updatedEmp; // Adăugam Employee actualizat la matricea temporară
                numUpdatedEmployees++; // Incrementam contorul
            }
            else {
                // Copiați angajații existenți în matricea temporară, dacă nu angajatul țintă
                updatedEmployees[numUpdatedEmployees] = employees[i];
                numUpdatedEmployees++;
            }
        }

        if (!found) {
            cerr << "Error: Employee with name \"" << name << "\" not found.\n";
            return;
        }

        // Copiați angajații actualizați înapoi în matricea originală și actualizați numEmployees
        numEmployees = numUpdatedEmployees;
        for (int i = 0; i < numEmployees; ++i) {
            employees[i] = updatedEmployees[i];
        }
        cout << "Employee data updated successfully.\n";
    }


    void saveChangesToCSV() {
        // Salvarea modificărilor în fișierul pentru angajați
        ofstream employeesFile("employees.csv");
        if (employeesFile.is_open()) {
            for (int i = 0; i < numEmployees; ++i) {
                employeesFile << employees[i].getLastName() << ","
                    << employees[i].getFirstName() << ","
                    << employees[i].getExperience() << ","
                    << employees[i].getSalary() << ","
                    << employees[i].getAge() << ","
                    << employees[i].getSex() << "\n";
            }
            employeesFile.close();
            cout << "Changes saved to employees.csv.\n";
        }
        else {
            cerr << "Error: Unable to open employees.csv for writing.\n";
        }

        // Salvarea modificărilor în fișierul pentru comenzile
        ofstream ordersFile("orders.csv");
        if (ordersFile.is_open()) {
            for (int i = 0; i < numOrders; ++i) {
                ordersFile << orders[i].getServiceName() << ","
                    << orders[i].getPrice() << ","
                    << orders[i].getQuantity() << "\n";
            }
            ordersFile.close();
            cout << "Changes saved to orders.csv.\n";
        }
        else {
            cerr << "Error: Unable to open orders.csv for writing.\n";
        }
    }
};

int main() {
    // Initializarea serviciului auto
    ServiceAuto service;

    // Citirea datelor angajatilor si comenzilor din fisierele CSV
    service.readEmployeesFromCSV("employees.csv");
    service.readOrdersFromCSV("orders.csv");

    // Meniul de optiuni
    int choice;
    do {
        cout << "Menu:\n";
        cout << "1. Display all orders alphabetically\n";
        cout << "2. Display all employees alphabetically\n";
        cout << "3. Search for an employee\n";
        cout << "4. Search for an order\n";
        cout << "5. Add an employee\n";
        cout << "6. Add an order\n";
        cout << "7. Delete an employee\n";
        cout << "8. Delete an order\n";
        cout << "9. Update employee data\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            service.displayAllOrdersAlphabetically();
            break;
        case 2:
            service.displayAllEmployeesAlphabetically();
            break;
        case 3:
        {
            string name;
            cout << "Enter employee name: ";
            cin >> name;
            service.searchEmployee(name);
        }
        break;
        case 4:
        {
            string serviceName;
            cout << "Enter service name: ";
            cin >> serviceName;
            service.searchOrder(serviceName);
        }
        break;
        case 5:
        {
            string lastName, firstName;
            int experience, age;
            double salary;
            char sex;
            cout << "Enter employee details:\n";
            cout << "Last Name: ";
            cin >> lastName;
            cout << "First Name: ";
            cin >> firstName;
            cout << "Experience: ";
            cin >> experience;
            cout << "Salary: ";
            cin >> salary;
            cout << "Age: ";
            cin >> age;
            cout << "Sex (M/F): ";
            cin >> sex;
            Employee emp(lastName, firstName, experience, salary, age, sex);
            service.addEmployee(emp);
        }
        break;
        case 6:
        {
            string serviceName;
            double price;
            int quantity;
            cout << "Enter order details:\n";
            cout << "Service Name: ";
            cin >> serviceName;
            cout << "Price: ";
            cin >> price;
            cout << "Quantity: ";
            cin >> quantity;
            Order ord(serviceName, price, quantity);
            service.addOrder(ord);
        }
        break;
        case 7:
        {
            string name;
            cout << "Enter employee name to delete: ";
            cin >> name;
            service.deleteEmployee(name);
        }
        break;
        case 8:
        {
            string serviceName;
            cout << "Enter service name to delete: ";
            cin >> serviceName;
            service.deleteOrder(serviceName);
        }
        break;
        case 9:
        {
            string name;
            cout << "Enter employee name to update: ";
            cin >> name;
            service.updateEmployeeData(name);
        }
        break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    // Salvarea modificarilor in fisierele CSV
    service.saveChangesToCSV();

    return 0;
}