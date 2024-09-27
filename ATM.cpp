#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Account {
private:
    string name;
    int accountID;
    double currentBalance;

public:
    Account(string accHolderName, int accNumber, double initDeposit) {
        name = accHolderName;
        accountID = accNumber;
        currentBalance = initDeposit;
    }

    int getAccountID() const {
        return accountID;
    }

    double getBalance() const {
        return currentBalance;
    }

    string getName() const {
        return name;
    }

    
    void makeDeposit(double amount) {
        currentBalance += amount;
        cout << "Successfully deposited: " << amount << ". New balance: " << currentBalance << endl;
    }

    // Function to withdraw money from the account
    void makeWithdrawal(double amount) {
        if (amount > currentBalance) {
            cout << "Error: Insufficient funds!" << endl;
        }
        else {
            currentBalance -= amount;
            cout << "Withdrawal of " << amount << " successful. Remaining balance: " << currentBalance << endl;
        }
    }

    
    void transferMoney(Account& recipientAccount, double amount) {
        if (amount > currentBalance) {
            cout << "Error: Not enough balance to make the transfer!" << endl;
        }
        else {
            currentBalance -= amount;
            recipientAccount.makeDeposit(amount);
            cout << "Transfer of " << amount << " to account " << recipientAccount.getAccountID() << " successful!" << endl;
        }
    }
};


void displayMenu() {
    cout << "\n--- Banking Menu ---\n";
    cout << "1. Open New Account\n";
    cout << "2. Deposit Funds\n";
    cout << "3. Withdraw Funds\n";
    cout << "4. Transfer Funds\n";
    cout << "5. View Account Info\n";
    cout << "6. Exit\n";
}


Account* locateAccount(vector<Account>& accountList, int accNumber) {
    for (auto& account : accountList) {
        if (account.getAccountID() == accNumber) {
            return &account;
        }
    }
    return nullptr;
}

int main() {
    vector<Account> accounts;
    int choice;
    int nextAccountNumber = 1001; 
    bool isRunning = true;

    
    while (isRunning) {
        displayMenu();
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string holderName;
            double initialDeposit;
            cout << "Enter your name: ";
            cin.ignore();  
            getline(cin, holderName);
            cout << "Enter the initial deposit amount: ";
            cin >> initialDeposit;

           
            Account newAccount(holderName, nextAccountNumber++, initialDeposit);
            accounts.push_back(newAccount);
            cout << "Account successfully created. Your account number is: " << nextAccountNumber - 1 << endl;
            break;
        }
        case 2: {
            int accNumber;
            double depositAmount;
            cout << "Enter your account number: ";
            cin >> accNumber;

            Account* account = locateAccount(accounts, accNumber);
            if (account) {
                cout << "Enter the amount to deposit: ";
                cin >> depositAmount;
                account->makeDeposit(depositAmount);
            }
            else {
                cout << "Account not found!" << endl;
            }
            break;
        }
        case 3: {
            int accNumber;
            double withdrawalAmount;
            cout << "Enter your account number: ";
            cin >> accNumber;

            Account* account = locateAccount(accounts, accNumber);
            if (account) {
                cout << "Enter the amount to withdraw: ";
                cin >> withdrawalAmount;
                account->makeWithdrawal(withdrawalAmount);
            }
            else {
                cout << "Account not found!" << endl;
            }
            break;
        }
        case 4: {
            int senderAccNumber, receiverAccNumber;
            double transferAmount;
            cout << "Enter your account number: ";
            cin >> senderAccNumber;

            Account* senderAccount = locateAccount(accounts, senderAccNumber);
            if (senderAccount) {
                cout << "Enter recipient's account number: ";
                cin >> receiverAccNumber;
                Account* receiverAccount = locateAccount(accounts, receiverAccNumber);
                if (receiverAccount) {
                    cout << "Enter the amount to transfer: ";
                    cin >> transferAmount;
                    senderAccount->transferMoney(*receiverAccount, transferAmount);
                }
                else {
                    cout << "Recipient account not found!" << endl;
                }
            }
            else {
                cout << "Your account not found!" << endl;
            }
            break;
        }
        case 5: {
            int accNumber;
            cout << "Enter your account number: ";
            cin >> accNumber;

            Account* account = locateAccount(accounts, accNumber);
            if (account) {
                cout << "Account Holder: " << account->getName() << endl;
                cout << "Account Number: " << account->getAccountID() << endl;
                cout << "Current Balance: " << account->getBalance() << endl;
            }
            else {
                cout << "Account not found!" << endl;
            }
            break;
        }
        case 6:
            isRunning = false;
            cout << "Thank you for using the banking system. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    }

    return 0;
}
