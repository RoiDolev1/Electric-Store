//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "utils.h"

Customer customersArray[MAX_CUSTOMERS];  // Define the customers array.
int customersCount = 0;                  // Initialize customer count to 0

// Sorts the customers array by joinDate (Since joinDate is in "YYYY-MM-DD HH:MM:SS" format, lexicographical order works.)
void sortCustomersByDate() {
    int i, j;
    for (i = 0; i < customersCount - 1; i++) {
        for (j = i + 1; j < customersCount; j++) {
            if (strcmp(customersArray[i].joinDate, customersArray[j].joinDate) > 0) {
                Customer temp = customersArray[i];
                customersArray[i] = customersArray[j];
                customersArray[j] = temp;
            }
        }
    }
}

// Finds the index of a customer by name. Complexity: O(n)
int findCustomerIndexByName(char* name) {
    int i;
    for (i = 0; i < customersCount; i++) {
        if (strcmp(customersArray[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Loads customers from the text file "customers.txt".
void loadCustomers() {
    customersCount = 0;
    FILE* file = fopen("customers.txt", "r");  // Open in text mode.
    if (!file) {
        return;
    }
    while (!feof(file) && customersCount < MAX_CUSTOMERS) {
        Customer c;
        if (fscanf(file, "%s %s %f", c.name, c.joinDate, &c.totalSpent) == 3) {
            customersArray[customersCount++] = c;
        }
    }
    fclose(file);
    sortCustomersByDate();
}

// Saves the customers array to the text file "customers.txt".
void saveCustomers() {
    sortCustomersByDate();
    FILE* file = fopen("customers.txt", "w");
    if (!file) {
        printf("Error opening customers file for writing!\n");
        return;
    }
    int i;
    for (i = 0; i < customersCount; i++) {
        fprintf(file, "%s %s %.2f\n",
            customersArray[i].name,
            customersArray[i].joinDate,
            customersArray[i].totalSpent);
    }
    fclose(file);
}

// Adds a new customer. Automatically sets the join date/time using getCurrentDate() from utils.
void addCustomer() {
    if (customersCount >= MAX_CUSTOMERS) {
        printf("Cannot add more customers. Array is full.\n");
        return;
    }
    printf("\n--- ADD CUSTOMER ---\n");
    Customer newCust;
    printf("Enter customer name: ");
    scanf("%s", newCust.name);
    if (findCustomerIndexByName(newCust.name) != -1) {
        printf("ERROR: Customer already exists.\n");
        return;
    }
    // Automatically capture current date/time.
    getCurrentDate(newCust.joinDate);
    newCust.totalSpent = 0.0f;
    customersArray[customersCount++] = newCust;
    saveCustomers();
    char msg[100];
    sprintf(msg, "Added customer [%s]", newCust.name);
    logAction(msg);
    printf("Customer added successfully!\n");
}

// Lists all customers.
void listCustomers() {
    int i;
    printf("\n--- LIST OF CUSTOMERS ---\n");
    for (i = 0; i < customersCount; i++) {
        printf("Name: %s | Join Date: %s | Total Spent: %.2f\n",
            customersArray[i].name,
            customersArray[i].joinDate,
            customersArray[i].totalSpent);
    }
}
