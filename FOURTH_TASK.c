#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int accNo;
    char holderName[50];
    double balance;
} Account;

void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();

int main() {
    int ch;

    while(1) {
        printf("\n===== MINI BANKING SYSTEM =====");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Balance Enquiry");
        printf("\n5. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        if(ch == 1)
            createAccount();
        else if(ch == 2)
            depositMoney();
        else if(ch == 3)
            withdrawMoney();
        else if(ch == 4)
            checkBalance();
        else if(ch == 5)
            exit(0);
        else
            printf("Wrong Choice\n");
    }

    return 0;
}

void createAccount() {
    FILE *f;
    Account a;

    f = fopen("bank.dat", "ab");

    printf("Enter Account Number: ");
    scanf("%d", &a.accNo);

    printf("Enter Account Holder Name: ");
    getchar();
    fgets(a.holderName, sizeof(a.holderName), stdin);

    printf("Enter Initial Deposit: ");
    scanf("%lf", &a.balance);

    fwrite(&a, sizeof(Account), 1, f);

    fclose(f);

    printf("Account Created\n");
}

void depositMoney() {
    FILE *f;
    Account a;
    int accNo, flag = 0;
    double amt;

    f = fopen("bank.dat", "rb+");

    if(f == NULL) {
        printf("No Accounts Found\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&a, sizeof(Account), 1, f)) {

        if(a.accNo == accNo) {

            printf("Current Balance : %.2lf\n", a.balance);

            printf("Enter Amount: ");
            scanf("%lf", &amt);

            a.balance = a.balance + amt;

            fseek(f, -sizeof(Account), SEEK_CUR);
            fwrite(&a, sizeof(Account), 1, f);

            printf("Deposit Successful\n");

            flag = 1;
            break;
        }
    }

    if(flag == 0)
        printf("Account Not Found\n");

    fclose(f);
}

void withdrawMoney() {
    FILE *f;
    Account a;
    int accNo, flag = 0;
    double amt;

    f = fopen("bank.dat", "rb+");

    if(f == NULL) {
        printf("No Accounts Found\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&a, sizeof(Account), 1, f)) {

        if(a.accNo == accNo) {

            printf("Current Balance : %.2lf\n", a.balance);

            printf("Enter Amount: ");
            scanf("%lf", &amt);

            if(amt > a.balance) {
                printf("Insufficient Balance\n");
            }
            else {
                a.balance = a.balance - amt;

                fseek(f, -sizeof(Account), SEEK_CUR);
                fwrite(&a, sizeof(Account), 1, f);

                printf("Withdrawal Successful\n");
            }

            flag = 1;
            break;
        }
    }

    if(flag == 0)
        printf("Account Not Found\n");

    fclose(f);
}

void checkBalance() {
    FILE *f;
    Account a;
    int accNo, flag = 0;

    f = fopen("bank.dat", "rb");

    if(f == NULL) {
        printf("No Accounts Found\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&a, sizeof(Account), 1, f)) {

        if(a.accNo == accNo) {

            printf("\nAccount No : %d", a.accNo);
            printf("\nHolder Name : %s", a.holderName);
            printf("Balance : %.2lf\n", a.balance);

            flag = 1;
            break;
        }
    }

    if(flag == 0)
        printf("Account Not Found\n");

    fclose(f);
}