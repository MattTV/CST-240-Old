#include <stdio.h>
#include <stdlib.h>

#include "list.h"

//******************************************

void PrintList(int data);

int main()
{
    linked_list_t list;
    int ii;
    int value;

    printf("Checking stack behavior\n");
    list = Init_List();
    if (list == NULL)
    {
        printf("Unable to initialize list\n");
        return 1;
    }

    for (ii=0; ii<10; ii++)
    {
        if (Insert_At_Beginning(list, ii) != 0)
        {
            printf("Error inserting %d\n", ii);
        }
    }

    if (Count(list) != 10) 
    {
        printf("Count is not correct after inserts: %d\n", Count(list));
    }

    Traverse(list, PrintList);

    for (ii=9; ii>=0; ii--)
    {
        if (Remove_From_Beginning(list, &value) != 0)
        {
            printf("Failed to remove item\n");
        }
        if (ii != value)
        {
            printf("Error removing %d %d\n", ii, value);
        }
    }

    if (!Empty(list)) 
    {
        printf("List is not empty after removes\n");
    }

    // Start putting in random items.
    printf("List iteration 2:\n");

    for (int jj = 0; jj < 10; ++jj)
    {
        int data = rand() % 1000;
        printf("Adding: %d.\n", data);
        Insert_In_Order(list, data);
    }

    Traverse(list, PrintList);

    Delete_List(list);

    printf("Tests complete\n");

    return 0;
}

void PrintList(int data)
{
    printf("List item: %d.\n", data);
}
