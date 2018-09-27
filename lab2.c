/**********************************************************************/
/*  Spencer Goles	 COEN 11	24 September 2018             */ 
/*  This program will administer a Urgent Care waiting list.          */
/*  It will be able to add, view, and exit the list.                  */
/**********************************************************************/

//C Preprocessor 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Create Global Variables
int dept[10];
char data[10][20];
int cmd,i,x;
int count = 0;
//Declaring modules
int insert();
int list();
//Create the main module
int main() 
{
	printf("\n\nWelcome to the Urgent Care Waiting List\n\n");
	while(cmd != 3)
	{
		printf("\n\nPlease Select a Command Below\n\n");
		printf("1. View List        2. Add Patient        3. Quit\n\n");
		printf("Enter Command: ");
		scanf("%d",&cmd);
		//Switch statement controls calling C modules from the main menu
                switch(cmd)
		{	
			case 1:
				list();
				break;
			case 2:
				insert();
				break;
			case 3:
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
	int test =0;
	if(count > 9)
	{
		printf("\nThe waiting list is full. Please try again later.\n");
	} 
	else
	{
		printf("Insert Name: ");
		scanf("%s",temp);
		//Create for loop to test names to ensure every name is unique 
		for(x = 0; x < 10; x++)
		{
			//Compares a temp variable against current array
			if(strcmp(temp,data[x]) == 0)
			{
				printf("\nThis name has already been used. Please select another.\n");
				test = 1;
				break; 
			}
		}
		//If statement prevents the name and department insertion if name matches a name in data
		if(test != 1)
		{
			strcpy(data[count],temp);
			printf("\nInsert Department (1-4): ");
			scanf("%d",&dept[count]);
			count++;
		}
	}
	return 1;
}
//Create the List Module which prints both arrays vertically 
int list()
{
	printf("\nUnrgent Care Waiting List\n");
	printf("Patient Name         Department\n");
	printf("------------------------------------\n");
        for(i = 0; i < 10; i++)
	{
		printf("%s			%d\n",data[i],dept[i]);
	}
	return 1; 
}

