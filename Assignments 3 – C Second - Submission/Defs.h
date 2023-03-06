//
// Created by ise on 12/14/21.
//

#ifndef C_PROJECT2_DEFS_H
#define C_PROJECT2_DEFS_H
typedef enum e_bool { false,true } bool;
typedef enum e_status { success, failure} status;
typedef void * element;
typedef element(*copyFunction) (element);
typedef status(*freeFunction) (element);
typedef status(*printFunction) (element);
typedef int(*equalFunction) (element, element);//1 first bigger, 0 - same, -1 second bigger
typedef char*(*getCategoryFunction)(element);
typedef int(*getAttackFunction)(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond);
// return the first attack - second attack . also produce the attack of each element, The function transmits the information through the pointers received in the function

#endif //C_PROJECT2_DEFS_H
