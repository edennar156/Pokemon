//
// Created by ise on 12/14/21.
//

//#ifndef C_PROJECT2_POKEMON_H
#define C_PROJECT2_POKEMON_H
#include <string.h>
#ifndef C_FIRST_POKEMON_H
#define C_FIRST_POKEMON_H
#include <stdio.h>
#include "Defs.h"
typedef struct type{
    int typeOfpokemon;
    char * name;
    int count_of_me;
    int count_of_other;
    struct type ** effective_against_me;
    struct type ** effective_against_other;

}type_pokemon;
typedef struct pokemon {
    char  * pokemon_name;
    char  * species;
    struct type* ptype;
    struct bio_info* pbio ;

}pokemon;
typedef struct bio_info{
    float hight;
    float weight;
    int attack;


}bio_pokemon;



type_pokemon * create_type(char* name_type );
/*creating the Pokemon type
 * getting pointer of char
 * initialize all the arguments to be null/zero, depends on the type
 * and allocate space for the name of the type
 * it returns pointer to a type structure
*/


pokemon* create_pokemon(char  * pokemon_name,char  * species,float hight,float weight,int attack,type_pokemon * typePokemon);
/*creating the Pokemon
 * getting the bio arguments by value and the rest of the arguments by pointer
 * initialize all the arguments
 * allocate space for the struct
 * creating pointers fot struct bio_info and type
 * it returns pointer to a pokemon structure
*/

status Add_to_effective_against_other(type_pokemon* typeP_this,type_pokemon* typeP_other);
/*
 * gets 2 pointer, one for origin type and one for adding
 * chancing the original array of this type
 * increase count_other++
 */

status Add_to_effective_against_me(type_pokemon* typeP_this,type_pokemon* typeP_other);
/*
* gets 2 pointer, one for origin type and one for adding
* chancing the original array of this type
* increase count_me++
*/

status Print_Pokemon(pokemon* pokemon_pointer);
/*
 * gets pokemon pointer and prints his all aguments
 */

status Print_Type_pokemon(type_pokemon* typePokemon);
/*
 * gets type pokemon pointer and prints all the information about him
 */

//======functions for battle========

//gets 2 pointers to pokmons and returns which pokemon is bigger by there attack
int compare_pokemons(pokemon* pokemon1,pokemon* pokemon2);
//copig the pokemon and returns the same pointer - shallow copy
pokemon * copy_pokemon(pokemon*  pointer_pokemon);
//gets pokemon pointer and frees all the memory that allocated for him
void destroy_pokemon(pokemon* pokemon_pointer);
//attackfunction
int getAttackPokemon(pokemon *pokemon1 ,pokemon *pokemon2 ,int* attackFirst,int* attackSecond);
//get category function
char * GetPokemonTypeString (pokemon* pokemon_pointer);
//destroy pokemon in battel, getting pokemon from the user and clear his memory
void delete_user_pokemon(pokemon* pokemon_user);

#endif //C_FIRST_POKEMON_H
