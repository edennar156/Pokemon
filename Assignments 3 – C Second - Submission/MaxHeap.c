//
// Created by ise on 12/14/21.
#include <malloc.h>
#include "Defs.h"
#include "MaxHeap.h"
#include <stdio.h>
#include <string.h>

struct maxHeap{
    char* MaxHeap_name;
    int max_capacity;
    element * heap_array;
    int curr_size;
    copyFunction copy_heap;
    freeFunction free_heap;
    printFunction print_heap;
    equalFunction equal_heap;

};


Pointer_maxHeap CreateHeap(printFunction printHeap,copyFunction copyHeap,equalFunction equalHeap,freeFunction freeHeap,char * heap_max_name,int max_capacity){
    if (max_capacity<=0 || printHeap == NULL|| copyHeap == NULL|| equalHeap == NULL|| freeHeap ==NULL){
        return NULL;
    }
    if (heap_max_name==NULL){return NULL;}
    Pointer_maxHeap maxHeap = (Pointer_maxHeap) malloc(sizeof(struct maxHeap));
    if (maxHeap==NULL){
        return NULL;
    }
    maxHeap->MaxHeap_name=(char *) malloc((sizeof(char)*strlen(heap_max_name))+1);
    if (maxHeap->MaxHeap_name==NULL){
        return NULL;
    }
    strcpy(maxHeap->MaxHeap_name,heap_max_name);
    maxHeap->max_capacity=max_capacity;
    maxHeap->heap_array=(element*) malloc(sizeof(element)*(max_capacity));
    if ( maxHeap->heap_array==NULL){
        return NULL;
    }
    maxHeap->curr_size=0;
    maxHeap->copy_heap=copyHeap;
    maxHeap->print_heap=printHeap;
    maxHeap->equal_heap=equalHeap;
    maxHeap->free_heap=freeHeap;

    return maxHeap;
}

int Parent(int index){
    return (index-1)/2;
}

int RightChild(int index){
    return (2*index)+2;
}

int LeftChild(int index){
    return (2*index)+1;
}

void swap(int i1,int i2,Pointer_maxHeap maxHeap){
    element temp;
    temp=maxHeap->heap_array[i1];
    maxHeap->heap_array[i1]=maxHeap->heap_array[i2];
    maxHeap->heap_array[i2]=temp;
}


status insertToHeap(element Element,Pointer_maxHeap max_heap){
    if (max_heap==NULL||Element==NULL){
        return failure;
    }

    element new_element = max_heap->copy_heap(Element);
    if (new_element==NULL){
        return failure;
    }
    max_heap->heap_array[max_heap->curr_size]=new_element;
    int curr=max_heap->curr_size;
    while (max_heap->equal_heap(max_heap->heap_array[curr],max_heap->heap_array[Parent(curr)])==1){
        swap(curr, Parent(curr),max_heap);
        curr = Parent(curr);

    }
    max_heap->curr_size++;
    return success;

}


void maxHeapify(int i, Pointer_maxHeap maxHeap){
    int left = LeftChild(i);
    int right = RightChild(i);
    int largest;
    if (left<=maxHeap->curr_size && maxHeap->equal_heap(maxHeap->heap_array[left],maxHeap->heap_array[i])==1){
        largest=left;
    } else{
        largest=i;
    }
    if ( right<=maxHeap->curr_size && maxHeap->equal_heap(maxHeap->heap_array[right],maxHeap->heap_array[largest])==1){
        largest=right;
    }
    if (largest!=i){
        swap(i,largest,maxHeap);
        maxHeapify(largest,maxHeap);
    }
}

status printHeap(Pointer_maxHeap max_heap){
    if (max_heap==NULL){return failure;}
    printf("%s:\n",max_heap->MaxHeap_name);
    if (max_heap->curr_size==0){
        printf("No elements.\n\n");
    }

    if (max_heap->curr_size!=1){
        for (int i = 0; i < max_heap->curr_size; ++i) {
            for (int k = 0; k < max_heap->curr_size-i-1; ++k) {
                if (max_heap->equal_heap(max_heap->heap_array[k],max_heap->heap_array[k+1])==-1){
                    swap(k,k+1,max_heap);

                }

            }
        }


    }


    for (int m = 0; m < max_heap->curr_size; ++m) {
        printf("%d. ",m+1);
        max_heap->print_heap(max_heap->heap_array[m]);

    }


    return success;
}

element PopMaxHeap(Pointer_maxHeap max_heap){
    if (max_heap==NULL||max_heap->curr_size==0){return NULL;}
    if(max_heap->curr_size==1){
        max_heap->curr_size--;
        element tmp=max_heap->heap_array[0];
        max_heap->heap_array[0]=NULL;
        return tmp;
    }
    element temp;
    temp = max_heap->heap_array[0];

    max_heap->heap_array[0]=max_heap->heap_array[max_heap->curr_size-1];
    max_heap->curr_size--;
    maxHeapify(0,max_heap);

    return temp;
}

element TopMaxHeap(Pointer_maxHeap max_heap){
    if (max_heap==NULL){
        return NULL;
    }
    return max_heap->heap_array[0];
}

char* getHeapId(Pointer_maxHeap max_heap){
    if (max_heap==NULL){return NULL;}
    return max_heap->MaxHeap_name;
}

int getHeapCurrentSize(Pointer_maxHeap max_heap){
    if (max_heap==NULL){return 0;}
    return max_heap->curr_size;
}

void destroyHeap(Pointer_maxHeap max_heap){
    for (int i = 0; i < max_heap->curr_size; ++i) {
        max_heap->free_heap(max_heap->heap_array[i]);
    }
    free(max_heap->heap_array);
    free(max_heap->MaxHeap_name);
    free(max_heap);
}


Pointer_maxHeap copy_max_heap(Pointer_maxHeap maxHeap){
    if (maxHeap==NULL){
        return NULL;
    }
    return maxHeap;


}
int compareHeaps(Pointer_maxHeap maxheap1, Pointer_maxHeap maxHeap2){

    return strcmp(getHeapId(maxheap1), getHeapId(maxHeap2));

}
