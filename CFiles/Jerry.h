//
// Created by noam on 12/24/22.
//

#ifndef C_3_JERRY_H
#define C_3_JERRY_H

#endif //C_3_JERRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"



typedef struct Planet_t{
    char* name;
    float x;
    float y;
    float z;
}Planet;

typedef struct Origin_t{
    Planet* origin_planet;
    char* dimention;

}Origin;

typedef struct Phyisical_t{
    char* charactar_name;
    float value;
}Phyisical_c;



typedef struct Jerry_t {
    char* id ;
    int happiness;
    Origin* origin;
    Phyisical_c **physical_c;
    int size_phyisical_c;
}Jerry;



// Creating function the Jerry object by all his field.
Jerry* Createjerry(char*, int, Planet*, char*);

// Creating function the Planet object by all his field.
Planet* CreatePlanet(char*, float, float, float);

// Creating function the phyisical character object by all it field.
Phyisical_c* CreatePhyisical(char*, float);

// Creating function the origin object of jerry  by all it field.
Origin* CreateOrigin(Planet*,char*);

// Function retun true/false if the character exist in some jerry.
bool phyisical_exists(Jerry*,char*);

// Add phyisical character to jerry and return status.
status add_phyisical(Jerry*,char*,float);

// Delete function of phyisical character from jerry and return status.
status delete_phyisical(Jerry*,char*);

// Print function of the jerry data.
void print_jerry(Jerry*);

// Print function of the planet data.
status print_planet(Planet*);

// Destroying function of the jerry object and all his fields.
void destroy_jerry(Jerry*);

// Destroying function of the phyisical character object and all his fields.
void destroy_Phyisical_c(Phyisical_c*);

// Destroying function of the origin object and it fields.
void destroy_origin(Origin*);

// Destroying function of the planet object and all it fields.
void destroy_planet(Planet*);

