
/**********************************************************************/
/*  Spencer Goles        COEN 11        25 October 2018  Version 5.0  */
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
void change_dept(void);
void read_file(char *fileName);
void write_all(char *fileName);
void delete_all(void);
//Main Control Function
int main(int argc, char *argv[ ])
{
        if (argc == 1)
        {
                printf("The name of the file is missing!\n");
                return 1;
        }
        read_file(argv[1]);
        int cmd;
        printf("\n\nWelcome to the Urgent Care Waiting List\n\n");
        while(1)
        {
                printf("\n\nPlease Select a Command Below\n\n");
                printf("1. View List              3. Add Patient        5. Search Name      7.Quit\n");
                printf("2. Show Department        4. Remove Patient     6. Change Department\n\n");
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
                                change_dept();
                                break;
                        case 7:
                                write_all(argv[1]);
                                delete_all();
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
//
//Changes a node from one department to another
void change_dept(void)
{
	int oldDept, newDept;
	char name[20];
	union u info;
	float feverTemporary;
	int dayTemp;
	NODE *p,*q;
	printf("Insert Name: ");
	scanf("%s", name);
	printf("Insert Current Department: ");
	scanf("%d",&oldDept);
	printf("Insert New Department: ");
	scanf("%d",&newDept);
	if(check_duplicate(name) == 1)
	{
        	if(oldDept <= 4 && oldDept >= 1 && newDept <= 4 && newDept >= 1)
        	{
            		p = q = lists[oldDept-1].head;
            		while (p != NULL)
            		{
              			if(strcmp(p->name, name) == 0)
                		{
                  			break;
                		}
                		q = p;
                		p = p->next;
            		}
            		if(p == lists[oldDept-1].head)
            		{
                		lists[oldDept-1].head = p->next;
            		}
            		if(p == lists[oldDept-1].tail)
            		{
                		lists[oldDept-1].tail = q;
                		q->next = NULL;
            		}
            		else
            		{
                		q->next = p->next;
            		}
            		free(p);
            		switch (newDept)
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
            		read_insert(name, newDept, info);
        	}
    	}
    	else
    	{
      		printf("The name has not been found");
    	}
        return;
}
//Read file from data.txt file
void read_file(char *fileName)
{
        FILE *fp;
        char name[20];
        int departmant;
        union u info;
        fp = fopen(fileName,"r");
        if(fp == NULL)
        {
                return;
        }
        fseek(fp, 28, SEEK_SET);
        while(fscanf(fp, "%s %d  ",name, &departmant) == 2)
        {
                switch(departmant)
                {
                        case 1:
                                fscanf(fp, "%f\n", &info.feverTemp);
                                break;
                        case 2:
                                fscanf(fp, "%s\n", info.painKind);
                                break;
                        case 3:
                                fscanf(fp, "%d\n", &info.sickDays);
                                break;
                        case 4:
                                fscanf(fp, "%d\n", &info.sickDays);
                                break;
                }
                read_insert(name, departmant, info);
        }
        fclose(fp);
        return;
}
//Writes data into a file
void write_all(char *fileName)
{
        FILE *fp;
        NODE *p;
        int i;
        fp = fopen(fileName, "w");
        fprintf(fp, "Name\tDepartment\tInformation\n");
        for(i = 0; i < 4; i++)
        {
                p = lists[i].head;
                while(p != NULL)
                {
                        fprintf(fp, "%s\t\t%d\t\t", p->name, p->dept);
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
        fclose(fp);
        return;
}
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
