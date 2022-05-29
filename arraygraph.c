#include "arraygraph.h" //queue
/*
to do list
space 2d -> 1d //adjacency list
vetex 100 0
*/

//create
ArrayGraph* createArrayGraph(int maxVertexCount, int type)
{
    if (maxVertexCount <= 0 || !(type == 1 || type == 2)) // nor
        return NULL;
    ArrayGraph *new = malloc(sizeof(ArrayGraph));
    new->currentVertexCount = 0;
    new->rear = -1;
    new->front = 0;
    new->graphType = type;
    new->maxVertexCount = maxVertexCount;
    new->ppAdjEdge = malloc(sizeof(int **) * maxVertexCount);
    new->pVertex = malloc(sizeof(int *) * maxVertexCount);
    return new;
}
/*
1 2 
x x T
o x F
x o F
o o F
*/

//delete
void deleteArrayGraph(ArrayGraph** pGraph)
{
    if(pGraph && *pGraph)
    {
        if((*pGraph)->ppAdjEdge)
        {
            if ((*pGraph)->rear >= 0)
                for(int i = (*pGraph)->front, j = 0; j < (*pGraph)->currentVertexCount; j++, i++)
                    free((*pGraph)->ppAdjEdge[i % (*pGraph)->maxVertexCount]);
            free((*pGraph)->ppAdjEdge);
        }
        if((*pGraph)->pVertex)
            free((*pGraph)->pVertex);
        free(*pGraph);
        *pGraph = NULL;
    }
}

/*
//is empty
int isEmptyAG(ArrayGraph* pGraph)
{
    return !pGraph || !pGraph->currentVertexCount;
}
*/

//search vertex
int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
    //if (pGraph && pGraph->pVertex)
    for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
        if(pGraph->pVertex[i % pGraph->maxVertexCount] == vertexID)
            return 1;
    return 0;
}

//add vertex
int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if(pGraph && pGraph->pVertex && (pGraph->graphType == 1 ||  pGraph->graphType == 2) && pGraph->currentVertexCount < pGraph->maxVertexCount && !checkVertexValid(pGraph, vertexID))
    {
        pGraph->currentVertexCount++;
        if (++pGraph->rear == pGraph->maxVertexCount)
            pGraph->rear = 0;
        pGraph->ppAdjEdge[pGraph->rear] = calloc(sizeof(int *), sizeof(int *) * pGraph->maxVertexCount);
        pGraph->ppAdjEdge[pGraph->rear][pGraph->rear]= 1;
        return pGraph->pVertex[pGraph->rear] = vertexID;
    }
    return 0;
}

//add edge to directed graph
int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if(pGraph && pGraph->pVertex && pGraph->graphType == 1 && fromVertexID != toVertexID && checkVertexValid(pGraph, fromVertexID) && checkVertexValid(pGraph, toVertexID))
    {
        int x=0, y=0;
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % pGraph->maxVertexCount] == fromVertexID)
            {
                x = i % pGraph->maxVertexCount;
                break;
            }
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % pGraph->maxVertexCount] == toVertexID)
            {
                y = i % pGraph->maxVertexCount;
                break;
            }
        pGraph->ppAdjEdge[x][y] = 1;
        pGraph->ppAdjEdge[y][x] = 1;
        return 1;
    }
    return 0;
}

//add edge to directed graph
int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    if(pGraph && pGraph->pVertex && pGraph->graphType == 2 && fromVertexID != toVertexID && checkVertexValid(pGraph, fromVertexID) && checkVertexValid(pGraph, toVertexID))
    {
        int x=0, y=0;
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % pGraph->maxVertexCount] == fromVertexID)
            {
                x = i % pGraph->maxVertexCount;
                break;
            }
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % pGraph->maxVertexCount] == toVertexID)
            {
                y = i % pGraph->maxVertexCount;
                break;
            }
        pGraph->ppAdjEdge[x][y] = weight;
        return 1;
    }
    return 0;
}

//remove vertex
int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if (pGraph && pGraph->pVertex && checkVertexValid(pGraph, vertexID) && (vertexID == pGraph->pVertex[pGraph->rear] || vertexID == pGraph->pVertex[pGraph->front]))
    {
        int y=0;
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % pGraph->maxVertexCount] == vertexID)
            {
                y = i % pGraph->maxVertexCount;
                break;
            }
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            pGraph->ppAdjEdge[i % pGraph->maxVertexCount][y] = 0;
        if(pGraph->pVertex[pGraph->rear] == vertexID)
        {
            free(pGraph->ppAdjEdge[pGraph->rear]);
            //int **a = &pGraph->ppAdjEdge[pGraph->rear];
            //*a = 0;
            //pGraph->pVertex[pGraph->rear--] = 0;
            pGraph->rear--;
        }
        else if(pGraph->pVertex[pGraph->front] == vertexID)
        {
            free(pGraph->ppAdjEdge[pGraph->front]);
            //int **a = &pGraph->ppAdjEdge[pGraph->front];
            //*a = 0;
            //pGraph->pVertex[pGraph->front++] = 0;
            pGraph->front++;
            if(pGraph->front > pGraph->maxVertexCount)
                pGraph->front = 0;
            if(!(pGraph->currentVertexCount - 1))
                pGraph->rear = -1;
        }
        else
            goto jump;
        pGraph->currentVertexCount--;
        return 1;
    }
    jump:
    return 0;
}

//remove edge
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (pGraph && pGraph->pVertex && checkVertexValid(pGraph, fromVertexID) && checkVertexValid(pGraph, toVertexID))
    {
        int x=0, y=0;
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % pGraph->maxVertexCount] == fromVertexID)
            {
                x = i;
                break;
            }
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % pGraph->maxVertexCount] == toVertexID)
            {
                y = i;
                break;
            }
        pGraph->ppAdjEdge[x][y] = 0;
        if(pGraph->graphType == 1)
            pGraph->ppAdjEdge[y][x] = 0;
        return 1;
    }
    return 0;
}

//display
void displayArrayGraph(ArrayGraph* pGraph)
{
    if(pGraph && pGraph->pVertex)
    {
        if (pGraph->graphType == 1)
            printf("type : undirected\n");
        else
            printf("type : directed\n");
        printf("max count : %d\n", pGraph->maxVertexCount);
        printf("current count : %d\n", pGraph->currentVertexCount);
        printf("front : %d\n", pGraph->front);
        printf("rear : %d\n", pGraph->rear);   
        printf("vetex : ");
        for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            printf("%d ",pGraph->pVertex[i % pGraph->maxVertexCount]);
        printf("\n");
        printf("vetex edge map: \n");
        printf("\n");
        if(pGraph->graphType == 1)
        {
            for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            {
                for (int k = 0; k < pGraph->maxVertexCount; k++)
                    if(pGraph->ppAdjEdge[i % pGraph->maxVertexCount][k] && k != i % pGraph->maxVertexCount)
                        printf("%d<-->%d ", pGraph->pVertex[i % pGraph->maxVertexCount],pGraph->pVertex[k]);
                printf("\n");
            }
        }
        else if(pGraph->graphType == 2)
        {
            for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            {
                for (int k = 0; k < pGraph->maxVertexCount; k++)
                    if(pGraph->ppAdjEdge[i % pGraph->maxVertexCount][k] && k != i % pGraph->maxVertexCount)
                        printf("%d-->%d[%d] ",pGraph->pVertex[i % pGraph->maxVertexCount], pGraph->pVertex[k], pGraph->ppAdjEdge[i % pGraph->maxVertexCount][k]);
                printf("\n");
            }
        }
        printf("\n");
    }
}
/*
int main()
{
    ArrayGraph *g = createArrayGraph(10,GRAPH_UNDIRECTED);
    addVertexAG(g, 15);
    addVertexAG(g, 1);
    addVertexAG(g, 2);
    addVertexAG(g, 3);
    addVertexAG(g, 4);
    addVertexAG(g, 5);
    addVertexAG(g, 6);
    addVertexAG(g, 25);
    addVertexAG(g, 30);
    addVertexAG(g, 35);
    addEdgeAG(g, 15, 1);
    addEdgeAG(g, 15, 2);
    addEdgeAG(g, 15, 3);
    addEdgeAG(g, 4, 15);
    addEdgeAG(g, 4, 21);
    addEdgeAG(g, 4, 30);
    addEdgeAG(g, 4, 6); // add edge and vertex
    displayArrayGraph(g);
    removeEdgeAG(g, 15, 1);
    removeEdgeAG(g, 15, 2);
    removeEdgeAG(g, 15, 3); // remove edge
    displayArrayGraph(g);
    removeVertexAG(g, 15);
    removeVertexAG(g, 4);
    removeVertexAG(g, 35);
    removeVertexAG(g, 30);
    removeVertexAG(g, 25); // remove vertex
    displayArrayGraph(g);
    addVertexAG(g, 7);
    addVertexAG(g, 8);
    addVertexAG(g, 9);
    addVertexAG(g, 10);
    addVertexAG(g, 11); // add vertex
    addEdgeAG(g, 4, 10);
    addEdgeAG(g, 7, 4);
    displayArrayGraph(g);
    deleteArrayGraph(&g); //delete

    g = createArrayGraph(10,GRAPH_DIRECTED);
    addVertexAG(g, 15);
    addVertexAG(g, 1);
    addVertexAG(g, 2);
    addVertexAG(g, 3);
    addVertexAG(g, 4);
    addVertexAG(g, 5);
    addVertexAG(g, 6);
    addVertexAG(g, 25);
    addVertexAG(g, 30);
    addVertexAG(g, 35);
    addEdgewithWeightAG(g, 0, 1, 1);
    addEdgewithWeightAG(g, 1, 0, 2);
    addEdgewithWeightAG(g, 3, 4, 3);
    addEdgewithWeightAG(g, 4, 3, 4);
    addEdgewithWeightAG(g, 4, 1, 5);
    addEdgewithWeightAG(g, 15, 25, 6);
    addEdgewithWeightAG(g, 4, 15, 7);
    addEdgewithWeightAG(g, 15, 4, 8);
    displayArrayGraph(g);
    removeVertexAG(g, 15);
    removeVertexAG(g, 4);
    removeVertexAG(g, 35);
    removeVertexAG(g, 30);
    removeVertexAG(g, 25); // remove vertex
    displayArrayGraph(g);
    deleteArrayGraph(&g); // delete
    //system("leaks a.out");
    //gcc -g -fsanitize=address -Wall -Wextra -Werror arraygraph.c
    return (0);
}
*/