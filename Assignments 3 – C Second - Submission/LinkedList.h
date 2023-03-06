//
// Created by ise on 12/14/21.
//

#ifndef C_PROJECT2_LINKEDLIST_H
#define C_PROJECT2_LINKEDLIST_H
#include  "Defs.h"
#include <stdio.h>


typedef struct Linked_List_s*  PlinkedList;
typedef struct Node* Pnode;


//creats linked list. returns NULL if its failes
PlinkedList creatLinkedList(copyFunction copyFunction,freeFunction freeFunction,printFunction printFunction,equalFunction equal_Function,getCategoryFunction categoryFunction);
//release the memory allocated for the linked list
void destroyList(PlinkedList linked_list);
//insert an element to the end of the list
status appendNode(PlinkedList  linked_list,element Element);
//deletes element if exist,if not returns failure
status deleteNode(PlinkedList linked_list,element Element);
//prints the list, returns successes or failure if it works
status displayList(PlinkedList linked_list);
/*
 * searching for node in the linked list,
 * if exist returns the value of the node
 * if not - returns null
 */
element searchByKeyInList(PlinkedList linked_list,element Element);





#endif //C_PROJECT2_LINKEDLIST_H
