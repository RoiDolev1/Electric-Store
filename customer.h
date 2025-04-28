//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#pragma once 

// Customer structure definition.
typedef struct customer {
    char name[30];       // Customer's name
    char joinDate[20];   // Join date/time (automatically set, format "YYYY-MM-DD HH:MM:SS")
    float totalSpent;    // Total amount spent by the customer
} Customer;

#define MAX_CUSTOMERS 100  // Maximum number of customers

// Declaration of the customers array.
extern Customer customersArray[MAX_CUSTOMERS];  // customers array
extern int customersCount;                      // Number of customers stored

// Function declarations for customer operations.
void loadCustomers();
void saveCustomers();
void addCustomer();
void listCustomers();
int findCustomerIndexByName(char* name);
