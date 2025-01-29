# Bank Management System

## Overview
The **Bank Management System** is a command-line program designed to manage bank accounts, transactions, and employee operations efficiently. It provides functionalities for employee authentication, account management, transaction handling, reporting, and data persistence through file storage.

## Features

### Employee Features
- **Employee Login**: Secure login using credentials stored in `users.txt`.
- **Load Accounts**: Retrieve account data from `accounts.txt`.
- **Account Management**:
  - Add, delete (if balance is zero), modify, and search for accounts.
- **Transaction Handling**:
  - Withdraw (max $10,000 per transaction).
  - Deposit (max $10,000 per transaction).
  - Transfer money between accounts.
- **Reporting**:
  - Generate the last five transactions for an account.
  - Print all accounts sorted by name, balance, or date opened.
- **Data Persistence**:
  - Save all changes back to `accounts.txt`.

### File Handling
- `users.txt`: Stores employee login credentials.
- `accounts.txt`: Contains account details in a comma-separated format.
- `<account_number>.txt`: Stores transaction history per account.

### Validation
- **Account Number**: Must be 10 digits and unique.
- **Email Address**: Must be in a valid format.
- **Numeric Inputs**: Ensures valid mobile numbers and balances.
- **Transaction Limits**: Withdrawals and deposits limited to $10,000 per transaction.

## How to Run the Project

### Clone the Repository
```bash
git clone https://github.com/your-username/bank-management-system.git
```

### Compile the Program
Navigate to the project directory and compile the C program using `gcc`:
```bash
gcc main.c -o bank_management_system
```

### Run the Program
```bash
./bank_management_system
```

### Login
Use credentials from `users.txt` to log in as an employee.

### Use the System
Follow the on-screen menu to manage accounts, perform transactions, and generate reports.

## File Structure
```
bank-management-system/
│── main.c
│── users.txt
│── accounts.txt
│── transactions/
    ├── <account_number>.txt
```

## Sample Runs

### Login
```plaintext
Enter username: ahmed.mohamed
Enter password: 123$@1
Login successful!
```

### Query (Search)
```plaintext
Enter account number: 9780136019
Account Number: 9780136019
Name: Mohamed Ali
E-mail: m.ali@gmail.com
Balance: 10000.54 $
Mobile: 01254698321
Date Opened: December 2008
```

### Advanced Search
```plaintext
Enter keyword: Ahmed
Search results:
Account Number: 9781503204212
Name: Ahmed Ali
E-mail: a.ali@yahoo.com
Balance: 56320 $
Mobile: 01148597411
Opened: December 2008
```

### Add Account
```plaintext
Enter account number: 9780136020
Enter name: John Doe
Enter email: john.doe@gmail.com
Enter balance: 5000
Enter mobile: 01234567890
Account added successfully!
```

### Withdraw
```plaintext
Enter account number: 9780136019
Enter amount to withdraw: 500
Withdrawal successful!
New balance: 9500.54 $
```

--

This **Bank Management System** provides a structured and efficient way to manage banking operations through a simple and secure interface. 🚀
