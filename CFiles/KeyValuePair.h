//
// Created by noam on 12/20/22.
//

#ifndef C_3_KEYVALUEPAIR_H
#define C_3_KEYVALUEPAIR_H

#endif //C_3_KEYVALUEPAIR_H
#include "Defs.h"

typedef struct KeyValuePair_t* KeyValuePair;

// ADT of object of a generic key-value pair
//The object has a pair of values, one is unique to the pair - the key, and the other is a value stored for it
//key.

// Creating a key value pair object generic using functions of copy, destroy, print and equal that the user need to provide.
KeyValuePair createKeyValuePair(Element key, Element value, CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                                CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey);

// Destroying a key value pair
status destroyKeyValuePair(KeyValuePair keyValuePair);

// Print the key value pair value
status displayValue(KeyValuePair keyValuePair);

// Print the key value pair key
status displayKey(KeyValuePair keyValuePair);

// Return key value pair value
Element getValue(KeyValuePair keyValuePair);

// Return key value pair key
Element getKey(KeyValuePair keyValuePair);

// Check if a key of some key value pair equal to another key.
bool isEqualKey(KeyValuePair keyValuePair, Element key);
