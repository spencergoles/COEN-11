/**********************************************************************/
/*  Spencer Goles	 COEN 11	11 October 2018  Version 3.0  */ 
/*  This program will administer a Urgent Care waiting list.          */
/*  It will be able to add, modify, view, and exit the list.          */
/**********************************************************************/

//C Preprocessor 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Create base structures
union u 
{
	float feverTemp;    // flag = 1
	char painKind[20];  // flag = 2 
	int sickDays;       // flag = 3
};
struct information
{
	int dept;
	char name[20];
	int flag; 
	union u extra; 
};
//Create Global Variables
struct information INFO[10];
int count = 0;
//Declaring modules
void insert(void);
void list(void);
void discard(void);
void show_dept(void);
int check_duplicate();
void show_name(void);
//Create the main module
int main() 
{
	int cmd;
	printf("\n\nWelcome to the Urgent Care Waiting List\n\n");
	while(1)
	{
		printf("\n\nPlease Select a Command Below\n\n");
		printf("1. View List              3. Add Patient        5. Search Name\n");
 		printf("2. Show Department        4. Remove Patient     6. Quit\n\n");
		printf("Enter Command: ");
		scanf("%d",&cmd);
		//Switch statement controls calling C modules from the main menu
		switch(cmd)
		{	
			case 1:
				list();
				break;
			case 2:
				show_dept();
				break;
			case 3:
				insert();
				break;
			case 4:
				discard();
				break;
			case 5:
				show_name();
				break;
			case 6:
				printf("\nHave a great day!\n\n");
				exit(0);
			default:
				printf("That was not a valid responce. Please try again.");
		} 
	}
	return 0;
}
//Create the Insert Module
void insert(void)
{
	char temp[20];
 	int temp2;
	int dayTemp;
	float feverTemporary;
	if(count > 9)
	{
		printf("\nThe waiting list is full. Please try again later.\n");
	} 
	else
	{
		printf("Insert Name: ");
		scanf("%s",temp);
		//Compares a temp variable against current array
		if(check_duplicate(temp) != 0)
		{
			printf("\nThis name has already been used. Please select another.\n");
		}
		//If statement prevents the name and department insertion if name matches a name in data
		if(check_duplicate(temp) == 0)
		{ 
			printf("\nInsert Department (1-4): ");
			scanf("%d", &temp2);
			if(temp2 == 1 || temp2 == 2 || temp2 == 3 || temp2 == 4) 
    			{	
				strcpy(INFO[count].name,temp);
      				INFO[count].dept = temp2;
      				switch (temp2)
      				{
					case 1:
						INFO[count].flag = 1;
						printf("\nInsert Fever Temperature in Farenheight: ");
						scanf("%f", &feverTemporary);
						INFO[count].extra.feverTemp = feverTemporary; 
						count++;
						break;
					case 2: 
						INFO[count].flag = 2;
						printf("\nInsert Information: ");
						scanf("%s", INFO[count].extra.painKind);
						count++;
					  	break;
					case 3: 
					  	INFO[count].flag = 3;
					  	printf("\nInsert Sick Day Count: ");
						scanf("%d",&dayTemp);
						INFO[count].extra.sickDays = dayTemp;
						count++;
						break;
					case 4:
						INFO[count].flag = 3;
						printf("\nInsert Sick Day Count: ");
						scanf("%d",&dayTemp);
						INFO[count].extra.sickDays = dayTemp;
						count++;
						break;
      				}
    			}
    			else
    			{
      				printf("Not a Valid Department");
    			}  	  
		}
	}
	return;
}
//Create the List Module which prints both arrays vertically 
void list(void) 
{
	//Declare pointer
	struct information *p;
	p = INFO;
	int i;
	printf("\nUnrgent Care Waiting List\n");
	printf("Patient Name\t\tDepartment\t\tInformation\n");
	printf("--------------------------------------------------------------\n");
	for(i = 0; i < 10; i++,p++)
	{
		switch(p->flag)
		{
			case 1:
				printf("%s\t\t\t%d\t\t\t%0.1f Degrees F\n",p->name,p->dept,p->extra.feverTemp);
				break;
			case 2:
				printf("%s\t\t\t%d\t\t\t%s\n",p->name,p->dept,p->extra.painKind);
				break; 
			case 3:
				printf("%s\t\t\t%d\t\t\t%d Days Sick\n",p->name,p->dept,p->extra.sickDays);
				break;
			default:
				printf("");
				break;
		}	 
	}
	return; 
}
//Create module to delete the oldest entry by copying arrays up 1
void discard(void)
{
	//Create two pointers with a difference of 1 to act as a temp
	struct information *p;
	p = INFO;
	struct information *q;
	q = p + 1;
	int x,i,del;
	printf("\nDelete Department: ");
	scanf("%d",&del);
  	if(del == 1 || del == 2 || del == 3 || del == 4)
	{
		for(i = 0; i < 10; i++,p++,q++)
		{
			if(p->dept == del)
			{
				for(i=0; i < 10; i++,p++,q++)
				{
					strcpy(p->name,q->name); 
					p->dept = q->dept;
					switch(p->flag)
					{
						case 1:
							p->extra.feverTemp = q->extra.feverTemp;
							break;
						case 2:
							strcpy(q->extra.painKind,p->extra.painKind);
							break;
						case 3: 
							p->extra.sickDays = q->extra.sickDays;
							break;
					}
				}
				count--;
			}
		}
	}
	else
	{
     		printf("\nThis is not a valid department.\n");
	}
  	return;
}
//Create module to list all the patients in a given department
void show_dept(void)
{
	struct information *p;
	p = INFO;
	int i,x;
	printf("\nInsert Department (1-4): ");
	scanf("%d", &x);
  	if(x == 1 || x == 2 || x == 3 || x == 4)
  	{
		printf("\nUnrgent Care Waiting List\n");
		printf("Patient Name\t\tDepartment\t\tInformation\n");
		printf("--------------------------------------------------------------\n");
    		for(i=0; i < 10; i++,p++)
    		{
      			if(p->dept == x)
      			{
				switch(p->flag)
				{
					case 1:
						printf("%s\t\t\t%d\t\t\t%0.1f Degrees F\n",p->name,p->dept,p->extra.feverTemp);
						break;
					case 2:
						printf("%s\t\t\t%d\t\t\t%s\n",p->name,p->dept,p->extra.painKind);
						break; 
					case 3:
						printf("%s\t\t\t%d\t\t\t%d Days Sick\n",p->name,p->dept,p->extra.sickDays);
						break;
					default:
						printf("");
						break;
				}
			}	 
    		}
  	}
  	else 
  	{
     		printf("\nThis is not a valid department.\n");
  	} 
  	return;
}
//This module shows all information for a given name
void show_name(void)
{ 
	int i;
	struct information *p;
	p = INFO;
	char nameSearch[20];
	printf("\nSearch Name: ");
	scanf("%s",nameSearch);
	for(i = 0; i < 10; i++,p++)
	{
		if(strcmp(p->name,nameSearch) ==0)
		{
			printf("\nUnrgent Care Waiting List\n");
			printf("Patient Name\t\tDepartment\t\tInformation\n");
			printf("--------------------------------------------------------------\n");
			switch(p->flag)
			{
				case 1:
					printf("%s\t\t\t%d\t\t\t%0.1f Degrees F\n",p->name,p->dept,p->extra.feverTemp);
					break;
				case 2:
					printf("%s\t\t\t%d\t\t\t%s\n",p->name,p->dept,p->extra.painKind);
					break; 
				case 3:
					printf("%s\t\t\t%d\t\t\t%d Days Sick\n",p->name,p->dept,p->extra.sickDays);
					break;
				default:
					printf("");
					break;
			}
    		}
  	} 
  	return;
}
//This module checks the current array if a new entry has been used 
int check_duplicate(char x[])
{
	struct information *p;
	p = INFO;
	int i;
	for(i =0; i < 10; i++,p++)
  	{
    		if((strcmp(p->name, x) == 0))
    			return 1;	
  	}
  	return 0;
}
