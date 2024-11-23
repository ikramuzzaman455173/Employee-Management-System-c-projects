#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define the maximum number of employees
#define MAX_EMPLOYEES 100

// Structure to store employee information
struct Employee {
    int id;
    char name[50];
    double salary;
    double bonus;
    double attendance;
    double net_salary;
};

// Function to clear input buffer in case of invalid input
void clearBuffer() {
    while (getchar() != '\n');
}

// Function to input employee details with proper error handling
void inputEmployee(struct Employee* employee) {
    printf("Enter Employee ID: ");
    if (scanf("%d", &employee->id) != 1) {
        printf("Error: Invalid ID format. Please enter a valid integer ID.\n");
        clearBuffer();
        return;
    }

    clearBuffer();  // Clear the buffer before reading a string

    printf("Enter Employee Name: ");
    if (fgets(employee->name, sizeof(employee->name), stdin) == NULL) {
        printf("Error: Failed to read employee name.\n");
        return;
    }
    employee->name[strcspn(employee->name, "\n")] = '\0';  // Remove the newline character

    printf("Enter Employee Salary: ");
    if (scanf("%lf", &employee->salary) != 1 || employee->salary < 0) {
        printf("Error: Invalid salary input. Please enter a valid positive number.\n");
        clearBuffer();
        return;
    }

    printf("Enter Employee Bonus: ");
    if (scanf("%lf", &employee->bonus) != 1 || employee->bonus < 0) {
        printf("Error: Invalid bonus input. Please enter a valid positive number.\n");
        clearBuffer();
        return;
    }

    printf("Enter Attendance (0 - 1 scale): ");
    if (scanf("%lf", &employee->attendance) != 1 || employee->attendance < 0 || employee->attendance > 1) {
        printf("Error: Invalid attendance input. Please enter a value between 0 and 1.\n");
        clearBuffer();
        return;
    }

    // Calculate net salary
    employee->net_salary = employee->salary + employee->bonus;
}

// Function to display employee details
void displayEmployee(struct Employee* employee) {
    printf("\nEmployee ID: %d\n", employee->id);
    printf("Employee Name: %s\n", employee->name);
    printf("Salary: %.2f\n", employee->salary);
    printf("Bonus: %.2f\n", employee->bonus);
    printf("Attendance: %.2f\n", employee->attendance);
    printf("Net Salary: %.2f\n", employee->net_salary);
}

// Function to sort employees by salary in ascending order
void sortEmployees(struct Employee* employees, int count) {
    if (count <= 1) {
        printf("Error: Insufficient employees to sort.\n");
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (employees[i].salary > employees[j].salary) {
                struct Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
    printf("Employees sorted by salary.\n");
}

// Function to apply a bonus to all employees
void applyBonus(struct Employee* employees, int count) {
    if (count == 0) {
        printf("Error: No employees to apply bonus to.\n");
        return;
    }

    double bonusPercentage;
    printf("Enter bonus percentage: ");
    if (scanf("%lf", &bonusPercentage) != 1 || bonusPercentage < 0) {
        printf("Error: Invalid bonus percentage. Please enter a valid number.\n");
        clearBuffer();
        return;
    }

    for (int i = 0; i < count; i++) {
        employees[i].bonus += employees[i].salary * (bonusPercentage / 100);
        employees[i].net_salary = employees[i].salary + employees[i].bonus;  // Recalculate net salary
    }

    printf("Bonus applied to all employees.\n");
}

// Function to mark employee attendance
void markAttendance(struct Employee* employees, int count) {
    if (count == 0) {
        printf("Error: No employees to mark attendance for.\n");
        return;
    }

    int id;
    printf("Enter Employee ID to mark attendance: ");
    if (scanf("%d", &id) != 1) {
        printf("Error: Invalid ID format.\n");
        clearBuffer();
        return;
    }

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            printf("Mark attendance (1 for present, 0 for absent): ");
            if (scanf("%lf", &employees[i].attendance) != 1 || (employees[i].attendance != 0 && employees[i].attendance != 1)) {
                printf("Error: Invalid attendance input. Please enter 1 for present or 0 for absent.\n");
                clearBuffer();
                return;
            }
            printf("Attendance for %s marked successfully.\n", employees[i].name);
            return;
        }
    }
    printf("Error: Employee with ID %d not found.\n", id);
}

// Function to generate a salary statement for all employees
void generateSalaryStatement(struct Employee* employees, int count) {
    if (count == 0) {
        printf("Error: No employees to generate salary statement for.\n");
        return;
    }

    printf("\nSalary Statement:\n");
    for (int i = 0; i < count; i++) {
        printf("Employee ID: %d, Name: %s, Salary: %.2f, Bonus: %.2f, Net Salary: %.2f\n",
               employees[i].id, employees[i].name, employees[i].salary, employees[i].bonus, employees[i].net_salary);
    }
}

// Function to generate a report
void generateReport(struct Employee* employees, int count) {
    if (count == 0) {
        printf("Error: No employees to generate report for.\n");
        return;
    }

    double totalPayroll = 0, highestSalary = employees[0].net_salary, lowestSalary = employees[0].net_salary;

    for (int i = 0; i < count; i++) {
        totalPayroll += employees[i].net_salary;
        if (employees[i].net_salary > highestSalary) highestSalary = employees[i].net_salary;
        if (employees[i].net_salary < lowestSalary) lowestSalary = employees[i].net_salary;
    }

    printf("\nEmployee Report:\n");
    printf("Total Employees: %d\n", count);
    printf("Total Payroll: %.2f\n", totalPayroll);
    printf("Highest Salary: %.2f\n", highestSalary);
    printf("Lowest Salary: %.2f\n", lowestSalary);
}

// Function to search an employee by ID or Name
void searchEmployee(struct Employee* employees, int count) {
    int choice;
    printf("Search Employee by:\n");
    printf("1. Employee ID\n");
    printf("2. Employee Name\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Error: Invalid input. Please enter a valid number.\n");
        clearBuffer();
        return;
    }

    if (choice == 1) {
        int id;
        printf("Enter Employee ID: ");
        if (scanf("%d", &id) != 1) {
            printf("Error: Invalid ID input. Please enter a valid integer.\n");
            clearBuffer();
            return;
        }

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (employees[i].id == id) {
                displayEmployee(&employees[i]);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Error: No employee found with ID %d.\n", id);
        }
    } else if (choice == 2) {
        char name[50];
        printf("Enter Employee Name: ");
        clearBuffer();
        if (fgets(name, sizeof(name), stdin) == NULL) {
            printf("Error: Failed to read employee name.\n");
            return;
        }
        name[strcspn(name, "\n")] = 0;  // Remove newline character

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(employees[i].name, name) == 0) {
                displayEmployee(&employees[i]);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Error: No employee found with name %s.\n", name);
        }
    } else {
        printf("Error: Invalid choice! Please enter 1 or 2.\n");
    }
}

int main() {
    struct Employee employees[MAX_EMPLOYEES];
    int count = 0;
    int choice;

    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Input Employee Details\n");
        printf("2. Display Employee Details\n");
        printf("3. Sort Employees\n");
        printf("4. Apply Bonus to Employees\n");
        printf("5. Mark Employee Attendance\n");
        printf("6. Generate Salary Statement\n");
        printf("7. Generate Report\n");
        printf("8. Search Employee\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid input! Please enter a valid number.\n");
            clearBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                if (count < MAX_EMPLOYEES) {
                    inputEmployee(&employees[count]);
                    count++;
                } else {
                    printf("Error: Maximum employee limit reached.\n");
                }
                break;
            case 2:
                if (count > 0) {
                    for (int i = 0; i < count; i++) {
                        displayEmployee(&employees[i]);
                    }
                } else {
                    printf("Error: No employee data available.\n");
                }
                break;
            case 3:
                sortEmployees(employees, count);
                break;
            case 4:
                applyBonus(employees, count);
                break;
            case 5:
                markAttendance(employees, count);
                break;
            case 6:
                generateSalaryStatement(employees, count);
                break;
            case 7:
                generateReport(employees, count);
                break;
            case 8:
                searchEmployee(employees, count);
                break;
            case 9:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Error: Invalid choice. Please enter a number between 1 and 9.\n");
        }
    }
}
