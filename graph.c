#include <stdio.h>
#include <stdlib.h>
#include "arraygraph.c" // graph
#include <time.h>
#define graphSize 100

void printEdgeSelectedVertex(ArrayGraph *pGraph, int vertex)
{
    for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
        {
            if(pGraph->pVertex[i % pGraph->maxVertexCount] == vertex)
            {
                for (int k = 0; k < pGraph->maxVertexCount; k++)
                    if(pGraph->ppAdjEdge[i % pGraph->maxVertexCount][k] && k != i % pGraph->maxVertexCount)
                        printf("%d-->%d[%d] ",pGraph->pVertex[i % pGraph->maxVertexCount], pGraph->pVertex[k], pGraph->ppAdjEdge[i % pGraph->maxVertexCount][k]);
                printf("\n");
                break;
            }
        }
}

void bfs (ArrayGraph *pGraph, int vertex, int q, int *visited)
{
    if (q < 0)
        return ;
    visited[vertex-1] = 1;
    printf("%d ",vertex);
    for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
                for (int k = 0; k < pGraph->maxVertexCount; k++)
                    if(pGraph->ppAdjEdge[i % pGraph->maxVertexCount][k] && k != i % pGraph->maxVertexCount && !visited[k] && pGraph->pVertex[i % pGraph->maxVertexCount] == vertex)
                        bfs(pGraph, pGraph->pVertex[k], q - 1, visited);
}

void dfs (ArrayGraph *pGraph, int vertex, int *visited)
{
    visited[vertex-1] = 1;
    printf("%d ",vertex);
    for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
                for (int k = 0; k < pGraph->maxVertexCount; k++)
                    if(pGraph->ppAdjEdge[i % pGraph->maxVertexCount][k] && k != i % pGraph->maxVertexCount && !visited[k] && pGraph->pVertex[i % pGraph->maxVertexCount] == vertex)
                        dfs(pGraph, pGraph->pVertex[k] ,visited);
}

/*

for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            {
                for (int k = 0; k < pGraph->maxVertexCount; k++)
                    if(pGraph->ppAdjEdge[i % pGraph->maxVertexCount][k] && k != i % pGraph->maxVertexCount)
                        printf("%d-->%d[%d] ",pGraph->pVertex[i % pGraph->maxVertexCount], pGraph->pVertex[k], pGraph->ppAdjEdge[i % pGraph->maxVertexCount][k]);
                printf("\n");
            }
*/

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
    int *dummy = malloc(sizeof(int*) * graphSize);
    int *extra = malloc(sizeof(int*) * graphSize);
    for (int i = 0; i < graphSize; i++)
    {
        dummy[i] = i + 1;
        extra[i] = i + 1;
    }
    //shuffle(dummy, graphSize);
    /*
    for (int i = 0; i < graphSize; i++)
        printf("%d ",dummy[i]);
    printf("\n");
    for (int i = 0; i < graphSize; i++)
        printf("%d ",dummy2[i]);
    printf("\n");
    */
    ArrayGraph *g = createArrayGraph(graphSize,GRAPH_DIRECTED);
    for(int i = 0 ;i < g->maxVertexCount; i++)
        addVertexAG(g, i + 1);
    //displayArrayGraph(g);
    for(int i = 0; i< g->currentVertexCount; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            shuffle(extra, g->currentVertexCount);
            shuffle(dummy, g->currentVertexCount);
            addEdgewithWeightAG(g, i+1, dummy[j], extra[j]);
        }
    }
    free(extra);
    free(dummy);
    displayArrayGraph(g);
    printf("first\n\n");
    int *visited = calloc(4,sizeof(int *) * g->currentVertexCount);
    /*
    for(int i = 0; i < g->currentVertexCount; i++)
        printf("%d\n", visited[i]);
    */
    dfs(g, 1, visited);
    printf("\n");
    free(visited);
    printf("second\n\n");
    visited = calloc(4,sizeof(int *) * g->currentVertexCount);
    printEdgeSelectedVertex(g, 1);
    bfs(g, 1, 2, visited);
    free(visited);
    printf("\n\n");
    printf("third\n\n");
    printf("fourth\n\n");
    deleteArrayGraph(&g);
    //system("leaks a.out");
    return 0;
}