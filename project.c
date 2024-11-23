#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for employee
struct Employee {
    int id;
    char name[50];
    char designation[50];
    float basic_salary;
    float hra;
    float da;
    float pf;
    float gross_salary;
    float net_salary;
};

// Function prototypes
void loadEmployees(struct Employee** employees, int* count);
void saveEmployees(struct Employee* employees, int count);
void addEmployee(struct Employee** employees, int* count);
void displayEmployees(struct Employee* employees, int count);
void searchEmployeeByID(struct Employee* employees, int count);
void searchEmployeeByName(struct Employee* employees, int count);
void updateEmployee(struct Employee* employees, int count);
void deleteEmployee(struct Employee** employees, int* count);
void calculateSalary(struct Employee* emp);
void clearBuffer();

int main() {
    struct Employee* employees = NULL; // Dynamic array
    int count = 0;
    int choice;

    // Load existing employees from file
    loadEmployees(&employees, &count);

    while (1) {
        printf("\nEmployee Payroll System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Search Employee by Name\n");
        printf("5. Update Employee\n");
        printf("6. Delete Employee\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(&employees, &count);
                break;
            case 2:
                displayEmployees(employees, count);
                break;
            case 3:
                searchEmployeeByID(employees, count);
                break;
            case 4:
                searchEmployeeByName(employees, count);
                break;
            case 5:
                updateEmployee(employees, count);
                break;
            case 6:
                deleteEmployee(&employees, &count);
                break;
            case 7:
                saveEmployees(employees, count);
                free(employees);
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to load employees from a file
void loadEmployees(struct Employee** employees, int* count) {
    FILE* file = fopen("employees.dat", "rb");
    if (file) {
        fread(count, sizeof(int), 1, file);
        *employees = (struct Employee*)malloc((*count) * sizeof(struct Employee));
        fread(*employees, sizeof(struct Employee), *count, file);
        fclose(file);
        printf("Loaded %d employee(s) from storage.\n", *count);
    } else {
        *employees = NULL;
        *count = 0;
    }
}

// Function to save employees to a file
void saveEmployees(struct Employee* employees, int count) {
    FILE* file = fopen("employees.dat", "wb");
    if (file) {
        fwrite(&count, sizeof(int), 1, file);
        fwrite(employees, sizeof(struct Employee), count, file);
        fclose(file);
        printf("Employees saved successfully.\n");
    } else {
        printf("Error saving employee data.\n");
    }
}

// Function to add a new employee
void addEmployee(struct Employee** employees, int* count) {
    int id;
    printf("Enter Employee ID: ");
    scanf("%d", &id);
    for (int i = 0; i < *count; i++) {
        if ((*employees)[i].id == id) {
            printf("Employee with ID %d already exists!\n", id);
            return;
        }
    }

    *employees = realloc(*employees, (*count + 1) * sizeof(struct Employee));
    (*employees)[*count].id = id;

    clearBuffer(); // Clear input buffer
    printf("Enter Employee Name: ");
    fgets((*employees)[*count].name, sizeof((*employees)[*count].name), stdin);
    (*employees)[*count].name[strcspn((*employees)[*count].name, "\n")] = 0;

    printf("Enter Employee Designation: ");
    fgets((*employees)[*count].designation, sizeof((*employees)[*count].designation), stdin);
    (*employees)[*count].designation[strcspn((*employees)[*count].designation, "\n")] = 0;

    printf("Enter Basic Salary: ");
    scanf("%f", &(*employees)[*count].basic_salary);

    // Calculate salary components
    calculateSalary(&(*employees)[*count]);

    (*count)++;
    printf("Employee added successfully!\n");
}

// Function to calculate salary components
void calculateSalary(struct Employee* emp) {
    emp->hra = emp->basic_salary * 0.2;
    emp->da = emp->basic_salary * 0.1;
    emp->pf = emp->basic_salary * 0.05;
    emp->gross_salary = emp->basic_salary + emp->hra + emp->da;
    emp->net_salary = emp->gross_salary - emp->pf;
}

// Function to display all employees
void displayEmployees(struct Employee* employees, int count) {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\n------------------- Employee %d -------------------\n", i + 1);
        printf("Employee ID: %d\n", employees[i].id);
        printf("Name: %s\n", employees[i].name);
        printf("Designation: %s\n", employees[i].designation);
        printf("Basic Salary: %.2f\n", employees[i].basic_salary);
        printf("HRA: %.2f\n", employees[i].hra);
        printf("DA: %.2f\n", employees[i].da);
        printf("PF: %.2f\n", employees[i].pf);
        printf("Gross Salary: %.2f\n", employees[i].gross_salary);
        printf("Net Salary: %.2f\n", employees[i].net_salary);
    }
}

// Function to search employee by ID
void searchEmployeeByID(struct Employee* employees, int count) {
    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            printf("\nEmployee ID: %d\n", employees[i].id);
            printf("Name: %s\n", employees[i].name);
            printf("Designation: %s\n", employees[i].designation);
            printf("Basic Salary: %.2f\n", employees[i].basic_salary);
            printf("HRA: %.2f\n", employees[i].hra);
            printf("DA: %.2f\n", employees[i].da);
            printf("PF: %.2f\n", employees[i].pf);
            printf("Gross Salary: %.2f\n", employees[i].gross_salary);
            printf("Net Salary: %.2f\n", employees[i].net_salary);
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

// Function to search employee by name
void searchEmployeeByName(struct Employee* employees, int count) {
    char name[50];
    clearBuffer();
    printf("Enter Employee Name to search: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(employees[i].name, name)) {
            printf("\nEmployee ID: %d\n", employees[i].id);
            printf("Name: %s\n", employees[i].name);
            printf("Designation: %s\n", employees[i].designation);
            printf("Basic Salary: %.2f\n", employees[i].basic_salary);
            printf("HRA: %.2f\n", employees[i].hra);
            printf("DA: %.2f\n", employees[i].da);
            printf("PF: %.2f\n", employees[i].pf);
            printf("Gross Salary: %.2f\n", employees[i].gross_salary);
            printf("Net Salary: %.2f\n", employees[i].net_salary);
            found = 1;
        }
    }
    if (!found) {
        printf("No employee found with name containing \"%s\".\n", name);
    }
}

// Function to update employee details
void updateEmployee(struct Employee* employees, int count) {
    int id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            clearBuffer();
            printf("Enter New Name: ");
            fgets(employees[i].name, sizeof(employees[i].name), stdin);
            employees[i].name[strcspn(employees[i].name, "\n")] = 0;

            printf("Enter New Designation: ");
            fgets(employees[i].designation, sizeof(employees[i].designation), stdin);
            employees[i].designation[strcspn(employees[i].designation, "\n")] = 0;

            printf("Enter New Basic Salary: ");
            scanf("%f", &employees[i].basic_salary);

            calculateSalary(&employees[i]);
            printf("Employee updated successfully!\n");
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

// Function to delete an employee
void deleteEmployee(struct Employee** employees, int* count) {
    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if ((*employees)[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                (*employees)[j] = (*employees)[j + 1];
            }
            *employees = realloc(*employees, (*count - 1) * sizeof(struct Employee));
            (*count)--;
            printf("Employee deleted successfully!\n");
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

// Function to clear input buffer
void clearBuffer() {
    while (getchar() != '\n');
}