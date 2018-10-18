/**********************************************************************/
/*  Spencer Goles	 COEN 11	18 October 2018  Version 4.0              */ 
/*  This program will administer a Urgent Care waiting list.          */
/*  It will be able to add, modify, view, and exit the linked list.   */
/**********************************************************************/

//C Preprocessor 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NODE struct node
//Create base structures
union u 
{
	float feverTemp;    // flag = 1
	char painKind[20];  // flag = 2 
	int sickDays;       // flag = 3
};
struct node
{
	int dept;
	char name[20];
	int flag; 
	union u extra; 
  NODE *next;
};
// Global Variables
NODE *head = NULL;
NODE *tail = NULL;
//Declaring modules
void insert(void);
void list(void);
void discard(void);
void show_dept(void);
int check_duplicate();
void show_name(void);

//Main Control Function
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
/Create Insert Function 
void insert(void)
{
  char temp[20];
 	int temp2;
	int dayTemp;
	float feverTemporary;
  NODE *p;
  p = (NODE*)malloc(sizeof(NODE));

  printf("Insert Name: ");
	scanf("%s",temp);
	if(check_duplicate(temp) != 0)
	{
			printf("\nThis name has already been used. Please select another.\n");
	}
 if(check_duplicate(temp) == 0)
 { 
			printf("\nInsert Department (1-4): ");
			scanf("%d", &temp2);
			if(temp2 == 1 || temp2 == 2 || temp2 == 3 || temp2 == 4) 
    			{	
            p->dept = temp2;
				    strcpy(p->name,temp);
      		  switch (temp2)
      		  {
					  case 1:
						  p->flag = 1;
						  printf("\nInsert Fever Temperature in Farenheight: ");
						  scanf("%f", &feverTemporary);
						  p->extra.feverTemp = feverTemporary; 
						  break;
					  case 2: 
					  	p->flag = 2;
					  	printf("\nInsert Information: ");
						  scanf("%s", p->extra.painKind);
					  	break;
					  case 3: 
					  	p->flag = 3;
					  	printf("\nInsert Sick Day Count: ");
						  scanf("%d",&dayTemp);
              p->extra.sickDays = dayTemp;
              break;
				  	case 4:
					    p->flag = 3;
					  	printf("\nInsert Sick Day Count: ");
						  scanf("%d",&dayTemp);
              p->extra.sickDays = dayTemp;
              break;
      			}
            if (head == NULL)
            {
              p->next = NULL;
              tail = head = p;
              return;
            }
            else
            {
              p->next = NULL;
              tail->next = p;
              tail = p;
            }
    			}
    			else
          {
            printf("Not a Valid Department");
          }
      		  
    			
    return;
  }
}
//Create function to print the linked list
void list(void)
{
  NODE *p;
  p = head;

  printf("\nUrgent Care Waiting List\n");
	printf("Patient Name\t\tDepartment\t\tInformation\n");
	printf("--------------------------------------------------------------\n");
  while(p != NULL)
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
    p = p->next;
  }
  return;
}
//Create function to print nodes of a certain department 
void show_dept(void)
{
  int temp;
  NODE *p;
  p = head;

  printf("\nInsert Department: ");
  scanf("%d",&temp);
  if(temp == 1 || temp == 2 || temp == 3 || temp == 4)
  {
    printf("\nUrgent Care Waiting List\n");
	  printf("Patient Name\t\tDepartment\t\tInformation\n");
	  printf("--------------------------------------------------------------\n");
    while(p != NULL)
    {
      if(p->dept == temp)
      {
        switch(p->dept)
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
          case 4:
			    	printf("%s\t\t\t%d\t\t\t%d Days Sick\n",p->name,p->dept,p->extra.sickDays);
			    	break;
		    	default:
		    		printf("");
			    	break;
        }
      }
     p = p->next;
    }
  }
  else
  {
    printf("\nThis is not a valid department.\n");
  }
  return;
}
//Create function to print information with a given name
void show_name(void)
{
  char temp[20];
  NODE *p;
  p = head;
  printf("Insert Name: ");
  scanf("%s",temp);
  printf("\nUrgent Care Waiting List\n");
	printf("Patient Name\t\tDepartment\t\tInformation\n");
	printf("--------------------------------------------------------------\n");
  while(p != NULL)
  {
    if(strcmp(p->name,temp) == 0)
    {
      switch(p->dept)
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
          case 4:
			    	printf("%s\t\t\t%d\t\t\t%d Days Sick\n",p->name,p->dept,p->extra.sickDays);
			    	break;
		    	default:
		    		printf("");
			    	break;
      }
    }
    p = p->next;
  }
  return;
}
int check_duplicate(char x[])
{
  NODE *p;
  p = head;
  while(p != NULL)
  {
    if(strcmp(p->name,x) == 0)
    {
      return (1);
    }
    p = p->next;
  }
  return 0;
}
