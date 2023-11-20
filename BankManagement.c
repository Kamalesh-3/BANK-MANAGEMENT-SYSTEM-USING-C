#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    int account_number;
    char name[50];
    double balance;
} BankAccount;

BankAccount* accounts[MAX_ACCOUNTS];
int num_accounts = 0;

int createAccount(char name[], double initial_balance) {
    if (num_accounts >= MAX_ACCOUNTS) {
        printf("Maximum number of accounts reached!\n");
        return -1;
    }

    BankAccount* newAccount = (BankAccount*)malloc(sizeof(BankAccount));
    if (newAccount == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    newAccount->account_number = num_accounts + 1;
    strcpy(newAccount->name, name);
    newAccount->balance = initial_balance;

    accounts[num_accounts] = newAccount;
    num_accounts++;

    return newAccount->account_number;
}

int findAccount(int account_number) {
    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i]->account_number == account_number) {
            return i;
        }
    }
    return -1;
}

void deposit(int account_number, double amount) {
    int index = findAccount(account_number);
    if (index != -1) {
        accounts[index]->balance += amount;
        printf("Deposited $%.2f into account %d. New balance: $%.2f\n", amount, account_number, accounts[index]->balance);
    } else {
        printf("Account not found.\n");
    }
}

void withdraw(int account_number, double amount) {
    int index = findAccount(account_number);
    if (index != -1) {
        if (accounts[index]->balance >= amount) {
            accounts[index]->balance -= amount;
            printf("Withdrawn $%.2f from account %d. New balance: $%.2f\n", amount, account_number, accounts[index]->balance);
        } else {
            printf("Insufficient balance.\n");
        }
    } else {
        printf("Account not found.\n");
    }
}

void checkBalance(int account_number) {
    int index = findAccount(account_number);
    if (index != -1) {
        printf("Account Number: %d\n", accounts[index]->account_number);
        printf("Account Holder: %s\n", accounts[index]->name);
        printf("Balance: $%.2f\n", accounts[index]->balance);
    } else {
        printf("Account not found.\n");
    }
}

int main() {
    int choice, account_number;
    char name[50];
    double initial_balance, amount;

    while (1) {
        printf("\nBanking System Menu:\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter account holder name: ");
                scanf("%s", name);
                printf("Enter initial balance: ");
                scanf("%lf", &initial_balance);
                int account_num = createAccount(name, initial_balance);
                if (account_num != -1) {
                    printf("Account created with account number %d.\n", account_num);
                }
                break;

            case 2:
                printf("Enter account number: ");
                scanf("%d", &account_number);
                printf("Enter deposit amount: ");
                scanf("%lf", &amount);
                deposit(account_number, amount);
                break;

            case 3:
                printf("Enter account number: ");
                scanf("%d", &account_number);
                printf("Enter withdrawal amount: ");
                scanf("%lf", &amount);
                withdraw(account_number, amount);
                break;

            case 4:
                printf("Enter account number: ");
                scanf("%d", &account_number);
                checkBalance(account_number);
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
