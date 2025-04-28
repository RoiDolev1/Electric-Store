//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "employees.h"
#include "item.h"
#include "customer.h"
#include "purchases.h"

//
// Modified sellProduct(): Limits total items purchased per transaction to 3 items
// (regardless of product type). The customer is first asked for the total number
// of items (max 3) and then prompted to enter each product's PN and quantity
// until the total quantity is reached.
//
void sellProduct() {
    printf("\n--- SELL PRODUCT ---\n");
    char customerName[30];
    printf("Enter existing customer name (or 'new' to add one): ");
    scanf("%s", customerName);
    if (strcmp(customerName, "new") == 0) {
        addCustomer();
        printf("Enter the new customer's name again: ");
        scanf("%s", customerName);
    }
    int totalQty;
    printf("Enter total number of items to purchase (max 3): ");
    scanf("%d", &totalQty);
    if (totalQty < 1 || totalQty > 3) {
        printf("You can only purchase up to 3 items per transaction.\n");
        return;
    }
    int sum = 0;
    while (sum < totalQty) {
        char PN[20];
        int qty;
        printf("Enter product number (P/N): ");
        scanf("%s", PN);
        printf("Enter quantity for this product (remaining %d): ", totalQty - sum);
        scanf("%d", &qty);
        if (qty < 1 || (sum + qty) > totalQty) {
            printf("Invalid quantity. You can only purchase %d more item(s).\n", totalQty - sum);
            continue;
        }
        ItemNode* node = findItemNodeByPN(PN);
        if (node == NULL) {
            printf("Item with P/N=%s not found!\n", PN);
            continue;
        }
        if (!node->data.inStock || node->data.inventory < qty) {
            printf("Not enough stock for product %s.\n", PN);
            continue;
        }
        recordPurchase(customerName, PN, qty, node->data.price);
        printf("Purchased %d of product [P/N=%s].\n", qty, PN);
        sum += qty;
    }
    printf("Sale completed.\n");
}

// Displays the main menu and processes user choices. Also prints the store title
void showMenu(unsigned int employeeLevel) {
    loadPurchases();
    int choice;
    do {
        printf(" _           _          _        _           _                       _                 \n");
        printf("(_)___  __ _| |__   ___| |   ___| | ___  ___| |_ _ __ ___        ___| |_ ___  _ __ ___ \n");
        printf("| / __|/ _` | '_ \\ / _ \\ |  / _ \\ |/ _ \\/ __| __| '__/ _ \\ _____/ __| __/ _ \\| '__/ _ \\\n");
        printf("| \\__ \\ (_| | |_) |  __/ | |  __/ |  __/ (__| |_| | | (_) |_____\\__ \\ || (_) | | |  __/\n");
        printf("|_|___/\\__,_|_.__/ \\___|_|  \\___|_|\\___|\\___|\\__|_|  \\___/      |___/\\__\\___/|_|  \\___|\n");
        printf("                                                                                        \n");

        printf("\n--- MAIN MENU (Level %u) ---\n", employeeLevel);
        printf("1. List Items\n");
        printf("2. Add Item\n");
        if (employeeLevel <= 2) {
            printf("3. Remove Item\n");
            printf("4. Update Item\n");
            printf("5. Sell Product\n");
        }
        printf("6. Add Customer\n");
        printf("7. List Customers\n");
        if (employeeLevel == 1) {
            printf("8. Add Employee\n");
        }
        printf("9. Search Items\n");
        printf("10. View Customer Purchase History\n");
        printf("11. Return Product\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            listItems();
            break;
        case 2:
            addItem();
            break;
        case 3:
            if (employeeLevel <= 2)
                removeItem();
            else
                printf("No permission.\n");
            break;
        case 4:
            if (employeeLevel <= 2)
                updateItem();
            else
                printf("No permission.\n");
            break;
        case 5:
            if (employeeLevel <= 2)
                sellProduct();
            else
                printf("No permission.\n");
            break;
        case 6:
            addCustomer();
            break;
        case 7:
            listCustomers();
            break;
        case 8:
            if (employeeLevel == 1)
                addEmployee();
            else
                printf("No permission.\n");
            break;
        case 9:
            searchItems();
            break;
        case 10: {
            char name[30];
            printf("Enter customer name: ");
            scanf("%s", name);
            listPurchasesByCustomer(name);
            break;
        }
        case 11: {
            char name[30];
            char PN[20];
            printf("Enter customer name: ");
            scanf("%s", name);
            printf("Enter product number (P/N) to return: ");
            scanf("%s", PN);
            int succ = returnProduct(name, PN);
            if (succ)
                printf("Return successful.\n");
            else
                printf("Return not possible (not found or >14 days).\n");
            break;
        }
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 0);
}
