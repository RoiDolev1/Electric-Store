//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "purchases.h"
#include "utils.h"
#include "customer.h"
#include "item.h"

Purchase purchasesArray[MAX_PURCHASES];  // Define the purchases array.
int purchasesCount = 0;  // Initialize purchase count to 0

// Loads purchase records from the text file "purchases.txt".
void loadPurchases() {
    purchasesCount = 0;
    FILE* file = fopen("purchases.txt", "r");
    if (!file) {
        return;
    }
    Purchase p;
    while (fscanf(file, "%s %s %19[0-9-: ] %d %f",// Adjusted format specifier to correctly read the entire date string (including spaces).
        p.customerName,
        p.productPN,
        p.purchaseDate,
        &p.quantity,
        &p.priceAtPurchase) == 5) {
        purchasesArray[purchasesCount++] = p;
    }
    fclose(file);
}

// Saves the purchase records to the text file "purchases.txt".
void savePurchases() {
    FILE* file = fopen("purchases.txt", "w");
    if (!file) {
        printf("Error opening purchases file for writing!\n");
        return;
    }
    int i;
    for (i = 0; i < purchasesCount; i++) {
        Purchase* p = &purchasesArray[i];
        fprintf(file, "%s %s %s %d %.2f\n",
            p->customerName, p->productPN, p->purchaseDate, p->quantity, p->priceAtPurchase);
    }
    fclose(file);
}

// Records a new purchase, updates customer spending and item inventory.
void recordPurchase(char* customerName, char* productPN, int quantity, float price) {
    if (purchasesCount >= MAX_PURCHASES) {
        printf("Cannot record more purchases.\n");
        return;
    }
    Purchase newP;
    strcpy(newP.customerName, customerName);
    strcpy(newP.productPN, productPN);
    getCurrentDate(newP.purchaseDate);// Capture the current date/time.
    newP.quantity = quantity;
    newP.priceAtPurchase = price;
    purchasesArray[purchasesCount++] = newP; //adding new purchases
    int cIndex = findCustomerIndexByName(customerName);
    if (cIndex != -1) {
        customersArray[cIndex].totalSpent += (price * quantity);// Update customer's totalSpent.
        saveCustomers();
    }
    // Update item inventory.
    ItemNode* node = findItemNodeByPN(productPN);
    if (node != NULL) {
        node->data.inventory -= quantity;
        if (node->data.inventory < 0)
            node->data.inventory = 0;
        if (node->data.inventory == 0)
            node->data.inStock = false;
        saveItems();
    }
    savePurchases();
    char msg[200];
    sprintf(msg, "Purchase recorded: Customer=%s, P/N=%s, Qty=%d, Price=%.2f",
        customerName, productPN, quantity, price);
    logAction(msg);
}

// Lists all purchase records for a given customer.
void listPurchasesByCustomer(char* customerName) {
    int i;
    printf("\n--- PURCHASES for %s ---\n", customerName);
    int foundAny = 0;
    for (i = 0; i < purchasesCount; i++) {
        Purchase* p = &purchasesArray[i];
        if (strcmp(p->customerName, customerName) == 0) {
            foundAny = 1;
            printf("P/N: %s | Date: %s | Qty: %d | Price: %.2f\n",
                p->productPN, p->purchaseDate, p->quantity, p->priceAtPurchase);
        }
    }
    if (!foundAny) {
        printf("No purchases found.\n");
    }
}

// Processes a return if the purchase was made within 14 days.
// Updates customer spending, restores item inventory, and removes the purchase record.
int returnProduct(char* customerName, char* productPN) {
    int i;
    for (i = 0; i < purchasesCount; i++) {
        Purchase* p = &purchasesArray[i];
        if (strcmp(p->customerName, customerName) == 0 &&
            strcmp(p->productPN, productPN) == 0)
        {
            char today[20];
            getCurrentDate(today);
            int diff = dateDifferenceInDays(p->purchaseDate, today);
            if (diff <= 14) {  // Allow return within 14 days.
                int cIndex = findCustomerIndexByName(customerName);
                if (cIndex != -1) {
                    float cost = p->priceAtPurchase * p->quantity;
                    customersArray[cIndex].totalSpent -= cost;
                    if (customersArray[cIndex].totalSpent < 0)
                        customersArray[cIndex].totalSpent = 0;
                    saveCustomers();
                }
                ItemNode* node = findItemNodeByPN(productPN);
                if (node != NULL) {
                    node->data.inventory += p->quantity;
                    node->data.inStock = true;
                    saveItems();
                }
                // Remove the purchase record.
                int j;
                for (j = i; j < purchasesCount - 1; j++) {
                    purchasesArray[j] = purchasesArray[j + 1];
                }
                purchasesCount--;
                savePurchases();
                char msg[200];
                sprintf(msg, "Return accepted: Customer=%s, P/N=%s", customerName, productPN);
                logAction(msg);
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    return 0;
}
