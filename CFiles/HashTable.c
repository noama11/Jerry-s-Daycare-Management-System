//
// Created by noam on 12/20/22.
//
#include <stdio.h>
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

struct hashTable_s{
    int size;
    int number_of_pairs;
    LinkedList* arr ;
    TransformIntoNumberFunction hashtransform;
    CopyFunction copy_key;
    CopyFunction copy_value;
    FreeFunction free_key;
    FreeFunction free_value;
    PrintFunction print_key;
    PrintFunction print_value;
    EqualFunction equal_key;
};

int hash_func(hashTable hash, Element element){
    int num = hash->hashtransform(element);
    int idx = num % hash->size;
    return idx;
}
// Initialization helper functions to support of the functionality of linked_list and key_value_pair.
// function for copy the element.

Element copy_pair_func(Element element){
    if (element == NULL)
        return NULL;
    return element;
}
// function for free the element
status free_pair(Element element){
    if (element == NULL)
        return failure;
    KeyValuePair pair = (KeyValuePair) element;
    return destroyKeyValuePair(pair);
}
// function for print the element
status print_pair (Element element){
    if (element == NULL)
        return failure;
    KeyValuePair pair = (KeyValuePair) element;
    if(displayKey(pair) == success && displayValue(pair) == success)
        return success;
    return failure;
}
// equal the key of some pair to another key.
bool equal_key(Element pair_e, Element k){
    if (pair_e == NULL || k == NULL)
        return false;
    KeyValuePair pair = (KeyValuePair) pair_e;
    return isEqualKey(pair, k);
}
// create hash table of linked list.
hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue,
                          PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
    hashTable hashtable = (hashTable) malloc (sizeof (struct hashTable_s));
    if (hashtable == NULL)
        return NULL;
    hashtable->arr = (LinkedList*) malloc(sizeof(LinkedList) * hashNumber);
    if (hashtable->arr == NULL){
        free(hashtable);
        return NULL;
    }
    hashtable->size = hashNumber;
    for(int i = 0; i < hashtable->size; i++){
        hashtable->arr[i] = NULL;
    }
    hashtable->equal_key = equalKey;
    hashtable->copy_value = copyValue;
    hashtable->copy_key = copyKey;
    hashtable->free_key = freeKey;
    hashtable->free_value = freeValue;
    hashtable->print_key = printKey;
    hashtable->print_value = printValue;
    hashtable->hashtransform = transformIntoNumber;
    hashtable->number_of_pairs = 0;
    return hashtable;
}
// Function that destroying the adt and return status.
status destroyHashTable(hashTable hash){
    if (hash == NULL)
        return failure;
    for(int i = 0; i < hash->size; i++){
        if(hash->arr[i] != NULL)
            destroyList(hash->arr[i]);
    }
    hash->number_of_pairs = 0;
    hash->size = 0;
    free(hash->arr);
    free(hash);
    hash = NULL;
    return success;
}
// add to hase by hash func output index.
status addToHashTable(hashTable hash, Element key,Element value){
    if (hash == NULL || key == NULL || value == NULL)
        return failure;
    if (lookupInHashTable(hash, key) != NULL) {
        return failure;
    }
    KeyValuePair pair = createKeyValuePair(key, value, hash->copy_key, hash->free_key, hash->print_key, hash->copy_value,
                       hash->free_value, hash->print_value, hash->equal_key);
    if (pair == NULL)
        return failure;
    int idx = hash_func(hash, getKey(pair));
    if (hash->arr[idx] != NULL){
        if (appendNode(hash->arr[idx],pair) == failure){
            destroyKeyValuePair(pair);
            return failure;
        }
        hash->number_of_pairs++;
        return success;
    }
    // if the list is empty, create linked_list and add the pair.
    hash->arr[idx] = createList(equal_key, free_pair, copy_pair_func, print_pair);
    if (hash->arr[idx] == NULL) {
        destroyKeyValuePair(pair);
        return failure;
    }
    if (appendNode(hash->arr[idx],pair) == failure){
        destroyList(hash->arr[idx]);
        destroyKeyValuePair(pair);
        hash->arr[idx] = NULL;
        return failure;
    }
    hash->number_of_pairs++;
    return success;
}

// Find some element in the hash and return it.
Element lookupInHashTable(hashTable hash, Element key){
    if (hash == NULL || key == NULL)
        return NULL;
    if (hash->number_of_pairs == 0)
        return NULL;
    int idx = hash_func(hash, key);
    if (hash->arr[idx] == NULL)
        return NULL;
    KeyValuePair e1 = (KeyValuePair) searchByKeyInList(hash->arr[idx], key);
    if(e1 == NULL)
        return NULL;

    return getValue(e1);
}

// Remove a key value pair from the hash and return status.
status removeFromHashTable(hashTable hash, Element key){
    if (hash == NULL || key == NULL)
    return failure;
    if (hash->number_of_pairs == 0)
        return failure;
    int idx = hash_func(hash, key);
    if (hash->arr[idx] == NULL)
        return failure;
    Element found_key = searchByKeyInList(hash->arr[idx], key);
    if (found_key == NULL)
        return failure;
    if (deleteNode(hash->arr[idx], key) == success){
        hash->number_of_pairs--;
        if (getLengthList(hash->arr[idx]) == 0) {
            destroyList(hash->arr[idx]);
            hash->arr[idx] = NULL;
        }
        return success;
    }
    return failure;
}

// Print function of all elements in the hash.
status displayHashElements(hashTable hash){
    if (hash == NULL)
        return failure;
    if (hash->number_of_pairs == 0)
        return failure;
    for (int i = 0; i < hash->size; i++){
        if (hash->arr[i] != NULL)
           displayList(hash->arr[i]);
    }
    return success;

}
