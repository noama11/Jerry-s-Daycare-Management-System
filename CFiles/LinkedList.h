//
// Created by noam on 12/20/22.
//

#ifndef C_3_LINKEDLIST_H
#define C_3_LINKEDLIST_H

#endif //C_3_LINKEDLIST_H
#include "Defs.h"

typedef struct LinkedList_t* LinkedList;

// ADT of a generic linked list consist of nodes (object) and supports saving a value for each node.
//ADT

// Creating function of the linked list using generic functions of copy, destroy, print and equal that the user need to provide.
LinkedList createList(EqualFunction equalFunc, FreeFunction freeFunc, CopyFunction copyFunc, PrintFunction printFunc);

// Destroying function of the linked list.
status destroyList(LinkedList list);

// Function adding a data to the list and creating a node to save it.
status appendNode(LinkedList list, Element);

// Delete node from the list that contain a specific data.
status deleteNode(LinkedList list, Element);

// Prints all the elements in the list.
status displayList(LinkedList list);

// Find and return the data by a specific index.
Element getDataByIndex(LinkedList list, int idx);

// Return the list size.
int getLengthList(LinkedList list);

// Find and return the requested data
Element searchByKeyInList(LinkedList list, Element);