#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node
{
    int data;
    int key;
} node;

typedef struct Record
{
    int count;
    int size;
    node *array;
} record;

void shuffle(record *dummy, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          node t = dummy->array[j];
          dummy->array[j] = dummy->array[i];
          dummy->array[i] = t;
        }
    }
}

int main()
{
    //init record
    srand(time(NULL));
    record *dummy = malloc(sizeof(record));
    dummy->array = malloc(sizeof(node) * 10000);
    dummy->count = -1;
    dummy->size = 10000;
    while(++dummy->count < dummy->size)
        dummy->array[dummy->count].key = dummy->count;
    shuffle(dummy, dummy->size);
    int i, j;
    /*
    for(i = 0; i < dummy->count; i++)
        printf("%d ", dummy->array[i].key);
    printf("\n");
    */
    printf("first\n");
    int max1 = INT_MIN, max2 = INT_MIN + 1, max3 = INT_MIN + 2;
    for(i = 0; i< dummy->size; i++)
    {
        if(dummy->array[i].key > max1)
        {
            max3 = max2;
            max2 = max1;
            max1 = dummy->array[i].key;
        }
        else if (dummy->array[i].key > max2)
        {
            max3 = max2;
            max2 = dummy->array[i].key;
        }
        else if (dummy->array[i].key > max3)
            max3 = dummy->array[i].key;
    }
    printf("max1 : %d max2 : %d max3 : %d \n",max1,max2,max3);
    printf("second\n"); //delete array[i] and rearrange

    printf("third\n"); // new array

    printf("fourth\n"); //min heap tree

    printf("fifth\n"); // avl tree

    free(dummy->array);
    free(dummy);
    return 0;
}