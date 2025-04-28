//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employees.h"
#include "utils.h"

#define EMPLOYEES_FILE "employees.txt"  // Text file storing employee records

// Checks if the employees file exists.
int checkIfEmployeeFileExists() {
    FILE* file = fopen(EMPLOYEES_FILE, "r");  // Open for reading
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// Creates a default admin record in the employees file.
void createDefaultAdmin() {
    FILE* file = fopen(EMPLOYEES_FILE, "w");  // Open for writing (text mode)
    if (!file) {
        printf("Error creating employees file!\n");
        return;
    }
    // Write the default admin record.
    fprintf(file, "admin manager 12345678 1\n");
    fclose(file);
    logAction("Created default admin [username=admin]");
}

// Login function with up to 3 attempts.
Employee login() {
    Employee loggedIn = { "", "", "", 0 };
    int attempts = 0;
    int found = 0;
    while (attempts < 3 && !found) {
        char username[20];
        char password[20];
        printf("\n--- LOGIN ---\n");
        printf("Username: ");
        scanf("%s", username);  // Read username
        printf("Password: ");
        scanf("%s", password);  // Read password

        FILE* file = fopen(EMPLOYEES_FILE, "r");
        if (!file) {
            printf("Could not open employees file!\n");
            exit(1);
        }
        Employee temp;
        // Loop through each employee record.
        while (fscanf(file, "%s %s %s %u", temp.username, temp.firstname, temp.password, &temp.level) == 4) {
            if (strcmp(temp.username, username) == 0 &&
                strcmp(temp.password, password) == 0)
            {
                loggedIn = temp;
                found = 1;
                break;
            }
        }
        fclose(file);
        if (!found) {
            attempts++;
            if (attempts < 3)
                printf("Invalid credentials. Please try again.\n");
        }
    }
    if (!found) {
        printf("Too many login attempts. Exiting.\n");
        exit(1);
    }
    // Log the successful login.
    char msg[100];
    sprintf(msg, "User [%s] logged in", loggedIn.username);
    logAction(msg);
    return loggedIn;
}

// Adds a new employee (admin-only).
void addEmployee() {
    printf("\n--- ADD NEW EMPLOYEE ---\n");
    Employee newEmp;
    printf("Enter username: ");
    scanf("%s", newEmp.username);
    // Check for duplicate username.
    FILE* checkFile = fopen(EMPLOYEES_FILE, "r");
    if (checkFile) {
        Employee temp;
        while (fscanf(checkFile, "%s %s %s %u", temp.username, temp.firstname, temp.password, &temp.level) == 4) {
            if (strcmp(temp.username, newEmp.username) == 0) {
                printf("ERROR: Username already exists!\n");
                fclose(checkFile);
                return;
            }
        }
        fclose(checkFile);
    }
    printf("Enter first name: ");
    scanf("%s", newEmp.firstname);
    printf("Enter password: ");
    scanf("%s", newEmp.password);
    printf("Enter level (1=admin, 2=employee, 3=trainee): ");
    scanf("%u", &newEmp.level);
    // Append new employee to the file.
    FILE* file = fopen(EMPLOYEES_FILE, "a");
    if (!file) {
        printf("Error opening employees file for appending!\n");
        return;
    }
    fprintf(file, "%s %s %s %u\n", newEmp.username, newEmp.firstname, newEmp.password, newEmp.level);
    fclose(file);
    char action[100];
    sprintf(action, "Added new employee [username=%s, level=%u]", newEmp.username, newEmp.level);
    logAction(action);
    printf("Employee added successfully!\n");
}
