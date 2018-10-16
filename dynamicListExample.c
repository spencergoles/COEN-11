#include <stdio.h>
#define NODE struct node
//Define node struct to create linked list
struct node
{
  int number;
  NODE *next;
};

NODE *head = NULL;

//Insert node at the end
void insert(int number)
{
  NODE *p;
  p = (NODE*)malloc(sizeof(NODE));
  if (p == NULL)
    return;

  p->number = number;
  p->next = head;
  head = p;
  return;
}
//Insert in the middle of the list
void insert_ordered(int number)
{
  NODE *p,*q;
  NODE *temp;

  temp = (NODE *)malloc(sizeof(NODE));
  if(temp == NULL)
  {
    return;
  }
  temp->number = number;
  p = q = head;
  while(p != NULL)
  {
    if(p->number > number)
    {
      break;
    }
    q = p; 
    p = p->next;
  }
  //Empty or first insert
  if(p == head)
  {
    temp->next = head;
    head = temp;
  }
  //Last insert
  else if(p == NULL)
  {
    temp->next = NULL;
    q->next = temp;
  }
  else
  {
    temp->next = p; 
    q->next = temp;
  }
  return;
}

//Print the linked list
void print (void)
{
  NODE *p;
  if(head == NULL)
  {
    printf("Empty");
    return;
  }
  p = head;
  while(p!=NULL)
  {
    printf("%d\n",p->number);
    p = p->next;
  }
  return;
}
//Create function to search linked list
int search(int number)
{
  NODE *p;

  p = head;
  while(p != NULL)
  {
    if(number == p->number)
    {
      return (1);
    }
  p = p->next;
  }
  return 0;
}
// Deleting function
int delete(int number)
{
  NODE *p, *q;

  p = q = head;
  while(p != NULL)
  {
    if(p->number == number)
    {
      break;
    }
    q = p;
    p = p->next;
  }
  //If search not found
  if(p == NULL)
  {
    printf("Not Found");
    return 0;
  }
  //First node
  if(p == head)
  {
    head = p->next;
    free(p);
  }
  //Last or middle node
  else
  {
    q->next = p->next;
    free(p);
  }
  return 1;
}
