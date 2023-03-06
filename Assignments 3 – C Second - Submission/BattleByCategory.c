
#include <stdio.h>
#include "BattleByCategory.h"
#include "Defs.h"
#include "stdlib.h"
#include <string.h>
#include "MaxHeap.h"
#include "LinkedList.h"
#include "Pokemon.h"
struct battle_s{
    PlinkedList linked_list;
    int capacity;
    int numberOfCategories;
    char** Categories;
    equalFunction equalElement;
    copyFunction copyElement;
    freeFunction freeElement;
    getCategoryFunction getCategory;
    getAttackFunction getAttack;
    printFunction printElement;
};



Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement){
    if (categories==NULL||equalElement==NULL||copyElement==NULL||freeElement==NULL||getCategory==NULL||getAttack==NULL||printElement==NULL){
        return NULL;
    }

    Battle  battle=(Battle) malloc(sizeof(struct battle_s));
    if(battle==NULL){
        return NULL;
    }


    battle->getCategory=getCategory;
    battle->equalElement=equalElement;
    battle->printElement=printElement;
    battle->copyElement=copyElement;
    battle->freeElement=freeElement;
    battle->numberOfCategories=numberOfCategories;
    battle->getAttack=getAttack;
    battle->capacity=capacity;
    battle->linked_list= creatLinkedList((copyFunction) copy_max_heap, (freeFunction) destroyHeap,
                                         (printFunction) printHeap, (equalFunction) compareHeaps,
                                         (getCategoryFunction) getHeapId);


    *(categories+strlen(categories)-2)='\0';
    char * token;

    battle->Categories=(char **) malloc(sizeof(char*)*numberOfCategories);

    if (battle->Categories==NULL){
        return NULL;
    }

    int i=0;

    token= strtok(categories,",");
    while (token!=NULL) {
        battle->Categories[i]=token;
        token = strtok(NULL, ",");
        i++;

    }



    for (int j = 0; j < numberOfCategories; ++j) {
        Pointer_maxHeap maxHeaptemp = CreateHeap((printFunction) Print_Pokemon, (copyFunction) copy_pokemon,
                                                 (equalFunction) compare_pokemons, (freeFunction) destroy_pokemon, battle->Categories[j], capacity);
        if (maxHeaptemp==NULL){
            return NULL;
        }
        appendNode(battle->linked_list,maxHeaptemp);
    }



    return battle;

    }



status insertObject(Battle b, element elem) {
    if (b == NULL || elem == NULL) {
        return failure;
    }
    Pnode temp=searchByKeyInList(b->linked_list,b->getCategory(elem));
    if (temp ==NULL){
        return failure;
    }
    if (getHeapCurrentSize((Pointer_maxHeap) temp) == b->capacity){
        return failure;

    }
    insertToHeap(elem,(Pointer_maxHeap)temp);
    return success;

}

void displayObjectsByCategories(Battle b){
    displayList(b->linked_list);
}

element removeMaxByCategory(Battle b,char* category){
    if (b==NULL||category==NULL){
        return NULL;
    }
    Pnode temp=searchByKeyInList(b->linked_list,category);
    if (temp==NULL){
        return NULL;
    }
    Pointer_maxHeap M_H =PopMaxHeap((Pointer_maxHeap) temp);
    if (M_H==NULL){
        return NULL;
    }

    return M_H;

}

int getNumberOfObjectsInCategory(Battle b,char* category){
    Pnode temp=searchByKeyInList(b->linked_list,category);
    if (temp==NULL){
        return -1;
    }
    return getHeapCurrentSize((Pointer_maxHeap) temp);

}


element fight(Battle b,element elem){
    if (b==NULL||elem==NULL){
        return NULL;
    }


    int attack_from_user;
    int attack_from_system;
    int max_diff=-1000000;
    int counter_nulls=0;
    Pnode curr;


    for (int i = 0; i < b->numberOfCategories; ++i) {
        curr=searchByKeyInList(b->linked_list,b->Categories[i]);
        element system=TopMaxHeap((Pointer_maxHeap) curr);
        if(system!=NULL){
            if(b->getAttack(elem,system,&attack_from_system,&attack_from_user) > max_diff){
                max_diff=b->getAttack(elem,system,&attack_from_user,&attack_from_system);
            }
        }
        else{
            counter_nulls++;

        }




    }


    if (counter_nulls==b->numberOfCategories){
        return NULL;
    }

    element system_final;
    for (int i = 0; i < b->numberOfCategories; ++i) {
        curr=searchByKeyInList(b->linked_list,b->Categories[i]);
        system_final= TopMaxHeap((Pointer_maxHeap) curr);
        if(system_final!=NULL) {
            if (max_diff==b->getAttack(elem,system_final,&attack_from_user,&attack_from_system)){
                break;
            }
        }


    }
    printf("The final battle between:\n");
    b->printElement(elem);

    printf("In this battle his attack is :%d\n\n",attack_from_user);
    printf("against ");
    b->printElement(system_final);
    printf("In this battle his attack is :%d\n\n",attack_from_system);


    //the system won
    if (max_diff>0){
        printf("THE WINNER IS:\n");
        b->printElement(system_final);
        return system_final;

    }
    //the user won if (max_diff<0)
    if (max_diff<0){
        printf("THE WINNER IS:\n");
        b->printElement(elem);
        return elem;

    }

    //its a tie
    printf("IT IS A DRAW.\n");
    return elem;


}

status destroyBattleByCategory(Battle b){
    if (b==NULL){
        return failure;
    }
    destroyList(b->linked_list);
    free(b->Categories);
    free(b);

    return success;

}


