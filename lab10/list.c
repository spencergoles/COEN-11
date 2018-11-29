#include "link.h"
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