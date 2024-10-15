//
// Created by noam on 12/24/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Jerry.h"

Jerry* Createjerry(char* id, int happy, Planet* p, char* d_name){
    // check if all the parameter is good and we can create jerry.
    // if not, free al what we allocate and return null.
    if (id == NULL){
        return NULL;
    }
    if (p == NULL)
        return NULL;
    if (d_name == NULL)
        return NULL;
    Jerry* j = (Jerry*) malloc(sizeof(Jerry));
    if(j == NULL)
        return NULL;
    j->id = (char*) malloc(strlen(id) +1);
    if(j->id == NULL) {
        free(j);
        return NULL;
    }
    strcpy(j->id,id);
    j->happiness = happy;
    j->origin = CreateOrigin(p, d_name);
    if (j->origin == NULL) {
        free(j->id);
        free(j);
        return NULL;
    }

    j->physical_c = NULL;
    j ->size_phyisical_c = 0;

    return j;
}


Planet* CreatePlanet(char* name, float x, float y, float z){
    if(name == NULL){
        return NULL;
    }
    Planet* p = (Planet*) malloc(sizeof(Planet));
    if(p == NULL)
        return NULL;
    p->name = (char*) malloc (strlen(name)+1);
    if (p->name == NULL) {
        free(p);
        return NULL;
    }
    strcpy(p->name, name);
    p -> x = x;
    p -> y = y;
    p -> z = z;
    return p;
}


Phyisical_c* CreatePhyisical(char* name, float val) {
    if (name == NULL) {
        return NULL;
    }
    Phyisical_c *ph = (Phyisical_c *) malloc(sizeof(Phyisical_c));
    if (ph == NULL)
        return NULL;
    ph->charactar_name = (char *) malloc(strlen(name)+1);
    if (ph->charactar_name == NULL) {
        free(ph);
        return NULL;
    }
    strcpy(ph ->charactar_name, name);
    ph->value = val;
    return ph;
}


Origin* CreateOrigin(Planet* p, char* d_name){
    if (d_name == NULL){
        return NULL;
    }
    if (p == NULL)
        return NULL;
    Origin* o = (Origin*) malloc(sizeof(Origin));
    if(o == NULL)
        return NULL;
    o->dimention = (char*) malloc(strlen(d_name)+1);
    if(o->dimention == NULL) {
        free(o);
        return NULL;
    }
    strcpy(o ->dimention, d_name);
    o -> origin_planet = p;
    return o;
}


bool phyisical_exists(Jerry* j, char* charactar){
    if (charactar == NULL)
        return false;
    if (j == NULL)
        return false;
    for(int i = 0; i< j->size_phyisical_c; i++){
        if(strcmp(j->physical_c[i]->charactar_name, charactar) == 0)
            return true;
    }
    return false;
}


status add_phyisical(Jerry* j, char* charactar_name, float k){
    if(charactar_name == NULL)
        return failure;
    if (j == NULL)
        return failure;
    if (j->size_phyisical_c == 0) {
        j->physical_c = (Phyisical_c **) malloc(sizeof(Phyisical_c *));
        if(j->physical_c == NULL)
            return failure;
        Phyisical_c * p = CreatePhyisical(charactar_name, k);
        if(p == NULL) {
            free(j->physical_c);
            j->physical_c = NULL;
            return failure;
        }
        j->physical_c[0] = p;
        j->size_phyisical_c ++;
        return success;
    }
    if (!phyisical_exists(j, charactar_name)){
        Phyisical_c* c = CreatePhyisical(charactar_name, k);  // create the phyisical character for jerry.
        if(c == NULL){  // if the alloccate failed go out.
            return failure;
        }
        j->size_phyisical_c ++;
        j->physical_c = (Phyisical_c**) realloc (j->physical_c , (j ->size_phyisical_c) * sizeof(Phyisical_c*));
        if(j->physical_c == NULL){  // if the realloc failed destroy the character and go out.
            destroy_Phyisical_c(c);
            return failure;
        }

        j ->physical_c[j->size_phyisical_c - 1] = c;
        return success;
    }
    return failure;
}

status delete_phyisical(Jerry* j, char* c_name){
    if (j == NULL)
        return failure;
    if(c_name == NULL)
        return failure;
    if (j->size_phyisical_c == 0)
        return failure;
    if (!phyisical_exists(j, c_name)){
        return failure;
    }
    if (j->size_phyisical_c == 1) {  // if just one character in the arrey
        destroy_Phyisical_c(j->physical_c[0]);
        free(j->physical_c);
        j->physical_c = NULL;
        j->size_phyisical_c --;
        return success;
    }
    for(int i=0; i< j->size_phyisical_c; i++){  // find the character
        if(strcmp(j->physical_c[i]->charactar_name, c_name) == 0){
            int num = i;
            Phyisical_c * ch = j->physical_c[i];  // keep the character to destroy later
            for(int k=num; k < j->size_phyisical_c -1; k++){ // delete the character by change pointers
                j->physical_c[k] = j->physical_c[k+1];
            }
            destroy_Phyisical_c(ch);
            break;
        }
    }
    j ->physical_c = (Phyisical_c**) realloc ( j->physical_c, (j->size_phyisical_c - 1) * sizeof(Phyisical_c*));
    if (j->physical_c == NULL)
        return failure;
    j->size_phyisical_c --;
    return success;
}
// print jerry and all the fields.
void print_jerry(Jerry* j){
    if(j== NULL)
        return;
    printf("Jerry , ID - %s : \n", j->id);
    printf("Happiness level : %d \n" , j->happiness);
    printf("Origin : %s \n", j->origin->dimention);
    printf("Planet : %s (%.2f,%.2f,%.2f) \n" ,j->origin->origin_planet->name, j->origin->origin_planet->x, j->origin->origin_planet->y, j->origin->origin_planet->z);
    if (j->size_phyisical_c != 0 ){
        printf("Jerry's physical Characteristics available : \n\t");
        int k= 0;
        for(int i=0; i<j->size_phyisical_c - 1; i++){
            printf("%s : %.2f , " , (j->physical_c)[i]->charactar_name, (j->physical_c)[i]->value);
            k ++;
        }
        printf("%s : %.2f \n", (j->physical_c)[k]->charactar_name, (j->physical_c)[k]->value);
    }
    return;
}
status print_planet(Planet* p){
    if (p == NULL)
        return failure;
    printf("Planet : %s (%.2f,%.2f,%.2f) \n" , p->name, p->x, p->y, p->z);
    return success;
}

void destroy_jerry(Jerry* j){ // destroy struct jerry and all the fields.
    if (j==NULL)
        return;
    free(j->id);
    j->id = NULL;
    j->happiness = 0;
    if (j->origin != NULL) {
        destroy_origin(j->origin);
        j->origin = NULL;
    }
    if (j->size_phyisical_c != 0){
        if(j->physical_c != NULL) {
            for (int i = 0; i < j->size_phyisical_c; i++) {
                destroy_Phyisical_c(j->physical_c[i]);
            }
        }
        free(j->physical_c);
        j->physical_c = NULL;
        j->size_phyisical_c = 0;
    }
    free(j);
    j = NULL;
}

void destroy_Phyisical_c(Phyisical_c* c){  // destroy struct Phyisical_c and all the fields.
    if (c== NULL)
        return;
    free(c->charactar_name);
    c->charactar_name = NULL;
    c->value = 0;
    free(c);
    c=NULL;
}

void destroy_origin(Origin* o){ // destroy struct Origin and all the fields.
    if(o == NULL)
        return;
    if (o->dimention == NULL) {
        free(o);
        return;
    }
    free(o->dimention);
    o->dimention = NULL;
    free(o);
    o = NULL;
}

void destroy_planet(Planet* p){ // destroy struct Planet and all the fields.
    if (p == NULL)
        return;
    if (p->name == NULL) {
        free(p);
        return;
    }
    free(p->name);
    p->name = NULL;
    p->x = 0;
    p->y = 0;
    p->z = 0;
    free(p);
    p = NULL;
}




