# Employee Management System

## Overview

The Employee Management System is a C-based console application designed to manage employee data. It allows users to input, update, and retrieve employee information, calculate salaries, apply bonuses, and generate reports. This system is intended for small to medium-sized organizations and provides a simple interface to handle employee records efficiently.

## Features

- **Employee Details Input**: Users can input employee information including ID, name, salary, bonus, and attendance.
- **Display Employee Information**: The program displays employee details, including calculated net salary.
- **Sort Employees by Salary**: Employees can be sorted by their salary in ascending order.
- **Apply Bonus to Employees**: A bonus percentage can be applied to all employees.
- **Mark Employee Attendance**: Attendance can be marked for each employee.
- **Generate Salary Statement**: A salary statement is generated for all employees, showing their individual net salary.
- **Generate Employee Report**: Generates a report with total payroll, highest salary, and lowest salary.
- **Search Employees by ID or Name**: Users can search for employees by either their ID or name.

## Requirements

- **C Compiler** (e.g., GCC or Clang)
- **Operating System**: Windows, macOS, or Linux

## Setup Instructions

### 1. Clone the repository or download the code.

```bash
git clone https://github.com/yourusername/employee-management-system.git
cd employee-management-system
```

### 2. Compile the code.

Using GCC (or another C compiler), compile the `main.c` file:

```bash
gcc main.c -o employee_management
```

### 3. Run the application.

To run the compiled program, simply execute:

```bash
./employee_management
```

## Usage

Upon running the program, you will be presented with a menu to select different operations. Here’s a description of each option:

1. **Input Employee Details**:
   - Allows the user to enter details for a new employee, such as ID, name, salary, bonus, and attendance.

2. **Display Employee Details**:
   - Displays a list of all employees entered into the system, including their ID, name, salary, bonus, attendance, and net salary.

3. **Sort Employees by Salary**:
   - Sorts all employees in ascending order based on their salary.

4. **Apply Bonus to Employees**:
   - Prompts for a bonus percentage and applies it to all employees.

5. **Mark Employee Attendance**:
   - Allows the user to mark attendance for a specific employee by their ID.

6. **Generate Salary Statement**:
   - Displays a summary of salaries for all employees, including individual net salaries.

7. **Generate Employee Report**:
   - Generates a report with total payroll, highest salary, and lowest salary.

8. **Search Employee**:
   - Allows the user to search for an employee either by their ID or by their name.

9. **Exit**:
   - Exits the program.

## Functions Breakdown

### 1. `inputEmployee`
   - Inputs employee details including ID, name, salary, bonus, and attendance.
   - Calculates the net salary by adding the salary and bonus.

### 2. `displayEmployee`
   - Displays the information for a specific employee, including their calculated net salary.

### 3. `sortEmployees`
   - Sorts the list of employees based on their salary in ascending order.

### 4. `applyBonus`
   - Applies a percentage-based bonus to all employees.

### 5. `markAttendance`
   - Marks attendance (0 or 1) for an employee identified by their ID.

### 6. `generateSalaryStatement`
   - Generates a statement showing the salary and bonus of each employee.

### 7. `generateReport`
   - Generates a summary report, including total payroll, highest and lowest salaries, and total number of employees.

### 8. `searchEmployee`
   - Allows the user to search for an employee by either ID or name.

## Example

Here’s an example of what the interaction might look like when running the program:

```
Employee Management System
1. Input Employee Details
2. Display Employee Details
3. Sort Employees
4. Apply Bonus to Employees
5. Mark Employee Attendance
6. Generate Salary Statement
7. Generate Report
8. Search Employee
9. Exit
Enter your choice: 1
Enter Employee ID: 101
Enter Employee Name: John Doe
Enter Employee Salary: 5000
Enter Employee Bonus: 500
Enter Attendance (0 - 1 scale): 1
Employee ID: 101
Employee Name: John Doe
Salary: 5000.00
Bonus: 500.00
Attendance: 1.00
Net Salary: 5500.00
```

## Error Handling

The application includes comprehensive error handling for invalid inputs:

- **Invalid Data Entry**: The program checks for proper data types (integer for IDs, double for salary and bonus).
- **Boundary Validation**: Ensures that salary, bonus, and attendance values are within acceptable ranges (e.g., salary and bonus cannot be negative, attendance must be between 0 and 1).
- **Search Failures**: Provides meaningful messages when no employee is found with the given ID or name.

## Contributing

If you'd like to contribute to this project, feel free to fork the repository, make improvements, and submit a pull request. Contributions are welcome!

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.