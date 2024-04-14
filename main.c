#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include <stdbool.h>
#include<conio.h>
#include <windows.h>

#define MaxUserLengnth 30
#define MaxPassLegnth 30
#define MaxAccountNumber 10
#define MaxFirstName 30
#define MaxLastName 30
#define MaxAdress 50
#define MaxphoneNumber 11
#define Maxbalance 20
#define MaxMonthLength 2
#define MaxYearLength 4

typedef struct
{
    int month;
    int year;
}date;

typedef struct
{
    char accountNumber[MaxAccountNumber+1];
    char firstName[MaxFirstName];
    char lastName[MaxLastName];
    char emailAdress[MaxAdress];
    float balance;
    char phoneNumber[MaxphoneNumber+1];
    date dateOpened;
} info;

char currentuser[50];
char timeString[80];
int numOfAccounts;
char forceclosed=0;
info account[10000];

int main()
{
    setconsletitle();
    checkclosingstatus();
    loginNavigation();
    while (1) MENU();
    return 0;
}

void record_activity()
{
    FILE *sheet=fopen("sheet.txt","r");
    if(sheet ==NULL)
    {
        printf("No History Yet\n");
    }
    else
    {
    char temp[50];
    while(!feof(sheet))
    {
            fscanf(sheet,"%s",temp);
            printf("User : %s\n",temp);
            fscanf(sheet,"%s",temp);
            printf("Opened : %s",temp);
            fscanf(sheet,"%s",temp);
            printf("  %s\n",temp);
            fscanf(sheet,"%s",temp);
            printf("Closed : %s",temp);
            fscanf(sheet,"%s",temp);
            printf("  %s\n\n",temp);
            fgetc(sheet);
    }
    }
    fclose(sheet);
}

void checkclosingstatus()
{
    FILE *checker=fopen("checker.txt","r");
    FILE *sheet=fopen("sheet.txt","a");
    char t=fgetc(checker);
    if(t=='1')
    {
        fprintf(sheet,"%s","Forced Closed");
        FILE *checker=fopen("checker.txt","w");
    }
    fclose(sheet);
    fclose(checker);
}

void setconsletitle()
{
    char consoleTitle[15];
    wsprintf(consoleTitle, ("BANK SYSTEM"));
}

void deterimetime()
{
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S",localTime);

}

char *convertMonths(int n)
{
    switch(n)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    }
}

void logout()
{
    printf("Bye\n");

    FILE *checker=fopen("checker.txt","w");
    fclose(checker);
    FILE *sheet=fopen("sheet.txt","a");
    deterimetime();
    fprintf(sheet,"%s",timeString);
    fclose(sheet);
    loginNavigation();
}

void clear()
{
    system("cls");
}

void advancedSearch()
{
    int i,flag=0;
    char Keyword[20];
    printf("Enter the Key Word: ");
    fflush(stdin);
    scanf("%20s",Keyword);
    fflush(stdin);
    for (i = 0; i < numOfAccounts; i++)
    {
        if (stricmp(account[i].firstName,Keyword)==0 || stricmp(account[i].lastName,Keyword)==0)
        {
            printf("Account Number: %s\n", account[i].accountNumber);
            printf("Name: %s %s\n", account[i].firstName,account[i].lastName);
            printf("E-mail: %s\n", account[i].emailAdress);
            printf("Balance: %f\n", account[i].balance);
            printf("Mobile: %s\n", account[i].phoneNumber);
            printf("Opened:%s - %d\n\n",convertMonths(account[i].dateOpened.month), account[i].dateOpened.year);
            flag++;
        }
    }
    if(flag==0)
    {
        printf("there aren't any matches\n");
    }

}

void mergeByName(int left,int middle,int right)
{
    int Lcount=middle-left+1;
    int Rcount=right-middle;
    info Larr[Lcount];
    info Rarr[Rcount];
    for(int i=0; i<Lcount; i++)
    {
        Larr[i]=account[i+left];
    }
    for(int i=0; i<Rcount; i++)
    {
        Rarr[i]=account[i+middle+1];
    }
    int i=0,j=0,z=left;
    while(Lcount>i&&Rcount>j)
    {
        if(stricmp(Larr[i].firstName,Rarr[j].firstName)<0)
        {
            account[z]=Larr[i];
            i++;
        }
        else if(stricmp(Larr[i].firstName,Rarr[j].firstName)>0)
        {
            account[z]=Rarr[j];
            j++;
        }
        else
        {
            if(stricmp(Larr[i].lastName,Rarr[j].lastName)<0||stricmp(Larr[i].lastName,Rarr[j].lastName)==0)
            {
                account[z]=Larr[i];
                i++;
            }
            else if(stricmp(Larr[i].lastName,Rarr[j].lastName)>0)
            {
                account[z]=Rarr[j];
                j++;
            }
        }
        z++;
    }
    while(Lcount>i)
    {
        account[z]=Larr[i];
        i++;
        z++;
    }
    while(Rcount>j)
    {
        account[z]=Rarr[j];
        j++;
        z++;
    }
}

void mergeByBalance(int left,int middle,int right)
{
    int Lcount=middle-left+1;
    int Rcount=right-middle;
    info Larr[Lcount];
    info Rarr[Rcount];
    for(int i=0; i<Lcount; i++)
    {
        Larr[i]=account[i+left];
    }
    for(int i=0; i<Rcount; i++)
    {
        Rarr[i]=account[i+middle+1];
    }
    int i=0,j=0,z=left;
    while(Lcount>i&&Rcount>j)
    {
        if(Larr[i].balance<=Rarr[j].balance)
        {
            account[z]=Larr[i];
            i++;
        }
        else
        {
            account[z]=Rarr[j];
            j++;
        }
        z++;
    }
    while(Lcount>i)
    {
        account[z]=Larr[i];
        i++;
        z++;
    }
    while(Rcount>j)
    {
        account[z]=Rarr[j];
        j++;
        z++;
    }
}

void mergeByDate(int left,int middle,int right)
{
    int Lcount=middle-left+1;
    int Rcount=right-middle;
    info Larr[Lcount];
    info Rarr[Rcount];
    for(int i=0; i<Lcount; i++)
    {
        Larr[i]=account[i+left];
    }
    for(int i=0; i<Rcount; i++)
    {
        Rarr[i]=account[i+middle+1];
    }
    int i=0,j=0,z=left;
    while(Lcount>i&&Rcount>j)
    {
        if(Larr[i].dateOpened.year<Rarr[j].dateOpened.year)
        {
            account[z]=Larr[i];
            i++;
        }
        else if(Larr[i].dateOpened.year>Rarr[j].dateOpened.year)
        {
            account[z]=Rarr[j];
            j++;
        }
        else
        {
            if(Larr[i].dateOpened.month<=Rarr[j].dateOpened.month)
            {
                account[z]=Larr[i];
                i++;
            }
            else if(Larr[i].dateOpened.month>Rarr[j].dateOpened.month)
            {
                account[z]=Rarr[j];
                j++;
            }
        }
        z++;
    }
    while(Lcount>i)
    {
        account[z]=Larr[i];
        i++;
        z++;
    }
    while(Rcount>j)
    {
        account[z]=Rarr[j];
        j++;
        z++;
    }
}

void sortByName(int left,int right)
{
    if(right>left)
    {
        int middle=(left+right)/2;
        sortByName(left,middle);
        sortByName(middle+1,right);
        mergeByName(left,middle,right);
    }
}

void sortByBalance(int left,int right)
{
    if(right>left)
    {
        int middle=(left+right)/2;
        sortByBalance(left,middle);
        sortByBalance(middle+1,right);
        mergeByBalance(left,middle,right);
    }
}

void sortByDate(int left,int right)
{
    if(right>left)
    {
        int middle=(left+right)/2;
        sortByDate(left,middle);
        sortByDate(middle+1,right);
        mergeByDate(left,middle,right);
    }
}

void PRINT()
{
    char option[20];
    printf("1)SortByName\n2)SortByBalance\n3)SortByDate\n");
    printf("please enter an option: ");
sortInvalidOption:
    fflush(stdin);
    fgets(option,sizeof(option)-1,stdin);
    fflush(stdin);
    if(!strcmp(option,"1\n"))
    {
        sortByName(0,numOfAccounts-1);
    }
    else if(!strcmp(option,"2\n"))
    {
        sortByBalance(0,numOfAccounts-1);
    }
    else if(!strcmp(option,"3\n"))
    {
        sortByDate(0,numOfAccounts-1);
    }
    else
    {
        printf("this is invalid option\n");
        printf("please enter a valid option: ");
        goto sortInvalidOption;
    }
    for(int i=0; i<=numOfAccounts-1; i++)
    {
        printf("Account Number : %s\n",account[i].accountNumber);
        printf("Name : %s %s\n",account[i].firstName,account[i].lastName);
        printf("E-mail : %s\n",account[i].emailAdress);
        printf("Balance : %.2f\n",account[i].balance);
        printf("Mobile : %s\n",account[i].phoneNumber);
        printf("Date opened : %s - %d\n\n",convertMonths(account[i].dateOpened.month),account[i].dateOpened.year);
    }

}

void MENU()
{
    char option[20];
    printf("\nCurrentuser : %s\n\n",currentuser);
    printf("1)ADD\n2)DELETE\n3)MODIFY\n4)SEARCH\n5)ADVANCED SEARCH\n6)WITHDRAW\n7)DEPOSIT\n8)TRANSFER\n9)REPORT\n10)PRINT\n11)Logout\n12)QUIT\n13)Clear\n");
    printf("please enter an option: ");
menuInvalidOption:
    fflush(stdin);
    fgets(option,sizeof(option)-1,stdin);
    fflush(stdin);
    if(!strcmp(option,"1\n"))
    {
        addaccount();
    }
    else if(!strcmp(option,"2\n"))
    {
        delete_element();
    }
    else if(!strcmp(option,"3\n"))
    {
        modify();
    }
    else if(!strcmp(option,"4\n"))
    {
        SEARCH();
    }
    else if(!strcmp(option,"5\n"))
    {
        advancedSearch();
    }
    else if(!strcmp(option,"6\n"))
    {
        WITHDRAW();
    }
    else if(!strcmp(option,"7\n"))
    {
        DEPOSIT();
    }
    else if(!strcmp(option,"8\n"))
    {
        transfer();
    }
    else if(!strcmp(option,"9\n"))
    {
        report();
    }
    else if(!strcmp(option,"10\n"))
    {
        PRINT();
    }
    else if(!strcmp(option,"11\n"))
    {
        logout();
    }
    else if(!strcmp(option,"12\n"))
    {
        Quit();
    }
    else if(!strcmp(option,"13\n"))
    {
        clear();
    }

    else
    {
        printf("this is invalid option\n");
        printf("please enter a valid option: ");
        goto menuInvalidOption;
    }
}

void LOAD()
{
    char*token;
    int i=0;
    FILE*accountsFile=fopen("accounts.txt","r");
    if(accountsFile==NULL)
    {
        printf("error in system!!!!\nPlease try again later");
        exit(0);
    }
    char LINE[MaxAccountNumber+MaxAdress+Maxbalance+MaxFirstName+MaxLastName+MaxphoneNumber+MaxMonthLength+MaxYearLength+5+1];
    while(!feof(accountsFile))
    {
        fgets(LINE,sizeof(LINE)-1,accountsFile);
        token=strtok(LINE,",");
        strcpy(account[i].accountNumber,token);
        token=strtok(NULL," ");
        strcpy(account[i].firstName,token);
        token=strtok(NULL,",");
        strcpy(account[i].lastName,token);
        token=strtok(NULL,",");
        strcpy(account[i].emailAdress,token);
        token=strtok(NULL,",");
        account[i].balance=atof(token);
        token=strtok(NULL,",");
        strcpy(account[i].phoneNumber,token);
        token=strtok(NULL,"-");
        account[i].dateOpened.month=atoi(token);
        token=strtok(NULL,"");
        account[i].dateOpened.year=atoi(token);
        i++;
    }
    numOfAccounts=i;
    fclose(accountsFile);

}

int validateCredentials(char*username,char*password)
{
    char storedUsername[MaxUserLengnth];
    char storedUserpassword[MaxPassLegnth];
    FILE*usersFile=fopen("users.txt","r");
    if(usersFile==NULL)
    {
        printf("error opening system!!!!\nPlease try again later");
        exit(-1);
    }
    while(fscanf(usersFile, "%s %s",storedUsername,storedUserpassword)==2)
    {
        if(strcmp(username,storedUsername)==0&&strcmp(password,storedUserpassword)==0)
        {
            fclose(usersFile);
            return 1;
        }
    }
    fclose(usersFile);
    return 0;
}

void LOGIN()
{
    char username[MaxUserLengnth];
    char password[MaxPassLegnth];
    fflush(stdin);
    printf("Please enter the username: ");
    scanf("%30s",username);
    fflush(stdin);
    printf("Please enter the password: ");
    scanf("%30s",password);
    fflush(stdin);
    if(validateCredentials(username,password)==1)
    {
        printf("Logged in successfully\n");
        strcpy(currentuser,username);
        FILE *sheet=fopen("sheet.txt","a");
        fprintf(sheet,"\n%s ",username);
        deterimetime();
        fprintf(sheet,"%s ",timeString);
        FILE *checker=fopen("checker.txt","w");
        fprintf(checker,"%s","1");
        fclose(sheet);
        fclose(checker);

        LOAD();
    }
    else if(validateCredentials(username,password)==0)
    {
        printf("invalid username or password\n");
        loginNavigation();
    }
}

void loginNavigation()
{
    char option[20];
    printf("1)LOGIN\n");
    printf("2)QUIT\n");
    printf("3)Record Activity\n");
    printf("please enter a option: ");
loginInvalidOption:
    fflush(stdin);
    fgets(option,sizeof(option)-1,stdin);
    fflush(stdin);
    if(!strcmp("1\n",option))
    {
        LOGIN();
    }
    else if(!strcmp("2\n",option))
    {
        Quit();
    }
    else if(!strcmp("3\n",option))
    {
        record_activity();
        loginNavigation();
    }
    else
    {
        printf("this is invalid option\n");
        printf("please enter a valid option: ");
        goto loginInvalidOption;
    }
}

void Quit()
{
    printf("Good bye :( \n");
    FILE *checker=fopen("checker.txt","w");
    fclose(checker);
    FILE *sheet=fopen("sheet.txt","a");
    deterimetime();
    fprintf(sheet,"%s",timeString);
    fclose(sheet);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    printf("*");
    SetConsoleTextAttribute(hConsole,8 );
    printf("****************************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("**");
    SetConsoleTextAttribute(hConsole, 8);
    printf("***************************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("***");
    SetConsoleTextAttribute(hConsole, 8);
    printf("**************************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("****");
    SetConsoleTextAttribute(hConsole, 8);
    printf("*************************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("*****");
    SetConsoleTextAttribute(hConsole, 8);
    printf("************************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("******");
    SetConsoleTextAttribute(hConsole, 7);
    printf("***********************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("*******");
    SetConsoleTextAttribute(hConsole, 7);
    printf("**********************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("********");
    SetConsoleTextAttribute(hConsole, 7);
    printf("*********************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("*******");
    SetConsoleTextAttribute(hConsole, 7);
    printf("**********************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("******");
    SetConsoleTextAttribute(hConsole, 7);
    printf("***********************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("*****");
    SetConsoleTextAttribute(hConsole, 2);
    printf("************************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("****");
    SetConsoleTextAttribute(hConsole, 2);
    printf("*************************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("***");
    SetConsoleTextAttribute(hConsole, 2);
    printf("**************************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("**");
    SetConsoleTextAttribute(hConsole, 2);
    printf("***************************************\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("*");
    SetConsoleTextAttribute(hConsole, 2);
    printf("****************************************\n");
    SetConsoleTextAttribute(hConsole, 7);
    exit(0);
}

void save(int n,int deleted_element)
{
    FILE*accountsFile=fopen("accounts.txt","w");
    char last=1;
    for(int i=0; i<n; i++)
    {
        if(deleted_element==n-1)
            last=2;
        if(i==deleted_element)
        {
            continue;
        }
        fprintf(accountsFile,"%s,",account[i].accountNumber);
        fprintf(accountsFile,"%s ",account[i].firstName);
        fprintf(accountsFile,"%s,",account[i].lastName);
        fprintf(accountsFile,"%s,",account[i].emailAdress);
        fprintf(accountsFile,"%f,",account[i].balance);
        fprintf(accountsFile,"%s,",account[i].phoneNumber);
        fprintf(accountsFile,"%d-",account[i].dateOpened.month);
        fprintf(accountsFile,"%d",account[i].dateOpened.year);
        if(i!=n-last)
            fprintf(accountsFile,"\n");
    }
    fclose(accountsFile);
}

void delete_element()
{
    int deleted=-1;
    char accountnumber[11];
    printf("Enter the account number you want to delete : ");
    fflush(stdin);
    scanf("%11s",accountnumber);
    fflush(stdin);
    int search_result=searchacc_number(accountnumber);
    if (search_result==-1)
    {
        printf("Account doesn't exist \n");
        return;
    }
    else
    {
        if (account[search_result].balance!=0)
        {
            printf("Can't delete account have balance more than 0\n");
           return;
        }
        else
            deleted=search_result;
    }
    char answer[2];
mark:
    printf("Do want to save changes ? y/n ");
    fflush(stdin);
    scanf("%2s",answer);
    fflush(stdin);
    if(!stricmp(answer,"y"))
    {
        save(numOfAccounts,deleted);
        printf("Changes saved\n\a");
        LOAD();
        return;
    }
    else if (!stricmp(answer,"n"))
    {
        printf("Changes Discard\n");
        return;
    }
    else
    {
        printf("Invalid option ");
        goto mark;
    }
}

bool isValidAccount( char *accountNumber, char *errorMessage)
{
    for (int i = 0; accountNumber[i] != '\0'; i++)
    {
        if (!isdigit(accountNumber[i]))
        {
            strcpy(errorMessage, "Account number must contain only digits.");
            return false;
        }
    }
    if (strlen(accountNumber) != MaxAccountNumber)
    {
        strcpy(errorMessage, "Account number must be exactly 10 digits.");
        return false;
    }
    for (int i = 0; i < numOfAccounts; i++)
    {
        if (strcmp(account[i].accountNumber, accountNumber) == 0)
        {
            strcpy(errorMessage, "Account number must be unique.");
            return false;
        }
    }
    return true ;
}

bool isValidPhoneNumber(const char *phoneNumber)
{
    for (int i = 0; phoneNumber[i] != '\0'; i++)
    {
        if (!isdigit(phoneNumber[i]))
        {
            return false;
        }

    }
    if (!(phoneNumber[2]=='0' || phoneNumber[2]=='1'||phoneNumber[2]=='2'||phoneNumber[2]=='5'))
        return false;
    return (strlen(phoneNumber) == MaxphoneNumber) && (strncmp(phoneNumber, "01", 2) == 0);
}


bool isValidName(const char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i])  && !isspace(name[i]))
        {
            return false;
        }
    }
    return true;
}


bool isValidEmail(const char *email)
{
    int i,atCount=0,atIndex,dotCount=0,dotIndex,charCount=0;
        for(i=0; email[i]!='\0'; i++)
        {
            if(! (isdigit(email[i]) || isalpha(email[i]) || email[i] == '_' || email[i] == '-' || email[i] == '.' || email[i] == '@') )
            {

                return false;
            }
            if (email[i] == '@')
            {
                atCount++;
                atIndex=i;
                if(email[i+1]=='.')
                {

                    return false;
                }

            }

            if (email[i] == '.'||email[i] == '-'||email[i] == '_')
            {
                if(email[i+1] == '.'||email[i+1] == '-'||email[i+1] == '_')
                {

                    return false;
                }

            }
        }
        if (atCount != 1)
        {

            return false;
        }
        for(int i=atIndex;email[i]!='\0';i++)
        {

            if (email[i+1]=='.')
            {
                dotCount++;
            }

        }
        if(dotCount>1||dotCount<1)
        {

            return false;
        }

for(int i=dotIndex;email[i]!='\0';i++)
        {

            if (isalpha(email[i+1]))
            {
                charCount++;
            }

        }
        if(charCount<2)
        {

            return false;
        }


        return true ;


}

bool isValidbalance(char *balance)
{
    char f=0;
    for (int i = 0; balance[i] != '\0'; i++)
    {
        if(balance[i]=='.')
        {
            f++;
        }
        if(f>1)
            return false;
        if ( !isdigit(balance[i])  )
        {
            if(balance[i]=='.')
                continue;
            return false;
        }
    }
    return true;
}
void addaccount()
{
    info temp;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char errorMessage[100];
    do
    {
        printf("Enter the new account number: ");
        fflush(stdin);
        scanf("%11s",temp.accountNumber);
        fflush(stdin);
    }
    while (!isValidAccount( temp.accountNumber, errorMessage) && printf("%s\n", errorMessage));
    do
    {
        printf("Enter the First Name: ");
        fflush(stdin);
        scanf("%30s",temp.firstName);
        fflush(stdin);
    }
    while (!isValidName(temp.firstName) && printf("Invalid name. Use only letters\n"));
    do
    {
        printf("Enter the Last Name: ");
        fflush(stdin);
        scanf("%30s",temp.lastName);
        fflush(stdin);
    }
    while (!isValidName(temp.lastName) && printf("Invalid name. Use only letters\n"));
    do
    {
        printf("Enter the email address: ");
        fflush(stdin);
        scanf("%50s",temp.emailAdress);
        fflush(stdin);
    }
    while (!isValidEmail(temp.emailAdress) && printf("Invalid email address.\n"));
    char scannedbalance[30];
    do
    {
        printf("Enter the Balance: ");
        fflush(stdin);
        scanf("%20s",scannedbalance);
        fflush(stdin);
    }
    while (!isValidbalance(scannedbalance) && printf("Invalid balance !!\n"));
    temp.balance=atof(scannedbalance);
    do
    {
        printf("Enter the phone number: ");
        fflush(stdin);
        scanf("%12s",temp.phoneNumber);
        fflush(stdin);
    }
    while (!isValidPhoneNumber(temp.phoneNumber) && printf("Invalid phone number.\n"));
    temp.dateOpened.month = tm.tm_mon + 1;
    temp.dateOpened.year = tm.tm_year + 1900;
    char answer[2];
mark:
    printf("Do want to save changes ? y/n ");
    fflush(stdin);
    scanf("%2s",answer);
    fflush(stdin);
    if( stricmp(answer,"y")==0 )
    {
        printf("Changes saved\n\a");
        account[numOfAccounts]=temp;
        save(numOfAccounts+1,-1);
        LOAD();
        return;
    }
    else if (stricmp(answer,"n")==0)
    {
        printf("Changes Discard\n");
        return;
    }
    else
    {
        printf("Invalid option ");
        goto mark;
    }

}
void transfer()
{
    char firstAccNum[11],secondAccNum[11],transAmount[Maxbalance+1];
    int index1,index2;
    printf("Enter the first client's account number-transfer from - : ");
    fflush(stdin);
    scanf("%10s", firstAccNum);
    fflush(stdin);
    index1=searchacc_number(firstAccNum);
    if (index1==-1)
    {
        printf("Error: Account does not exist\n");
        MENU();
    }
    printf("Enter the second client's account number: ");
    fflush(stdin);
    scanf("%10s", secondAccNum);
    fflush(stdin);
    index2=searchacc_number(secondAccNum);
    if (index2==-1)
    {
        printf("Error: Account does not exist\n");
        return;
    }
    if(index1==index2)
    {
        printf("Can't transfer from account to the same account \n");
        return;
    }
invalidMoney:
    printf("Enter the amount you want to transfer: ");
    fflush(stdin);
    scanf("%20s",transAmount);
    fflush(stdin);
    if(isValidbalance(transAmount)==0)
    {
        printf("The balance entered is incorrect\n");
        goto invalidMoney;
    }
    else
    {
        if(account[index1].balance < atof (transAmount) )
        {
            printf("Error: the amount exceeds the balance\n");
            goto invalidMoney;
        }
        char answer[2];
mark:
        printf("Do want to save changes ? y/n ");
        fflush(stdin);
        scanf("%2s",answer);
        fflush(stdin);
        if(stricmp(answer,"y")==0)
        {
            printf("Changes saved\n\a");
            addTransaction(index1,index2,transAmount,"transfer");
            account[index1].balance-=atof (transAmount);
            account[index2].balance+=atof (transAmount);
            save(numOfAccounts,-1);
            LOAD();
            return;
        }
        else if (stricmp(answer,"n")==0)
        {
            printf("Changes Discard\n");
            return;
        }
        else
        {
            printf("Invalid option ");
            goto mark;
        }
    }
}

void report()
{
    char accNum[11];
    char accNumFile[11];
    char LINE[Maxbalance+10];
    int lineIndex,lineSpot=0;
    printf("Enter the client's account number: ");
    scanf("%10s", accNum);
    int index;
    index=searchacc_number(accNum);
    if (index==-1)
    {
        printf("Error: Account does not exist\n");
        return;
    }
    FILE *clientAccPtr;
    strcpy(accNumFile,account[index].accountNumber);
    strcat(accNumFile,".txt");
    clientAccPtr = fopen(accNumFile,"r");
    if(clientAccPtr==NULL)
    {
        printf("No transaction recorded\n");
        return;
    }
    int line_count=0;
    char c;
    while(!feof(clientAccPtr))
    {
        c=fgetc(clientAccPtr);
        if(c=='\n')
            line_count++;

    }
    rewind(clientAccPtr);
    line_count--;
    if(line_count<5)
    {
        for(int i=0; i<=line_count; i++)
        {
            fgets(LINE,sizeof(LINE),clientAccPtr);
            printf("%s",LINE);
        }
        for(int i=1; i<=5-line_count-1; i++)
        {
            printf("empty\n");
        }
    }
    else
    {
        lineIndex=line_count-5+1;
        while(1)
        {
            c=fgetc(clientAccPtr);
            if(c=='\n')
                lineSpot++;
            if(lineSpot==lineIndex)
                break;

        }
        for(int i=lineIndex; i<=line_count; i++)
        {
            fgets(LINE,sizeof(LINE),clientAccPtr);
            printf("%s",LINE);
        }
        printf("\n");
    }
    fclose(clientAccPtr);
    return;
}

void modify()
{
    info temp;
    char accountnumber[11],field[2];
    printf("Enter the account number you want to modify : ");
    fflush(stdin);
    scanf("%11s",accountnumber);
    fflush(stdin);
    int result=searchacc_number(accountnumber);
    if(result == -1)
    {
        printf("Not found\n");

        return;
    }
    char flag=0;
    printf("Choose a field to modify \n1-first name\n2-last name\n3-mobile\n4-email address\n: ");
    fflush(stdin);
    scanf("%2s",field);
    fflush(stdin);
    if(strcmp(field,"1")==0 )
    {
        do
        {
            printf("Enter the new First Name: ");
            fflush(stdin);
            scanf("%30s",temp.firstName);
            fflush(stdin);
        }
        while (!isValidName(temp.firstName) && printf("Invalid name. Use only letters, underscores\n"));
        flag=1;
    }

    else if(strcmp(field,"2")==0)
    {
        do
        {
            printf("Enter the Last Name: ");
            fflush(stdin);
            scanf("%30s",temp.lastName);
            fflush(stdin);
        }
        while (!isValidName(temp.lastName) && printf("Invalid name. Use only letters, underscores\n"));

        flag=2;
    }
    else if(strcmp(field,"3")==0)
    {
        do
        {
            printf("Enter the phone number: ");
            fflush(stdin);
            scanf("%12s",temp.phoneNumber);
            fflush(stdin);
        }
        while (!isValidPhoneNumber(temp.phoneNumber) && printf("Invalid phone number.\n"));
        flag=3;

    }
    else if(strcmp(field,"4")==0)
    {
        do
        {
            printf("Enter the email address: ");
            fflush(stdin);
            scanf("%50s",temp.emailAdress);
            fflush(stdin);
        }
        while (!isValidEmail(temp.emailAdress) && printf("Invalid email address.\n"));
        flag=4;
    }
    else
    {
        printf("Error: Invalid choice\n");
        MENU();
    }

    char answer[2];
mark:
    printf("Do want to save changes ? y/n ");
    fflush(stdin);
    scanf("%2s",answer);
    fflush(stdin);
    if(stricmp(answer,"y")==0)
    {
        printf("Changes saved\n\a");
        if(flag==3)
            strcpy(account[result].emailAdress,temp.emailAdress);
        else if(flag==1)
            strcpy(account[result].firstName,temp.firstName);
        else if(flag==2)
            strcpy(account[result].lastName,temp.lastName);
        else if(flag==4)
            strcpy(account[result].phoneNumber,temp.phoneNumber);
        save(numOfAccounts,-1);
        LOAD();
        return;
    }

    else if (stricmp(answer,"n")==0)
    {
        printf("Changes Discard\n");
        return;
    }
    else
    {
        printf("Invalid option ");
        goto mark;
    }

}

void addTransaction(int fromAccountIndex,int toAccountIndex,char*amount,char*transType)
{
    if(fromAccountIndex!=-1)
    {
        char fromAccountFile[15];
        strcpy(fromAccountFile,account[fromAccountIndex].accountNumber);
        strcat(fromAccountFile,".txt");
        FILE*fromFilePtr=fopen(fromAccountFile,"a");
        if(fromFilePtr==NULL)
        {
            printf("Error: File does not exist\n");
            exit(-2);
        }
        fprintf(fromFilePtr,"-%s %s\n",amount,transType);
        fclose(fromFilePtr);
    }
    char toAccountFile[15];
    strcpy(toAccountFile,account[toAccountIndex].accountNumber);
    strcat(toAccountFile,".txt");
    FILE*toFilePtr=fopen(toAccountFile,"a");
    if(toFilePtr==NULL)
    {
        printf("Error: File does not exist \n");
       exit(-3);
    }
    fprintf(toFilePtr,"%s %s\n",amount,transType);
    fclose(toFilePtr);
}

int searchacc_number(char *accnumber)
{
    int i;
    for(i=0; i<numOfAccounts; i++)
    {
        if (strcmp(accnumber,account[i].accountNumber)==0)
            return i;
    }
    return -1;
}

void SEARCH()
{
    char accnumber[11];
    printf("Enter The Account Number : ");
    fflush(stdin);
    scanf("%10s",accnumber);
    fflush(stdin);
    int i;
    i= searchacc_number(accnumber);
    if(i==-1)
    {
        printf("Notfound\n");
        return;
    }
    char month[10];
    printf("Account Number: %s\n",account[i].accountNumber);
    printf("Name: %s %s\n",account[i].firstName,account[i].lastName);
    printf("E-mail: %s\n",account[i].emailAdress);
    printf("Balance: %f\n",account[i].balance);
    printf("Mobile: %s\n",account[i].phoneNumber);
    printf("Date Opened: %s %d\n",convertMonths(account[i].dateOpened.month),account[i].dateOpened.year);
    return;
}

void WITHDRAW()
{
    char accnumber[11], valid;
    printf("Enter The Account Number : ");
    fflush(stdin);
    scanf("%10s",accnumber);
    fflush(stdin);
    int i=searchacc_number(accnumber);
    if(i==-1)
    {
        printf("Account does not exist \n");
        return;
    }
    char withdrawedmoney[21];
invalidwithdrawedmoney:
    printf("Enter the amount of money you need to withdraw : ");
    fflush(stdin);
    scanf("%20s",withdrawedmoney);
    fflush(stdin);
    valid=isValidbalance(withdrawedmoney);
    if(valid==0)
    {
        printf("The balance entered is incorrect");
        goto invalidwithdrawedmoney;
    }
    else
    {
        if(atof(withdrawedmoney)<=10000)
        {
            if (account[i].balance>=atof(withdrawedmoney))
            {
                char answer[2];
mark:
                printf("Do want to save changes ? y/n ");
                fflush(stdin);
                scanf("%2s",answer);
                fflush(stdin);
                if(stricmp(answer,"y")==0)
                {
                    printf("Changes saved\n\a");
                    account[i].balance-=atof(withdrawedmoney);
                    addTransaction(-1,i,withdrawedmoney,"withdraw");
                    save(numOfAccounts,-1);
                    LOAD();
                    return;
                }
                else if (stricmp(answer,"n")==0)
                {
                    printf("Changes Discard\n");
                    return;
                }
                else
                {
                    printf("Invalid option ");
                    goto mark;
                }

            }
            else
            {
                printf("The transaction wasn't successful. No enough money in your account \n");
                goto invalidwithdrawedmoney;
            }
        }
        else
        {
            printf("the maximum withdrawal limit for each transaction is 10,000$ per transaction\n");
            goto invalidwithdrawedmoney;
        }
    }
}

void DEPOSIT()
{
    char accnumber[11],valid;
    printf("Enter The Account Number : ");
    fflush(stdin);
    scanf("%10s",accnumber);
    fflush(stdin);
    int i=searchacc_number(accnumber);
    if(i==-1)
    {
        printf("Account doesnot exist \n");
        return;
    }
    char depositedmoney[21];
invaliddeposiedmoney:
    printf("Enter the amount of money you need to deposit : ");
    fflush(stdin);
    scanf("%20s",depositedmoney);
    fflush(stdin);
    valid=isValidbalance(depositedmoney);
    if(valid==0)
    {
        printf("The balance entered is incorrect");
        goto invaliddeposiedmoney;
    }
    else
    {
        if(atof(depositedmoney)<=10000)
        {
            char answer[2];
mark:
            printf("Do want to save changes ? y/n ");
            fflush(stdin);
            scanf("%2s",answer);
            fflush(stdin);
            if(stricmp(answer,"y")==0)
            {
                printf("Changes saved\n\a");
                account[i].balance+=atof(depositedmoney);
                addTransaction(-1,i,depositedmoney,"Deposit");
                save(numOfAccounts,-1);
                LOAD();
                return;
            }
            else if (stricmp(answer,"n")==0)
            {
                printf("Changes Discard\n");
                return;
            }
            else
            {
                printf("Invalid option ");
                goto mark;
            }
        }
        else
        {
            printf("the maximum withdrawal limit for each transaction is 10,000$ per transaction");
            goto invaliddeposiedmoney;
        }
    }
}
