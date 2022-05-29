#ifndef _GRAPH_ADJMATRIX_
#define _GRAPH_ADJMATRIX_

#include "stdio.h"
#include "stdlib.h"

typedef struct ArrayGraphType
{
	int maxVertexCount;		//
	int currentVertexCount;	//
	int graphType;			// Undirected, 2-Directed
	int **ppAdjEdge;		// array
	int *pVertex;			// array
	int front;
	int rear;
} ArrayGraph;

//create
ArrayGraph* createArrayGraph(int maxVertexCount, int type);

//delete
void deleteArrayGraph(ArrayGraph** pGraph);

//is empty
int isEmptyAG(ArrayGraph* pGraph);

//add vertex
int addVertexAG(ArrayGraph* pGraph, int vertexID);

//add edge
int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID);
int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight);

//is vertex ok
int checkVertexValid(ArrayGraph* pGraph, int vertexID);

//remove vertex
int removeVertexAG(ArrayGraph* pGraph, int vertexID);

//remove edge
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID);

//display
void displayArrayGraph(ArrayGraph* pGraph);
#endif

#ifndef _COMMON_GRAPH_DEF_
#define _COMMON_GRAPH_DEF_

#define USED				1
#define NOT_USED			0

#define SUCCESS				1
#define FAIL				0

#define TRUE				1
#define FALSE				0

#define GRAPH_UNDIRECTED	1 // not arrow
#define GRAPH_DIRECTED		2 // arrow
#endif
