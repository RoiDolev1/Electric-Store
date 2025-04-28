//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#pragma once

#include <stdbool.h>

// Definition of an item (product).
typedef struct item {
    char PN[20];           // Product Number (unique identifier)
    char product_name[20]; // Product name
    char category[20];     // Product category
    float price;           // Price of the product
    bool inStock;          // True if the item is in stock
    char date[20];         // Date/time when the item was added ("YYYY-MM-DD HH:MM:SS")
    int inventory;         // Inventory count
} Item;

// Node structure for the linked list of items.
typedef struct itemNode {
    Item data;
    struct itemNode* next;
} ItemNode;

// Function declarations for item operations using a linked list.
void loadItems();         // Loads items from "items.dat" into the linked list.
void saveItems();         // Saves the linked list of items into "items.dat".
void addItem();           // Adds a new item via user input.
void listItems();         // Displays all items; if empty, shows "No items found".
void removeItem();        // Removes an item by its product number.
void updateItem();        // Updates an item’s details.
void searchItems();       // Searches for items based on various criteria.

// Helper functions:
ItemNode* findItemNodeByPN(char* PN);  // Finds an item node by product number.
void insertItemSorted(Item newItem);   // Inserts a new item into the linked list in sorted order.
