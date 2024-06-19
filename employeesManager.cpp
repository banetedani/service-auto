#include "employeesManager.h"
using namespace std;

void EmployeesManager::readEmployeesFromCSV(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    cin.ignore();
    while (getline(file, line)) {
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
            getline(iss, sex, ','))
        {
            employees[numEmployees] = Employee(lastName, firstName, stoi(experience), stod(salary), stoi(age), sex[0]);
            numEmployees++;
        }
        else {
            cerr << "Error: Invalid format in CSV file" << endl;
        }
    }

    file.close();

    /* We do not have a guarantee that in the file, the employees were
      alphabetically sorted or that nobody altered the order of the employees */
    sortEmployees();
}

void EmployeesManager::writeEmployeesToCSV(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    for (int i = 0; i < numEmployees; i++) {
        file << employees[i].lastName << ','
            << employees[i].firstName << ','
            << employees[i].experience << ','
            << employees[i].salary << ','
            << employees[i].age << ','
            << employees[i].sex << '\n';
    }

    file.close();
}

void EmployeesManager::displayAllEmployees() {
    for (int i = 0; i < numEmployees; i++) {
        employees[i].display();
        cout << endl;
    }
}

void EmployeesManager::searchEmployeeByName(string lastName, string firstName) {
    bool found = false;

    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].lastName == lastName && employees[i].firstName == firstName) {
            employees[i].display();
            found = true;
            break;
        }
    }
  
    if (!found) {
        cout << "Employee with name " << lastName << " " << firstName << " not found." << endl;
    }
}

void EmployeesManager::addAnEmployee() {
    if (numEmployees < 50) {
        string lastName, firstName;
        int experience;
        double salary;
        int age;
        char sex;

        lastName = readEmployeeLastName();
        firstName = readEmployeeFirstName();
        cout << "Enter experience (years): ";
        cin >> experience;
        cout << "Enter salary: ";
        cin >> salary;
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter sex (M/F): ";
        cin >> sex;

        bool foundEmployeeInsertPosition = false;
        for (int i = 0; i < numEmployees; i++) {
          if (strcmp(employees[i].lastName.c_str(), lastName.c_str()) >= 0) {
            for (int j = numEmployees + 1; j > i; j--) {
              employees[j] = employees[i];
            }

            employees[i] = Employee(lastName, firstName, experience, salary, age, sex);
            foundEmployeeInsertPosition = true;
            break;
          }
        }

        if (!foundEmployeeInsertPosition) {
            employees[numEmployees] = Employee(lastName, firstName, experience, salary, age, sex);
        }

        numEmployees++;
        
        writeEmployeesToCSV("employees.csv");
    }
    else {
        cerr << "Error: Employee array is full" << endl;
    }
}

void EmployeesManager::updateEmployee() {
    string lastName = readEmployeeLastName();
    string firstName = readEmployeeFirstName();

    bool found = false;
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].lastName == lastName && employees[i].firstName == firstName) {
            found = true;
            cout << "Current details of the employee:\n";
            employees[i].display();

            cout << "Enter new details for the employee (leave empty to keep current value):\n";

            string input;
            cout << "Enter last name: ";
            cin.ignore();
            getline(cin, input);
            
            // If the input is empty, we skip updating the last name
            if (!input.empty()) {
                employees[i].lastName = input;
            }

            cout << "Enter first name: ";
            getline(cin, input);
            if (!input.empty()) {
                employees[i].firstName = input;
            }

            cout << "Enter experience (years): ";
            getline(cin, input);
            if (!input.empty() && stoi(input) != NULL && stoi(input) >= 0  && stoi(input) < 50) {
                employees[i].experience = stoi(input);
            }

            cout << "Enter salary: ";
            getline(cin, input);
            if (!input.empty()) {
                employees[i].salary = stod(input);
            }

            cout << "Enter age: ";
            getline(cin, input);
            if (!input.empty()) {
                employees[i].age = stoi(input);
            }

            cout << "Enter sex (M/F): ";
            getline(cin, input);
            if (!input.empty()) {
                employees[i].sex = input[0];
            }

            cout << "Employee details updated successfully.\n";
            sortEmployees();
            writeEmployeesToCSV("employees.csv");
            break;
        }
    }

    if (!found) {
        cout << "Employee with name " << lastName << " " << firstName << " not found.\n";
    }
}

void EmployeesManager::deleteEmployee() {
    string lastName = readEmployeeLastName();
    string firstName = readEmployeeFirstName();

    bool found = false;
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].lastName == lastName && employees[i].firstName == firstName) {
            for (int j = i; j < numEmployees - 1; j++) {
                employees[j] = employees[j + 1];
            }
            numEmployees--;
            found = true;
            cout << "Employee " << lastName << " " << firstName << " has been deleted." << endl;
            writeEmployeesToCSV("employees.csv");
            break;
        }
    }

    if (!found) {
        cout << "Employee with name " << lastName << " " << firstName << " not found." << endl;
    }
}

string EmployeesManager::readEmployeeFirstName() {
  string firstName;
  cout << "Enter the first name: ";
  cin.ignore();
  getline(cin, firstName);
  return firstName;
}

string EmployeesManager::readEmployeeLastName() {
  string lastName;
  cout << "Enter the last name: ";
  cin >> lastName;
}

void EmployeesManager::sortEmployees() {
    sort(employees, employees + numEmployees, [](Employee& a, Employee& b) {
        return a.lastName < b.lastName;
    });
}