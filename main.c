#include <stdio.h>
#include <string.h>
#include <windows.h>

// Constants
#define MAX_ALLOWED_ACCOUNTS 100
#define SLEEP_IN_ANIMATION 1000
#define CIN_SIZE 10
#define NAME_SIZE 50

// Declaration of Account Structure
typedef struct S_Account{
    char CIN[CIN_SIZE];
    char nomPrenom[NAME_SIZE];
    double montant;
} Account;

// Declaration of Order types
typedef enum S_Order {
    ASC,
    DESC
} Order;

// Declaration of Global Variables
Account accounts[MAX_ALLOWED_ACCOUNTS];
Account * currentAccount = NULL;
int nOfAccounts = 0;

// Functions
void createMultiAccounts();
void createAccount();
void withdraw();
void deposit();
void swap(Account*, Account*);
void selectionSort(Order);
void printAccounts(double, int);
void displayAccounts(Order, double);
void search(char*);
void loyaltyBonus(); // TODO: Change montant to multi account
void sendMoney();
void generateTestAccount();
void showOperationsMenu();
void showDisplayMenu();
void changePrimaryAccount();
void saveToFile();
void openFromFile();


/** \brief The main Function that executes the flow of the program
 *
 * \return int
 *
 */
int main()
{
    int choice;
    printf("Welcome to M-AB Bank Solution!\n\n");

    // Loading();

    MAIN_MENU:
    system("cls");
    do {
        if(nOfAccounts > 0){
            printf("Curent Primary Account:\n");
            printf("CIN: %s\tName: %s\tMontant: %.2lf\n\n", (*currentAccount).CIN, (*currentAccount).nomPrenom, (*currentAccount).montant);
        }
        printf("Please select from the Menu below:\n");
        printf("#############################--MAIN MENU--#############################\n\n");
        printf("1: Create Account\t2: Create multiple Accounts\t3: Use test Accounts\n");
        printf("4: Operations\t5: Display\t6: Loyalty Bonus\t7: Change Primary Account\n");
        printf("8: Save accounts to file\t9: Load accounts from save file\n");
        printf("0: EXIT\n\n:::");
        scanf("%d", &choice);
        getc(stdin);
    } while(choice < 0 || choice > 9);

    switch(choice){
    case 0:
        printf("Thanks for using our service! Have a great weekend.");
        Sleep(SLEEP_IN_ANIMATION);
        printf(".");
        Sleep(SLEEP_IN_ANIMATION);
        printf(".");
        exit(0);
    case 1:
        createAccount();
        printAccounts(0, nOfAccounts);
        system("pause");
        goto MAIN_MENU;
        break;
    case 2:
        createMultiAccounts();
        printAccounts(0, nOfAccounts);
        system("pause");
        goto MAIN_MENU;
        break;
    case 3:
        generateTestAccount();
        printAccounts(0, nOfAccounts);
        system("pause");
        goto MAIN_MENU;
        break;
    case 4:
        if(nOfAccounts == 0){
            printf("/!\\You Can't access these features unless you create 1 or more accounts,/!\\\n/!\\Please Create an Account or generate a test account from the Menu./!\\\n");
            system("pause");
            goto MAIN_MENU;
            break;
        }
        showOperationsMenu();
        system("pause");
        goto MAIN_MENU;
        break;
    case 5:
        if(nOfAccounts == 0){
            printf("/!\\You Can't access these features unless you create 1 or more accounts,/!\\\n/!\\Please Create an Account or generate a test account from the Menu./!\\\n");
            system("pause");
            goto MAIN_MENU;
            break;
        }
        showDisplayMenu();
        system("pause");
        goto MAIN_MENU;
        break;
    case 6:
        if(nOfAccounts == 0){
            printf("/!\\You Can't access these features unless you create 1 or more accounts,/!\\\n/!\\Please Create an Account or generate a test account from the Menu./!\\\n");
            system("pause");
            goto MAIN_MENU;
            break;
        }
        loyaltyBonus();
        system("pause");
        goto MAIN_MENU;
        break;
    case 7:
        if(nOfAccounts == 0){
            printf("/!\\You Can't access these features unless you create 1 or more accounts,/!\\\n/!\\Please Create an Account or generate a test account from the Menu./!\\\n");
            system("pause");
            goto MAIN_MENU;
            break;
        }
        changePrimaryAccount();
        system("pause");
        goto MAIN_MENU;
        break;
    case 8:
        if(nOfAccounts == 0){
            printf("/!\\You Can't access these features unless you create 1 or more accounts,/!\\\n/!\\Please Create an Account or generate a test account from the Menu./!\\\n");
            system("pause");
            goto MAIN_MENU;
            break;
        }
        printf("Saving to file.");
        Sleep(SLEEP_IN_ANIMATION);
        printf(".");
        Sleep(SLEEP_IN_ANIMATION);
        printf(".\n");
        saveToFile();
        system("pause");
        goto MAIN_MENU;
        break;
    case 9:
        printf("Loading from file.");
        Sleep(SLEEP_IN_ANIMATION);
        printf(".");
        Sleep(SLEEP_IN_ANIMATION);
        printf(".\n");
        openFromFile();
        if(nOfAccounts != 0){
            changePrimaryAccount();
        }
        system("pause");
        goto MAIN_MENU;
        break;

    }

    return 0;
}

/** \brief Function that creates multiple accounts at once.
 *
 * \return void
 *
 */
void createMultiAccounts(){
    int size, i;

    printf("How many accounts would you like to create? ");
    scanf("%d", &size);

    for(i = 0; i< size; i++){
        createAccount();
    }
}

/** \brief Function that creates an account with user input.
 *
 * \return void
 *
 */
void createAccount(){
    if(nOfAccounts == MAX_ALLOWED_ACCOUNTS){
        printf("\n/!\\ You're not allowed to create more than %d accounts! /!\\\n", MAX_ALLOWED_ACCOUNTS);
        return;
    }

    char CIN[CIN_SIZE], nomPrenom[NAME_SIZE];

    double montant;

    printf("Enter your CIN: ");
    gets(CIN);
    strcpy(accounts[nOfAccounts].CIN, CIN);

    printf("Enter your First Name and Last Name: ");
    gets(nomPrenom);
    strcpy(accounts[nOfAccounts].nomPrenom, nomPrenom);

    printf("Enter how much Credit this account have: ");
    scanf("%lf", &montant);
    accounts[nOfAccounts].montant = montant;

    if(currentAccount == NULL)
        currentAccount = &accounts[nOfAccounts];

    nOfAccounts++;
}

/** \brief A function that withdraws money from a specific account
 *
 * \return void
 *
 */
void withdraw(){
    double montant;

    while(1){
        printf("How much would you like to retreat? ");
        scanf("%lf", &montant);

        if((*currentAccount).montant < montant){
            printf("/!\\You don't have that much money to begin with! Enter a smaller amount... please./!\\");
            continue;
        } else
            break;
    }

    (*currentAccount).montant-= montant;
}

/** \brief A function that adds credit to a specific account
 *
 * \return void
 *
 */
void deposit(){
    double montant;

    while(1){
        printf("How much would you like to deposit? ");
        scanf("%lf", &montant);

        if(montant <= 0){
            printf("\n/!\\The amount you entered is so small that we can't even see it... Enter a bigger amount... please/!\\\n");
            continue;
        } else
            break;
    }

    (*currentAccount).montant+= montant;
}

/** \brief A function that switches two Accounts directly in the array
 *
 * \param xp Account*
 * \param yp Account*
 * \return void
 *
 */
void swap(Account *xp, Account *yp)
{
    Account temp;

    strcpy(temp.CIN, (*xp).CIN);
    strcpy(temp.nomPrenom, (*xp).nomPrenom);
    temp.montant = (*xp).montant;

    strcpy((*xp).CIN, (*yp).CIN);
    strcpy((*xp).nomPrenom, (*yp).nomPrenom);
    (*xp).montant = (*yp).montant;

    strcpy((*yp).CIN, temp.CIN);
    strcpy((*yp).nomPrenom, temp.nomPrenom);
    (*yp).montant = temp.montant;

    //printf("x: %x, y: %x, c: %x\n", xp, yp, currentAccount);
}

/** \brief A function to sort Accounts based on sortOrder
 *
 * \param sortOrder Order
 * \return void
 *
 */
void selectionSort(Order sortOrder){
    int i, j, idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < nOfAccounts-1; i++)
    {
        // Find the minimum element in unsorted array
        idx = i;
        if(sortOrder == ASC){
            for (j = i+1; j < nOfAccounts; j++)
              if (accounts[j].montant < accounts[idx].montant)
                idx = j;
        }
        else if(sortOrder == DESC){
            for (j = i+1; j < nOfAccounts; j++)
              if (accounts[j].montant > accounts[idx].montant)
                idx = j;
        }

        // Save current value before swapping
            if(&accounts[idx] == currentAccount)
                currentAccount = &accounts[i];
            else if(&accounts[i] == currentAccount)
                currentAccount = &accounts[idx];

        // Swap the found minimum/maximum element with the first element
        swap(&accounts[idx], &accounts[i]);
    }
}

/** \brief A function that prints the available accounts
 *
 * \param min double
 * \return void
 *
 */
void printAccounts(double min, int nOfLines){
    int i;
    for(i=0; i<nOfLines; i++){
        if(accounts[i].montant < min)
            continue;
        printf("Account N_%d:\nCIN: %s\tName: %s\tMontant: %.2lf\n", i+1, accounts[i].CIN, accounts[i].nomPrenom, accounts[i].montant);
    }
}

/** \brief A function that sorts and shows arrays according to displayOrder
 *
 * \param displayOrder Order
 * \param min double
 * \return void
 *
 */
void displayAccounts(Order displayOrder, double min){

    printf("Here are the Available accounts sorted in %s order:\n", displayOrder == ASC ? "Ascending" : "Descending");
    switch(displayOrder){
    case ASC:
        selectionSort(ASC);
        printAccounts(min, nOfAccounts);
        break;
    case DESC:
        selectionSort(DESC);
        printAccounts(min, nOfAccounts);
        break;
    }
}

/** \brief A function that returns index of element if found and -1 if not
 *
 * \param cin char*
 * \return int
 *
 */
void search(char *cin){
    int i, index = -1, choice;
    for(i = 0; i< nOfAccounts; i++){
        if(strcmp(accounts[i].CIN, cin) == 0){
            index = i;
            break;
        }
    }
    if(index == -1){
        printf("\nCIN not found!\n");
    } else {
        printf("\nCIN found at %d\n", index);
        do{
            printf("Would you like to make it your Primary Account for Transactions? 1: YES, 2: NO : ");
            scanf("%d", &choice);
        } while(choice != 1 && choice != 2);
        if(choice == 1){
            currentAccount = &accounts[index];
        }
    }
}

/** \brief A function that adds 1.3% bonus to loyal costumers that has the most assets at any given time.
 *
 * \return void
 *
 */
void loyaltyBonus(){
    int i = 0, changeCounter = 0, accountsCounter = 0;
    selectionSort(DESC);


    while(changeCounter < 3){
        if(accounts[i].montant != accounts[i + 1].montant)
            changeCounter++;
        accountsCounter++;
        i++;
    }

    printf("\nAccounts *before* adding Loyalty Bonus:\n");
    printAccounts(0, accountsCounter);

    for(i = 0; i < accountsCounter; i++)
        accounts[i].montant += (accounts[i].montant * 0.013);

    printf("\nAccounts *after* adding Loyalty Bonus:\n");
    printAccounts(0, accountsCounter);
}

/** \brief A function to send money from account to account while the credit is enough.
 *
 * \param amount double
 * \param recipientIndex int
 * \return void
 *
 */
void sendMoney(){
    double amount;
    int recipientIndex;
    printf("How much would you like to send? ");
    scanf("%lf", &amount);

    printAccounts(0, nOfAccounts);
    printf("\nTo who would you like to send? select from the list Above: ");
    scanf("%d", &recipientIndex);

    if((*currentAccount).montant >= amount){
        (*currentAccount).montant -= amount;
        accounts[recipientIndex-1].montant += amount;
    } else {
        printf("\n/!\\You don't Have enough money, try lowering the amount a bit next time.../!\\\n");
    }

}

/** \brief A function that generates a Test Account with random values.
 *
 * \return void
 *
 */
void generateTestAccount() {
    int index, i;
    char temp[8], charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if(nOfAccounts == 100){
        printf("/!\\Number of accounts is limited to 100./!\\\n");
        return;
    }

    // Generating random Name
    for(i = 0; i< 6; i++) {
        index = rand() % (sizeof(charset)/sizeof(charset[0]));
        temp[i] = charset[index];
    }
    temp[6] = '\0';
    strcpy(accounts[nOfAccounts].nomPrenom, temp);

    // Generating random CIN
    for(i = 0; i< 6; i++) {
        index = rand() % (sizeof(charset)/sizeof(charset[0]));
        temp[i] = charset[index];
    }
    temp[6] = '\0';
    strcpy(accounts[nOfAccounts].CIN, temp);

    // Generating random Montant
    accounts[nOfAccounts].montant = (double)(rand() % 100) * 1000;
    if(currentAccount == NULL)
        currentAccount = &accounts[nOfAccounts];

    nOfAccounts++;
}

/** \brief A function that shows the Operations sub-menu and manages calls for appropriate functions
 *
 * \return void
 *
 */
void showOperationsMenu(){
    int choice;
    do{
        printf("Please select from the Menu below:\n");
        printf("############################--Operations--#############################\n\n");
        printf("1: Withdraw\t2: Deposit\t3: Send Money\t0: Return to Main Menu\n\n:::");
        scanf("%d", &choice);
    } while(choice < 0 || choice > 3);
    getc(stdin);
    switch(choice){
    case 0:
        break;
    case 1:
        withdraw();
        break;
    case 2:
        deposit();
        break;
    case 3:
        sendMoney();
        break;
    }
}

/** \brief A function that shows the Display sub-menu and manages calls for appropriate functions
 *
 * \return void
 *
 */
void showDisplayMenu(){
    int choice;
    double limit = 0;
    char cin[CIN_SIZE];

    do{
        printf("Please select from the Menu below:\n");
        printf("#############################--Display--###############################\n\n");
        printf("1: Show Accounts in Ascending order\t2: Show Accounts in Descending order\n");
        printf("3: Show Accounts in Ascending order with Minimum limit\n");
        printf("4: Show Accounts in Descending order with Minimum limit\n");
        printf("5: Search for CIN\n");
        printf("0: Return to Main Menu\n\n:::");
        scanf("%d", &choice);
    } while(choice < 0 || choice > 5);
    getc(stdin);

    switch(choice){
    case 0:
        break;
    case 1:
        displayAccounts(ASC, limit);
        break;
    case 2:
        displayAccounts(DESC, limit);
        break;
    case 3:
        do{
            printf("Please enter a limit greater than 0: ");
            scanf("%lf", &limit);
        } while(limit<0);
        displayAccounts(ASC, limit);
        break;
    case 4:
        do{
            printf("Please enter a limit greater than 0: ");
            scanf("%lf", &limit);
        } while(limit<0);
        displayAccounts(DESC, limit);
        break;
    case 5:
        printf("Please enter a valid CIN: ");
        gets(cin);

        search(cin);
        break;
    }

}

/** \brief A function to change the primary account of operations to an account of choice
 *
 * \return void
 *
 */
void changePrimaryAccount(){
    int choice;
    printAccounts(0, nOfAccounts);
    do{
        printf("Please choose an account from the list above: ");
        scanf("%d", &choice);
    } while(choice < 1 || choice > nOfAccounts);

    currentAccount = &accounts[choice-1];
    printf("Changed Successfully!");
}

/** \brief A function to save accounts to file to load afterwards
 *
 * \return void
 *
 */
void saveToFile(){
    int i;
    FILE *fptr;
    fptr = fopen("accounts.txt","a+");

    if(fptr == NULL){
      printf("/!\\Permission denied./!\\\n");
    } else {
        for(i = 0; i< nOfAccounts; i++){
            fprintf(fptr, "%s\n%s\n%.2lf\n\n", accounts[i].CIN, accounts[i].nomPrenom, accounts[i].montant);
        }
        printf("Saved %d accounts Successfully!\n", nOfAccounts);
        fclose(fptr);
    }
}

/** \brief A function to load accounts from save file into accounts array
 *
 * \return void
 *
 */
void openFromFile(){    int i = 0;
    FILE *fptr;
    fptr = fopen("accounts.txt","r");

    if(fptr == NULL){
      printf("/!\\Save file Can't be loaded./!\\\n");
    } else {
        while(fscanf(fptr,"%s\n%s\n%lf\n\n", accounts[i].CIN, accounts[i].nomPrenom, &accounts[i].montant) != EOF && nOfAccounts < 100){
            nOfAccounts++;
            i++;
        }

        printf("Loaded %d accounts from save file...\n", nOfAccounts);
        fclose(fptr);
    }
}
