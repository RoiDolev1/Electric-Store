//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "item.h"
#include "utils.h"

ItemNode* itemsHead = NULL;  // head pointer for the items linked list

// Inserts a new item into the linked list in sorted order by product number.
void insertItemSorted(Item newItem) {
    ItemNode* newNode = (ItemNode*)malloc(sizeof(ItemNode));
    if (!newNode) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    newNode->data = newItem;
    newNode->next = NULL;
    // If the list is empty or newItem.PN is less than the head's PN.
    if (itemsHead == NULL || strcmp(newItem.PN, itemsHead->data.PN) < 0) {
        newNode->next = itemsHead;
        itemsHead = newNode;
        return;
    }
    ItemNode* current = itemsHead;
    while (current->next != NULL && strcmp(current->next->data.PN, newItem.PN) < 0) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

// Finds an item node by its product number (PN). Complexity: O(n)
ItemNode* findItemNodeByPN(char* PN) {
    ItemNode* current = itemsHead;
    while (current != NULL) {
        if (strcmp(current->data.PN, PN) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

// Loads items from the binary file "items.dat" into the linked list.
void loadItems() {
    // Clear existing list.
    while (itemsHead != NULL) {
        ItemNode* temp = itemsHead;
        itemsHead = itemsHead->next;
        free(temp);
    }
    FILE* file = fopen("items.dat", "rb");
    if (!file) {
        return;  // No items file exists yet.
    }
    Item tempItem;
    while (fread(&tempItem, sizeof(Item), 1, file) == 1) {
        insertItemSorted(tempItem);
    }
    fclose(file);
}

// Saves the linked list of items to the binary file "items.dat".
void saveItems() {
    FILE* file = fopen("items.dat", "wb");
    if (!file) {
        printf("Error opening items file for writing!\n");
        return;
    }
    ItemNode* current = itemsHead;
    while (current != NULL) {
        fwrite(&current->data, sizeof(Item), 1, file);
        current = current->next;
    }
    fclose(file);
}

// Adds a new item.
void addItem() {
    Item newItem;
    printf("\n--- ADD ITEM ---\n");
    printf("Enter product number (P/N): ");
    scanf("%s", newItem.PN);
    if (findItemNodeByPN(newItem.PN) != NULL) {
        printf("ERROR: Item with P/N %s already exists!\n", newItem.PN);
        return;
    }
    printf("Enter product name: ");
    scanf("%s", newItem.product_name);
    printf("Enter category: ");
    scanf("%s", newItem.category);
    printf("Enter price: ");
    scanf("%f", &newItem.price);
    int stockVal;
    printf("Is in stock? (1=true, 0=false): ");
    scanf("%d", &stockVal);
    newItem.inStock = (stockVal == 1);
    getCurrentDate(newItem.date);// get the current date and time.
    printf("Enter inventory quantity: ");
    scanf("%d", &newItem.inventory);

    insertItemSorted(newItem);
    saveItems();

    char msg[100];
    sprintf(msg, "Added item [P/N=%s]", newItem.PN);
    logAction(msg);
    printf("Item added successfully!\n");
}

// Lists all items.
void listItems() {
    printf("\n--- LIST OF ITEMS ---\n");
    if (itemsHead == NULL) {
        printf("No items found.\n");
        return;
    }
    ItemNode* current = itemsHead;
    while (current != NULL) {
        Item it = current->data;
        printf("P/N: %s | product_name: %s | category: %s | price: %.2f | inStock: %d | date: %s | inv: %d\n",
            it.PN, it.product_name, it.category, it.price, it.inStock, it.date, it.inventory);
        current = current->next;
    }
}

// Removes an item from the linked list by its product number.
void removeItem() {
    char PN[20];
    printf("\n--- REMOVE ITEM ---\n");
    printf("Enter product number (P/N) to remove: ");
    scanf("%s", PN);
    // Special case: if the head is to be removed.
    if (itemsHead != NULL && strcmp(itemsHead->data.PN, PN) == 0) {
        ItemNode* temp = itemsHead;
        itemsHead = itemsHead->next;
        free(temp);
        saveItems();
        char msg[100];
        sprintf(msg, "Removed item [P/N=%s]", PN);
        logAction(msg);
        printf("Item removed successfully!\n");
        return;
    }
    ItemNode* current = itemsHead;
    while (current != NULL && current->next != NULL) {
        if (strcmp(current->next->data.PN, PN) == 0) {
            ItemNode* temp = current->next;
            current->next = temp->next;
            free(temp);
            saveItems();
            char msg[100];
            sprintf(msg, "Removed item [P/N=%s]", PN);
            logAction(msg);
            printf("Item removed successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Item not found!\n");
}

// Updates an existing item's details.
void updateItem() {
    char PN[20];
    printf("\n--- UPDATE ITEM ---\n");
    printf("Enter product number (P/N) to update: ");
    scanf("%s", PN);

    ItemNode* node = findItemNodeByPN(PN);
    if (node == NULL) {
        printf("Item not found!\n");
        return;
    }
    Item* it = &node->data;
    printf("Current data:\n");
    printf("P/N: %s | product_name: %s | category: %s | price: %.2f | inStock: %d | date: %s | inv: %d\n",
        it->PN, it->product_name, it->category, it->price, it->inStock, it->date, it->inventory);
    char buffer[20];
    float fBuf;
    int iBuf;
    printf("Enter new product name (or '-' to skip): ");
    scanf("%s", buffer);
    if (strcmp(buffer, "-") != 0) {
        strcpy(it->product_name, buffer);
    }
    printf("Enter new category (or '-' to skip): ");
    scanf("%s", buffer);
    if (strcmp(buffer, "-") != 0) {
        strcpy(it->category, buffer);
    }
    printf("Enter new price (or -1 to skip): ");
    scanf("%f", &fBuf);
    if (fBuf >= 0) {
        it->price = fBuf;
    }
    printf("Change stock? (1=in, 0=out, -1=skip): ");
    scanf("%d", &iBuf);
    if (iBuf == 1 || iBuf == 0) {
        it->inStock = (iBuf == 1);
    }
    printf("Enter new date (YYYY-MM-DD HH:MM:SS or '-' to skip): ");
    scanf("%s", buffer);
    if (strcmp(buffer, "-") != 0) {
        strcpy(it->date, buffer);
    }
    printf("Enter new inventory (or -1 to skip): ");
    scanf("%d", &iBuf);
    if (iBuf >= 0) {
        it->inventory = iBuf;
    }
    saveItems();
    char msg[100];
    sprintf(msg, "Updated item [P/N=%s]", PN);
    logAction(msg);
    printf("Item updated successfully!\n");
}

// Searches for items based on criteria.
void searchItems() {
    int choice;
    printf("\n--- SEARCH ITEMS ---\n");
    printf("1. By product name/category substring\n");
    printf("2. By price (>/<)\n");
    printf("3. By inStock\n");
    printf("4. By date (before/after/between)\n");
    printf("5. By inventory (>/<)\n");
    printf("6. By exact product number (P/N)\n");
    scanf("%d", &choice);
    int foundAny = 0;
    ItemNode* current = itemsHead;
    switch (choice) {
    case 1: {
        char subName[20], subCategory[20];
        printf("Enter product name substring (or '-' to ignore): ");
        scanf("%s", subName);
        printf("Enter category substring (or '-' to ignore): ");
        scanf("%s", subCategory);
        while (current != NULL) {
            int matchName = (strcmp(subName, "-") == 0) || (strstr(current->data.product_name, subName) != NULL);
            int matchCategory = (strcmp(subCategory, "-") == 0) || (strstr(current->data.category, subCategory) != NULL);
            if (matchName && matchCategory) {
                foundAny = 1;
                printf("P/N: %s | product_name: %s | category: %s\n",
                    current->data.PN, current->data.product_name, current->data.category);
            }
            current = current->next;
        }
        break;
    }
    case 2: {
        char op;
        float val;
        printf("Enter operator (>/<) and price: ");
        scanf(" %c %f", &op, &val);
        current = itemsHead;
        while (current != NULL) {
            float p = current->data.price;
            if ((op == '>' && p > val) || (op == '<' && p < val)) {
                foundAny = 1;
                printf("P/N: %s | price: %.2f\n", current->data.PN, p);
            }
            current = current->next;
        }
        break;
    }
    case 3: {
        int stockVal;
        printf("Enter 1 for inStock, 0 for not: ");
        scanf("%d", &stockVal);
        bool needed = (stockVal == 1);
        current = itemsHead;
        while (current != NULL) {
            if (current->data.inStock == needed) {
                foundAny = 1;
                printf("P/N: %s | inStock: %d\n", current->data.PN, stockVal);
            }
            current = current->next;
        }
        break;
    }
    case 4: {
        int sub;
        printf("1. Before date\n2. After date\n3. Between two dates\n");
        scanf("%d", &sub);
        char d1[20], d2[20];
        current = itemsHead;
        if (sub == 1) {
            printf("Enter date (YYYY-MM-DD HH:MM:SS): ");
            scanf("%s", d1);
            while (current != NULL) {
                if (strcmp(current->data.date, d1) < 0) {
                    foundAny = 1;
                    printf("P/N: %s | date: %s\n", current->data.PN, current->data.date);
                }
                current = current->next;
            }
        }
        else if (sub == 2) {
            printf("Enter date (YYYY-MM-DD HH:MM:SS): ");
            scanf("%s", d1);
            while (current != NULL) {
                if (strcmp(current->data.date, d1) > 0) {
                    foundAny = 1;
                    printf("P/N: %s | date: %s\n", current->data.PN, current->data.date);
                }
                current = current->next;
            }
        }
        else if (sub == 3) {
            printf("Enter start date (YYYY-MM-DD HH:MM:SS): ");
            scanf("%s", d1);
            printf("Enter end date (YYYY-MM-DD HH:MM:SS): ");
            scanf("%s", d2);
            while (current != NULL) {
                if (strcmp(current->data.date, d1) >= 0 &&
                    strcmp(current->data.date, d2) <= 0)
                {
                    foundAny = 1;
                    printf("P/N: %s | date: %s\n", current->data.PN, current->data.date);
                }
                current = current->next;
            }
        }
        break;
    }
    case 5: {
        char op;
        int val;
        printf("Enter operator (>/<) and inventory: ");
        scanf(" %c %d", &op, &val);
        current = itemsHead;
        while (current != NULL) {
            int inv = current->data.inventory;
            if ((op == '>' && inv > val) || (op == '<' && inv < val)) {
                foundAny = 1;
                printf("P/N: %s | inventory: %d\n", current->data.PN, inv);
            }
            current = current->next;
        }
        break;
    }
    case 6: {
        char searchPN[20];
        printf("Enter product number (P/N): ");
        scanf("%s", searchPN);
        ItemNode* node = findItemNodeByPN(searchPN);
        if (node == NULL) {
            printf("Item with P/N=%s not found.\n", searchPN);
        }
        else {
            foundAny = 1;
            Item it = node->data;
            printf("Found: P/N: %s | product_name: %s | category: %s | price: %.2f | date: %s | inventory: %d\n",
                it.PN, it.product_name, it.category, it.price, it.date, it.inventory);
        }
        break;
    }
    default:
        printf("Invalid choice.\n");
        return;
    }
    if (!foundAny && choice != 6) {
        printf("No matching items found.\n");
    }
}
