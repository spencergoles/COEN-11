/**********************************************************************/
/*  Spencer Goles	 COEN 11	25 October 2018  Version 5.0  */ 
/*  This program will administer a Urgent Care waiting list.          */
/*  It will be able to add, modify, view, and exit the linked list.   */
/*  Array of linked lists for each dept with text file I/O            */
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
struct head_tail
{
  NODE *head;
  NODE *tail;
};
//Global Variables
struct head_tail lists[4];
//Declaring modules
void read_insert(char patient[20],int deptNum, union u info);
void collectInfo(void);
void list(void);
void discard(void);
void show_dept(void);
int check_duplicate(char *str);
void show_name(void);
void save_file(void);
void write_all(void);
void delete_all(void);
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
				collectInfo();
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
//Create Insert for individual node
void collectInfo(void)
{
	char nameTemp[20];
 	int deptTemp;
	union u info;
  float feverTemporary;
  int dayTemp;
  printf("Insert Name: ");
	scanf("%s",nameTemp);
	if(check_duplicate(nameTemp) != 0)
	{
		printf("\nThis name has already been used. Please select another.\n");
	}
 	if(check_duplicate(nameTemp) == 0)
 	{ 
		printf("\nInsert Department (1-4): ");
		scanf("%d", &deptTemp);
		if(deptTemp == 1 || deptTemp == 2 || deptTemp == 3 || deptTemp == 4) 
    {
      switch (deptTemp)
      {
				case 1:
					printf("\nInsert Fever Temperature in Farenheight: ");
					scanf("%f", &feverTemporary);
					info.feverTemp = feverTemporary; 
					break;
				case 2: 
					printf("\nInsert Information: ");
					scanf("%s", info.painKind);
					break;
				case 3: 
					printf("\nInsert Sick Day Count: ");
					scanf("%d",&dayTemp);
          info.sickDays = dayTemp;
          break;
				case 4:
					printf("\nInsert Sick Day Count: ");
					scanf("%d",&dayTemp);
          info.sickDays = dayTemp;
          break;
      }
      read_insert(nameTemp, deptTemp, info);
    }
    else
    {
      printf("Not a Valid Department");
    }
    return;
  }
}
//Create Insert Function to re-create list from text file
void read_insert(char patient[20],int deptNum, union u info)
{
  NODE *p;
  p = (NODE*)malloc(sizeof(NODE));
	if(check_duplicate(patient) != 0)
	{
		printf("\nThis name has already been used. Please select another.\n");
	}
 	if(check_duplicate(patient) == 0)
 	{ 
    	p->dept = deptNum;
			strcpy(p->name,patient);
      switch (deptNum)
    	{
				case 1:
					p->flag = 1;
					p->extra.feverTemp = info.feverTemp; 
					break;
				case 2: 
					p->flag = 2;
          strcpy(p->extra.painKind, info.painKind);
					break;
				case 3: 
					p->flag = 3;
          p->extra.sickDays = info.sickDays;
          break;
				case 4:
					p->flag = 3;
          p->extra.sickDays = info.sickDays;
          break;
      }  
			//Once full node is linked to the list
            		if (lists[deptNum-1].head == NULL)
            		{
              			p->next = NULL;
              			lists[deptNum-1].tail = lists[deptNum-1].head = p;
              			return;
            		}
            		else
            		{
              			p->next = NULL;
              			lists[deptNum-1].tail->next = p;
              			lists[deptNum-1].tail = p;
              			return; 
            		}
      		return;
  	}
}
//Create function to check if name already exists
int check_duplicate(char *str)
{
	NODE *p;
  int i;
  for(i = 0; i < 4; i++)
  {
    p = lists[i].head;
  	while(p != NULL)
  	{
    		if(strcmp(p->name,str) == 0)
    		{
      			return (1);
    		}
    		p = p->next;
  	}
  }
  return 0;
}
void list(void)
{
	NODE *p;
  int i;
  printf("\nUrgent Care Waiting List\n");
	printf("Patient Name\t\tDepartment\t\tInformation\n");
	printf("--------------------------------------------------------------\n");
  for(i = 0; i < 4; i++)
  {
    p = lists[i].head;
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
  }
  return;
} 
//Discard is used to delete an individual node from a list
void discard(void)
{
  int del;
  NODE *p,*q;
  printf("Insert Department: ");
  scanf("%d", &del);
  if(del == 1 || del == 2 || del == 3 || del == 4)
  {
    p = lists[del-1].head;
    q = p;
    lists[del-1].head = p->next;
    free(q);
  }
  return;
}
//Create function to show individual departmant
void show_dept()
{
  NODE *p;
  int num;
  printf("Show Department: ");
  scanf("%d",&num);
  printf("\nUrgent Care Waiting List\n");
	printf("Patient Name\t\tDepartment\t\tInformation\n");
	printf("--------------------------------------------------------------\n");
  p = lists[num-1].head;
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
//Shows information for a searched name 
void show_name()
{
  int i;
  char temp[20];
	NODE *p;
  printf("Insert Name: ");
  scanf("%s",temp);
  printf("\nUrgent Care Waiting List\n");
	printf("Patient Name\t\tDepartment\t\tInformation\n");
	printf("--------------------------------------------------------------\n");
  for(i = 0; i < 4; i++)
  {
    p = lists[i].head;
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
  }
  
  return;
}

/*
//Save file into .txt file
void save_file(void)
{
  FILE *fp;
  int departmant;
  char name[20];
  union u det;
  fp = fopen("data.txt","r");
  if(fp == NULL)
  {
    return;
  }
  //fseek(fp, 25, SEEK_SET);
  while(scanf("%s %d ",name, &departmant) == 2)
  {
    switch(departmant)
    {
      case 1: 
        fscanf(fp, "%f\n", &det.feverTemp);
        read_insert(name, departmant, det.feverTemp);
        break;
      case 2:
        fscanf(fp, "%s\n", det.painKind);
        read_insert(name, departmant, det.painKind);
        break;
      case 3: 
        fscanf(fp, "%d\n", &det.sickDays);
        read_insert(name, departmant, det.sickDays);
        break;
      case 4:
        fscanf(fp, "%d\n", &det.sickDays);
        read_insert(name, departmant, det.sickDays);
        break;
    }
  }
  return;
}
//Writes data into a file
void write_all(void)
{
  FILE *fp;
  NODE *p;
  int i;
  fp = fopen("data.txt", "w");
  fprintf(fp, "\nUrgent Care Waiting List\n");
	fprintf(fp, "Patient Name\t\tDepartment\t\tInformation\n");
	fprintf(fp, "--------------------------------------------------------------\n");
  for(i = 0; i < 0; i++)
  {
    p = lists[i].head;
    while(p != NULL)
    {
      fprintf(fp, "%s %d ", p->name, p->dept);
      switch(p->dept)
      {
        case 1:
          fprintf(fp, "%f\n", p->extra.feverTemp);
          break;
        case 2: 
          fprintf(fp, "%s\n", p->extra.painKind);
          break;
        case 3:
          fprintf(fp, "%d\n", p->extra.sickDays);
          break;
        case 4:
          fprintf(fp, "%d\n", p->extra.sickDays);
          break;
      }
      p = p->next;
    }
  }
  return;
}


*/

//Delete all nodes from memory; function called after file is saved
void delete_all(void)
{
  NODE *p,*q;
  int i;
  for(i = 0; i < 4; i++)
  {
    p = lists[i].head;
    while(p != NULL)
    {
      q = p;
      p = p->next;
      free(q);
    }
  }
  printf("List Deleted");
  return;
}
