//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "employees.h"
#include "menu.h"
#include "item.h"
#include "customer.h"
#include "purchases.h"

int main() {
    // Check if the employees file exists; if not, create the default admin.
    if (!checkIfEmployeeFileExists()) {
        createDefaultAdmin();
    }
    // Load data:
    loadItems();    // Items are loaded from the binary file "items.dat".
    loadCustomers();// Customers are loaded from the text file "customers.txt".
    loadPurchases();// Purchases are loaded from the text file "purchases.txt".
    Employee currentEmployee = login();
    showMenu(currentEmployee.level);// Display the main menu based on the employee's authorization level.
    printf("Goodbye!\n");
    return 0;
}
