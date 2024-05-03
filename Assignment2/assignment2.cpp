//#include "common.h"

#ifndef _common_h_
#include "common.h"
#define _common_h_
#endif

#include <stack>
#include <queue>

void sortArrayGraphNode(Graph &myGraph){
    bool flag = false;
    while(flag == false){
        flag = true;
        for(int i = 0; i < myGraph.nVertexNum - 1; i++){
            if(myGraph.nOrder == 0){
                if(strcmp(myGraph.graph[i].vertex.strName, myGraph.graph[i+1].vertex.strName) > 0){
                    swap(myGraph.graph[i], myGraph.graph[i+1]);
                    flag = false;
                }
            }
            else{
                if(strcmp(myGraph.graph[i].vertex.strName, myGraph.graph[i+1].vertex.strName) < 0){
                    swap(myGraph.graph[i], myGraph.graph[i+1]);
                    flag = false;
                }
            }
        }
    }
}

void sortAdjencyList(GraphNode &graph, int nOrder){
    VertexType *head = graph.adjVertex;
    if(head == NULL || head->next == NULL) return;
    bool flag = false;
    while(flag == false){
        flag = true;
        VertexType *walker = head;
        while(walker->next != NULL){
            if(nOrder == 0){
                if(strcmp(walker->strName, walker->next->strName) > 0){
                    swap(walker->strName, walker->next->strName);
                    swap(walker->weight, walker->next->weight);
                    flag = false;
                }
            }
            else{
                if(strcmp(walker->strName, walker->next->strName) < 0){
                    swap(walker->strName, walker->next->strName);
                    swap(walker->weight, walker->next->weight);
                    flag = false;
                }
            }
            walker = walker->next;
        }
    }
}

int lengthList(VertexType *head){
    VertexType *temp = head;
    int length = 0;
    while(temp != NULL){
        length++;
        temp = temp->next;
    }
    return length;
}

void updateOutDegree(Graph &myGraph){
    for(int i = 0; i < myGraph.nVertexNum; i++){
        int outDegree = lengthList(myGraph.graph[i].adjVertex);
        myGraph.graph[i].outdegree = outDegree;
    }
}

void updateInDegree(Graph &myGraph){
    for(int i = 0; i < myGraph.nVertexNum; i++){
        VertexType *temp = myGraph.graph[i].adjVertex;
        while(temp != NULL){
            for(int j = 0; j < myGraph.nVertexNum; j++){
                if(strcmp(temp->strName, myGraph.graph[j].vertex.strName) == 0){
                    myGraph.graph[j].indegree++;
                    break;
                }
            }
            temp = temp->next;
        }
    }
}

int readFile(Graph &myGraph, char* filename )
{
#define MAX_CHARACTER_PER_LINE 1000
    char* file_name = filename;
    FILE* f = 0;

    f = fopen(file_name, "r");
    if (f == NULL)	//file not found || cannot read
		return 0;

    char str[MAX_CHARACTER_PER_LINE];

    fgets(str, MAX_CHARACTER_PER_LINE, f);
    sscanf(str, "%d", &myGraph.nGraphType);

    fgets(str, MAX_CHARACTER_PER_LINE, f);
    sscanf(str, "%d", &myGraph.nOperation);

    fgets(str, MAX_CHARACTER_PER_LINE, f);
    sscanf(str, "%d", &myGraph.nVertexNum);

    fgets(str, MAX_CHARACTER_PER_LINE, f);

    char *token = strtok(str, " ");
    int i = 0;
    while(token != NULL){
        sscanf(token, "%s", myGraph.graph[i].vertex.strName);
        i++;
        token = strtok(NULL, " ");
    }

    fgets(str, MAX_CHARACTER_PER_LINE, f);
    sscanf(str, "%s", myGraph.startVertex.strName);

    fgets(str, MAX_CHARACTER_PER_LINE, f);
    sscanf(str, "%d", &myGraph.nOrder);

    for(i = 0; i < myGraph.nVertexNum; i++){
        fgets(str, MAX_CHARACTER_PER_LINE, f);
        token = strtok(str, " ");
        int j = 0;
        while(token != NULL && j < myGraph.nVertexNum){
            float weight;
            sscanf(token, "%f", &weight);
            if(weight != 0){
                VertexType* newVertex = new VertexType();
                strcpy(newVertex->strName, myGraph.graph[j].vertex.strName);
                newVertex->next = NULL;
                newVertex->weight = weight;
                if(myGraph.graph[i].adjVertex == NULL)
                    myGraph.graph[i].adjVertex = newVertex;
                else{
                    VertexType *temp = myGraph.graph[i].adjVertex;
                    while(temp->next != NULL)
                        temp = temp->next;
                    temp->next = newVertex;
                }
            }
            token = strtok(NULL, " ");
            j++;
        }
    }
    fclose(f);

    sortArrayGraphNode(myGraph);

    for(int i = 0; i < myGraph.nVertexNum; i++){
        sortAdjencyList(myGraph.graph[i], myGraph.nOrder);
    }

    updateInDegree(myGraph);
    updateOutDegree(myGraph);

    return 1;
}

void isMarked(Graph &myGraph, VertexType visit){
    for(int i = 0; i < myGraph.nVertexNum; i++){
        if(strcmp(visit.strName, myGraph.graph[i].vertex.strName) == 0){
            myGraph.graph[i].vertex.isMarked = true;
            myGraph.graph[i].isMarked = true;
        }
        VertexType *temp = myGraph.graph[i].adjVertex;
        while(temp != NULL){
            if(strcmp(temp->strName, visit.strName) == 0){
                temp->isMarked = true;
                break;
            }
            temp = temp->next;
        }
    }
}

string depthFirstTraversal(Graph &myGraph, VertexType startVertex)
{
    string result = "";
    for(int i = 0; i < myGraph.nVertexNum; i++){
        myGraph.graph[i].vertex.isMarked = false;
        myGraph.graph[i].isMarked = false;
        VertexType *temp = myGraph.graph[i].adjVertex;
        while(temp != NULL){
            temp->isMarked = false;
            temp = temp->next;
        }
    }

    stack<VertexType> myStack;
    myStack.push(myGraph.startVertex);
    isMarked(myGraph, myGraph.startVertex);

    while(!myStack.empty()){
        VertexType visit = myStack.top();
        myStack.pop();
        result = result + visit.strName + " ";
        VertexType *adjList;
        for(int i = 0; i < myGraph.nVertexNum; i++){
            if(strcmp(visit.strName, myGraph.graph[i].vertex.strName) == 0){
                adjList = myGraph.graph[i].adjVertex;
                break;
            }
        }
        while(adjList != NULL){
            if(adjList->isMarked == false){
                myStack.push(*adjList);
                isMarked(myGraph, *adjList);
            }
            adjList = adjList->next;
        }

    }

    for(int i = 0; i < myGraph.nVertexNum; i++){
        if(myGraph.graph[i].isMarked == false){
            isMarked(myGraph, myGraph.graph[i].vertex);
            myStack.push(myGraph.graph[i].vertex);
            while(!myStack.empty()){
                VertexType visit = myStack.top();
                myStack.pop();
                result = result + visit.strName + " ";
                VertexType *adjList;
                for(int i = 0; i < myGraph.nVertexNum; i++){
                    if(strcmp(visit.strName, myGraph.graph[i].vertex.strName) == 0){
                        adjList = myGraph.graph[i].adjVertex;
                        break;
                    }
                }
                while(adjList != NULL){
                    if(adjList->isMarked == false){
                        myStack.push(*adjList);
                        isMarked(myGraph, *adjList);
                    }
                    adjList = adjList->next;
                }
            }
        }
    }

    int lastIndex = result.length();
    result[lastIndex - 1] = '\0';
    return result;
}
string breadthFirstTraversal(Graph &myGraph, VertexType startVertex)
{
    string result = "";

    for(int i = 0; i < myGraph.nVertexNum; i++){
        myGraph.graph[i].vertex.isMarked = false;
        myGraph.graph[i].isMarked = false;
        VertexType *temp = myGraph.graph[i].adjVertex;
        while(temp != NULL){
            temp->isMarked = false;
            temp = temp->next;
        }
    }

    queue<VertexType> myQueue;
    myQueue.push(myGraph.startVertex);
    isMarked(myGraph, myGraph.startVertex);

    while(!myQueue.empty()){
        VertexType visit = myQueue.front();
        myQueue.pop();
        result = result + visit.strName + " ";
        VertexType *adjList;
        for(int i = 0; i < myGraph.nVertexNum; i++){
            if(strcmp(visit.strName, myGraph.graph[i].vertex.strName) == 0){
                adjList = myGraph.graph[i].adjVertex;
                break;
            }
        }
        while(adjList != NULL){
            if(adjList->isMarked == false){
                myQueue.push(*adjList);
                isMarked(myGraph, *adjList);
            }
            adjList = adjList->next;
        }

    }

    for(int i = 0; i < myGraph.nVertexNum; i++){
        if(myGraph.graph[i].isMarked == false){
            isMarked(myGraph, myGraph.graph[i].vertex);
            myQueue.push(myGraph.graph[i].vertex);
            while(!myQueue.empty()){
                VertexType visit = myQueue.front();
                myQueue.pop();
                result = result + visit.strName + " ";
                VertexType *adjList;
                for(int i = 0; i < myGraph.nVertexNum; i++){
                    if(strcmp(visit.strName, myGraph.graph[i].vertex.strName) == 0){
                        adjList = myGraph.graph[i].adjVertex;
                        break;
                    }
                }
                while(adjList != NULL){
                    if(adjList->isMarked == false){
                        myQueue.push(*adjList);
                        isMarked(myGraph, *adjList);
                    }
                    adjList = adjList->next;
                }
            }
        }
    }

    int lastIndex = result.length();
    result[lastIndex - 1] = '\0';
    return result;
}


string depthTopoSort(Graph &myGraph)
{
    string result = "";

    stack<VertexType> myStack;

    for(int i = 0; i < myGraph.nVertexNum; i++){
        if(myGraph.graph[i].outdegree == 0){
            myStack.push(myGraph.graph[i].vertex);
        }
    }

    while(!myStack.empty()){
        VertexType visit = myStack.top();
        myStack.pop();
        result = string(visit.strName) + " " + result;
        for(int i = 0; i < myGraph.nVertexNum; i++){
            VertexType *adjList = myGraph.graph[i].adjVertex;
            while(adjList != NULL){
                if(strcmp(adjList->strName, visit.strName) == 0){
                    myGraph.graph[i].outdegree--;
                    if(myGraph.graph[i].outdegree == 0){
                        myStack.push(myGraph.graph[i].vertex);
                    }
                    break;
                }
                adjList = adjList->next;
            }
        }
    }

    int n = result.length();

    /*for (int i = 0; i < n / 2; i++)
        swap(result[i], result[n - i - 1]);

    result.erase(0,1);*/

    int lastIndex = result.length();
    result[lastIndex - 1] = '\0';

    return result;
}
string breadthTopoSort(Graph &myGraph)
{
    string result = "";

    queue<VertexType> myQueue;

    for(int i = 0; i < myGraph.nVertexNum; i++){
        if(myGraph.graph[i].indegree == 0){
            myQueue.push(myGraph.graph[i].vertex);
        }
    }

    while(!myQueue.empty()){
        VertexType visit = myQueue.front();
        myQueue.pop();
        result = result + visit.strName + " ";
        VertexType *adjList;
        for(int i = 0; i < myGraph.nVertexNum; i++){
            if(strcmp(visit.strName, myGraph.graph[i].vertex.strName) == 0){
                adjList = myGraph.graph[i].adjVertex;
                break;
            }
        }
        
        while(adjList != NULL){
            for(int i = 0; i < myGraph.nVertexNum; i++){
                if(strcmp(adjList->strName, myGraph.graph[i].vertex.strName) == 0){
                    myGraph.graph[i].indegree--;
                    if(myGraph.graph[i].indegree == 0){
                        myQueue.push(myGraph.graph[i].vertex);
                    }
                }
            }
            adjList = adjList->next;
        }
    }

    int lastIndex = result.length();
    result[lastIndex - 1] = '\0';

    return result;
}
string minSpanTree(Graph &myGraph, VertexType startVertex)
{
    string result="";

    int numVertexMarked = 0;

    int weightTotal = 0;

    for(int i = 0; i < myGraph.nVertexNum; i++){
        myGraph.graph[i].vertex.isMarked = false;
        myGraph.graph[i].isMarked = false;
        VertexType *temp = myGraph.graph[i].adjVertex;
        while(temp != NULL){
            temp->isMarked = false;
            temp = temp->next;
        }
    }

    VertexType visit = myGraph.startVertex;
    isMarked(myGraph,visit);

    VertexType smallest;

    VertexType *adjList;

    for(int i = 0; i < myGraph.nVertexNum; i++){
        if(strcmp(visit.strName, myGraph.graph[i].vertex.strName) == 0){
            adjList = myGraph.graph[i].adjVertex;
            break;
        }
    }

    smallest = *adjList;

    while(adjList != NULL){
        if(adjList->weight < smallest.weight){
            smallest = *adjList;
        }
        adjList = adjList->next;
    }

    weightTotal += smallest.weight;
    numVertexMarked+=2;
    isMarked(myGraph, smallest);

    while(numVertexMarked < myGraph.nVertexNum){

        smallest.weight = INT_MAX;

        for(int i = 0; i < myGraph.nVertexNum; i++){
            if(myGraph.graph[i].isMarked == true){
                adjList = myGraph.graph[i].adjVertex;
                while(adjList != NULL){
                    if(adjList->weight < smallest.weight && adjList->isMarked == false){
                        smallest = *adjList;
                    }
                    adjList = adjList->next;
                }
            }
        }

        weightTotal += smallest.weight;
        numVertexMarked++;
        isMarked(myGraph,smallest);
    }

    result = to_string(weightTotal);

    return result;
}
