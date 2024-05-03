
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <climits>
#include <string>

using namespace std;

#define     MAX_VERTEX              500

#define     UNDIRECTEDGRAPH         0
#define     DIRECTEDGRAPH           1

#define     DISPLAYGRAPH            0
#define     DEPTHFIRSTTRAVERSAL     1
#define     BREADTHFIRSTTRAVERSAL   2
#define     DEPTHTOPOSORT           3
#define     BREADTHTOPOSORT         4
#define     MINIMUMSPANTREE         5

#define     INCREASINGORDER         0
#define     DECREASINGORDER         1

struct VertexType{
    char        strName[10];
    float       weight;
    bool        isMarked;
    VertexType  *next;
    VertexType()
    {
        strcpy(strName, "");
        weight = 0;
        isMarked = false;
        next = NULL;
    }
};
struct GraphNode{
    VertexType  vertex;
    VertexType  *adjVertex;
    int         indegree;
    int         outdegree;
    bool        isMarked;
    GraphNode(){
        indegree = 0;
        outdegree = 0;
        isMarked = false;
        adjVertex = NULL;
    }
};

struct Graph{
    int         nGraphType;
    int         nOperation;
    int         nVertexNum;
    VertexType  startVertex;
    int         nOrder;

    GraphNode   graph[MAX_VERTEX];
};

Graph   myGraph;

