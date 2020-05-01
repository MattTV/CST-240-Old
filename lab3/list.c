//**************************************************
// Linked list implementation
//

#include <stdlib.h>

#include "list.h"

typedef struct item_t
{
    int data;
    struct item_t * next;
    struct item_t * prev;
} item_t;

typedef struct list_t
{
    item_t * head;
    item_t * tail;
    int count;
} list_t;

// Create and initialize a list. 
// Return pointer to list. Return NULL on failure.
linked_list_t Init_List()
{
   list_t * list = (list_t *)malloc(sizeof(list_t));

   list->head = NULL;
   list->tail = NULL;
   list->count = 0;

   return (linked_list_t *)list; // I don't know much about malloc, but my understanding is that the pointer will be NULL if it fails, so it will return NULL on failure as the function says.
}

// Delete a list are free all memory used by the list
// It is erroneous to use the list pointer after caling this routine.
// Return zero on success
int Delete_List(linked_list_t list)
{
    list_t * l = (list_t *)list; // Cast.
    item_t * curr = l->head;
    item_t * next = NULL;
    
    while (curr != NULL)
    {
        next = curr->next;

        free(curr);

        curr = next;
    }

    free(l);

    return 0;
}

// Returns the number of items in the list
int Count(linked_list_t list)
{
    return ((list_t *)list)->count;
}

// Insert an item at the beginning of the list
// Return zero on success
// Params:
//    list: list to add item to
//    data: Data to be added to the list
int Insert_At_Beginning(linked_list_t list, int data)
{
    list_t * l = (list_t *) list;
    item_t * n = malloc(sizeof(item_t));

    // Set the data as it should be.
    n->data = data;
    n->next = l->head;
    n->prev = NULL;

    // Replace head in the list.
    l->head = n;

    // If this is the only node in the list, point the tail to it as well.
    if (l->tail == NULL)
        l->tail = n;

    // Increase the number of nodes by 1.
    ++(l->count);

    return 0;
}

// Insert an item at the end of the list
// Return zero on success
// Params:
//    list: list to add item to
//    data: Data to be added to the list
int Insert_At_End(linked_list_t list, int data)
{
    list_t * l = (list_t *) list;
    item_t * n = malloc(sizeof(item_t));

    // Set the data as it should be.
    n->data = data;
    n->next = NULL;
    n->prev = l->tail;

    // Replace the tail in the list.
    l->tail = n;

    // If this is the only node in the list, point the head to it as well.
    if (l->head == NULL)
        l->head = n;

    // Increase the number of nodes by 1.
    ++(l->count);

    return 0;
}

// Return true (non-zero) if the list is empty
//    list: list to examine
int Empty(linked_list_t list)
{
    // If count is 0, invert to return true. Else, invert so 0 (false) is returned.
    return !(((list_t *)list)->count);
}

// Remove an item from the beginning of the list 
// Return zero on success
// Returns 1 if the list is blank.
// Params:
//    list: list to remove item from
//    data: pointer to location to store data of removed item
//          if data is NULL, data is not returned
int Remove_From_Beginning(linked_list_t list, int* data)
{
    list_t * l = (list_t *) list;
    item_t * n = NULL;
    int ret = 1;
    
    if (l->head != NULL)
    {
        if (data != NULL)           // If there is a data pointer, give it the data.
            *data = l->head->data;

        if (l->tail == l->head)     // If there is only one node in the list before deleting it, point the tail to NULL.
            l->tail = NULL;

        if (l->head->next != NULL)
        {
            n = l->head;
            l->head = l->head->next;    // Set the new head to the head's next node.
            free(n);        // Delete the old head.
            l->head->prev = NULL;       // Point the new head back to NULL.
        }
        else
        {
            free(l->head);
            l->head = NULL;
        }

        --(l->count);               // Decrease the count.
        ret = 0;                    // If this happened, set the return value to 0.
    }

    return ret;
}

// Remove an item from the end of the list 
// Return zero on success
// Returns 1 if the list is blank.
// Params:
//    list: list to remove item from
//    data: pointer to location to store data of removed item
//          if data is NULL, data is not returned
int Remove_From_End(linked_list_t list, int* data)
{
    list_t * l = (list_t *) list;
    item_t * n = NULL;
    int ret = 1;

    if (l->tail != NULL)
    {
        if (data != NULL)           // If there is a data pointer, give it the data from the node.
            *data = l->tail->data;

        if (l->head == l->tail)     // If there is only one node in the list before deleting it, point the head to NULL.
            l->head = NULL;
        if (l->tail->prev != NULL)
        {
            n = l->tail;
            l->tail = l->tail->prev;    // Set the new tail to the node before the current tail.
            free(n);        // Free the old tail.
            l->tail->next = NULL;       // Point the new tail forward to NULL.
        }
        else
        {
            free(l->tail);
            l->tail = NULL;
        }

        --(l->count);
        ret = 0;
    }

    return ret;
}

// This function traverses the list and performs the given function on each item.
// Returns 0 on success.
// Returns 1 if the list is empty.
// Params:
//    list: the list to traverse.
//    action: the function to execute on each item.
int Traverse(linked_list_t list, void (*action)(int data))
{
    list_t * l = (list_t *)list;
    item_t * n = l->head;
    int ret = 0;

    if (n == NULL)          // If the list is empty, return 1.
        ret = 1;

    while (n != NULL)       // For each item, perform the action with the data passed in, and jump to the next node..
    {
        action(n->data);
        n = n->next;
    }
    
    return ret;
}

// This function adds a new data item to an ordered list, in order.
// Returns 0 on success.
// Params:
//    list: the list to add to.
//    value: the data value to add as an item.
int Insert_In_Order(linked_list_t list, int value)
{
    list_t * l = (list_t *)list;
    item_t * n = malloc(sizeof(item_t));
    n->data = value;
    n->next = NULL;
    n->prev = NULL;

    if (l->head == NULL)                // If the list is empty, make the node the only node in it.
    {
        l->head = n;
        l->tail = n;
    }
    else                                // If the list has at least one node...
    {
        item_t * travel = l->head;

        while (travel != NULL && travel->data < value)  // ...travel to the right spot so the new data will be in order. 
            travel = travel->next;

        if (travel == NULL)             // If that spot happens to be at the end of the list, add this tail node.
        {
            n->prev = l->tail;
            l->tail->next = n;
            l->tail = n;
        }
        else                            // Or if it's at the front or in the middle of the list, place the node and mend the list.
        {
            n->next = travel;
            n->prev = travel->prev;
            travel->prev = n;
            
            if (n->prev != NULL)        // If the new node should not be the head of the list, point it to the node that should be before it.
                n->prev->next = n;
            if (n->prev == NULL)        // If the new node should be the new head of the list, point the list's head pointer to it.
                l->head = n;
        }
    }

    ++(l->count);

    return 0;
}

