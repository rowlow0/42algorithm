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
    int *extra = malloc(sizeof(int*) * 100);
    for (int i = 0; i < 100; i++)
    {
        dummy[i] = i + 1;
        extra[i] = i + 1;
    }
    //shuffle(dummy, 100);
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
        for (int j = 0; j < 10; j++)
        {
            shuffle(extra, 100);
            shuffle(dummy, 100);
            addEdgewithWeightAG(g, i+1, dummy[j], extra[j]);
        }
    }
    free(dummy);
    free(extra);
    displayArrayGraph(g);
    deleteArrayGraph(&g);
    //system("leaks a.out");
    return 0;
}