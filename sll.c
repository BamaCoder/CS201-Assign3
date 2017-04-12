#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

sll *newSLL(void (*d)(FILE *,void *)) //d is the display function
{
  sll *items = malloc(sizeof(sll));
  if (items == 0)
  {
    fprintf(stderr,"out of memory");
    exit(-1);
  }
  items->head = 0;
  items->tail = 0;
  items->size = 0;
  items->display = d;
  return items;
}

void insertSLL(sll *items, int index, void *value)
{
  int i;
  sllnode *newnode = malloc(sizeof(sllnode));
  sllnode *traversenode = items->head;
  // Error Checking for Index input
  newnode->value = value;
  newnode->next = 0;
  if(index == 0)
  {
    newnode->next = items->head;
    if(items->tail == 0) items->tail = newnode;
    items->head = newnode;
  }
  else if(index == sizeSLL(items))
  {
    if(items->tail != 0) items->tail->next = newnode;
    items->tail = newnode;
  }
  else
  {
    for(i = 0; i < index-1; i++)
    {
      traversenode = traversenode->next;
    }
    newnode->next = traversenode->next;
    traversenode->next = newnode;
  }
  items->size++;
}

void *removeSLL(sll *items, int index)
{
  int i;
  sllnode *traversenode = items->head;
  sllnode *temp;
  void *delval;
  if(index == 0)
  {
    temp = items->head;
    delval = temp->value;
    if(items->head == items->tail) items->tail = 0;
    items->head = items->head->next;
    free(temp);
    temp = 0;
  }
  else if (index == sizeSLL(items)-1)
  {
    temp = items->tail;
    delval = temp->value;
    while(traversenode->next != temp) traversenode = traversenode->next;
    items->tail = traversenode;
    items->tail->next = 0;
    free(temp);
    temp = 0;
  }
  else
  {
    for(i = 0; i < index-1; i++)
    {
      traversenode = traversenode->next;
    }
    temp = traversenode->next;
    delval = temp->value;
    traversenode->next = traversenode->next->next;
    free(temp);
    temp = 0;
  }
  items->size--;
  return delval;
}

void unionSLL(sll *recipient, sll*donor)
{
  recipient->tail->next = donor->head;
  recipient->tail = donor->tail;
  recipient->size += donor->size;
}

void *getSLL(sll *items, int index)
{
  int i;
  sllnode *traversenode = items->head;
  if(index == 0)
  {
    return items->head->value;
  }
  else if(index == sizeSLL(items)-1)
  {
    return items->tail->value;
  }
  else
  {
    for(i = 0; i < index; i++)
    {
      traversenode = traversenode->next;
    }
    return traversenode->value;
  }
}

int sizeSLL(sll *items)
{
  return items->size;
}

void displaySLL(FILE *fp, sll *items)
{
  sllnode *traversenode = items->head;
  fprintf(fp, "[");
  if(traversenode != 0)
  {
    while(traversenode->next != 0)
      {
        items->display(fp,traversenode->value);
        traversenode = traversenode->next;
        fprintf(fp, ",");
      }
    items->display(fp,traversenode->value);
  }
  fprintf(fp, "]");
}
