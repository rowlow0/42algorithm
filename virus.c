#include <stdio.h>
#include <stdlib.h>
#define N 10
#define K 1
typedef unsigned long long ull;

struct Node
{
    int data;
    int k;
} typedef node;

struct ArrayList
{
    int count;
    int size;
    int dup_time;
    ull sum;
    node *array;
} typedef array_list;

int main()
{
    if (N <= 0)
    {
        printf("Null\n");
        return (1);
    }
    array_list *arr = malloc(sizeof(array_list));
    arr->array = calloc(1, sizeof(node) * N);
    arr->count = 0;
    arr->dup_time = K;
    arr->size = N;
    for(int i = 0;i< arr->size;i++)
    {
        for(int j = 0; j< arr->count; j++)
        {
            if(!--arr->array[j].k)
            {
                arr->sum -= arr->array[j].data;
                arr->array[j].data *= 2;
                arr->sum += arr->array[j].data;
                arr->array[j].k = arr->dup_time;
            }
        }
        arr->array[arr->count].k = arr->dup_time;
        arr->array[arr->count].data++;
        arr->sum += arr->array[arr->count++].data;
        printf("%llu virus in %d times\n",arr->sum, i + 1);
    }
    free(arr->array);
    free(arr);
    arr = 0;
    //system("leaks a.out");
    return (0);
}