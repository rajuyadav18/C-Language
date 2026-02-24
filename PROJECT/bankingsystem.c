/*A simple Bank Management System in C using structures and file handling to perform basic banking operations.
 Features:
 - Create new bank accounts
 - Deposit money
 - Withdraw money
 - Display all accounts
 - Delete an account
 - Data stored permanently using files
 */
#include <stdio.h>
#include <stdlib.h>

struct bank {
    int acc_no;
    char name[50];
    float balance;
};
// function declaration
void createAccount();
void deposit();
void withdrawMoney();
void displayAccounts();
void deleteAccount();
int accountExists(int acc);

int main() {
    int choice;

    do {
        printf("\n--- BANK MANAGEMENT SYSTEM ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Display All Accounts\n");
        printf("5. Delete Account\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdrawMoney(); break;
            case 4: displayAccounts(); break;
            case 5: deleteAccount(); break;
            case 6: printf("Thank you!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}

// Check duplicate account 
int accountExists(int acc) {
    struct bank b;
    FILE *fp = fopen("bank.txt", "rb");

    if (fp == NULL) return 0;

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.acc_no == acc) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// Create Account 
void createAccount() {
    struct bank b;
    FILE *fp = fopen("bank.txt", "ab");

    printf("Enter Account Number: ");
    scanf("%d", &b.acc_no);

    if (b.acc_no <= 0) {
        printf("❌ Account number must be positive!\n");
        fclose(fp);
        return;
    }

    if (accountExists(b.acc_no)) {
        printf("❌ Account already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    scanf("%s", b.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &b.balance);

    if (b.balance < 0) {
        printf("❌ Initial balance cannot be negative!\n");
        fclose(fp);
        return;
    }

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("✅ Account created successfully!\n");
}

//Deposit Money 
void deposit() {
    struct bank b;
    FILE *fp = fopen("bank.txt", "rb+");
    int acc;
    float amt;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.acc_no == acc) {
            printf("Enter deposit amount: ");
            scanf("%f", &amt);

            if (amt <= 0) {
                printf("❌ Deposit must be greater than 0!\n");
                fclose(fp);
                return;
            }

            b.balance += amt;
            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);

            printf("✅ Deposit successful!\n");
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("❌ Account not found!\n");
}

// Withdraw Money 
void withdrawMoney() {
    struct bank b;
    FILE *fp = fopen("bank.txt", "rb+");
    int acc;
    float amt;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.acc_no == acc) {
            printf("Enter withdrawal amount: ");
            scanf("%f", &amt);

            if (amt <= 0) {
                printf("❌ Withdrawal must be greater than 0!\n");
                fclose(fp);
                return;
            }

            if (amt > b.balance) {
                printf("❌ Insufficient balance!\n");
                fclose(fp);
                return;
            }

            b.balance -= amt;
            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);

            printf("✅ Withdrawal successful!\n");
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("❌ Account not found!\n");
}

// Display Accounts 
void displayAccounts() {
    struct bank b;
    FILE *fp = fopen("bank.txt", "rb");

    printf("\nAcc No\tName\tBalance\n");
    while (fread(&b, sizeof(b), 1, fp)) {
        printf("%d\t%s\t%.2f\n", b.acc_no, b.name, b.balance);
    }
    fclose(fp);
}

// Delete Account 
void deleteAccount() {
    struct bank b;
    FILE *fp = fopen("bank.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");
    int acc, found = 0;

    printf("Enter Account Number to delete: ");
    scanf("%d", &acc);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.acc_no != acc) {
            fwrite(&b, sizeof(b), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("bank.txt");//delete the file permanently
    rename("temp.txt", "bank.txt"); // replace the file name with newname

    if (found)
        printf("✅ Account deleted successfully!\n");
    else
        printf("❌ Account not found!\n");
}