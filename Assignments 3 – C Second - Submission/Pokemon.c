//
// Created by ise on 12/14/21.
//

#include "Pokemon.h"
#include <stdio.h>
#include "Pokemon.h"
#include "Defs.h"
#include "stdlib.h"
#include <string.h>



/*creating the Pokemon type
 * getting pointer of char
 * initialize all the arguments to be null/zero, depends on the type
 * and allocate space for the name of the type
 * it returns pointer to a type structure
*/

type_pokemon *create_type(char *name_type) {
    if (name_type == NULL) { return NULL; }
    type_pokemon *pType =(type_pokemon *)malloc(sizeof(type_pokemon));
    if(pType==NULL){
        return NULL;
    }
    pType->name = (char *) malloc((strlen(name_type)*sizeof(char))+1);
    if (pType->name==NULL){
        return NULL;
    }
    strcpy(pType->name, name_type);
    pType->count_of_me = 0;
    pType->count_of_other = 0;
    pType->typeOfpokemon = 0;
    pType->effective_against_me = NULL;
    pType->effective_against_other = NULL;
    return pType;

}




/*creating the bio_info of the Pokemon
 * getting the arguments by value
 * initialize all the arguments
 * allocate space for the struct
 * it returns pointer to a bio_info structure
*/

bio_pokemon *create_bio(float hight, float weight, int attack) {

    bio_pokemon *bioPtr = (bio_pokemon *) malloc(sizeof(bio_pokemon));
    if (bioPtr==NULL){
        return NULL;
    }
    bioPtr->hight = hight;
    bioPtr->weight = weight;
    bioPtr->attack = attack;

    return bioPtr;

}

/*creating the Pokemon
 * getting the bio arguments by value and the rest of the arguments by pointer
 * initialize all the arguments
 * allocate space for the struct
 * creating pointers fot struct bio_info and type
 * it returns pointer to a pokemon structure
*/

pokemon *
create_pokemon(char *pokemon_name, char *species, float hight, float weight, int attack, type_pokemon *typePokemon) {
    if (pokemon_name == NULL || species == NULL || typePokemon == NULL) {
        return NULL;
    }

    pokemon *pokPtr = (pokemon *) malloc(sizeof(pokemon) );
    if (pokPtr==NULL){
        return NULL;
    }
    pokPtr->pokemon_name = (char *) malloc((strlen(pokemon_name) * sizeof(char)) + 1);
    if (pokPtr->pokemon_name==NULL){
        return NULL;
    }
    strcpy(pokPtr->pokemon_name, pokemon_name);

    pokPtr->species = (char *) malloc((strlen(species) * sizeof(char)) + 1);
    if (pokPtr->species==NULL){
        return NULL;
    }
    strcpy(pokPtr->species, species);
    pokPtr->pbio = create_bio(hight, weight, attack);
    pokPtr->ptype = typePokemon;
    return pokPtr;

}

/*
 * gets 2 pointer, one for origin type and one for adding
 * chancing the original array of this type
 * increase count_me++
 */

status Add_to_effective_against_me(type_pokemon *typeP_this, type_pokemon *typeP_other) {
    if (typeP_this != NULL && typeP_other != NULL) {
        if (typeP_this->effective_against_me == NULL) {
            typeP_this->effective_against_me = (type_pokemon **) malloc(sizeof(type_pokemon*));
            if (typeP_this->effective_against_me==NULL){
                return failure;
            }
            typeP_this->effective_against_me[0] = typeP_other;
            typeP_this->count_of_me++;
            return success;
        } else {
            typeP_this->effective_against_me = (type_pokemon **) realloc(typeP_this->effective_against_me,
                                                                         sizeof(type_pokemon *) *
                                                                         (typeP_this->count_of_me + 1));
            if (typeP_this->effective_against_me==NULL){
                return failure;

            }
            typeP_this->effective_against_me[typeP_this->count_of_me] = typeP_other;
            typeP_this->count_of_me++;
            return success;
        }


    }

    return failure;


}

/*
 * gets 2 pointer, one for origin type and one for adding
 * chancing the original array of this type
 * increase count_other++
 */

status Add_to_effective_against_other(type_pokemon *typeP_this, type_pokemon *typeP_other) {
    if (typeP_this != NULL && typeP_other != NULL) {

        if (typeP_this->effective_against_other == NULL) {
            typeP_this->effective_against_other = (type_pokemon **) malloc(sizeof(type_pokemon*));
            if (typeP_this->effective_against_other==NULL){
                return failure;

            }
            typeP_this->effective_against_other[0] = typeP_other;
            typeP_this->count_of_other++;
            return success;
        } else {
            typeP_this->effective_against_other = (type_pokemon **) realloc(typeP_this->effective_against_other,
                                                                            sizeof(type_pokemon *) *
                                                                            (typeP_this->count_of_other + 1));
            if (typeP_this->effective_against_other==NULL){
                return failure;

            }
            typeP_this->effective_against_other[typeP_this->count_of_other] = typeP_other;
            typeP_this->count_of_other++;
            return success;
        }

    }
    return failure;
}





/*
 * gets pokemon pointer and prints his all arguments
 */

status Print_Pokemon(pokemon *pokemon_pointer) {
    if (pokemon_pointer != NULL) {
        printf("%s :\n", pokemon_pointer->pokemon_name);
        printf("%s, %s Type.\n", pokemon_pointer->species, pokemon_pointer->ptype->name);
        printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n", pokemon_pointer->pbio->hight,
               pokemon_pointer->pbio->weight, pokemon_pointer->pbio->attack);
        return success;
    }
    return failure;

}


status Print_Type_pokemon(type_pokemon *typePokemon) {
    if (typePokemon != NULL) {
        printf("Type %s -- %d pokemons\n", typePokemon->name, typePokemon->typeOfpokemon);
        if (typePokemon->count_of_me != 0) {
            printf("\tThese types are super-effective against %s:", typePokemon->name);
            if (typePokemon->count_of_me == 1) {
                printf("%s\n", typePokemon->effective_against_me[0]->name);
            } else if (typePokemon->count_of_me > 1) {
                printf("%s", typePokemon->effective_against_me[0]->name);
                for (int i = 1; i < typePokemon->count_of_me; ++i) {
                    if (i == typePokemon->count_of_me - 1) {
                        printf(" ,%s\n", typePokemon->effective_against_me[i]->name);
                        break;
                    }
                    printf(" ,%s", typePokemon->effective_against_me[i]->name);
                }
            }

        }

        if (typePokemon->count_of_other != 0) {
            printf("\t%s moves are super-effective against:", typePokemon->name);
            if (typePokemon->count_of_other == 1) {
                printf("%s\n", typePokemon->effective_against_other[0]->name);
            } else if (typePokemon->count_of_other > 1) {
                printf("%s", typePokemon->effective_against_other[0]->name);
                for (int i = 1; i < typePokemon->count_of_other; ++i) {
                    if (i == typePokemon->count_of_other - 1) {
                        printf(" ,%s\n", typePokemon->effective_against_other[i]->name);
                        break;
                    }
                    printf(" ,%s", typePokemon->effective_against_other[i]->name);
                }
            }
        }

        printf("\n");





        return success;


    }
    return failure;

}

char * GetPokemonTypeString (pokemon* pokemon_pointer){
    return pokemon_pointer->ptype->name;
}


int compare_pokemons(pokemon* pokemon1,pokemon* pokemon2){
    if (pokemon1==NULL||pokemon2==NULL){
        return -600;
    }

    if (pokemon1->pbio->attack> pokemon2->pbio->attack){
        return 1;
    }
    else if (pokemon1->pbio->attack < pokemon2->pbio->attack){
        return -1;
    } else{return 0;}
}

pokemon * copy_pokemon(pokemon*  pointer_pokemon){
    return pointer_pokemon;
}

void destroy_pokemon(pokemon* pokemon_pointer){
    if (pokemon_pointer==NULL){
        return;
    }
    if(pokemon_pointer->pbio!=NULL){
        free(pokemon_pointer->pbio);
        pokemon_pointer->pbio=NULL;
    }
    if (pokemon_pointer->species!=NULL){
        free(pokemon_pointer->species);
        pokemon_pointer->species=NULL;
    }
    if (pokemon_pointer->pokemon_name!=NULL){
        free(pokemon_pointer->pokemon_name);
        pokemon_pointer->pokemon_name=NULL;
    }
    pokemon_pointer->ptype->typeOfpokemon--;
    pokemon_pointer->ptype=NULL;

    free(pokemon_pointer);


}

bool is_type1_in_effective_other_type2 (pokemon* pokemon1,pokemon* pokemon2){
    for (int i = 0; i < pokemon2->ptype->count_of_other; ++i) {
        if(strcmp(pokemon1->ptype->name,pokemon2->ptype->effective_against_other[i]->name)==0){
            return true;
        }

    }
    return false;
}

bool is_type2_in_effective_me_type1(pokemon* pokemon1,pokemon* pokemon2){
    for (int i = 0; i < pokemon1->ptype->count_of_me; ++i) {
        if(strcmp(pokemon2->ptype->name,pokemon1->ptype->effective_against_me[i]->name)==0){
            return true;
        }

    }
    return false;
}


int getAttackPokemon(pokemon *pokemon1 ,pokemon *pokemon2 ,int* attackFirst,int* attackSecond){


    *attackFirst= pokemon1->pbio->attack;
    *attackSecond= pokemon2->pbio->attack;

    int final_point1=pokemon1->pbio->attack-10;
    if(is_type1_in_effective_other_type2(pokemon1,pokemon2)==true|| is_type2_in_effective_me_type1(pokemon1,pokemon2)==true){
        *attackFirst= final_point1;

    }
    int final_point2=pokemon2->pbio->attack-10;
    if(is_type1_in_effective_other_type2(pokemon2,pokemon1)==true|| is_type2_in_effective_me_type1(pokemon2,pokemon1)==true){
        *attackSecond= final_point2;

    }


    int diff;
    diff= (*attackSecond)-(*attackFirst);
    return diff;

}

void delete_user_pokemon(pokemon* pokemon_user){
    if (pokemon_user==NULL){
        return;
    }
    free(pokemon_user->pbio);
    pokemon_user->pbio=NULL;
    free(pokemon_user->species);
    pokemon_user->species=NULL;
    free(pokemon_user->pokemon_name);
    pokemon_user->pokemon_name=NULL;
    pokemon_user->ptype=NULL;
    free(pokemon_user);

}




