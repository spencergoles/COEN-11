#include "link.h"
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