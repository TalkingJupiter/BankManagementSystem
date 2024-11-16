#include <stdio.h>
#include <math.h>

#define NUM_ACCOUNTS 50
#define BASE_ACCOUNT_NUM 100
#define MIN_DEPOSIT 100
#define FILENAME "account.dat"

typedef struct {
    double balance;
    int isOpen;

    union {
        struct{
            int months;
            double debt;
            float interest;
        }loanInfo;
    };
    
} Account;


int getIndex(int accountNumber);
void openAccount(Account accounts[], int *openAccounts);
void deposit(Account accounts[]);
void withdraw(Account accounts[]);
void balanceInquiry(Account account[]);
void computeInterest(Account accounts[]);
void closeAccount(Account accounts[], int *openAccounts);
void loan(Account accounts[]);
void loanPaymentCalc(Account accounts[]);
void printAllAccounts(Account accounts[]);
void transfer(Account accounts[]);
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
        printf("L - Get a loan\n");
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

            case 'L':
            case 'l':
                loan(accounts);
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
//TODO: Apply Loan 
void loan(Account accounts[]){
    double annualIncome, loanAmount, additionalAmount;
    double targetDTI = 0.35;
    double interestRate = 0.0692;
    int accountNumber, month;
    char additionalDept, choice;

    //Request the account info
    printf("Enter your account number: ");
    scanf("%d", &accountNumber);
    int index = getIndex(accountNumber);
    //getchar();

    if(index != -1 && accounts[index].isOpen){
        printf("Enter the requested ammount for the loan: ");
        scanf("%lf", &loanAmount);
        
        printf("Enter your annual income: ");
        scanf("%lf", &annualIncome);

        printf("How long are you thinking to pay? ");
        scanf("%d", &month); //BUG: What if they put something else except then months 

        printf("Do you have additional dept payments [Y/N]: ");
        getchar();
        scanf("%c", &additionalDept);
        
        
        if(additionalDept == 'Y' || additionalDept == 'y'){
            printf("Enter the monthly amount that you pay: ");
            scanf("%lf", &additionalAmount);
        } else {
            additionalDept = 0.00;
        }

        //Suggestion: You can devide these to functions to clear the code
        int currentDTI = additionalAmount/(annualIncome/12);

        if(currentDTI >= targetDTI){
            printf("You are not eligible for a new loan.\n");
        } else {
            printf("You are eligible for a new loan.\n");
        }

        double loanFactor = (interestRate * pow((1 + interestRate), month)) / (pow((1 + interestRate), month) - 1);
        double maxLoanAmmount = (annualIncome*targetDTI)/loanFactor;
        printf("The max amount = %.2lf\n",maxLoanAmmount);

        if(loanAmount <= maxLoanAmmount){
            printf("You are eligible to get %.2lf.\n", loanAmount);
            printf("Do you want to get the loan [Y/N]? ");
            getchar();
            scanf("%c", &choice);

            if(choice == 'Y' || choice == 'y'){
                accounts[index].loanInfo.debt = loanAmount+(loanAmount*interestRate);
                accounts[index].loanInfo.interest = interestRate;
                accounts[index].loanInfo.months = month;

                printf("Your loan dept = %.2lf\nYour interest rate = %%%.2lf\nMonths left = %d\n", accounts[index].loanInfo.debt, accounts[index].loanInfo.interest*100, accounts[index].loanInfo.months);
            } else {
                printf("Ok, no new loan amount added to the account. Exitting...");
                return;
            }
        } else {
            printf("The amont that you requested is exeeding your max loan amount. Please try again later!\n");
            return;
        }
    }
}

//TODD: Loan Payment Calculator
void loanPaymentCalc(Account accounts[]){
    double amount;
    int month;
    double interestRate = 0.0692;
    printf("Please enter the loan amount: ");
    scanf("%lf", &amount);

    printf("Enter the total months: ");
    scanf("%d", &month);

    double monthlyPayments = (amount + (amount*interestRate))/(double)month;

    printf("Estimated payments is %.2lf for %d.", monthlyPayments, month); 
}

//TODO: Compute Interest
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
    const char *headerColor = "\033[1;34m";  // Blue
    const char *balanceColor = "\033[1;32m";  // Green
    const char *debtColor = "\033[1;31m";  // Red
    const char *resetColor = "\033[0m";
    
     printf("\033[1;34m%-15s\033[0m \033[1;34m%-15s\033[0m \033[1;34m%-15s\033[0m\n", "Account Number", "Balance", "Dept");
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        if (accounts[i].isOpen) {
            printf("%-15d \033[1;32m$%-14.2f\033[0m \033[1;31m-$%-14.2f\033[0m\n", BASE_ACCOUNT_NUM + i, accounts[i].balance, accounts[i].loanInfo.debt);
        }
    }
}
//TODO: Money Transfer
void transfer(Account accounts[]){  
    double amount;
    int accountNumber;
    char choice;
    printf("Enter the senders account number: ");
    scanf("%d", &accountNumber);
    int indexSender = getIndex(accountNumber);

    printf("Enter the receivers account number: ");
    scanf("%d", &accountNumber);
    int indexReceiver = getIndex(accountNumber);

    printf("The amount that you want to transfer: ");
    scanf("%lf", &amount);

    if((indexSender != -1 || accounts[indexSender].isOpen)&& (indexReceiver!= -1 || accounts[indexReceiver].isOpen )){
        if(accounts[indexSender].balance >= amount){
            printf("\033[1;32mThe transfer amount is availabe...\033[0m"); //Green
            printf("Do you want to tranfer %.2lf to account %d [Y/N]? ", amount, accountNumber);
            getchar();
            scanf("%c", &choice);

            if(choice=='Y' || choice=='y'){
                printf("\033[1;32mTransfering the money...\033[0m"); //Green
                accounts[indexSender].balance -= amount; 
                accounts[indexReceiver].balance += amount;
                printf("\033[1;32mTransfer has been completed...\033[0m"); //green
            } else {
                printf("\033[1;31mNot transfering the money. Exitting...\033[0m"); //red
            }

        } else { 
            printf("\033[1;31mNot enough money to transfer...\033[0m"); //Red
        }
    } else {
        printf("Unable to transfer the money please make sure that the both accounts are open...");
        return;
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
