#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "bin_search_tree.c"

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

void swap(node *a, node *b) {
 
  node temp = *a;
  *a = *b;
  *b = temp;
}
 
// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(node *arr, int n, int i) {
 
  // Find largest among root, left child and right child
 
    // Initialize largest as root
  int largest = i;
 
   // left = 2*i + 1
  int left = 2 * i + 1;
 
   // right = 2*i + 2
  int right = 2 * i + 2;
 
  // If left child is larger than root
  if (left < n && arr[left].key > arr[largest].key)
 
    largest = left;
 
  // If right child is larger than largest
    // so far
  if (right < n && arr[right].key > arr[largest].key)
 
    largest = right;
 
  // Swap and continue heapifying if root is not largest
// If largest is not root
  if (largest != i) {
 
    swap(&arr[i], &arr[largest]);
 
     // Recursively heapify the affected
     // sub-tree
    heapify(arr, n, largest);
 
  }
 
}
 
// Main function to do heap sort
void heapSort(node *arr, int n) {
 
  // Build max heap
  for (int i = n / 2 - 1; i >= 0; i--)
 
    heapify(arr, n, i);
 
  // Heap sort
  for (int i = n - 1; i >= 0; i--) {
 
    swap(&arr[0], &arr[i]);
 
    // Heapify root element to get highest element at root again
    heapify(arr, i, 0);
 
  }
 
}

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
    printf("first\n"); // printf max 3
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
    printf("second\n"); // descending order
    int min;
    {
        for(j =0;j<dummy->size;j++)
        {
            min = j;
            for(i = j + 1;i<dummy->size;i++)
                if(dummy->array[i].key < dummy->array[min].key)
                    min = i;
            printf("%d ",dummy->array[min].key);
            node t = dummy->array[min];
            dummy->array[min] = dummy->array[j];
            dummy->array[j] = t;
            if((j + 31) % 30 == 0)
                printf("\n");
        }
    }
    printf("\n");
    shuffle(dummy, dummy->size);
    printf("third\n"); // push & balance
    record *dummy2 = malloc(sizeof(record));
    dummy2->array = malloc(sizeof(node) * dummy->size);
    dummy2->count = 0;
    dummy2->size = dummy->size;
    for(i = 0; i < dummy->size;i++)
    {
        dummy2->array[i] = dummy->array[i];
        dummy2->count++;
        if(i > 0 && dummy2->array[i-1].key > dummy2->array[i].key)
        {
            j = i;
            while(j > 0 && dummy2->array[j-1].key > dummy2->array[j].key)
            {
                node t = dummy2->array[j];
                dummy2->array[j] = dummy2->array[j - 1];
                dummy2->array[j - 1] = t;
                j--;
            }
        }
    }
    for(i = 0; i < dummy2->size; i++)
    {
        printf("%d ", dummy2->array[i].key);
        if((i + 31) % 30 == 0)
            printf("\n");
    }
    printf("\n");
    printf("fourth\n"); //min heap tree
    shuffle(dummy2, dummy2->size);
    heapSort(dummy2->array, dummy2->size);
    for(i = 0; i < dummy2->size; i++)
    {
        printf("%d ", dummy2->array[i].key);
        if((i + 31) % 30 == 0)
            printf("\n");
    }
    printf("\n");
    free(dummy2->array);
    free(dummy2);
    printf("fifth\n"); // avl tree
    shuffle(dummy,dummy->size);
    BinTreeNode root;
    root.data = 0;
    root.next = NULL;
    root.parent = NULL;
    root.visited = 0;
    root.key = 0;
    root.pRightChild = NULL;
    root.pLeftChild = NULL;
    BinTree *tree;
    tree = makeBinSearchTree(root);
    for (i = 0; i < dummy->size; i++)
    {
        root.key = dummy->array[i].key;
        insertBinSearchTree(tree, root);
    }
    printf("inorder : ");inOrderB(tree->pRootNode);
    deleteBinTree2(&tree);
    free(dummy->array);
    free(dummy);
    //system("leaks a.out");
    return 0;
}