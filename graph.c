#include <stdio.h>
#include <stdlib.h>
#include "arraygraph.c"
#include <time.h>

void shuffle(int *dummy, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = dummy[i];
          dummy[i] = dummy[j];
          dummy[j] = t;
        }
    }
}

int main()
{
    srand(time(NULL));
    int *dummy = malloc(sizeof(int*) * 100);
    int *dummy2 = malloc(sizeof(int*) * 100);
    int *dummy3 = malloc(sizeof(int*) * 100);
    int *dummy4 = malloc(sizeof(int*) * 100);
    int *dummy5 = malloc(sizeof(int*) * 100);
    int *dummy6 = malloc(sizeof(int*) * 100);
    int *dummy7 = malloc(sizeof(int*) * 100);
    int *dummy8 = malloc(sizeof(int*) * 100);
    int *dummy9 = malloc(sizeof(int*) * 100);
    int *dummy10 = malloc(sizeof(int*) * 100);
    for (int i = 0; i < 100; i++)
    {
        dummy[i] = i + 1;
        dummy2[i] = i + 1;
        dummy3[i] = i + 1;
        dummy4[i] = i + 1;
        dummy5[i] = i + 1;
        dummy6[i] = i + 1;
        dummy7[i] = i + 1;
        dummy8[i] = i + 1;
        dummy9[i] = i + 1;
        dummy10[i] = i + 1;
    }
    shuffle(dummy, 100);
    shuffle(dummy2, 100);
    shuffle(dummy3, 100);
    shuffle(dummy4, 100);
    shuffle(dummy5, 100);
    shuffle(dummy6, 100);
    shuffle(dummy7, 100);
    shuffle(dummy8, 100);
    shuffle(dummy9, 100);
    shuffle(dummy10, 100);
    /*
    for (int i = 0; i < 100; i++)
        printf("%d ",dummy[i]);
    printf("\n");
    for (int i = 0; i < 100; i++)
        printf("%d ",dummy2[i]);
    printf("\n");
    */
    ArrayGraph *g = createArrayGraph(100,GRAPH_DIRECTED);
    for(int i = 0 ;i < 100; i++)
        addVertexAG(g, i + 1);
    //displayArrayGraph(g);
    for(int i = 0; i< 100; i++)
    {
        addEdgewithWeightAG(g, i+1, dummy[i],  i+1);
        addEdgewithWeightAG(g, i+1, dummy2[i], i+1);
        addEdgewithWeightAG(g, i+1, dummy3[i], i+1);
        addEdgewithWeightAG(g, i+1, dummy4[i], i+1);
        addEdgewithWeightAG(g, i+1, dummy5[i], i+1);
        addEdgewithWeightAG(g, i+1, dummy6[i], i+1);
        addEdgewithWeightAG(g, i+1, dummy7[i], i+1);
        addEdgewithWeightAG(g, i+1, dummy8[i], i+1);
        addEdgewithWeightAG(g, i+1, dummy9[i], i+1);
        addEdgewithWeightAG(g, i+1, dummy10[i], i+1);
    }
    displayArrayGraph(g);
    free(dummy);
    free(dummy2);
    free(dummy3);
    free(dummy4);
    free(dummy5);
    free(dummy6);
    free(dummy7);
    free(dummy8);
    free(dummy9);
    free(dummy10);
    deleteArrayGraph(&g);
    return 0;
}