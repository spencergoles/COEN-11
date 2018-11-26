/**********************************************************************/
/*  Spencer Goles        COEN 11        15 November 2018  Version 8.0 */
/*  This program will administer a Urgent Care waiting list.          */
/*  It will be able to add, modify, view, and exit the linked list.   */
/*  Autosave feature updating into a binary file                      */
/*  Add XOR encryption to the text file before and after saving       */          
/*  Array of linked lists for each dept with text file I/O            */
/**********************************************************************/

//C Preprocessor
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define NODE struct node
#define DEPARTMENT(a) ((a == 1 || a == 2 || a == 3 || a == 4) ? (1) : (0))
//Create base structures
union u
{
        float feverbuffer;    // flag = 1
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
pthread_mutex_t mutex;
//Declaring modules
void read_insert(char patient[20],int deptNum, union u info);
void collectInfo(void);
void list(void);
void discard(void);
void show_dept(void);
int check_duplicate(char *str);
void show_name(void);
void change_dept(void);
void read_file(char *fileName, int key);
void write_all(char *fileName, int key);
void delete_all(NODE *p);
void *auto_save(void *args);
void read_auto_save(char *fileName);
//Main Control Function
int main(int argc, char *argv[ ])
{
        if (argc == 1)
        {
                printf("The name of the file is missing!\n");
                return 1;
        }
        //Convert key to int
        int key = atoi(argv[3]);
        read_file(argv[1],key);
	    //Create thread and mutex
        pthread_t thr;
        pthread_mutex_init (&mutex, NULL);
        pthread_create(&thr,NULL, auto_save,(void *) argv[2]);
        int cmd, i;
        printf("\n\nWelcome to the Urgent Care Waiting List\n\n");
        while(1)
        {
                printf("\n\nPlease Select a Command Below\n\n");
                printf("1. View List              3. Add Patient        5. Search Name          7. Read Autosave\n");
                printf("2. Show Department        4. Remove Patient     6. Change Department    8. Quit\n\n");
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
                                read_auto_save(argv[2]);
                                break;
                        case 8:
				//Cancel thread
                                pthread_mutex_lock(&mutex);
                                pthread_cancel(thr);
                                pthread_mutex_unlock(&mutex);
                                write_all(argv[1],key);
                                //For loop uses recursive delete on array of linked lists
                                for(i = 0; i < 4; i++)
                                {
                                	delete_all(lists[i].head);
                                }
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
        char namebuffer[20];
        int deptbuffer;
        union u info;
        float feverbufferorary;
        int daybuffer;
        printf("Insert Name: ");
        scanf("%s",namebuffer);
        if(check_duplicate(namebuffer) != 0)
        {
                printf("\nThis name has already been used. Please select another.\n");
        }
        if(check_duplicate(namebuffer) == 0)
        {
                printf("\nInsert Department (1-4): ");
                scanf("%d", &deptbuffer);
                if(DEPARTMENT(deptbuffer) == 1)
                {
                        switch (deptbuffer)
                        {
                                case 1:
                                        printf("\nInsert Fever buffererature in Farenheight: ");
                                        scanf("%f", &feverbufferorary);
                                        info.feverbuffer = feverbufferorary;
                                        break;
                                case 2:
                                        printf("\nInsert Information: ");
                                        scanf("%s", info.painKind);
                                        break;
                                case 3:
                                        printf("\nInsert Sick Day Count: ");
                                        scanf("%d",&daybuffer);
                                        info.sickDays = daybuffer;
                                        break;
                                case 4:
                                        printf("\nInsert Sick Day Count: ");
                                        scanf("%d",&daybuffer);
                                        info.sickDays = daybuffer;
                                        break;
                        }
                        read_insert(namebuffer, deptbuffer, info);
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
                                p->extra.feverbuffer = info.feverbuffer;
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
                //Full node is linked to the list after thread locked
                pthread_mutex_lock(&mutex);
                if (lists[deptNum-1].head == NULL)
                {
                        p->next = NULL;
                        lists[deptNum-1].tail = lists[deptNum-1].head = p;
                        pthread_mutex_unlock(&mutex);
                        return;
                }
                else
                {
                        p->next = NULL;
                        lists[deptNum-1].tail->next = p;
                        lists[deptNum-1].tail = p;
                        pthread_mutex_unlock(&mutex);
                        return;
                }
                pthread_mutex_unlock(&mutex);
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
//Function prints out each full linked list
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
                                        printf("%s\t\t\t%d\t\t\t%0.1f Degrees F\n",p->name,p->dept,p->extra.feverbuffer);
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
        if(DEPARTMENT(del) == 1)
        {
                pthread_mutex_lock(&mutex);
                p = lists[del-1].head;
                q = p;
                lists[del-1].head = p->next;
                free(q);
                pthread_mutex_unlock(&mutex);
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
                                printf("%s\t\t\t%d\t\t\t%0.1f Degrees F\n",p->name,p->dept,p->extra.feverbuffer);
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
                                                printf("%s\t\t\t%d\t\t\t%0.1f Degrees F\n",p->name,p->dept,p->extra.feverbuffer);
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
//Changes a node from one department to another
void change_dept(void)
{
	int oldDept, newDept;
	char name[20];
	union u info;
	float feverbufferorary;
	int daybuffer;
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
                            		printf("\nInsert Fever buffererature in Farenheight: ");
                            		scanf("%f", &feverbufferorary);
                            		info.feverbuffer = feverbufferorary;
                            		break;
                    		case 2:
                            		printf("\nInsert Information: ");
                            		scanf("%s", info.painKind);
                            		break;
                    		case 3:
                            		printf("\nInsert Sick Day Count: ");
                            		scanf("%d",&daybuffer);
                            		info.sickDays = daybuffer;
                            		break;
                    		case 4:
                            		printf("\nInsert Sick Day Count: ");
                            		scanf("%d",&daybuffer);
                            		info.sickDays = daybuffer;
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
//Delete all nodes from memory; recursive function called after file is saved
void delete_all(NODE *p)
{
	if(p == NULL)
    		return;
  	delete_all(p->next);
  	free(p);
  	return;
}
//Read text file and insert into linked list array
//Uses XOR loop and param key to decrypt data 
void read_file(char *fileName, int key)
{
	FILE *fp;
	char name[20];
	int i, departmant;
	union u info;
        char temp[60];
	fp = fopen(fileName,"r");
	if(fp == NULL)
		return;
	while(fgets(temp, 60, fp) != NULL)
	{
                for(i = 0; temp[i] != '\n';i++)
                {
                        temp[i] = ((temp[i]) ^ (key));
                }
                sscanf(temp, "%s\t%d",name, &departmant);
		switch(departmant)
		{
	    		case 1:
				sscanf(temp, "%s\t%d\t%f\n",name, &departmant ,&info.feverbuffer);
                                read_insert(name, departmant, info);
				break;
	    		case 2:
				sscanf(temp, "%s\t%d\t%s\n", name, &departmant, info.painKind);
                                read_insert(name, departmant, info);
				break;
	    		case 3:
                        case 4:
				sscanf(temp, "%s\t%d\t%d\n", name, &departmant, &info.sickDays);
                                read_insert(name, departmant, info);
				break;
		}
	}
	fclose(fp);
	return;
}
//Writes data into a text file from the lists 
//Uses XOR loop and param key to encrypt data 
void write_all(char *fileName, int key)
{
	FILE *fp;
	NODE *p;
	int i,j;
        char temp[60];
	fp = fopen(fileName, "w");
	for(i = 0; i < 4; i++)
	{
		p = lists[i].head;
		while(p != NULL)
		{
		    	switch(p->dept)
		    	{
				case 1:
		    			sprintf(temp, "%s\t%d\t%f\n", p->name, p->dept, p->extra.feverbuffer);
			    		break;
				case 2:
					sprintf(temp, "%s\t%d\t%s\n", p->name, p->dept, p->extra.painKind);
				    	break;
				case 3:
				    	sprintf(temp, "%s\t%d\t%d\n", p->name, p->dept, p->extra.sickDays);
				    	break;
				case 4:
				    	sprintf(temp, "%s\t%d\t%d\n", p->name, p->dept, p->extra.sickDays);
				    	break;
		    	}
                        for(j = 0; j < strlen(temp); j++)
                        {
                                temp[j] = ((temp[j]) ^ (key));
                        }
                        fprintf(fp, "%s\n", temp); 
		    	p = p->next;
		}
	}
	fclose(fp);
	return;
}
//Autosaves list into a binary file every 15 seconds
void *auto_save(void *args)
{
	FILE *fp;
	NODE *p;
	int i;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		fp = fopen(args, "wb");
		for (i = 0; i < 4;i++)
		{
			p = lists[i].head;
		    	while(p != NULL)
		    	{
				fwrite(p, sizeof(NODE),1,fp);
				p = p->next;
		    	}
		}
		fclose(fp);
		pthread_mutex_unlock(&mutex);
		sleep(15);
	}
}
//Reads the data from binary autosave file and outputs
void read_auto_save(char *fileName)
{
	FILE *fp;
	NODE temp;
	pthread_mutex_lock(&mutex);
	fp = fopen(fileName, "rb");
	if (fp == NULL)
	{
		printf("No Autosaved File");
		pthread_mutex_unlock(&mutex);
		return;
	}
	printf("Name    Department  Information\n");
	while(fread(&temp,sizeof(NODE),1, fp) > 0)
	{
		if(temp.flag ==1)
			printf("%s	%d	%0.2f\n", temp.name, temp.dept, temp.extra.feverbuffer);
		if(temp.flag == 2)
			printf("%s	%d	%s\n", temp.name, temp.dept, temp.extra.painKind);
		if(temp.flag == 3)
		    	printf("%s	%d	%d\n", temp.name, temp.dept, temp.extra.sickDays);
	}
	fclose(fp);
	pthread_mutex_unlock(&mutex);
	return;
}
