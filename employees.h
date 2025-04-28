//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#pragma once 

// Employee structure definition.
typedef struct employee {
    char username[20];    // Username for login
    char firstname[10];   // Employee's first name
    char password[10];    // Password for login
    unsigned int level;   // Authorization level: 1 = admin, 2 = employee, 3 = trainee
} Employee;

// Function declarations for employee operations.
int checkIfEmployeeFileExists();
void createDefaultAdmin();
Employee login();
void addEmployee();
