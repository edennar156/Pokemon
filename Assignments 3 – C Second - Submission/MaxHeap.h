//
// Created by ise on 12/14/21.
//

#ifndef C_PROJECT2_MAXHEAP_H
#define C_PROJECT2_MAXHEAP_H
#include  "Defs.h"
#include <stdio.h>

typedef struct maxHeap* Pointer_maxHeap;
/*
 * the function gets all the function pointers that she needs to creat generic heap
 * char * for the uniq name
 * and last it gets max capacity
 * returns pointer to a struct of generic max heap
 */
Pointer_maxHeap CreateHeap(printFunction printHeap,copyFunction copyHeap,equalFunction equalHeap,freeFunction freeHeap,char * heap_max_name,int max_capacity);
/*
 * destroys the heap
 * gets pointer to max heap
 * clears all the memory that allocated by max heap
 * returns successes if works or failure if not
 */
void destroyHeap(Pointer_maxHeap max_heap);
/*
 * the function inserts new element in to max heap
 * it gets pointer to element (void**)
 * if the heap didnt got to its max capacity
 * the function will insert the pointer element into the heap
 * returns successes if works or failure if not
 */
status insertToHeap(element Element,Pointer_maxHeap max_heap);
/*
 * function that prints all the elements sorted way
 * gets pointer to max heap
 * returns successes if works or failure if not
 */
status printHeap(Pointer_maxHeap max_heap);
/*
 * the function gets pointer to the heap
 * and returns the max element in the heap, if the heap empty returns NULL
 * and deletes its from the heap
 */
element PopMaxHeap(Pointer_maxHeap max_heap);
/*
 * the function gets pointer to the heap
 * and returns max element , if the heap is empty returns null
 */
element TopMaxHeap(Pointer_maxHeap max_heap);
/*
 * gets pointer to max heap
 * returns heap name (char*)
 */
char* getHeapId(Pointer_maxHeap max_heap);
/*
 * gets pointer to max heap
 * returns the current number of elements
 */
int getHeapCurrentSize(Pointer_maxHeap max_heap);

//=======help function for battle category======
Pointer_maxHeap copy_max_heap(Pointer_maxHeap maxHeap);
//copy the heap
int compareHeaps(Pointer_maxHeap maxheap1, Pointer_maxHeap maxHeap2);
//compare heaps name

#endif //C_PROJECT2_MAXHEAP_H
