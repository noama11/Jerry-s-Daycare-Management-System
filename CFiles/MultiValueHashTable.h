//
// Created by noam on 12/23/22.
//

#ifndef C_3_MULTIVALUEHASHTABLE_H
#define C_3_MULTIVALUEHASHTABLE_H

#endif //C_3_MULTIVALUEHASHTABLE_H

#include <stdio.h>
#include "LinkedList.h"

typedef struct MultiValueHashTable* MultiHash;

// Generic ADT of MultiValueHashTable which consists of a HashTable generic ADT, so the value in the object (key value pair)
// that the linked list in the hash holds in this implementation will be linked list


// Creating the generic ADT of MultiValueHashTable using generic functions of copy, destroy, print and equal that the user need to provide.
MultiHash createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue,
                                     PrintFunction printValue, EqualFunction equalKey, EqualFunction equalVal, TransformIntoNumberFunction transformIntoNumber, int hashNumber);

// Destroying the generic ADT of MultiValueHashTable
status destroyMultiValueHashTable(MultiHash multi);

// Add to MultiValueHashTable object of a key value pair.
status addToMultiValueHashTable(MultiHash multi, Element key, Element val);

// Searching a key of key value pair and return it value (linked list in this adt).
LinkedList lookupInMultiValueHashTable(MultiHash, Element key);

// Removing key of key value pair
status removeFromMultiValueHashTable(MultiHash multi, Element key, Element val);

// Display all elements that belongs the value os some key value pair, in this adt it could be several values.
status displayMultiValueHashElementsByKey(MultiHash multi, Element key);