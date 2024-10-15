#include <stdio.h>
#include "LinkedList.h"

typedef struct Node_t{
    Element data;
    struct Node_t* next;
}Node;

struct LinkedList_t{
    int size;
    Node* head;
    Node* tail;
    EqualFunction equalFunc;
    FreeFunction freeFunc;
    CopyFunction copyFunc;
    PrintFunction printFunc;

};

// Creating function of the linked list and return it.
LinkedList createList(EqualFunction equalFunc, FreeFunction freeFunc, CopyFunction copyFunc, PrintFunction printFunc){
    if (equalFunc == NULL || freeFunc == NULL || copyFunc == NULL || printFunc == NULL)
        return NULL;
    LinkedList list = (LinkedList) malloc(sizeof(struct LinkedList_t));
    if (list == NULL)
        return NULL;
    list->equalFunc = equalFunc;
    list->freeFunc = freeFunc;
    list->copyFunc = copyFunc;
    list->printFunc = printFunc;
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Delete element using freefunc from the user.
status deleteNode(LinkedList list, Element element){
    if (list == NULL)
        return failure;
    if (element == NULL)
        return failure;
    if (list->size == 0)
        return failure;
    if (list->size == 1){
        if (list->equalFunc(list->head->data, element) == true){
            list->freeFunc(list->head->data);
            free(list->head);
            list->head = list->tail = NULL;
            list->size--;
            return success;
        }
    }
    Node* temp = list->head;
    if (list->equalFunc(temp->data, element) == true){
        list->head = temp->next;
        list->freeFunc(temp->data);
        free(temp);
        temp = NULL;
        list->size--;
        if (list->size == 1)
            list->head = list->tail;
        return success;
        // if the element is the head of the list.
    }
    while (temp->next != NULL){
        if (list->equalFunc(temp->next->data, element) == true) {  // we found the element in the list
            Node* cur = temp->next;
            temp->next = cur->next;
            list->freeFunc(cur->data);  // free the element.
            free(cur);
            cur = NULL;
            list->size--;
            if(list->size == 1)
                list->tail = list->head;
            if (temp->next == NULL)
                list->tail = temp;
            return success;
        }
        temp = temp->next;
    }
    return failure;  // the element is not in the list.
}

// Function gets list and some element and adding it to the list.
status appendNode(LinkedList list, Element element){
    if (list == NULL)
        return failure;
    if (element == NULL)
        return failure;
    Node *new = (Node*) malloc(sizeof (Node));
    if (new == NULL)
        return failure;
    new->data = list->copyFunc(element);
    if (new->data == NULL) {
        free(new);
        return failure;
    }
    if (list->size == 0){
        list->head = list->tail = new;
        new->next = NULL;
        list->size++;
        return success;
    }
    if (list->size ==1){
        list->head->next = list->tail = new;
        new->next = NULL;
        list->size++;
        return success;
    }
    list->tail->next = new;
    list->tail = new;
    new->next = NULL;
    list->size++;
    return success;
}
// delete the list, free all the elements using the function from the user.
status destroyList(LinkedList list){
    if(list == NULL)
        return failure;
    if (list->size == 0){
        free(list);
        return success;
    }
    Node* temp = list->head;
    Node* cur;
    while(list->size != 0){
        cur = temp->next;
        list->freeFunc(temp->data);
        free(temp);
        temp = cur;
        list->size--;
    }
    //list->freeFunc(temp);
    free(temp);
    free(list);
    list = NULL;
    return success;
}

// Function that Prints all the elements in the list and return status.
status displayList(LinkedList list){
    if (list == NULL)
        return failure;
    Node* temp = list->head;
    int k = 0;
    while( k != list->size){
        list->printFunc(temp->data);
        temp = temp->next;
        k++;
    }
    return success;
}

// Find and return the data by a specific index.
Element getDataByIndex(LinkedList list, int idx){
    if (list == NULL)
        return NULL;
    if (idx <= 0 || idx > list->size)
        return NULL;
    int k = idx;
    Node* temp = list->head;
    while( k != 1){
        temp = temp->next;
        k--;
    }
    return temp->data;
}

// Return the list size.
int getLengthList(LinkedList list){
    if (list == NULL)
        return 0;
    return list->size;
}

// Find and return the requested data
Element searchByKeyInList(LinkedList list, Element element){
    if (list == NULL)
        return NULL;
    if (element == NULL)
        return NULL;
    if (list->size == 0)
        return NULL;
    int k = 1;
    Node * temp = list->head;
    while ( k != list->size +1){
        if (list->equalFunc(temp->data, element) == true)
            return getDataByIndex(list, k);
        temp = temp->next;
        k++;
    }
    return NULL;
}

