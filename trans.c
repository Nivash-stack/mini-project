#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Structure Definition
struct Account
{
    int accNo;
    char name[50];
    char mobile[15];
    char accType[20];
    float balance;
    int transactionCount;
};

struct Account accounts[MAX];
int totalAccounts = 0;

// Function Prototypes
void addAccount();
void displayAccounts();
void deposit();
void withdrawMoney();
void searchAccount();
void sortAccounts();
void saveToFile();
void loadFromFile();
void miniStatement();
int findAccount(int accNo);

int main()
{
    int choice;

    loadFromFile();

    do
    {
        printf("\n====== BANK MANAGEMENT SYSTEM ======\n");
        printf("1. Add Account\n");
        printf("2. Display Accounts\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Search Account\n");
        printf("6. Sort Accounts\n");
        printf("7. Mini Statement\n");
        printf("8. Save Accounts to File\n");
        printf("9. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addAccount();
                break;

            case 2:
                displayAccounts();
                break;

            case 3:
                deposit();
                break;

            case 4:
                withdrawMoney();
                break;

            case 5:
                searchAccount();
                break;

            case 6:
                sortAccounts();
                break;

            case 7:
                miniStatement();
                break;

            case 8:
                saveToFile();
                break;

            case 9:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 9);

    return 0;
}

// Add Account
void addAccount()
{
    struct Account *acc = &accounts[totalAccounts];

    printf("Enter Account Number: ");
    scanf("%d", &acc->accNo);

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", acc->name);

    printf("Enter Mobile Number: ");
    scanf("%s", acc->mobile);

    printf("Enter Account Type: ");
    scanf("%s", acc->accType);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc->balance);

    acc->transactionCount = 0;

    totalAccounts++;

    printf("Account Added Successfully!\n");
}

// Display Accounts
void displayAccounts()
{
    int i;

    printf("\n-------------------------------------------------\n");
    printf("AccNo\tName\t\tType\tBalance\n");
    printf("-------------------------------------------------\n");

    for(i = 0; i < totalAccounts; i++)
    {
        printf("%d\t%s\t\t%s\t%.2f\n",
               accounts[i].accNo,
               accounts[i].name,
               accounts[i].accType,
               accounts[i].balance);
    }
}

// Find Account
int findAccount(int accNo)
{
    int i;

    for(i = 0; i < totalAccounts; i++)
    {
        if(accounts[i].accNo == accNo)
        {
            return i;
        }
    }

    return -1;
}

// Deposit
void deposit()
{
    int accNo, index;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    index = findAccount(accNo);

    if(index == -1)
    {
        printf("Invalid Account Number!\n");
        return;
    }

    printf("Enter Deposit Amount: ");
    scanf("%f", &amount);

    accounts[index].balance += amount;
    accounts[index].transactionCount++;

    printf("Amount Deposited Successfully!\n");
}

// Withdraw
void withdrawMoney()
{
    int accNo, index;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    index = findAccount(accNo);

    if(index == -1)
    {
        printf("Invalid Account Number!\n");
        return;
    }

    printf("Enter Withdrawal Amount: ");
    scanf("%f", &amount);

    if(amount > accounts[index].balance)
    {
        printf("Insufficient Balance!\n");
        return;
    }

    accounts[index].balance -= amount;
    accounts[index].transactionCount++;

    printf("Withdrawal Successful!\n");
}

// Search Account
void searchAccount()
{
    int accNo, index;

    printf("Enter Account Number to Search: ");
    scanf("%d", &accNo);

    index = findAccount(accNo);

    if(index == -1)
    {
        printf("Account Not Found!\n");
        return;
    }

    printf("\nAccount Found\n");
    printf("Name: %s\n", accounts[index].name);
    printf("Balance: %.2f\n", accounts[index].balance);
}

// Sort Accounts
void sortAccounts()
{
    int i, j;
    struct Account temp;

    for(i = 0; i < totalAccounts - 1; i++)
    {
        for(j = i + 1; j < totalAccounts; j++)
        {
            if(accounts[i].balance > accounts[j].balance)
            {
                temp = accounts[i];
                accounts[i] = accounts[j];
                accounts[j] = temp;
            }
        }
    }

    printf("Accounts Sorted by Balance!\n");
}

// Mini Statement
void miniStatement()
{
    int accNo, index;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    index = findAccount(accNo);

    if(index == -1)
    {
        printf("Account Not Found!\n");
        return;
    }

    printf("\n------ MINI STATEMENT ------\n");
    printf("Account Number : %d\n", accounts[index].accNo);
    printf("Customer Name  : %s\n", accounts[index].name);
    printf("Balance        : %.2f\n", accounts[index].balance);
    printf("Transactions   : %d\n",
           accounts[index].transactionCount);
}

// Save to File
void saveToFile()
{
    FILE *fp;

    fp = fopen("accounts.txt", "w");

    if(fp == NULL)
    {
        printf("File Opening Failed!\n");
        return;
    }

    int i;

    for(i = 0; i < totalAccounts; i++)
    {
        fprintf(fp, "%d %s %s %s %.2f %d\n",
                accounts[i].accNo,
                accounts[i].name,
                accounts[i].mobile,
                accounts[i].accType,
                accounts[i].balance,
                accounts[i].transactionCount);
    }

    fclose(fp);

    printf("Accounts Saved to File Successfully!\n");
}

// Load from File
void loadFromFile()
{
    FILE *fp;

    fp = fopen("accounts.txt", "r");

    if(fp == NULL)
    {
        return;
    }

    while(fscanf(fp, "%d %s %s %s %f %d",
                 &accounts[totalAccounts].accNo,
                 accounts[totalAccounts].name,
                 accounts[totalAccounts].mobile,
                 accounts[totalAccounts].accType,
                 &accounts[totalAccounts].balance,
                 &accounts[totalAccounts].transactionCount) != EOF)
    {
        totalAccounts++;
    }

    fclose(fp);
}