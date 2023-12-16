#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <dirent.h>

/* When user make payment current time data will be needed to write a reciept
https://www.tutorialspoint.com/c_standard_library/time_h.htm
https://www.tutorialspoint.com/c_standard_library/c_function_gmtime.htm
*/
#define BST (+5)
#define CCT (+8)

typedef struct
{
    char name[40];
    char surname[40];
    char username[20];
    char password[20];
    char phoneNumber[20];
    int walletNumber;
    double balance;

} UserInfo;

void start(UserInfo *user);
void menu(UserInfo *user);
void paymentMenu(UserInfo *user);
void createUser(UserInfo *user);
bool usernameAvalibility(char username[]);
void paymentHistory(UserInfo *user);
void checkLogin(UserInfo *user);
void makeDeposit(UserInfo *user);
void sendMoney(UserInfo *user);
void makePayment(UserInfo *user);
void updateBalance(int wallet, double newbalance);
void deleteUser(UserInfo *user, FILE *dataBase);

int main()
{

    srand(time(0));

    UserInfo user;

    start(&user);

    menu(&user);

    return 0;
}

void start(UserInfo *user)
{

    for (int i = 0; i == 0;)
    {

        int answer;
        printf("Do you have an account(If answer is yes enter 1 else enter 0): ");
        scanf("%d", &answer);

        switch (answer)
        {
        case 1:
            i++;
            checkLogin(user);
            break;
        case 0:
            i++;
            createUser(user);
            break;
        default:
            printf("There is no operations available(you have entered an invalid answer)");
            break;
        }
    }
}

void menu(UserInfo *user)
{

    while (1)
    {
        printf("-----------------------------------\n");
        printf("\t%s ", user->name);
        printf("%s\n", user->surname);
        printf("-----------------------------------\n");
        printf("\tWallet: %d\n", user->walletNumber);
        printf("\tBalance: %.3lf sum\n\n", user->balance);

        printf("---------------------- \n");
        printf("Available operations: \n");
        printf("----------------------\n\n");

        printf("Make deposit (enter 1) \n");
        printf("Make a payment (enter 2) \n");
        printf("Send money to existing user in this program(commission free) (enter 3) \n");
        printf("Payment history (enter 4) \n");
        printf("Exit (enter 5) \n");

        int command;
        scanf("%d", &command);

        switch (command)
        {
        case 1:
            makeDeposit(user);
            break;

        case 2:
            paymentMenu(user);
            break;

        case 3:
            sendMoney(user);
            break;

        case 4:
            paymentHistory(user);
            break;

        case 5:
            Beep(2000, 400);
            Beep(3000, 500);
            Beep(2000, 400);
            exit(1);
            return;
            break;

        default:
            printf("There is no operations available(you have entered an invalid answer)");
            break;
        }
        break;
    }
}

void paymentMenu(UserInfo *user)
{

    system("cls");
    int answer;
    printf("\tAvailable operations: \n");
    printf("Mobile number (enter 1)\n");
    printf("Utility bills (enter 2)\n");
    printf("Electronic wallets (enter 3)\n");
    printf("Credit bills (enter 4)\n");
    printf("Return to main menu (enter 5)\n");

    scanf("%d", &answer);

    switch (answer)
    {
    case 1:
        printf("Enter phone number: ");
        makePayment(user);
        break;

    case 2:
        printf("Enter Id number: ");
        makePayment(user);
        break;

    case 3:
        printf("Enter your wallet Id or number: ");
        makePayment(user);
        break;

    case 4:
        printf("Enter credit Id Number: ");
        makePayment(user);
        break;

    case 5:
        break;

    default:
        printf("There is no operations available(you have entered an invalid answer)");
        Sleep(1500);
        system("cls");
        menu(user);
        break;
    }
    Sleep(1500);
    system("cls");
}

void createUser(UserInfo *user)
{
    FILE *dataBase = fopen("DataBase.txt", "a");

    if (dataBase == NULL)
    {
        perror("Error opening database file");
        return;
    }

    printf("Enter your name: ");
    scanf("%s", user->name);
    printf("Enter your last name: ");
    scanf(" %s", user->surname);
    printf("Enter your phone number (+998112345678): ");
    scanf(" %s", user->phoneNumber);

    while (1)
    {
        printf("Create a username: ");
        scanf(" %s", user->username);

        if (!(usernameAvalibility(user->username)))
        {
            Beep(500, 800);
            printf("Another user is using this username. Enter another username.\n");
        }
        else
        {
            break;
        }
    }

    printf("Create a password: ");
    scanf(" %s", user->password);

    user->walletNumber = rand() % 10000;
    user->walletNumber *= 10;
    user->walletNumber += rand() % 10;

    fprintf(dataBase, "UserData:\n");
    fprintf(dataBase, "Name: %s\n", user->name);
    fprintf(dataBase, "Surname: %s\n", user->surname);
    fprintf(dataBase, "PhoneNumber: %s\n", user->phoneNumber);
    fprintf(dataBase, "Username: %s\n", user->username);
    fprintf(dataBase, "Password: %s\n", user->password);
    fprintf(dataBase, "WalletNumber: %d\n", user->walletNumber);
    fprintf(dataBase, "Balance: %.3lf\n", user->balance);
    fprintf(dataBase, "%s", "\n\n\n");

    fclose(dataBase);

    printf("Registration successfully completed.\n");
    Beep(1800, 800);

    fclose(dataBase);
    Sleep(1500);
    system("cls");
    makeDeposit(user);
}

bool usernameAvalibility(char username[])
{

    FILE *dataBase = fopen("DataBase.txt", "r");

    while (1)
    {
        char check[50];
        fscanf(dataBase, "%s", check);
        if (feof(dataBase))
        {
            if (strcmp(username, check) == 0)
            {
                return false;
            }
            break;
        }
        if (strcmp(username, check) == 0)
        {
            return false;
        }
    }

    return true;
}

void checkLogin(UserInfo *user)
{
    FILE *dataBase = fopen("DataBase.txt", "r");

    if (dataBase == NULL)
    {
        Beep(300, 300);
        Beep(500, 400);
        Beep(300, 300);
        perror("Error opening database file");
        return;
    }

    char username[50];
    char inpassword[50];
    char inpassword2[50];

    printf("Enter Username: ");
    scanf(" %s", username);
    printf("Enter password: ");
    scanf(" %s", inpassword);

    strcpy(inpassword2, inpassword);

    int loginSuccessful = 0;

    char def[20];

    while (1)
    {
        fscanf(dataBase, "%s", def);

        if (strcmp(def, "UserData:") == 0)
        {
            fscanf(dataBase, "%s", def);
        }

        fscanf(dataBase, "%s", user->name);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", user->surname);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", user->phoneNumber);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", user->username);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", user->password);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%d", &user->walletNumber);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%lf", &user->balance);

        if ((strcmp(username, user->username) == 0) && (strcmp(inpassword, user->password) == 0 || strcmp(inpassword2, user->password) == 0))
        {
            Beep(2000, 1000);
            printf("Log in was successful\n");
            loginSuccessful = 1;
            break;
        }
        if (feof(dataBase))
        {
            break;
        }
    }

    if (!loginSuccessful)
    {
        Beep(300, 300);
        Beep(500, 400);
        Beep(300, 300);
        printf("Incorrect or non-existent username and password\n");
        printf("Do you want to register? Enter 1, 0 to retry:\n");
        int an;
        scanf("%d", &an);

        if (an)
        {
            system("cls");
            fclose(dataBase);
            createUser(user);
        }
        else
        {
            system("cls");
            fclose(dataBase);
            checkLogin(user);
        }
    }

    fclose(dataBase);

    Sleep(1500);
    system("cls");

    menu(user);
}

void makePayment(UserInfo *user)
{

    char number[50];
    double amount;

    scanf(" %s", number);

    printf("How much you want to send: ");
    scanf("%lf", &amount);

    int confirm;
    printf("Are you sure you want to continue (enter 1, otherwise enter 0): ");
    scanf("%d", &confirm);

    if (confirm != 1)
    {
        printf("Payment cancelled.\n");
        return;
    }

    // Validate that the user has sufficient balance before processing the payment
    if (amount > user->balance)
    {
        printf("Invalid amount. There are insufficient funds in your account.\n");
        Sleep(1500);
        menu(user);
        return;
    }

    /* To'lov qilingan paytda vaqtni olish uchun kerak bo'ladi
    https://www.tutorialspoint.com/c_standard_library/time_h.htm
    https://www.tutorialspoint.com/c_standard_library/c_function_gmtime.htm
    */

    time_t rawtime;
    struct tm *info;

    time(&rawtime);
    /* Get GMT time */
    info = gmtime(&rawtime);
    (info->tm_hour + BST) % 24, info->tm_min;

    user->balance -= amount + (amount * 0.001);

    // User pul operatsiyasini qilsa saqlab qoýadigan file
    char fileName[100];
    strcpy(fileName, user->username);
    strcat(fileName, "payments.txt");

    FILE *payments = fopen(fileName, "a");

    if (payments == NULL)
    {
        perror("Error opening payments file");
        return;
    }

    // Yuqoridagi filega kerakli ma'lumotlarni kiritish
    fprintf(payments, "From: %s %s\n", user->name, user->surname);
    fprintf(payments, "To whom: %s\n", number);
    fprintf(payments, "Transfer amount: %.2lf\n", amount);
    fprintf(payments, "Commission: %.2lf\n", amount * 0.001);
    fprintf(payments, "Total: %.2lf\n", amount + (amount * 0.001));
    fprintf(payments, "Date and time: %02d.%02d.2023\t", info->tm_mday, info->tm_mon + 1);
    fprintf(payments, "%2d:%02d\n", (info->tm_hour + BST) % 24, info->tm_min);
    fprintf(payments, "Issued by: %s\n\n", "FAKE PAYMENTS LLC");

    fclose(payments);

    printf("The payment was made successfully. Your remaining balance: %.2lf sum\n", user->balance);
    Beep(1800, 1000);

    updateBalance(user->walletNumber, user->balance);

    Sleep(1500);
    system("cls");
    fclose(payments);
    menu(user);
}

void makeDeposit(UserInfo *user)
{

    FILE *dataBase = fopen("DataBase.txt", "r");

    double deposit;
    printf("How much you want to deposit: ");
    scanf("%lf", &deposit);

    user->balance = user->balance + deposit;

    
    time_t rawtime;
    struct tm *info;

    time(&rawtime);
    /* Get GMT time */
    info = gmtime(&rawtime);
    (info->tm_hour + BST) % 24, info->tm_min;

    // User pul operatsiyasini qilsa saqlab qoýadigan file
    char fileName[100];
    strcpy(fileName, user->username);
    strcat(fileName, "payments.txt");

    FILE *payments = fopen(fileName, "a");

    if (payments == NULL)
    {
        perror("Error opening payments file");
        return;
    }

    // Yuqoridagi filega kerakli ma'lumotlarni kiritish
    fprintf(payments, "Wallet holder: %s %s\n", user->name, user->surname);
    fprintf(payments, "Total Deposit: %.2lf\n", deposit);
    fprintf(payments, "Date and time: %02d.%02d.2023\t", info->tm_mday, info->tm_mon + 1);
    fprintf(payments, "%2d:%02d\n", (info->tm_hour + BST) % 24, info->tm_min);
    fprintf(payments, "Issued by: %s\n\n", "FAKE PAYMENTS LLC");

    fclose(payments);

    updateBalance(user->walletNumber, user->balance);

    printf("The deposit was made successfully ");

    Sleep(1500);
    Beep(1100, 500);	
    system("cls");

    menu(user);
}

// Database da mavjud bo'lgan walletga pul yuborish uchun
void sendMoney(UserInfo *user)
{

    FILE *dataBase = fopen("DataBase.txt", "r");

    if (dataBase == NULL)
    {
        perror("Error opening database file");
        return;
    }

    int walletAdress;
    double amount;

    printf("Enter the wallet number: ");
    scanf("%d", &walletAdress);
    printf("How much money you want to send: ");
    scanf("%lf", &amount);

    char name2[50];
    char def[15];
    char surname[50];
    int walletnum;
    double balance;

    while (1)
    {
        fscanf(dataBase, "%s", def);

        if (strcmp(def, "UserData:") == 0)
        {
            fscanf(dataBase, "%s", def);
        }

        fscanf(dataBase, "%s", name2);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", surname);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%d", &walletnum);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%lf", &balance);

        if (walletAdress == walletnum)
        {
            break;
        }
        if (feof(dataBase))
        {
            break;
        }
    }

    int an;
    printf("Name of the payee: %s\n", name2);
    printf("Do you want to continue paying (1 to continue): ");
    scanf("%d", &an);

    if (an != 1)
    {
        Beep(300, 300);
        Beep(500, 400);
        Beep(300, 300);
        printf("Payment stopped!");
        menu(user);
    }

    if (amount > user->balance)
    {
        printf("Invalid amount. There are insufficient funds in your account.\n");
        Beep(300, 300);
        Beep(500, 400);
        Beep(300, 300);

        Sleep(1500);
        menu(user);
        return;
    }

    user->balance -= amount;

    time_t rawtime;
    struct tm *info;

    time(&rawtime);
    /* Get GMT time */
    info = gmtime(&rawtime);
    (info->tm_hour + BST) % 24, info->tm_min;

    char fileName[100] = "";
    strcpy(fileName, user->username);
    strcat(fileName, "payments.txt");

    FILE *payments = fopen(fileName, "a");

    if (payments == NULL)
    {
        perror("Error opening payments file");
        return;
    }

    fprintf(payments, "From: %s %s\n", user->name, user->surname);
    fprintf(payments, "To whom: %d\n", walletAdress);
    fprintf(payments, "Transfer amount: %.2lf\n", amount);
    fprintf(payments, "Commission: %.2lf\n", 0.00);
    fprintf(payments, "Total: %.2lf\n", amount);
    fprintf(payments, "Date and time: %02d.%02d.2023\t", info->tm_mday, info->tm_mon + 1);
    fprintf(payments, "%2d:%02d\n", (info->tm_hour + BST) % 24, info->tm_min);
    fprintf(payments, "Issued by: %s\n\n", "FAKE PAYMENTS LLC");

    fclose(payments);

    printf("The payment was made successfully. Your remaining balance: %.2lf sum\n", user->balance);
    Beep(2000, 900);

    fclose(dataBase);

    updateBalance(user->walletNumber, user->balance);
    updateBalance(walletAdress, balance + amount);

    Sleep(1500);
    system("cls");

    menu(user);
}

// Database dagi userning eki balansini yangisiga almashtiruvchi funksiya
void updateBalance(int wallet, double newbalance)
{
    FILE *dataBase = fopen("DataBase.txt", "r+");

    if (dataBase == NULL)
    {
        perror("Error opening database file");
        return;
    }

    int walletnum;
    char oldbalance[20];
    char def[20];

    while (1)
    {
        fscanf(dataBase, "%s", def);

        if (strcmp(def, "UserData:") == 0)
        {
            fscanf(dataBase, "%s", def);
        }

        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%d", &walletnum);
        fscanf(dataBase, "%s", def);
        fscanf(dataBase, "%s", oldbalance);

        if (walletnum == wallet)
        {
            break;
        }
        if (feof(dataBase))
        {
            break;
        }
    }

    fseek(dataBase, -(strlen(oldbalance)), SEEK_CUR);
    fprintf(dataBase, "%.2lf\n", newbalance);
    // fseek(dataBase, 0, SEEK_CUR);

    fclose(dataBase);
}

void paymentHistory(UserInfo *user)
{

    char fileName[100] = "";
    strcpy(fileName, user->username);
    strcat(fileName, "payments.txt");

    FILE *payments = fopen(fileName, "r");

    while (1)
    {
        char c = fgetc(payments);
        if (feof(payments))
        {
            break;
        }

        printf("%c", c);
    }
    printf("To return to the main menu 1: ");
    int an;
    scanf("%d", &an);
    if (an == 1)
    {
        system("cls");
        Beep(2000, 900);
        menu(user);
    }
    Sleep(3000);
    Beep(2000, 900);
    menu(user);
}