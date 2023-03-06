#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Defs.h"
#include "Pokemon.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include "stdlib.h"
#include "BattleByCategory.h"

//finding pokemon in the pointer list type
status finde_pokemon_type( char* name_from_the_user,type_pokemon**type_list,int numTypes){
    for (int i = 0; i < numTypes; ++i) {
        if (strcmp(type_list[i]->name,name_from_the_user)==0){
            return success;
        }

    }
    return failure;
}

//finding if name of type exist in the list
type_pokemon * finde_pointer_type(char * name,type_pokemon** type_list,int numTypes){
    for (int i = 0; i < numTypes; ++i) {
        if (strcmp(type_list[i]->name,name)==0){
            return type_list[i];
        }
    }
    return NULL;

}
//increce the num of pokemons of a specific type
void finde_type_and_inccreceNumPok(char * name,type_pokemon** type_list,int numTypes){
    for (int i = 0; i < numTypes; ++i) {
        if (strcmp(type_list[i]->name,name)==0){
             type_list[i]->typeOfpokemon++;
        }
    }


}

//geting line and creating pokemon
pokemon * pokemons_text(char  * pokemon_line,type_pokemon ** type_list,int numTypes){
    if (pokemon_line[strlen(pokemon_line)-1]=='\n'){
        *(pokemon_line+strlen(pokemon_line)-2) = '\0';
    }

    char * token10;
    const char char10[2]=",";
    char * helper10[300];


    int indexx =0;

    token10= strtok(pokemon_line,char10);

    while (token10!=NULL){
        helper10[indexx]=token10;
        token10= strtok(NULL,char10);
        indexx++;

    }


    int g_index=0;
    for (int i = 0; i < numTypes ; ++i) {
        if (strcmp(helper10[5],type_list[i]->name)==0){
            type_list[i]->typeOfpokemon++;
            g_index=i;

        }

    }
    //converting the helper10[2] to float

    float hight1 = atof(helper10[2]);
    //converting helper10[3] to float
    float weight = atof(helper10[3]);
    //converting helper10[4] to int
    int attack = atoi(helper10[4]);


    return create_pokemon(helper10[0],helper10[1],hight1,weight,attack,type_list[g_index]);


}

void type_effective_text(char* line,int numTypes,type_pokemon** type_list){

    *(line+strlen(line)-2)='\0';
    char * token4;
    char * helper2[300];
    int o1 =0;

    token4= strtok(line,"\t -:,");

    while (token4!=NULL){
        helper2[o1]=token4;
        token4= strtok(NULL,"\t -:,");
        o1++;

    }


    type_pokemon * name_to_add_too = finde_pointer_type(helper2[0],type_list,numTypes);


    if (strcmp(helper2[3],"me") == 0){
        int L =4;
        int j=0;
        while (L<o1){
            while (j<numTypes){
                if (strcmp(helper2[L],type_list[j]->name) == 0){
                    Add_to_effective_against_me(name_to_add_too,type_list[j]);

                }
                j++;
            }
            j=0;
            L++;
        }
    }

    if (strcmp(helper2[3],"other") == 0){
        int L1 =4;
        int j1=0;
        while (L1<o1){
            while (j1<numTypes){
                if (strcmp(helper2[L1],type_list[j1]->name) == 0){
                    Add_to_effective_against_other(name_to_add_too,type_list[j1]);
                }
                j1++;
            }
            j1=0;
            L1++;
        }
    }


}

type_pokemon ** type_list(char* line,int numTypes){

    *(line+strlen(line)-2)='\0';
    char * token;
    char * temp[300];
    int i=0;

    token= strtok(line,",");
    while (token!=NULL){
        temp[i]=token;
        token= strtok(NULL,",");
        i++;


    }

    type_pokemon ** type_list = (type_pokemon**) malloc(numTypes*sizeof(type_pokemon*));
    if (type_list==NULL){
        return NULL;
    }
    for (int j = 0; j < numTypes; ++j) {
        type_list[j]= create_type(temp[j]);

    }

    return type_list;

}

void destroy_program(type_pokemon** type_List,Battle battle,int numTypes){
    for (int j = 0; j < numTypes; ++j) {
        free(type_List[j]->effective_against_other);
        type_List[j]->effective_against_other = NULL;
        free(type_List[j]->effective_against_me);
        type_List[j]->effective_against_me = NULL;

    }

    for (int j = 0; j < numTypes; ++j) {
        free(type_List[j]->name);
        type_List[j]->name=NULL;
        free(type_List[j]);
        type_List[j] = NULL;

    }
    free(type_List);
    destroyBattleByCategory(battle);

}


int main(int argc, char *argv[]) {

    int numTypes = atoi(argv[1]);
    int capacityType = atoi(argv[2]);
    char const* const fileName = argv[3];
    //=========initialize 2 variable=======

    type_pokemon ** type_List=NULL;
    Battle  battle = NULL;



    //=======reading the file==========
    FILE* file = fopen(fileName, "r");



    char line[300];
    int counter=0;
    int flag=0;

    char typeLine[300];




    while (fgets(line, sizeof(line), file)) {

        if (counter==1){
            strcpy(typeLine,line);

            type_List=type_list(line, numTypes);
            if (type_List==NULL){
                destroy_program(type_List,battle,numTypes);
                printf("No memory available\n");
            }

            battle= createBattleByCategory(capacityType, numTypes, typeLine, (equalFunction) compare_pokemons,
                                   (copyFunction) copy_pokemon, (freeFunction) destroy_pokemon,
                                   (getCategoryFunction) GetPokemonTypeString, (getAttackFunction) getAttackPokemon,
                                   (printFunction) Print_Pokemon);
            if (battle==NULL){
                destroy_program(type_List,battle,numTypes);
                printf("No memory available\n");

            }


        }
        else if(line[0]=='P'&&line[1]=='o'&&line[2]=='k'&&line[3]=='e'&&line[4]=='m'&&line[5]=='o'&&line[6]=='n'&&line[7]=='s'){
            flag=1;
            continue;
        }
        else if (counter>=2&&flag==0){
            type_effective_text(line,numTypes,type_List);


        }

        else if (flag==1){
            insertObject(battle,pokemons_text(line,type_List,numTypes));


        }


        counter++;

    }

    fclose(file);




    //building the main function

    char choice[300];
    int num = 0,numF;
    char term;
    //3
    char  name_of_type[300];
    char name_of_pokemon[300];
    char species[300];
    char height[300];
    char weight[300];
    char attack[300];

    //4
    char type_name4[300];
    //5
    char  name_of_type5[300];
    char name_of_pokemon5[300];
    char species5[300];
    char height5[300];
    char weight5[300];
    char attack5[300];



    while( num != 1 ) {
        printf("Please choose one of the following numbers:\n");
        printf("1 : Print all Pokemons by types\n");
        printf("2 : Print all Pokemons types\n");
        printf("3 : Insert Pokemon to battles training camp\n");
        printf("4 : Remove strongest Pokemon by type\n");
        printf("5 : Fight\n");
        printf("6 : Exit\n");


        scanf("%s",choice);
        numF = atoi(choice);


        switch (numF) {
            case 1:

                displayObjectsByCategories(battle);
                break;

            case 2:
                for (int j = 0; j < numTypes; ++j) {
                    Print_Type_pokemon(type_List[j]);

                }
                break;

            case 3:
                printf("Please enter Pokemon type name:\n");
                scanf("%s",name_of_type);
                if (finde_pokemon_type(name_of_type,type_List,numTypes) == failure){
                    printf("Type name doesn't exist.\n");
                    break;
                }
                if (getNumberOfObjectsInCategory(battle,name_of_type)==capacityType){
                    printf("Type at full capacity.\n");
                    break;

                }
                printf("Please enter Pokemon name:\n");
                scanf("%s",name_of_pokemon);

                printf("Please enter Pokemon species:\n");
                scanf("%s",species);

                printf("Please enter Pokemon height:\n");
                scanf("%s",height);

                printf("Please enter Pokemon weight:\n");
                scanf("%s",weight);

                printf("Please enter Pokemon attack:\n");
                scanf("%s",attack);
                finde_type_and_inccreceNumPok(name_of_type,type_List,numTypes);
                type_pokemon * Ptype = finde_pointer_type(name_of_type,type_List,numTypes);
                pokemon * Ppokemon=create_pokemon(name_of_pokemon,species, atof(height), atof(weight), atoi(attack),Ptype);
                if (Ppokemon==NULL){
                    destroy_program(type_List,battle,numTypes);
                    printf("No memory available\n");
                }
                if(insertObject(battle,Ppokemon)==success){
                    printf("The Pokemon was successfully added.\n");
                    Print_Pokemon(Ppokemon);
                }
                break;


            case 4:
                printf("Please enter type name:\n");
                scanf("%s",type_name4);
                if (finde_pokemon_type(type_name4,type_List,numTypes) == failure){
                    printf("Type name doesn't exist.\n");
                    break;
                }
                if(getNumberOfObjectsInCategory(battle,type_name4)==0){
                    printf("There is no Pokemon to remove.\n");
                    break;
                }
                printf("The strongest Pokemon was removed:\n");
                pokemon* delete_pokemon = removeMaxByCategory(battle,type_name4);
                Print_Pokemon(delete_pokemon);
                destroy_pokemon(delete_pokemon);


                break;

            case 5:
                printf("Please enter Pokemon type name:\n");
                scanf("%s",name_of_type5);
                if (finde_pokemon_type(name_of_type5,type_List,numTypes) == failure){
                    printf("Type name doesn't exist.\n");
                    break;
                }
                printf("Please enter Pokemon name:\n");
                scanf("%s",name_of_pokemon5);
                printf("Please enter Pokemon species:\n");
                scanf("%s",species5);
                printf("Please enter Pokemon height:\n");
                scanf("%s",height5);
                printf("Please enter Pokemon weight:\n");
                scanf("%s",weight5);
                printf("Please enter Pokemon attack:\n");
                scanf("%s",attack5);

                type_pokemon * Ptype5 = finde_pointer_type(name_of_type5,type_List,numTypes);
                pokemon * pokemon_user = create_pokemon(name_of_pokemon5,species5, atof(height5), atof(weight5), atoi(attack5),Ptype5);
                if(pokemon_user==NULL){
                    destroy_program(type_List,battle,numTypes);
                    printf("No memory available\n");
                }

                printf("You choose to fight with:\n");
                Print_Pokemon(pokemon_user);
                pokemon * pokemon_from_fight= fight(battle,pokemon_user);
                if(pokemon_from_fight==NULL){
                    printf("There are no Pokemons to fight against you.\n");
                    delete_user_pokemon(pokemon_user);
                    break;
                }

                delete_user_pokemon(pokemon_user);

                break;

            case 6:

                destroy_program(type_List,battle,numTypes);


                printf("All the memory cleaned and the program is safely closed.\n");
                return 0;


            default:
                printf("Please choose a valid number.\n");
                break;
        }

    }




}
