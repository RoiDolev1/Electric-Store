//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#pragma once 

// Purchase structure definition.
typedef struct purchase {
    char customerName[30];   // Name of the customer
    char productPN[20];      // Product Number (P/N) of the purchased item
    char purchaseDate[20];   // Date/time of purchase ("YYYY-MM-DD HH:MM:SS")
    int quantity;            // Quantity purchased
    float priceAtPurchase;   // Price per unit at purchase time
} Purchase;

#define MAX_PURCHASES 200  // Maximum number of purchase records

// Declaration of the purchases array and count.
extern Purchase purchasesArray[MAX_PURCHASES];  // purchases array
extern int purchasesCount;  // Number of purchase records

// Function declarations for purchase operations.
void loadPurchases();
void savePurchases();
void recordPurchase(char* customerName, char* productPN, int quantity, float price);
void listPurchasesByCustomer(char* customerName);
int returnProduct(char* customerName, char* productPN);
