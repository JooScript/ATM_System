# Simple ATM System in C++

## 📌 Overview
This is a simple ATM system developed in C++ with a focus on **Separation of Concerns (SoC)** and **file-based data persistence**. It simulates basic ATM functionalities, ensuring clean code organization and secure data handling.

## 🚀 Key Features
✅ **User Authentication** – Users log in using a unique PIN.  
✅ **Account Management** – Check balance, deposit, withdraw, and transfer funds.  
✅ **File-Based Storage** – Account details and transactions are stored in text files for persistence.  
✅ **Separation of Concerns (SoC)** – The system is structured into logical modules:  
- **ATM Core Logic** – Handles transactions.  
- **File I/O Operations** – Manages data storage.  
- **User Interface** – Handles console interactions.  
✅ **Error Handling** – Validates inputs and prevents invalid transactions.  

## 🛠 Technologies Used
- **C++** – Core programming language.
- **File Handling** – Text-based storage system.
- **Console Application** – User interaction via CLI.

## 🔧 Installation & Usage
1. **Clone the repository**:
   ```bash
   git clone https://github.com/Yousef-Refat/ATM_System.git
   ```
2. **Navigate to the project directory**:
   ```bash
   cd ATM_System
   ```
3. **Compile the code**:
   ```bash
   g++ -o ATM_System main.cpp ATM.cpp FileManager.cpp -std=c++11
   ```
4. **Run the application**:
   ```bash
   ./ATM_System
   ```

## 🎯 How It Works
1. **User Login** – Enter the account number and PIN.
2. **Main Menu** – Choose an operation:
   - Check Balance
   - Deposit Money
   - Withdraw Money
   - Transfer Funds
3. **Transactions** – The system processes transactions and updates files accordingly.

## 🚀 Future Improvements
- **Encryption** – Secure PIN and data storage.
- **Transaction History** – Store timestamps for each transaction.
- **Multi-Account Support** – Implement Admin & User roles.

## 📜 License
This project is open-source under the **MIT License**.

## 🤝 Contributing
Pull requests are welcome! For major changes, please open an issue first to discuss your ideas.
