# Electric Store Management System

This project is a simulation of an electric store management system, developed entirely in C.

## Features
- Customer management (add, update, delete customers)
- Employee management with roles and permissions
- Item inventory management (add, update, delete items)
- Purchase and return processes
- Activity logging (purchases, returns, employee actions)

## Technical Highlights
- Modular code structure (separated `.c` and `.h` files)
- File handling: text and binary files
- Structured programming and error handling
- Data organization using `structs` and dynamic memory

## Project Structure
- `customer.c / customer.h` - Handle customer operations
- `employees.c / employees.h` - Manage employees
- `item.c / item.h` - Manage inventory items
- `purchases.c / purchases.h` - Handle purchases and returns
- `menu.c / menu.h` - User interface handling
- `utils.c / utils.h` - Utility functions
- `main.c` - Entry point of the application

## How to Compile
You can compile the project with a simple gcc command:

```bash
gcc main.c customer.c employees.c item.c purchases.c menu.c utils.c -o ElectricStore
