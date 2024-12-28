#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define FILENAME "employees.dat"

// Structure for Employee
struct Employee {
    int id;
    char name[50];
    double salary;
    int attendance; // 1 for present, 0 for absent
};

// Function prototypes
void saveToFile(struct Employee employees[], int count);
int loadFromFile(struct Employee employees[]);
void addEmployee(struct Employee employees[], int *count);
void displayAllEmployees(struct Employee employees[], int count);
void markAttendance(struct Employee employees[], int count);
void searchEmployee(struct Employee employees[], int count);
void updateEmployee(struct Employee employees[], int count);
void deleteEmployee(struct Employee employees[], int *count);

// Save employees to file
void saveToFile(struct Employee employees[], int count) {
    FILE *file = fopen(FILENAME, "wb");
    if (file) {
        fwrite(&count, sizeof(int), 1, file);
        fwrite(employees, sizeof(struct Employee), count, file);
        fclose(file);
    }
}

// Load employees from file
int loadFromFile(struct Employee employees[]) {
    FILE *file = fopen(FILENAME, "rb");
    int count = 0;
    if (file) {
        fread(&count, sizeof(int), 1, file);
        fread(employees, sizeof(struct Employee), count, file);
        fclose(file);
    }
    return count;
}

// Add a new employee
void addEmployee(struct Employee employees[], int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("Maximum employee limit reached.\n");
        return;
    }

    struct Employee newEmployee;
    printf("Enter Employee ID: ");
    scanf("%d", &newEmployee.id);
    getchar();

    printf("Enter Employee Name: ");
    fgets(newEmployee.name, sizeof(newEmployee.name), stdin);
    newEmployee.name[strcspn(newEmployee.name, "\n")] = '\0';

    printf("Enter Employee Salary: ");
    scanf("%lf", &newEmployee.salary);

    newEmployee.attendance = 0; // Default attendance is absent

    employees[*count] = newEmployee;
    (*count)++;
    saveToFile(employees, *count);
    printf("Employee added successfully.\n");
}

// Display all employees
void displayAllEmployees(struct Employee employees[], int count) {
    if (count == 0) {
        printf("No employees to display.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\nName: %s\nSalary: %.2f\nAttendance: %s\n",
               employees[i].id, employees[i].name, employees[i].salary,
               employees[i].attendance ? "Present" : "Absent");
    }
}

// Mark attendance for an employee
void markAttendance(struct Employee employees[], int count) {
    int id;
    printf("Enter Employee ID to mark attendance: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            employees[i].attendance = 1; // Mark as present
            saveToFile(employees, count);
            printf("Attendance marked for %s.\n", employees[i].name);
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

// Search for an employee by ID
void searchEmployee(struct Employee employees[], int count) {
    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            printf("\nID: %d\nName: %s\nSalary: %.2f\nAttendance: %s\n",
                   employees[i].id, employees[i].name, employees[i].salary,
                   employees[i].attendance ? "Present" : "Absent");
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

// Update an employee's details
void updateEmployee(struct Employee employees[], int count) {
    int id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            printf("Enter new name: ");
            fgets(employees[i].name, sizeof(employees[i].name), stdin);
            employees[i].name[strcspn(employees[i].name, "\n")] = '\0';

            printf("Enter new salary: ");
            scanf("%lf", &employees[i].salary);

            saveToFile(employees, count);
            printf("Employee details updated successfully.\n");
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

// Delete an employee
void deleteEmployee(struct Employee employees[], int *count) {
    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if (employees[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            (*count)--;
            saveToFile(employees, *count);
            printf("Employee deleted successfully.\n");
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

int main() {
    struct Employee employees[MAX_EMPLOYEES];
    int count = loadFromFile(employees);
    int choice;

    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Mark Attendance\n");
        printf("4. Search Employee\n");
        printf("5. Update Employee\n");
        printf("6. Delete Employee\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &count);
                break;
            case 2:
                displayAllEmployees(employees, count);
                break;
            case 3:
                markAttendance(employees, count);
                break;
            case 4:
                searchEmployee(employees, count);
                break;
            case 5:
                updateEmployee(employees, count);
                break;
            case 6:
                deleteEmployee(employees, &count);
                break;
            case 7:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

