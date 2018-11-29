//C Preprocessor
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define  NODE struct node
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
extern struct head_tail lists[4];
extern pthread_mutex_t mutex;
//Declaring modules 
extern void read_insert(char patient[20],int deptNum, union u info);
extern void collectInfo(void);
extern void list(void);
extern void discard(void);
extern void show_dept(void);
extern int check_duplicate(char *str);
extern void show_name(void);
extern void change_dept(void);
extern void read_file(char *fileName, int key);
extern void write_all(char *fileName, int key);
extern void delete_all(NODE *p);
extern void *auto_save(void *args);
extern void read_auto_save(char *fileName);
