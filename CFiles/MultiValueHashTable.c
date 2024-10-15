//
// Created by noam on 12/23/22.
//
#include <stdio.h>
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
#include "MultiValueHashTable.h"
#include "Defs.h"


struct MultiValueHashTable{
    hashTable hash;
    CopyFunction copy_key;
    CopyFunction copy_value;
    FreeFunction free_key;
    FreeFunction free_value;
    PrintFunction print_key;
    PrintFunction print_value;
    EqualFunction equal_key;
    EqualFunction equal_val;
};

// Helper function for this adt functionality

// In Multi Hash wu Know the value of the pair is linked list.
status free_values_list(Element element){
    if (element == NULL)
        return failure;
    LinkedList list_values = (LinkedList) element;
    return destroyList(list_values);
}

// Shallow copy function os the values (linked list)
Element copy_values_list(Element element){
    if (element == NULL)
        return NULL;
    return element;
}

// Print function os the values list.
status print_values_list(Element element){
    if (element == NULL)
        return failure;
    LinkedList list_values = (LinkedList) element;
    return (displayList(list_values));
}

// Creating function of MultiValueHashTable
MultiHash createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue,
                                    PrintFunction printValue, EqualFunction equalKey, EqualFunction equalVal, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
    if (copyKey == NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL || printValue == NULL || equalKey == NULL)
        return NULL;
    MultiHash multiHash = (MultiHash) malloc (sizeof(struct MultiValueHashTable));
    if (multiHash == NULL)
        return NULL;
    multiHash->hash = createHashTable(copyKey, freeKey, printKey, copy_values_list, free_values_list,
           print_values_list, equalKey, transformIntoNumber, hashNumber);
    if (multiHash->hash == NULL) {
        free(multiHash);
        return NULL;
    }
    multiHash->equal_key = equalKey;
    multiHash->equal_val = equalVal;
    multiHash->copy_value = copyValue;
    multiHash->copy_key = copyKey;
    multiHash->free_key = freeKey;
    multiHash->free_value = freeValue;
    multiHash->print_key = printKey;
    multiHash->print_value = printValue;
    return multiHash;
}
// The val of the pair is linked list of values with the sema key.
status addToMultiValueHashTable(MultiHash multi, Element key, Element val) {
    if (key == NULL || val == NULL || multi == NULL)
        return failure;
    LinkedList list_values = lookupInHashTable(multi->hash, key);
    // if null, create new list with the equal func of the value, add the new val, and add new pair with the list as a value to the hash.
    if (list_values == NULL) {
        list_values = createList(multi->equal_val, multi->free_value, multi->copy_value,
                                multi->print_value);
        if (list_values == NULL)
            return failure;
        if (appendNode(list_values, val) == failure) {
            destroyList(list_values);
            return failure;
        }
        if (addToHashTable(multi->hash, key, list_values) == failure){
            destroyList(list_values);
        }
        return success;
    }
    // If not null there is an exist linked list.
    // Check if exist pair with the same key and value.
    if (searchByKeyInList(list_values, val) != NULL)
        return failure;   // Exist key with the same value.
    // check if need to destroy the list, there is elements in.
    if (appendNode(list_values, val) == failure) {
        return failure;
    }
    return success;
}

// Return the list values (Linked List) by the key wo got.
LinkedList lookupInMultiValueHashTable(MultiHash multi, Element key){
    if (multi == NULL || key == NULL)
        return NULL;
    Element elem = lookupInHashTable(multi->hash, key);
    if (elem == NULL)
        return NULL;
    // Not Null so we know this is linked list, casting it to linked list.
    LinkedList list_values = (LinkedList) elem;
    return list_values;
}

// Remove a value or part of it that belong to this key.
status removeFromMultiValueHashTable(MultiHash multi, Element elem_key, Element elem_val){
    if (multi == NULL || elem_key == NULL || elem_val == NULL)
        return failure;
    // check if the key exist.
    LinkedList list_values = lookupInMultiValueHashTable(multi, elem_key);
    if (list_values == NULL)
        return failure;
    // If the value is not in the list values of this key its return failure, else delete it.
    if (deleteNode(list_values, elem_val) == failure)
        return failure;
    if (getLengthList(list_values) == 0){
        if (removeFromHashTable(multi->hash, elem_key) == failure)
            return failure;
        return success;
    }
    return success;
}
// destroy multi hashtable;
status destroyMultiValueHashTable(MultiHash multi){
    if (multi == NULL)
        return failure;
    if (destroyHashTable(multi->hash) == failure)
        return failure;
    free(multi);
    return success;
}

// print all values that belongs to this key.
status displayMultiValueHashElementsByKey(MultiHash multi, Element key){
    if (multi == NULL || key == NULL)
        return failure;
    LinkedList list_values = lookupInMultiValueHashTable(multi, key);
    if (list_values == NULL)
        return failure;
    if ( multi->print_key(key) == success && displayList(list_values) == success)
        return success;
    return failure;
}

