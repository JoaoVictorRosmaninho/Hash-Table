#ifndef LIST_H
# define LIST_H

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>

  enum {INSERT_END=-2, INSERT_INI};

  typedef struct node{
    char * data;
    struct node *next;
    struct node *prev; 
  } Node;

  typedef struct list {
    Node *node_ini;
    Node *node_end;
    unsigned int size;
  } List;

  void *makenode(uint16_t size);

  List *initList(void);

  void insert(List *list, uint16_t pos, char *value);

  void add(List *list, char *data);

  void display(List * list);

  void save(List *list);

  List *load(char *filename);

#endif