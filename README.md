# Bank Management System

This project is a Bank Management System designed to manage bank accounts, transactions, and employee operations through a command-line interface. The system allows bank employees to perform various tasks such as adding, deleting, modifying, and searching for accounts, as well as handling transactions like withdrawals, deposits, and transfers.

## Project Overview

The Bank Management System is built to handle the following functionalities:

- **Employee Login**: Employees must log in using credentials stored in a file.
- **Account Management**: Employees can add, delete, modify, and search for bank accounts.
- **Transaction Handling**: Employees can perform withdrawals, deposits, and transfers between accounts.
- **Reporting**: Employees can generate reports of recent transactions for specific accounts.
- **Data Persistence**: All account data and transaction histories are saved to and read from text files.

The system is built using C and follows a structured approach with the following key components:

- **Account Management**: Handles the creation, deletion, and modification of bank accounts.
- **Transaction Management**: Manages withdrawals, deposits, and transfers.
- **File Handling**: Reads and writes account and transaction data to text files.
- **Validation**: Ensures all user inputs are validated (e.g., account numbers, email addresses, etc.).

## Features

### Employee Features
- **Employee Login**: Employees must log in using credentials stored in `users.txt`.
- **Load Accounts**: Load account data from `accounts.txt`.
- **Add Account**: Add a new bank account to the system.
- **Delete Account**: Delete an account with a zero balance.
- **Modify Account**: Modify account details (name, mobile, email).
- **Query (Search)**: Search for a specific account by account number.
- **Advanced Search**: Search for accounts by a keyword (e.g., name).
- **Withdraw**: Withdraw money from an account (max $10,000 per transaction).
- **Deposit**: Deposit money into an account (max $10,000 per transaction).
- **Transfer**: Transfer money between two accounts.
- **Report**: Generate a report of the last 5 transactions for an account.
- **Print (Sort)**: Print all accounts sorted by name, balance, or date opened.
- **Save**: Save account data back to `accounts.txt`.
- **Quit**: Exit the program.

### File Handling
- `users.txt`: Stores employee login credentials.
- `accounts.txt`: Stores account data in a comma-delimited format.
- `<account_number>.txt`: Stores transaction history for each account.

### Validation
- **Account Number**: Must be 10 digits and unique.
- **Email Address**: Must be in a valid format.
- **Numeric Inputs**: All numeric inputs (e.g., balance, mobile number) are validated.
- **Transaction Limits**: Withdrawals and deposits are limited to $10,000 per transaction.

## How to Run the Project

### Clone the Repository
```bash
git clone https://github.com/your-username/bank-management-system.git
```

### Compile the Program
Navigate to the project directory and compile the C program using a C compiler (e.g., gcc):
```bash
gcc main.c -o bank_management_system
```

### Run the Program
Execute the compiled program:
```bash
./bank_management_system
```

### Login
Use the credentials stored in `users.txt` to log in as an employee.

### Use the System
Follow the on-screen menu to perform various operations such as adding accounts, performing transactions, and generating reports.

## File Structure
- `users.txt`: Contains employee login credentials.
- `accounts.txt`: Contains account data in a comma-delimited format.
- `<account_number>.txt`: Stores transaction history for each account.

## Sample Runs

### Login
```bash
Enter username: ahmed.mohamed
Enter password: 123$@1
Login successful!
```

### Query (Search)
```bash
Enter account number: 9780136019
Account Number: 9780136019
Name: Mohamed Ali
E-mail: m.ali@gmail.com
Balance: 10000.54 $
Mobile: 01254698321
Date Opened: December 2008
```

### Advanced Search
```bash
Enter keyword: Ahmed
Search results:
Account Number: 9781503204212
Name: Ahmed Ali
E-mail: a.ali@yahoo.com
Balance: 56320 $
Mobile: 01148597411
Opened: December 2008

Account Number: 9781152304222
Name: Mohamed Ahmed
E-mail: m.ahmed@yahoo.com
Balance: 100000 $
Mobile: 01254698321
Opened: February 2007
```

### Add Account
```bash
Enter account number: 9780136019
Account number already exists!
Enter account number: 9780136020
Enter name: John Doe
Enter email: john.doe@gmail.com
Enter balance: 5000
Enter mobile: 01234567890
Account added successfully!
```

### Withdraw
```bash
Enter account number: 9780136019
Enter amount to withdraw: 500
Withdrawal successful!
New balance: 9500.54 $
```
