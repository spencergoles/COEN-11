/**********************************************************************/
/*  Spencer Goles	 COEN 11	4 October 2018                */ 
/*  This program will administer a Urgent Care waiting list.          */
/*  It will be able to add, modify, view, and exit the list.          */
/**********************************************************************/

//C Preprocessor 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Create base structure
struct information
{
	int dept;
	char name[20];
};
//Create Global Variables
struct information INFO[10];
int count = 0;
//Declaring modules
int insert();
int list();
int discard();
int show_dept();
int check_duplicate();
//Create the main module
int main() 
{
  int cmd;
	printf("\n\nWelcome to the Urgent Care Waiting List\n\n");
	while(1)
	{
		printf("\n\nPlease Select a Command Below\n\n");
		printf("1. View List              3. Add Patient        5. Quit\n");
 		printf("2. Show Department        4. Remove Patient\n\n");
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
				printf("\nHave a great day!\n\n");
				exit(0);
			default:
				printf("That was not a valid responce. Please try again.");
		} 
	}
	return 0;
}
//Create the Insert Module
int insert()
{
	char temp[20];
 	int temp2;
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
        		count++;
        	}
        	else 
        	{
        		printf("This is not a valid department.");
        	}
       
		}
	}
	return 1;
}
//Create the List Module which prints both arrays vertically 
int list() 
{
	//Declare pointer
	struct information *p;
	p = INFO;
	int i;
	printf("\nUnrgent Care Waiting List\n");
	printf("Patient Name         Department\n");
	printf("----------------------------------\n");
        for(i = 0; i < 10; i++,p++)
	{
		 printf("%s			%d\n",p->name,p->dept);
	}
	return 1; 
}
//Create module to delete the oldest entry by copying arrays up 1
int discard()
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
				}
				count--;
			}
		}
	}
	else
	{
     		printf("\nThis is not a valid department.\n");
	}
  	return 1;
}
//Create module to list all the patients in a given department
int show_dept()
{
	struct information *p;
	p = INFO;
	int i,x;
	printf("\nInsert Department (1-4): ");
	scanf("%d", &x);
  	if(x == 1 || x == 2 || x == 3 || x == 4)
  	{
    		printf("\nUnrgent Care Waiting List\n");
    		printf("Patient Name     Department\n");
    		printf("-------------------------------\n");
    		for(i=0; i < 10; i++,p++)
    		{
      			if(p->dept == x)
      			{
        			printf("%s			%d\n",p->name,p->dept);
      			}
    		}
  	}
  	else 
  	{
     		printf("\nThis is not a valid department.\n");
  	} 
  	return 1;
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
