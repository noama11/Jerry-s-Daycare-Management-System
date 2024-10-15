//
// Created by noam on 12/20/22.
//
#include <stdio.h>
#include "KeyValuePair.h"

struct KeyValuePair_t{
    Element key;
    Element value;
    FreeFunction freeKey;
    FreeFunction freeValue;
    CopyFunction copyKey;
    CopyFunction copyValue;
    EqualFunction equalKey;
    PrintFunction printKey;
    PrintFunction printValue;
};

// Creating function of  a key value pair
KeyValuePair createKeyValuePair(Element key, Element value, CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                                CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey){
    if (copyKey == NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL || printValue == NULL || equalKey == NULL)
        return NULL;
    if (key == NULL)
        return NULL;
    if (value == NULL)
        return NULL;
    KeyValuePair keyValuePair = (KeyValuePair) malloc(sizeof(struct KeyValuePair_t));
    if (keyValuePair == NULL)
        return NULL;
    keyValuePair->freeValue = freeValue;
    keyValuePair->freeKey = freeKey;
    keyValuePair->copyValue = copyValue;
    keyValuePair->copyKey = copyKey;
    keyValuePair->equalKey = equalKey;
    keyValuePair->printValue = printValue;
    keyValuePair->printKey = printKey;
    keyValuePair->key = keyValuePair->copyKey(key);
    if (keyValuePair->key == NULL){
        free(keyValuePair);
        return NULL;
    }
    keyValuePair->value = keyValuePair->copyValue(value);
    if (keyValuePair->value == NULL){
        keyValuePair->freeKey(keyValuePair->key);
        free(keyValuePair);
        return NULL;
    }
    return keyValuePair;
}
// Delete the object.
status destroyKeyValuePair(KeyValuePair keyValuePair){
    if (keyValuePair == NULL)
        return failure;
    if (keyValuePair->key == NULL && keyValuePair->value == NULL)
        return failure;
    keyValuePair->freeKey(keyValuePair->key);
    keyValuePair->freeValue(keyValuePair->value);
    free(keyValuePair);
    keyValuePair = NULL;
    return success;
}

// Display function of  a key value pair - value
status displayValue(KeyValuePair keyValuePair){
    if (keyValuePair == NULL)
        return failure;
    if (keyValuePair->value != NULL){
        keyValuePair->printValue(keyValuePair->value);
    }
    return success;
}

// Display function of  a key value pair - key
status displayKey(KeyValuePair keyValuePair){
    if (keyValuePair == NULL)
        return failure;
    if (keyValuePair->key != NULL){
        keyValuePair->printKey(keyValuePair->key);
    }
    return success;
}

// Return function of a key value pair - value
Element getValue(KeyValuePair keyValuePair){
    if (keyValuePair == NULL)
        return NULL;
    return keyValuePair->value;
}

// Return function of a key value pair - key
Element getKey(KeyValuePair keyValuePair){
    if (keyValuePair == NULL)
        return NULL;
    return keyValuePair->key;
}

// Function return true if a key of some key value pair equal to another key, and return false if not equal.
bool isEqualKey(KeyValuePair keyValuePair, Element key){
    if (keyValuePair == NULL)
        return false;
    if (key == NULL)
        return false;
    return (keyValuePair->equalKey(keyValuePair->key, key));
}






