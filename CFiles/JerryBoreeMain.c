//
// Created by noam on 12/24/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
#include "MultiValueHashTable.h"
#include "Defs.h"
#include "Jerry.h"

// General funcs for diffrent uses.

// Print the string for all the Multi/regular hashes key.
status print_key_string(Element element){
    if (element == NULL)
        return failure;
    char* elem_name = (char *) element;
    printf("%s : \n", elem_name);
    return success;
}
// Shallow copy of the id as a key of the hash.
Element copy_shallow_key(Element element){
    if (element == NULL)
        return NULL;
    return element;
}

// Func for free just the pointer.
status free_pointer(Element element){
    if (element == NULL)
        return failure;
    return success;
}

// Equal func for twp strings.
bool equal_strings(Element element1, Element element2){
    if (element1 == NULL || element2 == NULL)
        return false;
    char* s1 = (char*) element1;
    char* s2 = (char *) element2;
    if (strcmp(s1, s2) == 0)
        return true;
    return false;
}


// Funcs for Jerrie's linked list (deep alocate)
// Equal for jerry list
bool equal_for_list(Element e1, Element e2){
    if (e1 == NULL || e2 == NULL)
        return false;
    Jerry * j = (Jerry*) e1;
    char* s = (char*) e2;
    if (strcmp(j->id, s) == 0)
        return true;
    return false;

}

// Destroy jerry
status free_jerry_for_list(Element element){
    if (element == NULL)
        return failure;
    Jerry* jerry = (Jerry*) element;
    destroy_jerry(jerry);
    jerry == NULL;
    return success;
}
// Create deep copy of jerry.
Element copy_jerry_for_list(Element element){
    if (element == NULL)
        return NULL;
    Jerry* jerry = (Jerry*) element;
    Jerry* new_jerry = Createjerry(jerry->id, jerry->happiness, jerry->origin->origin_planet, jerry->origin->dimention);
   //Need to destroy the jerry element we got in the main func
   // Add to the new jerry the charactertstic of the older one.
   if (new_jerry == NULL)
       return NULL;
   for(int i = 0; i< jerry->size_phyisical_c; i++){
       if (add_phyisical(new_jerry, jerry->physical_c[i]->charactar_name, jerry->physical_c[i]->value) == failure) {
           destroy_jerry(new_jerry);
           return NULL;
       }
   }
    return new_jerry;
}
// print func of jerry for the list
status print_jerry_for_list(Element element){
    if (element == NULL)
        return failure;
    Jerry * jerry = (Jerry*) element;
    print_jerry(jerry);
    return success;
}

// Funcs for MultiHash table (the key is the character and the val is list of jerry)

// Func for find the nearest prime bigger number then (n) for the hash size number.
int find_prime_number(int n){
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    int flag = 1;
    int check = 0;
    // check the first input.
    for(int i = 2; i < n; i++){
        if (n % i  == 0)
            check ++;
    }
    if (check == 0)
        return n;
    // check the nearest bigger num.
    int m = n;
    while( flag != 0){
        m = m+1;
        check = 0;
        for(int i = 2; i < m; i++){
            if (m % i  == 0)
                check ++;
        }
        if(check == 0)
            return m;
    }
}

// Deep copy of the key!
Element copy_key_character(Element element){
    if (element == NULL)
        return NULL;
    char* elem_name = (char *) element;
    // Alocate the name of the character
    char* new_name = (char*) malloc(strlen(elem_name) +1);
    if (new_name == NULL)
        return NULL;
    strcpy(new_name, elem_name);
    return new_name;
}
// Free the allocation i have made.
status free_char(Element element){
    if (element == NULL)
        return failure;
    char* elem_name = (char *) element;
    free(elem_name);
    return success;
}


// print the value -> print jerry.
status print_val_character(Element element) {
    if (element == NULL)
        return failure;
    Jerry * jerry = (Jerry*) element;
    print_jerry(jerry);
    return success;
}


// Equal between jerrie's
bool equal_val_character(Element element1, Element element2){
    if (element1 == NULL || element2 == NULL)
        return false;
    Jerry * jer1 = (Jerry*) element1;
    Jerry * jer2 = (Jerry*) element2;
    if (strcmp(jer1->id, jer2->id) == 0)
        return true;
    return false;
}
//bool equal_val_character_partial(Element element1, Element element){
//}

// transform to sum of the ascii number of the chars.
int transform_number(Element element){
    if (element == NULL)
        return 0;
    char * str = (char *) element;
    int ascii = 0;
    for(int i =0; i < strlen(str); i++){
        ascii += str[i];
    }
    return ascii;
}

//Free func for planet
status free_for_planet(Element element){
    if (element == NULL)
        return failure;
    Planet* planet = (Planet*) element;
    destroy_planet(planet);
    return success;
}
// Deep copy between planets.
Element deep_copy_planet(Element element){
    if (element == NULL)
        return NULL;
    Planet* elem_planet = (Planet*) element;
    Planet* new_planet = CreatePlanet(elem_planet->name, elem_planet->x, elem_planet->y, elem_planet->z);
    if (new_planet == NULL)
        return NULL;
    return new_planet;
}

status print_for_list_planet(Element element){
    if (element == NULL)
        return success;
    Planet* planet = (Planet*) element;
    print_planet(planet);
    return success;
}

// equal the planet name and string name.
bool equal_for_planet(Element element, Element element1){
    if (element == NULL || element1 == NULL)
        return false;
    Planet* planet = (Planet*) element;
    char* str = (char*) element1;
    if (strcmp(planet->name, str) == 0)
        return true;
    return false;
}

// Helper functions for the main missions

//Helper func for create and append to multi hash  the character of each jerry
MultiHash Create_MultiHash(LinkedList jerry_list, int size1){
    if(jerry_list == NULL)
        return NULL;
    int size = find_prime_number(size1);
    MultiHash multi = createMultiValueHashTable(copy_key_character, free_char, print_key_string, copy_shallow_key,
                                                free_pointer,
                                                print_val_character, equal_strings, equal_val_character,
                                                transform_number, size);
    if (multi == NULL)
        return NULL;
    for (int i = 1; i < getLengthList(jerry_list)+1; i++){
        Jerry * jerry = getDataByIndex(jerry_list, i);
        if (jerry == NULL)
            return NULL;
        for (int j = 0; j < jerry->size_phyisical_c; j++){
            addToMultiValueHashTable(multi, jerry->physical_c[j]->charactar_name, jerry);
        }
    }
    return multi;
}
// Helper func for create and append to Jerry_hash the jerrie's object in jerry_list (Linked List).
hashTable Create_JerryHash(LinkedList jerry_list, int j_num){
    if (jerry_list == NULL)
        return NULL;
    int size = find_prime_number(j_num);  // find the prime bigger number than j_size for the best hash size.
    hashTable hash = createHashTable(copy_key_character, free_char, print_key_string, copy_shallow_key, free_pointer,
                                     print_jerry_for_list, equal_strings, transform_number, size);
    if (hash == NULL){
        return NULL;
    }
    for (int i = 1; i < getLengthList(jerry_list) + 1; i++){
        Jerry * jerry = getDataByIndex(jerry_list, i);
        if (jerry == NULL)
            return NULL;
        if (addToHashTable(hash, jerry->id, jerry) == failure){
            printf("Memory problem");
            // go home
            return NULL;
        }
    }
    return hash;
}



// Destroy all the program and close it.
status go_home(MultiHash multi, hashTable jerry_hash, LinkedList jerry_list, LinkedList planet_list) {
    destroyList(jerry_list);
    destroyList(planet_list);
    destroyHashTable(jerry_hash);
    destroyMultiValueHashTable(multi);
    return success;

}
// change negative to positive func.
float make_positive(float x){
    if (x < 0)
        x = x * (-1);
    return x;
}

// helper func for delete jerry from the program.

status remove_jerry_program(Jerry*j,  MultiHash multi, hashTable hash, LinkedList jerry_list){
    if (j == NULL)
        return failure;
    if (removeFromHashTable(hash, j->id) == success) {
        for (int i = 0; i < j->size_phyisical_c; i++)
            if (removeFromMultiValueHashTable(multi, j->physical_c[i]->charactar_name, j) == success)
                continue;

        if (deleteNode(jerry_list, j->id) == success) {
            return success;
        }
    }
    return failure;
}


//---------------------------------------------------------------

// Reading from the file.

int main (int argc, char* argv[]) {
    if (argv[1] == NULL || argv[2] == NULL)
        return 1;
    int j_size = 0;
    int p_size = 0;
    LinkedList arr_chars = createList(equal_strings, free_char, copy_key_character, print_key_string);
    if (arr_chars == NULL) {
        printf("Memory problem");
        // go home
        return 1;
    }
    int char_size = 0;
    p_size = atoi(argv[1]);  //number of Planets.
    int p_num = 0; // for following on the planets counting
    int j_num = 0; //  for following on the planets counting
    LinkedList jerry_list = createList(equal_for_list, free_jerry_for_list, copy_jerry_for_list, print_jerry_for_list);
    if (jerry_list == NULL) {
        printf("Memory Problem \n ");
        destroyList(arr_chars);
        return 1;
    }
    LinkedList planet_list = createList(equal_for_planet, free_for_planet, deep_copy_planet, print_for_list_planet);
    if (planet_list == NULL) {  // close the program
        destroyList(jerry_list);
        destroyList(arr_chars);
        printf("Memory Problem \n ");
        return 1;
    }
    int i = atoi(argv[1]);
    FILE *f = fopen(argv[2], "r");
    char buffer[300];
    if (f == NULL) {
        printf("Unable to open!"); // print error
        fclose(f); // close file
        destroyList(jerry_list);
        destroyList(planet_list);
        return 1;
    }
    int line = 0;
    while (!feof(f) && !ferror(f)) {
        if (fgets(buffer, 300, f) != NULL) {
            if (line == 1) {
                // this is the planet's list by lines
                for (int j = 0; j < p_size; j++) {
                    char *planet_name; // storing the planet name
                    float planet_params[4]; // storing the params of each planet.
                    // now the first line (planet)
                    char *piece = strtok(buffer, " , "); // piece = plant name
                    planet_name = piece;
                    int k = 1;
                    while (piece != NULL && k < 4) { // take x, y, z, in loop
                        piece = strtok(NULL, ",");
                        if (piece != NULL) {
                            planet_params[k] = atof(piece); // convert to float
                            k++;
                        }
                    }
                    p_num++;
                    Planet *new_planet = CreatePlanet(planet_name, planet_params[1], planet_params[2],
                                                      planet_params[3]);
                    if (new_planet == NULL) {
                        printf("Memory Problem \n ");
                        destroyList(jerry_list);
                        destroyList(arr_chars);
                        destroyList(planet_list);
                        printf("Memory Problem \n ");
                        return 1;
                    }
                    if (appendNode(planet_list, new_planet) == failure) {
                        destroy_planet(new_planet);
                        destroyList(jerry_list);
                        destroyList(arr_chars);
                        destroyList(planet_list);
                        printf("Memory Problem \n ");
                        return 1;
                    }
                    destroy_planet(new_planet); // Free the allocation we made in main function.
                    fgets(buffer, 300, f); // taking a new planet.
                    line++;
                }
            }
            if (line == atoi(argv[1]) + 2) {  // Checking if this is the jerries lines in the file.
                int flag = 1; // When the flag == 0 we finished to read the file.
                while (flag != 0) {
                    char *id = strtok(buffer, ",");
                    char *dim = strtok(NULL, ",");
                    char *planet_name = strtok(NULL, ",");
                    char *hap_level = strtok(NULL, "\n ");
                    int hap_level_val = atoi(hap_level);
                    Planet *planet = searchByKeyInList(planet_list, planet_name); // check and return planet pointer.
                    if (planet == NULL) {
                        destroyList(jerry_list);
                        destroyList(arr_chars);
                        destroyList(planet_list);
                        printf("Memory Problem \n ");
                        return 1;
                    }
                    Jerry *j1 = Createjerry(id, hap_level_val, planet, dim); // new jerry
                    if (j1 == NULL) {
                        destroyList(jerry_list);
                        destroyList(arr_chars);
                        destroyList(planet_list);
                        printf("Memory Problem \n");
                        return 1;
                    }

                    j_num++;
                    if(fgets(buffer, 300, f) == NULL) {
                        appendNode(jerry_list, j1);
                        destroy_jerry(j1);
                        break;
                    }
                    line++;
                    while (buffer[0] == 9) { // checking if character
                        char new_baf[300];
                        char *p = buffer + 1;
                        strcpy(new_baf, p); //  first character
                        char *name_charactar = strtok(new_baf, ":"); // name of character
                        char *val = strtok(NULL, "\n");
                        float v = atof(val); // float val
                        char *name = searchByKeyInList(arr_chars, name_charactar);
                        if (name == NULL)
                            appendNode(arr_chars, name_charactar);
                        if (add_phyisical(j1, name_charactar, v) == failure) {// add phisical_character to new jerry
                            destroy_jerry(j1);
                            destroyList(jerry_list);
                            destroyList(arr_chars);
                            destroyList(planet_list);
                            printf("Memory Problem \n");
                            return 1;
                        }
                        if (fgets(buffer, 300, f) == NULL) { // new line
                            flag = 0;
                            break;
                        }
                        line++;
                    }
                    if (appendNode(jerry_list, j1) == failure) { // add to jerries list.
                        destroy_jerry(j1);
                        destroyList(jerry_list);
                        destroyList(arr_chars);
                        destroyList(planet_list);
                        printf("Memory Problem \n");
                        return 1;
                    }
                    destroy_jerry(j1); // Free the allocation we made in main function.
                    line++;
                }

            }
        }
        line++; // to the next line
    }
    fclose(f);
    // Create all ADT-----------------------------
    int multi_size = getLengthList(arr_chars);
    MultiHash multi = Create_MultiHash(jerry_list, multi_size);
    if (multi == NULL) {
        destroyList(jerry_list);
        destroyList(arr_chars);
        destroyList(planet_list);
        printf("Memory Problem \n");
        return 1;
    }
    // j_num is the Hash size
    hashTable jerry_hash = Create_JerryHash(jerry_list, j_num);
    if (jerry_hash == NULL) {
        destroyList(jerry_list);
        destroyList(arr_chars);
        destroyList(planet_list);
        destroyMultiValueHashTable(multi);
        printf("Memory Problem \n");
        return 1;
    }
    // After using it for the Multi Hash size, need to destroy it.
    destroyList(arr_chars);

    // Start menu!
    int flag = 0;
    char buf[300];
    char c_flag[300];
    while (flag != 9) {
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");
        scanf("%s", c_flag);
        flag = atoi(c_flag);
        if (flag <= 0 || flag > 9) { //check if number or char
            printf("Rick this option is not known to the daycare ! \n");
            continue;
        }
        switch (flag) {    // Do the mission by the flag number.
            case 1 : // Adding jerry to the program.
                printf("What is your Jerry's ID ? \n");
                char id[300];
                scanf("%s", id);
                if (lookupInHashTable(jerry_hash, id) != NULL) {
                    printf("Rick did you forgot ? you already left him here ! \n");
                    break;
                }
                printf("What planet is your Jerry from ? \n");
                char planet_name[300];
                scanf("%s", planet_name);
                Planet *planet = searchByKeyInList(planet_list, planet_name);
                if (planet == NULL) {
                    printf("%s is not a known planet ! \n", planet_name);
                    break;
                }
                printf("What is your Jerry's dimension ? \n");
                char dim_name[300];
                scanf("%s", dim_name);
                printf("How happy is your Jerry now ? \n");
                char happy_val[300];
                scanf("%s", happy_val);
                Jerry *new_jerry = Createjerry(id, atoi(happy_val), planet, dim_name);
                if (new_jerry == NULL) {
                    printf("Memory Problem \n");
                    go_home(multi, jerry_hash, jerry_list, planet_list);
                    break;
                }
                if (appendNode(jerry_list, new_jerry) == success) {
                    Jerry *jerry = searchByKeyInList(jerry_list, new_jerry->id);
                    for (int j = 0; j < new_jerry->size_phyisical_c; j++) {
                        addToMultiValueHashTable(multi, jerry->physical_c[j]->charactar_name, jerry);
                    }
                    if (addToHashTable(jerry_hash, jerry->id, jerry) == success) {
                        print_jerry_for_list(lookupInHashTable(jerry_hash, id));
                        destroy_jerry(new_jerry);
                        break;
                    }
                }
                // mission failed.
                destroy_jerry(new_jerry);
                printf("Memory Problem");
                go_home(multi, jerry_hash, jerry_list, planet_list);
                return 1;

            case 2 : // physical character to the requested jerry.
                printf("What is your Jerry's ID ? \n");
                scanf("%s", id);
                Jerry *j = lookupInHashTable(jerry_hash, id);
                if (j == NULL) {
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }
                printf("What physical characteristic can you add to Jerry - %s ? \n", id);
                scanf("%s", id);
                if (phyisical_exists(j, id) == true) {
                    printf("The information about his %s already available to the daycare ! \n", id);
                    break;
                }
                printf("What is the value of his %s ? \n", id);
                scanf("%s", buf);
                if (add_phyisical(j, id, atof(buf)) == success)
                    if (addToMultiValueHashTable(multi, id, j) == success) {
                        displayMultiValueHashElementsByKey(multi, id);
                        break;
                    }
                // mission failed.
                printf("Memory Problem");
                go_home(multi, jerry_hash, jerry_list, planet_list);
                return 1;


            case 3 : // Delete a physical character from a certain jerry and from the program.
                printf("What is your Jerry's ID ? \n");
                scanf("%s", id);
                Jerry *jerry = lookupInHashTable(jerry_hash, id);
                if (jerry == NULL) {
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }
                printf("What physical characteristic do you want to remove from Jerry - %s ? \n", id);
                char char_name[300];
                scanf("%s", char_name);
                if (phyisical_exists(jerry, char_name) == false) {
                    printf("The information about his %s not available to the daycare ! \n", char_name);
                    break;
                }
                if (removeFromMultiValueHashTable(multi, char_name, jerry) == success) {
                    if (delete_phyisical(jerry, char_name) == success) {
                        print_jerry(jerry);
                        break;
                    }
                }
                // mission failed.
                printf("Memory Problem");
                go_home(multi, jerry_hash, jerry_list, planet_list);
                return 1;


            case 4 : // Deleting specific jerry from the program.
                printf("What is your Jerry's ID ? \n");
                scanf("%s", id);
                Jerry *jer = lookupInHashTable(jerry_hash, id);
                if (jer == NULL) {
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }
                if (removeFromHashTable(jerry_hash, jer->id) == success) {
                    for (int i = 0; i < jer->size_phyisical_c; i++)
                        if (removeFromMultiValueHashTable(multi, jer->physical_c[i]->charactar_name, jer) == success)
                            continue;

                    if (deleteNode(jerry_list, jer->id) == success) {
                        printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                        break;
                    }
                }
                // mission failed.
                printf("Memory Problem");
                go_home(multi, jerry_hash, jerry_list, planet_list);
                return 1;



            case 5:  // Adopting the Gerry most similar to a certain Gerry by phyisical character, and deleting him from the program
                printf("What do you remember about your Jerry ? \n");
                scanf("%s", char_name);
                LinkedList list_j = lookupInMultiValueHashTable(multi, char_name);
                if (list_j == NULL) {
                    printf("Rick we can not help you - we do not know any Jerry's %s ! \n", char_name);
                    break;
                }
                float character_val;
                printf("What do you remember about the value of his %s ? \n", char_name);
                scanf("%f", &character_val);
                int idx = 0;
                float min = character_val;
                float sum = 0;
                for (int i = 1; i < getLengthList(list_j) + 1; i++) {
                    Jerry *temp = (Jerry *) getDataByIndex(list_j, i);
                    for (int j = 0; j < temp->size_phyisical_c; j++) {
                        if (strcmp(temp->physical_c[j]->charactar_name, char_name) == 0) {
                            sum = ((temp->physical_c[j]->value) - min);
                            sum = make_positive(sum);
                            if (sum < min) {
                                min = sum;
                                idx = i;
                            }
                        }
                    }
                }
                Jerry *similar_jerry = getDataByIndex(list_j, idx);
                printf("Rick this is the most suitable Jerry we found : \n");
                print_jerry(similar_jerry);
                if (remove_jerry_program(similar_jerry, multi, jerry_hash, jerry_list) == success) {
                    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                    break;
                }
                printf("Memory problem");
                go_home(multi, jerry_hash, jerry_list, planet_list);
                return 1;

                // Find the most sad jerry
            case 6:
                if (getLengthList(jerry_list) == 0) {
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                // Idx for checking who is the most sad jerry.
                int sad = 101;
                Jerry *sad_jerry;
                int idx_jerry = 0;
                for (int i = 1; i < getLengthList(jerry_list) + 1; i++) {
                    sad_jerry = getDataByIndex(jerry_list, i);
                    if (sad_jerry->happiness < sad) {
                        sad = sad_jerry->happiness;
                        idx = i;
                    }
                }
                sad_jerry = getDataByIndex(jerry_list, idx);
                printf("Rick this is the most suitable Jerry we found : \n");
                print_jerry(sad_jerry);
                if (remove_jerry_program(sad_jerry, multi, jerry_hash, jerry_list) == success) {
                    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                    break;
                }
                // mission failed.
                printf("Memory Problem");
                go_home(multi, jerry_hash, jerry_list, planet_list);
                return 1;

                // Printing various reports on Gerry divided into three topics.
            case 7:
                while (flag != 9) {
                    printf("What information do you want to know ? \n");
                    printf("1 : All Jerries \n");
                    printf("2 : All Jerries by physical characteristics \n");
                    printf("3 : All known planets \n");
                    scanf("%s", c_flag);
                    flag = atoi(c_flag);
                    if (flag <= 0 || flag > 3) { //check if number or char
                        printf("Rick this option is not known to the daycare ! \n");
                        break;
                    }
                    switch (flag) {    // Do the mission by the flag number
                        // Print all jerry in the program.
                        case 1:
                            if (getLengthList(jerry_list) == 0) {
                                printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                                break;
                            }
                            displayList(jerry_list);
                            break;

                            // print all jerries by a character.
                        case 2:
                            printf("What physical characteristics ? \n");
                            scanf("%s", char_name);
                            LinkedList list_jer = lookupInMultiValueHashTable(multi, char_name);
                            if (list_jer == NULL) {
                                printf("Rick we can not help you - we do not know any Jerry's %s ! \n", char_name);
                                break;

                            }
                            displayMultiValueHashElementsByKey(multi, char_name);
                            break;
                            // Print all planets in the program.
                        case 3:
                            displayList(planet_list);
                    }
                    break;
                }
                break;
            case 8:  // Add to jerry happiness by some conditions divided into three cases.
                if (getLengthList(jerry_list) == 0) {
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                while (flag != 9) {
                    printf("What activity do you want the Jerries to partake in ? \n");
                    printf("1 : Interact with fake Beth \n");
                    printf("2 : Play golf \n");
                    printf("3 : Adjust the picture settings on the TV \n");
                    scanf("%s", c_flag);
                    flag = atoi(c_flag);
                    if (flag <= 0 || flag > 3) { //check if number or char
                        printf("Rick this option is not known to the daycare ! \n");
                        break;
                    }
                    switch (flag) {    // Do the mission by the flag number
                        //
                        case 1:
                            if (getLengthList(jerry_list) == 0) {
                                printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                                break;
                            }
                            printf("The activity is now over ! \n");
                            for (int i = 1; i < getLengthList(jerry_list) + 1; i++) {
                                jerry = getDataByIndex(jerry_list, i);
                                if (jerry->happiness > 19) {
                                    jerry->happiness = jerry->happiness + 15;
                                    if (jerry->happiness > 100)
                                        jerry->happiness = 100;
                                }
                                if (jerry->happiness <= 19) {
                                    jerry->happiness = jerry->happiness - 5;
                                    if (jerry->happiness < 0)
                                        jerry->happiness = 0;
                                }
                            }
                            displayList(jerry_list);
                            break;

                        case 2:
                            if (getLengthList(jerry_list) == 0) {
                                printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                                break;
                            }
                            printf("The activity is now over ! \n");
                            for (int i = 1; i < getLengthList(jerry_list) + 1; i++) {
                                jerry = getDataByIndex(jerry_list, i);
                                if (jerry->happiness > 49) {
                                    jerry->happiness = jerry->happiness + 10;
                                    if (jerry->happiness > 100)
                                        jerry->happiness = 100;
                                }
                                if (jerry->happiness < 50) {
                                    jerry->happiness = jerry->happiness - 10;
                                    if (jerry->happiness < 0)
                                        jerry->happiness = 0;
                                }
                            }
                            displayList(jerry_list);
                            break;

                        case 3:
                            if (getLengthList(jerry_list) == 0) {
                                printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                                break;
                            }
                            printf("The activity is now over ! \n");
                            for (int i = 1; i < getLengthList(jerry_list) + 1; i++) {
                                jerry = getDataByIndex(jerry_list, i);
                                jerry->happiness = jerry->happiness + 20;
                                if (jerry->happiness > 100)
                                    jerry->happiness = 100;
                            }
                            displayList(jerry_list);
                            break;
                    }
                    break;
                }
                break;

            case 9: // Close the program by destroying our all allocations
                go_home(multi, jerry_hash, jerry_list, planet_list);
                printf("The daycare is now clean and close ! ");
                return 0;

        }
    }

    return 0;

}







