#include <stdio.h>
#include <stdlib.h>
#include "arraygraph.c" // graph
#include <time.h>
#include <limits.h>
#define graphSize 10
#define V 9

    typedef struct T_STRUCT
    {
        int *visited;
        int vertex;
        int q;
    } t_struct;

    int minDistance(int *dist, int *sptSet)
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
// A utility function to print the constructed distance array
void printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
    int dist[V]; // The output array.  dist[i] will hold the shortest
    // distance from src to i
 
    int sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);
 
        // Mark the picked vertex as processed
        sptSet[u] = 1;
 
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
 
    // print the constructed distance array
    printSolution(dist);
}

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

void bfs2 (ArrayGraph *pGraph, ArrayGraph **dest, t_struct *temp)
{
    if (temp->q < 0)
        return ;
    temp->visited[temp->vertex-1] = 1;
    addVertexAG2(dest, temp->vertex);
    for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
    {
                for (int k = 0; k < pGraph->maxVertexCount; k++)
                {
                    if(pGraph->ppAdjEdge[i % pGraph->maxVertexCount][k] && k != i % pGraph->maxVertexCount && !temp->visited[k] && pGraph->pVertex[i % pGraph->maxVertexCount] == temp->vertex)
                    {
                        temp->q--;
                        int tt = temp->vertex;
                        temp->vertex = pGraph->pVertex[k];
                        bfs2(pGraph, dest, temp);
                        temp->q++;
                        temp->vertex = tt;
                    }
                }
    }
    if(temp->q)
        for (int i = 0; i < pGraph->currentVertexCount; i++)
            addEdgewithWeightAG(*dest, temp->vertex, pGraph->pVertex[i], pGraph->ppAdjEdge[temp->vertex-1][i]);
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
        for (int j = 0; j < 2; j++)
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
    printf("\n\n");
    free(visited);
    printf("second\n\n");
    visited = calloc(4,sizeof(int *) * g->currentVertexCount);
    printEdgeSelectedVertex(g, 1);
    bfs(g, 1, 2, visited);
    free(visited);
    printf("\n\n");
    printf("third\n\n");
    ArrayGraph *g2 = createArrayGraph(graphSize,GRAPH_DIRECTED);
    t_struct *temp = malloc(sizeof(t_struct));
    temp->visited = calloc(4, sizeof(int *) * g->currentVertexCount);
    temp->vertex=1;
    temp->q = 2;
    bfs2(g, &g2,temp);
    displayArrayGraph(g2);
    free(temp->visited);
    free(temp);
    deleteArrayGraph(&g2);
    printf("fourth\n\n");
    deleteArrayGraph(&g);
    //system("leaks a.out");
    //gcc -g -fsanitize=address -Wall -Wextra -Werror graph.c
    return 0;
}