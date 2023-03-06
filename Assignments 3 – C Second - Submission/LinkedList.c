//
// Created by ise on 12/14/21.
//

#include <malloc.h>
#include "LinkedList.h"
#include "Defs.h"
#include <stdio.h>
#include <string.h>



struct Node {
    element node;
    struct Node* next;

};


struct Linked_List_s {

    struct Node * head;
    struct Node* tail;
    int Size_LL;
    copyFunction copy_element;
    freeFunction free_element;
    printFunction print_element;
    equalFunction equal_element;
    getCategoryFunction category;





};

PlinkedList creatLinkedList(copyFunction copyFunction,freeFunction freeFunction,printFunction printFunction,equalFunction equal_Function,getCategoryFunction categoryFunction ){
    if (copyFunction == NULL|| freeFunction == NULL || printFunction==NULL || equal_Function==NULL){
        return NULL;
    }

    PlinkedList  linked_list=(PlinkedList) malloc(sizeof(struct Linked_List_s));
    if (linked_list==NULL){
        return NULL;
    }
    linked_list->Size_LL=0;
    linked_list->free_element=freeFunction;
    linked_list->copy_element=copyFunction;
    linked_list->equal_element=equal_Function;
    linked_list->print_element=printFunction;
    linked_list->category=categoryFunction;


    linked_list->head=NULL;
    linked_list->tail=NULL;

    return linked_list;

}
void destroyList(PlinkedList linked_list){
    if (linked_list==NULL){return;}
    if (linked_list->head==NULL||linked_list->tail==NULL){return;}

    Pnode temp=linked_list->head;
    Pnode next_node;
    while (linked_list->Size_LL>0) {
        if (linked_list->Size_LL==1){
            linked_list->free_element(temp);
            linked_list->Size_LL=0;
            break;
        }

        next_node=temp->next;
        linked_list->free_element(temp);
        temp=next_node;
        linked_list->Size_LL--;
    }
    linked_list->head=NULL;
    linked_list->tail=NULL;
    free(linked_list);

}
status appendNode(PlinkedList  linked_list,element Element){
    if (linked_list==NULL){return failure;}
    if (Element==NULL){return failure;}
    if (linked_list->head==NULL && linked_list->tail==NULL){
        element new_element = linked_list->copy_element(Element);
        if (new_element==NULL){
            return failure;
        }
        linked_list->head=new_element;
        linked_list->tail=new_element;
        linked_list->Size_LL++;
    }
    else{
        element new_element = linked_list->copy_element(Element);
        if (new_element==NULL){
            return failure;
        }
        linked_list->tail->next=new_element;
        linked_list->tail=new_element;
        linked_list->Size_LL++;


    }
    return success;

}

status deleteNode(PlinkedList linked_list,element Element){
    if (linked_list==NULL||Element==NULL){
        return failure;}
    if (linked_list->head==NULL||linked_list->tail==NULL){return failure;}
    if (linked_list->Size_LL==1&&(linked_list->equal_element(Element,linked_list->head)==0)){
        linked_list->free_element(linked_list->head);
        linked_list->head=NULL;
        linked_list->tail=NULL;
        linked_list->Size_LL--;


    }
    Pnode temp=linked_list->head;
    struct Node* next_node;
    while (temp!=NULL){
        if (linked_list->equal_element(linked_list->head,Element)==0){
            linked_list->head=linked_list->head->next;
            linked_list->free_element(temp);
            linked_list->Size_LL--;
            break;


        }
        if (linked_list->equal_element(temp->next,linked_list->tail)==0&&linked_list->equal_element(temp->next,Element)==0){
            linked_list->tail=temp;
            linked_list->free_element(temp->next);
            temp->next=NULL;
            linked_list->Size_LL--;
            break;

        }
        if (linked_list->equal_element(temp->next,Element)==0&&linked_list->equal_element(temp->next,linked_list->tail)!=0){
            next_node=temp->next;
            temp->next=temp->next->next;
            next_node->next=NULL;
            linked_list->free_element(next_node);
            linked_list->Size_LL--;
            break;



        }
        temp=temp->next;

    }
    return success;

}

status displayList(PlinkedList linked_list){
    if (linked_list==NULL){return failure;}

    Pnode temp=linked_list->head;
    for (int i = 0; i < linked_list->Size_LL ; ++i) {
        linked_list->print_element(temp);
        temp=temp->next;


    }

    return success;


}


element searchByKeyInList(PlinkedList linked_list,element Element){
    if (linked_list==NULL||Element==NULL){
        return NULL;}
    Pnode temp=linked_list->head;
    while (temp!=NULL){
        if( strcmp(linked_list->category(temp),Element)==0){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;

}



