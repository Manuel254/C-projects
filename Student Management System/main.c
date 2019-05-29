#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#define NULL 0

COORD coord = {0,0};

struct student{
char regno[15];
char firstname[20];
char lastname[20];
char gender[10];
char course[30];
} s;

void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

main(){
//clears screen
system("cls");
char option,another;
char reg_no[15];
long int recsize;
int isfound=0;


FILE *ptr1,*ptr2;
 ptr1 = fopen("students.txt","rb+");
    if(ptr1 == NULL)
    {
        ptr1 = fopen("students.txt","wb+");
        if(ptr1 == NULL)
        {
            printf("Error!!Cannot open file");
            exit(1);
        }
    }
recsize = sizeof(s);

while(1){
system("cls");
gotoxy(30,10);
printf("STUDENT MANAGEMENT SYSTEM\n\n");
gotoxy(33,12);
printf("1) Add Student Details\n");
gotoxy(33,14);
printf("2) Edit Student Details\n");
gotoxy(33,16);
printf("3) Display Student Details\n");
gotoxy(33,18);
printf("4) Search Student Details\n");
gotoxy(33,20);
printf("5) Delete Student Details\n\n");
gotoxy(30,22);
printf("Enter your option");
fflush(stdin);
option  = getche(); //

switch(option)
        {
        case '1':  /// if user press 1
            system("cls");
            fseek(ptr1,0,SEEK_END); /// search the file and move cursor to end of the file
            /// here 0 indicates moving 0 distance from the end of the file
            gotoxy(40,0);
            printf("**************Add Record***************");
            another = 'y';
            while(another == 'y')  /// if user want to add another record
            {
                printf("\nEnter registration number: ");
                scanf("%s",s.regno);
                printf("\nEnter First name: ");
                scanf("%s", &s.firstname);
                printf("\nEnter Last name: ");
                scanf("%s", &s.lastname);
                printf("\nEnter gender: ");
                scanf("%s", &s.gender);
                printf("\nEnter course: ");
                scanf("%s", &s.course);

                fwrite(&s,recsize,1,ptr1); /// write the record in the file

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '2':
            system("cls");
            gotoxy(40,0);
            printf("**************Edit Record***************");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter registration number to edit record: ");
                scanf("%s", reg_no);
                rewind(ptr1);
                while(fread(&s,recsize,1,ptr1)==1)  /// fetch all record from file
                {
                    if(strcmp(s.regno,reg_no) == 0)  ///if entered name matches with that in file
                    {
                        fflush(stdin);
                        printf("Registration number: ");gets(s.regno);
                        printf("First name: ");gets(s.firstname);
                        printf("Last name: ");gets(s.lastname);
                        printf("Gender: ");gets(s.gender);
                        printf("Course: ");gets(s.course);
                        fseek(ptr1,-recsize,SEEK_CUR); /// move the cursor 1 step back from current position
                        fwrite(&s,recsize,1,ptr1); /// override the record
                        break;
                    }
                }
                printf("\nEdit another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;

        case '3':
            system("cls");
            gotoxy(40,0);
            printf("**************Diplay All Records****************");
            rewind(ptr1); ///this moves file cursor to start of the file
            while(fread(&s,recsize,1,ptr1)==1)  /// read the file and fetch the record one record per fetch
            {
                printf("\n%s %s %s %s %s",s.regno,s.firstname,s.lastname,s.gender,s.course);
            }
            getch();
            break;

        case '4':
        system("cls");
        rewind(ptr1);
        if(ptr1==0)
		exit(0);
        fflush(stdin);
        system("cls");
        gotoxy(40,0);
        printf("**************Search Record***************\n");
        printf("Enter Registration number:");
        scanf("%s", &reg_no);
        while(fread(&s,sizeof(s),1,ptr1)==1)
        {
		if(strcmp(s.regno,reg_no)==0)
		{
		    system("cls");
			printf(" Record Found ");
			printf("\n\nRegistration number: %s\nFirst Name: %s\nLast Name: %s\nGender: %s\nCourse: %s\n",s.regno,s.firstname,s.lastname,s.gender,s.course);
			isfound=0;
			break;
		}
	}
	getch();
	break;

        case '5':
            system("cls");
            gotoxy(40,0);
            printf("**************Delete Record***************");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter registration of student to delete: ");
                scanf("%s",reg_no);
                ptr2 = fopen("Temporary.txt","w");  /// create a intermediate file for temporary storage
                rewind(ptr1); /// move record to starting of file
                while(fread(&s,recsize,1,ptr1) == 1)  /// read all records from file
                {
                    if(strcmp(s.regno,reg_no) != 0)  /// if the entered record match
                    {
                        fwrite(&s,recsize,1,ptr2); /// move all records except the one that is to be deleted to temp file
                    }
                }
                fclose(ptr1);
                fclose(ptr2);
                remove("students.txt"); /// remove the orginal file
                rename("Temporary.txt","students.txt"); /// rename the temp file to original file name
                ptr1 = fopen("students.txt", "r");
                printf("Delete another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
    }
}
    return 0;

}

