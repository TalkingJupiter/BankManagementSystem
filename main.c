#include <stdio.h>

#define NUM_ACCOUNTS 50
#define BASE_ACCOUNT_NUM 100
#define MIN_DEPOSIT 100
#define FILENAME "account.dat"

typedef struct {
    double balance;
    int isOpen;
} Account;


int getIndex(int accountNumber);
//char userInput();
void openAccount(Account accounts[], int *openAccounts);
void deposit(Account accounts[]);
void withdraw(Account accounts[]);
void balanceInquiry(Account account[]);
void computeInterest(Account accounts[]);
void closeAccount(Account accounts[], int *openAccounts);
void printAllAccounts(Account accounts[]);
void exitProgram(Account accounts[], int *openAccounts);

int main(){
    //TODO: Get a user input for requested function
    Account accounts[NUM_ACCOUNTS];
    int openAccounts = 0;
    char choice;

    for(int i=0; i<NUM_ACCOUNTS;i++){
        accounts[i].isOpen = 0;
        accounts[i].balance = 0;
    }

    //TODO: Write a switch case function to call the requested function
    do{
        printf("\n--- Bank Account Management ---\n");
        printf("O - Open an account\n");
        printf("B - Balance inquiry\n");
        printf("D - Deposit money\n");
        printf("W - Withdraw money\n");
        printf("C - Close an account\n");
        printf("I - Compute interest\n");
        printf("P - Print all accounts\n");
        printf("E - Exit program\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice){
            case('o'):
            case('O'):
                openAccount(accounts, &openAccounts);
                break;
            
            case 'b':
            case 'B':
                balanceInquiry(accounts);
                break;

            case 'D':
            case 'd':
                deposit(accounts);
                break;

            case 'W':
            case 'w':
                withdraw(accounts);
                break;

            case 'C':
            case 'c':
                closeAccount(accounts, &openAccounts);
                break;

            case 'I':
            case 'i':
                computeInterest(accounts);
                break;

            case 'P':
            case 'p':
                printAllAccounts(accounts);
                break;

            case 'E':
            case 'e':
                exitProgram(accounts, &openAccounts);
                break;

            default:
                printf("Invalid Input...");
        }
    }while((choice != 'E') && (choice != 'e'));
}

int getIndex(int accountNumber){
    if(accountNumber<BASE_ACCOUNT_NUM || accountNumber >= BASE_ACCOUNT_NUM + NUM_ACCOUNTS){
        printf("Invalid account number\n.");
        return -1;
    }
    return accountNumber - BASE_ACCOUNT_NUM;
}

//TODO: Create Open account function
void openAccount(Account accounts[], int *openAccounts){
    int accountNumber, index;
    double initialDeposit;

    if(*openAccounts >= NUM_ACCOUNTS){
        printf("Cannot open more than 50 accounts.\n");
        return;
    }
    printf("Enter initial deposit (minimum $100): ");
    scanf("%lf", &initialDeposit);

    if(initialDeposit < MIN_DEPOSIT){
        printf("Initial deposit should be at least $100.\n");
        return;
    }
    for(index = 0; index < NUM_ACCOUNTS; index++){
        if(!accounts[index].balance){
            accounts[index].balance = initialDeposit;
            accounts[index].isOpen = 1;
            *openAccounts += 1;
            accountNumber = BASE_ACCOUNT_NUM + index;
            printf("Account %d opened with a balance of $%.2f\n", accountNumber, initialDeposit);
            return;

        }
    }

}
//TODO: Create balance inquiry function
void balanceInquiry(Account accounts[]){
    int accountNumber, index;
    printf("Enter account number to check balance: ");
    scanf("%d", &accountNumber);

    index = getIndex(accountNumber);

    if(index != -1 && accounts[index].isOpen){
        printf("Balance for account %d is $%.2lf.\n", accountNumber, accounts[index].balance);
    } else {
        printf("Account not open or invalid account number.");
    }
}
//TODO: Create Deposit function
void deposit(Account accounts[]){
    int accountNumber, index;
    double amount;

     // Request the index from the array
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    index = getIndex(accountNumber);

    if(index !=-1 && accounts[index].isOpen){
        printf("Enter deposit amount: ");
        scanf("%lf", &amount);

        if(amount > 0){
            accounts[index].balance += amount;
            printf("Deposited $%.2lf to account %d. New balance is $%.2f.\n", amount, accountNumber, accounts[index].balance);
        } else {
            printf("Deposit amount must be positive. \n");
        }
    } else {
        printf("Account not open or invalid account number.\n");
    }    
}
//TODO: Create Withdrawal function
void withdraw(Account accounts[]){
    int accountNumber, index;
    double amount;

    //Request the index from the array
    printf("Enter account number for withdrawal: ");
    scanf("%d", &accountNumber);
    index = getIndex(accountNumber);

    if(index != -1 || accounts[index].isOpen){
        printf("Enter withdraw amount: ");
        scanf("%lf", &amount);

        if(amount > 0 && amount <= accounts[index].balance){
            accounts[index].balance -= amount;
            printf("Withdrew $%.2f from account %d. New balance is $%.2f.\n", amount,accountNumber, accounts[index].balance);
        } else {
            printf("Invalid withdraw amount or insufficient founds...\n");
        }
    } else {
        printf("Account not open or invalid account number...\n");
    }
}
//TODO: Create Close Account function
void closeAccount(Account accounts[], int *openAccounts){
    int accountNumber, index;

    //Request the index from the array
    printf("Enter account number to close: ");
    scanf("%d", &accountNumber);
    index = getIndex(accountNumber);

    if(index != -1 && accounts[index].isOpen){
        accounts[index].isOpen = 0; //Close the open state
        accounts[index].balance = 0; //Clear the balance for security
        *openAccounts -= 1;
        printf("Account %d closed successfully.\n", accountNumber);
    } else {
        printf("Account not open or invalid account number.\n");
    }
}

void computeInterest(Account accounts[]){
    double interestRate;
    printf("Enter interest rate (%%): ");
    scanf("%lf", &interestRate);

    for(int i=0; i<NUM_ACCOUNTS; i++){
        if(accounts[i].isOpen){
            accounts[i].balance += accounts[i].balance * interestRate /100;
        }
    }
    printf("Interest rate applied to all open accounts");
}

void printAllAccounts(Account accounts[]) {
    printf("Account Number\tBalance\n");
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        if (accounts[i].isOpen) {
            printf("%d\t\t$%.2f\n", BASE_ACCOUNT_NUM + i, accounts[i].balance);
        }
    }
}

void exitProgram(Account accounts[], int *openAccounts){
    for(int i = 0; i< NUM_ACCOUNTS; i++){
        accounts[i].isOpen = 0;
        accounts[i].balance = 0;
    }
    *openAccounts = 0;
    printf("All accounts closed. Exiting program.\n");
}
