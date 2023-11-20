#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct transport
{
    int id;
    int age;
    char name[30];
    char vehiclename[30];
    char destination[30];
    char shift[20];
    int amount;
} t;

void insert_record();
void display_record();
void search_record();
void delete_record();
void update_record();

int main()
{
    int ch; // for switch case
    char username[] = "transport", password[] = "password";
    char user[20], pass[20]; // for string comparison

    printf("USERNAME:");
    gets(user);
    printf("PASSWORD:");
    gets(pass);

    if (strcmp(username, user) == 0 && strcmp(password, pass) == 0)
    {
        printf("\n\n\n\n\n");
        printf("\t\t** WELCOME TO TRANSPORTATION MANAGEMENT SYSTEM**\n");

        do
        {
            printf("\n\t....CHOOSE any one OPERATION...\n\n");
            printf("\t****Available operation****\n\n");
            printf("\t\t1:Insert Costumer record:\n");
            printf("\t\t2:Display Costumer record:\n");
            printf("\t\t3:Search Costumer record:\n");
            printf("\t\t4:Delete Costumer record:\n");
            printf("\t\t5:Update Costumer record:\n");
            printf("\t\t6:Exit\n");
            scanf("%d", &ch);

            switch (ch)
            {
                case 1:
                    system("cls");
                    insert_record();
                    break;
                case 2:
                    system("cls");
                    display_record();
                    break;
                case 3:
                    system("cls");
                    search_record();
                    break;
                case 4:
                    system("cls");
                    delete_record();
                    break;
                case 5:
                    system("cls");
                    update_record();
                    break;
                case 6:
                    exit(0);
                default:
                    printf("Invalid choice. Please select a valid option.\n");
            }
        } while (ch > 0 && ch <= 6);
    }
    else
    {
        printf("\n\n\n\t\t ***INCORRECT USERNAME PASSWORD COMBINATION***\n\n");
    }

    return 0;
}

void insert_record()
{
    int i, n; // number of passengers
    FILE *fptr;
    fptr = fopen("transport.txt", "a+");
    if (fptr == NULL)
    {
        printf("\n\nError: Unable to open file!!!\n");
        return;
    }
    printf("\n\n\t***ENTER PASSENGER DETAILS****\n\n");
    printf("Enter number of passengers: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter traveler identity number provide unique identity to each passenger: ");
        scanf(" \n %d", &t.id);
        printf("\n Enter the traveler Name: ");
        scanf(" \n %s", &t.name);
        printf("\n Enter the traveler Age : ");
        scanf("\n %d", &t.age);
        printf("\n Enter Vehicle Name: ");
        scanf(" \n %s", t.vehiclename);
        printf("\n Enter traveler destination: ");
        scanf("\n %s", t.destination);
        printf("\n Enter Traveling shift: ");
        scanf(" \n %s", t.shift);
        printf("\n Enter the amount for transportation: ");
        scanf(" %d", &t.amount);
   
        fwrite(&t, sizeof(t), 1, fptr); // Write the data to the file
    }
      printf("\n\tCongratulations your record has been successfully entered...\n");

    fclose(fptr);
}

void display_record() {
    FILE *fptr;
    fptr = fopen("transport.txt", "rb");
    if (fptr == NULL) {
        printf("\n\n\t Error: cannot open this file!!!\n");
        return;
    }
    printf("\n\t***Traveler Details***\n\n");
    printf("Id \tName \t\tAge \tVehiclename \tDestination \tTravelling Shift \tTransportation Amount");
    while (fread(&t, sizeof(t), 1, fptr) == 1){
    printf("\n%d \t%s \t\t%d \t%s \t\t%s \t\t%s \t\t%d", t.id, t.name, t.age, t.vehiclename, t.destination, t.shift, t.amount);
    }
    fclose(fptr);
}

  	
	
void search_record()
{
    int search, flag = 0;
    FILE *fptr;
    fptr = fopen("transport.txt", "rb");
    if (fptr == NULL)
    {
        printf("\n\t Unable to open file...!!!");
        return;
    }

    printf("\nEnter the id of the traveler you want to search:\n");
    scanf("%d", &search);

    while (fread(&t, sizeof(t), 1, fptr) > 0) //read and search the record in file
    {
        if (search == t.id)
        {
            flag = 1;
            printf("\n\nSearch successful, record found...");
             printf("\n Id\tName\t\tAge\tVehiclename\tDestination\tTravelling Shift\tTransportation Amount\n");
              printf("\n%d\t%s\t\t%d\t%s\t\t%s\t\t%s\t\t\t%d", t.id, t.name, t.age, t.vehiclename, t.destination, t.shift, t.amount);
            break;
        }
    }

    if (flag == 0)
    {
        printf("\n\n*** Record not found!! Please check the process properly***\n");
    }
    fclose(fptr);
}

	
 void delete_record()
 {
 	int id;
 	int count=0,n=0;
 	FILE*fptr,*nfptr;
 	fptr=fopen("transport.txt","rb");
 	if(fptr==NULL)
 	{
 		printf("Error!cannot open the file...");
 		return;
	 }
	 printf("\n\t\t***Previously stored record***\n\n");
	 display_record();
	 printf("\n\nEnter traveller id which you want to delete");
	 scanf("%d",&id);
	 nfptr=fopen("new.txt","ab+");
	 if(nfptr==NULL)
	 {
	 	printf("\n\nError! Unable to open file\n\n");
	 	return;
	 }
	 while(fread(&t,sizeof(t),1,fptr)==1)
	 {
	 	n++;
	 	if(id!=t.id)
	 	{
	 		fwrite(&t,sizeof(t),1,nfptr); //writing in file
	 		count++;
	 		
		 }
	 }
	 if(count<n)
	 {
	 	printf("\n\t\t***RECORD DELETED SUCCESSFULLY***\n");
	 }
	 else{
	 	printf("\n\t\t***RECORD NOT FOUND***\n");
	 }
	  fclose(fptr);
	  fclose(nfptr);
	  remove("transport.txt");
	  rename("new.txt","transport.txt");
	  display_record();
}

void update_record() {
    int id;
    int flag = 0;
    FILE* fptr;
    FILE* nfptr;


    fptr = fopen("transport.txt", "rb+");
    if (fptr == NULL) {
        printf("ERROR! Cannot open the file...\n");
        return;
    }

    printf("Enter the id of the customer you want to update:");
    scanf("%d", &id);

    nfptr = fopen("newfile.txt", "ab+");
    if (nfptr == NULL) {
        printf("\n\n Error ! Cannot open the file...\n");
        fclose(fptr);
        return;
    }

    while (fread(&t, sizeof(t), 1, fptr) == 1) {
        if (id != t.id) {
            fwrite(&t, sizeof(t), 1, nfptr);
        } else {
            flag = 1;
                 printf("Id\t\tName\t\tAge\t\tVehiclename\t\tDestination\t\tTravelling Shift\t\tTransportation Amount\n\n");
                printf("\n%d\t\t%s\t\t%d\t\t%s\t%s\t\t%s\t\t%d", t.id, t.name, t.age, t.vehiclename, t.destination, t.shift, t.amount);
         printf("\t**Now Enter the new record***\n\n");
            printf("Updated Customer ID No: ");
            scanf("%d", &t.id);
            printf("Updated Customer Age: ");
            scanf("%d", &t.age);
            printf("Updated Customer Name: ");
            scanf("%s", t.name);
            printf("Updated Vehicle Name: ");
            scanf("%s", t.vehiclename);
            printf("Updated Passenger Destination: ");
            scanf("%s", t.destination);
            printf("Updated Passenger Traveling Shift: ");
            scanf("%s", t.shift);
            printf("Updated Transportation Amount: ");
            scanf("%d", &t.amount);

            fwrite(&t, sizeof(t), 1, nfptr);
            printf("\n \n \t**RECORD UPDATED SUCCESSFULLY***\n");
        }
    }

    if (flag == 0) {
        printf("\n\t\tError: Record not found....!!!\n\n");
    }

    fclose(fptr);
    fclose(nfptr);
    remove("transport.txt");
    rename("newfile.txt", "transport.txt");
    display_record(); 
}

     
     
     
     
     

  
 

	


