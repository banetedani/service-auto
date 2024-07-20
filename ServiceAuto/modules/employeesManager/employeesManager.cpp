#include "employeesManager.h"

void EmployeesManager::readEmployeesFromCSV() {
    readEmployeesFromCSV(employeesFileName);
}

void EmployeesManager::readEmployeesFromCSV(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    unsigned currentReadLine = 1;
    while (getline(file, line)) {
        if (numEmployees >= maxEmployees) {
            cerr << "Error: You reached the maximum of " << maxEmployees << " you can store. File reading stopped." << endl;
            break;
        }

        istringstream iss(line);
        string lastName;
        string firstName;
        string experience, age;
        string salary;
        string gender;

        if (getline(iss, lastName, ',') &&
            getline(iss, firstName, ',') &&
            getline(iss, experience, ',') &&
            getline(iss, salary, ',') &&
            getline(iss, age, ',') &&
            getline(iss, gender, ','))
        {

            EmployeeValidator employeeValidator;
            Employee readEmployee(lastName, firstName, stoi(experience), stod(salary), stoi(age), gender[0]);

            try {
                if (employeeValidator.isValidEmployee(readEmployee)) {
                    employees[numEmployees] = readEmployee;
                    numEmployees++;
                }
            }
            catch (string error) {
                cerr << "Error: " << error << " (line " << currentReadLine << ")" << endl;
            }
        }
        else {
            cerr << "Error: Invalid format in employees CSV file. (line " << currentReadLine << ")" << endl;
        }

        currentReadLine++;
    }

    file.close();

    /* We do not have a guarantee that in the file, the employees were
       alphabetically sorted or that nobody altered the order of the employees */
    sortEmployees();
}

void EmployeesManager::writeEmployeesToCSV() {
    writeEmployeesToCSV(employeesFileName);
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
            << employees[i].gender << '\n';
    }

    file.close();
}

void EmployeesManager::displayAllEmployees() {
    cout << endl;
    for (int i = 0; i < numEmployees; i++) {
        employees[i].display();
        cout << endl;
    }
}

void EmployeesManager::searchEmployeeByName() {
    /* It seems that we need to clear the cin buffer (with cin.ignore()) for the first field only, after the cout
       was done. If we try to clear it for subsequent getline() calls, it will remove the first character entered. */
    cin.ignore();
    string lastName = readEmployeeField("Enter last name: ", EMPLOYEE_LAST_NAME);
    string firstName = readEmployeeField("Enter first name: ", EMPLOYEE_FIRST_NAME);
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
    if (numEmployees < maxEmployees) {
        Employee newEmployee;

        cin.ignore();
        newEmployee.lastName = readEmployeeField("Enter last name: ", EMPLOYEE_LAST_NAME);
        newEmployee.firstName = readEmployeeField("Enter first name: ", EMPLOYEE_FIRST_NAME);
        newEmployee.experience = stoi(readEmployeeField("Enter experience (years): ", EMPLOYEE_EXPERIENCE));
        newEmployee.salary = stod(readEmployeeField("Enter salary: ", EMPLOYEE_SALARY));
        newEmployee.age = stoi(readEmployeeField("Enter age: ", EMPLOYEE_AGE));
        newEmployee.gender = readEmployeeField("Enter gender (M/F): ", EMPLOYEE_GENDER)[0];

        // Insert employee by taking into consideration alphabetic ordering by name

        bool foundEmployeeInsertPosition = false;
        for (int i = 0; i < numEmployees; i++) {
          if (employees[i].lastName.compare(newEmployee.lastName) >= 0) {
            for (int j = numEmployees + 1; j > i; j--) {
              employees[j] = employees[j - 1];
            }

            employees[i] = newEmployee;
            foundEmployeeInsertPosition = true;
            break;
          }
        }

        if (!foundEmployeeInsertPosition) {
            employees[numEmployees] = newEmployee;
        }

        numEmployees++;
        
        writeEmployeesToCSV();
    }
    else {
        cerr << "Error: You reached the maximum of " << maxEmployees << " you can store." << endl;
    }
}

void EmployeesManager::updateEmployee() {
    cin.ignore();
    string lastNameToSearchFor = readEmployeeField("Enter last name: ", EMPLOYEE_LAST_NAME);
    string firstNameToSearchFor = readEmployeeField("Enter first name: ", EMPLOYEE_FIRST_NAME);

    bool found = false;
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].lastName == lastNameToSearchFor && employees[i].firstName == firstNameToSearchFor) {
            found = true;
            cout << "Current details of the employee:\n";
            employees[i].display();

            cout << "Enter new details for the employee (leave empty to keep current value):\n";

            string lastName = readEmployeeField("Enter last name: ", EMPLOYEE_LAST_NAME, true);
            employees[i].lastName = lastName == "" ? employees[i].lastName : lastName;

            string firstName = readEmployeeField("Enter first name: ", EMPLOYEE_FIRST_NAME, true);
            employees[i].firstName = firstName == "" ? employees[i].firstName : firstName;

            string experience = readEmployeeField("Enter experience (years): ", EMPLOYEE_EXPERIENCE, true);
            employees[i].experience = experience == "" ? employees[i].experience : stoi(experience);

            string salary = readEmployeeField("Enter salary: ", EMPLOYEE_SALARY, true);
            employees[i].salary = salary == "" ? employees[i].salary : stod(salary);

            string age = readEmployeeField("Enter age: ", EMPLOYEE_AGE, true);
            employees[i].age = age == "" ? employees[i].age : stoi(age);

            string gender = readEmployeeField("Enter gender (M/F): ", EMPLOYEE_GENDER, true);
            employees[i].gender = gender == "" ? employees[i].gender : gender[0];

            cout << "Employee details updated successfully.\n";
            sortEmployees();
            writeEmployeesToCSV();
            break;
        }
    }

    if (!found) {
        cout << "Employee with name " << lastNameToSearchFor << " " << firstNameToSearchFor << " not found.\n";
    }
}

void EmployeesManager::deleteEmployee() {
    cin.ignore();
    string lastName = readEmployeeField("Enter last name: ", EMPLOYEE_LAST_NAME);
    string firstName = readEmployeeField("Enter first name: ", EMPLOYEE_FIRST_NAME);

    bool found = false;
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].lastName == lastName && employees[i].firstName == firstName) {
            for (int j = i; j < numEmployees - 1; j++) {
                employees[j] = employees[j + 1];
            }
            numEmployees--;
            found = true;
            cout << "Employee " << lastName << " " << firstName << " has been deleted." << endl;
            writeEmployeesToCSV();
            break;
        }
    }

    if (!found) {
        cout << "Employee with name " << lastName << " " << firstName << " not found." << endl;
    }
}

void EmployeesManager::sortEmployees() {
    sort(employees, employees + numEmployees, [](Employee& a, Employee& b) {
        return a.lastName < b.lastName;
    });
}

string EmployeesManager::readEmployeeField(string message, EmployeeFieldToValidate fieldToValidate) {
    return readEmployeeField(message, fieldToValidate, false);
}

string EmployeesManager::readEmployeeField(string message, EmployeeFieldToValidate fieldToValidate, bool allowEmptyField) {
    EmployeeValidator employeeValidator;
    string input;
    bool isFieldValid = false;

    while (!isFieldValid) {
        cout << message;
        getline(cin, input);

        // There might be cases when we allow empty fields, like when we want to update employees
        if (!input.empty()) {
            try {
                switch (fieldToValidate) {
                case EMPLOYEE_LAST_NAME:
                    isFieldValid = employeeValidator.isValidLastName(input);
                    break;
                case EMPLOYEE_FIRST_NAME:
                    isFieldValid = employeeValidator.isValidFirstName(input);
                    break;
                case EMPLOYEE_EXPERIENCE:
                    isFieldValid = employeeValidator.isValidExperience(stoi(input));
                    break;
                case EMPLOYEE_SALARY:
                    isFieldValid = employeeValidator.isValidSalary(stod(input));
                    break;
                case EMPLOYEE_AGE:
                    isFieldValid = employeeValidator.isValidAge(stoi(input));
                    break;
                case EMPLOYEE_GENDER:
                    isFieldValid = employeeValidator.isValidGender(input);
                    break;
                }
            }
            catch (string error) {
                cerr << error << endl;
            }

            if (isFieldValid) {
                return input;
            }
        }
        else {
            isFieldValid = allowEmptyField;
        }
    }

    return "";
}