// Ass1.cpp : Defines the entry point for the console application.
//
#ifndef _common_h_
#include "common.h"
#define _common_h_
#endif

#ifndef _assignment2_cpp_
#include "assignment2.cpp"
#define _assignment2_cpp_
#endif

void writeFile(char* filename, string str)
{
	char* file_name = filename;
	FILE* f = 0;

	f = fopen(file_name, "w");
	if (f == NULL)
		return;

    char    s[2000];

    strcpy(s, str.c_str());

	fwrite(s, strlen(s), 1, f);

	fclose(f);
}

int main()
{
    string  result;

    for(int i = 0; i<MAX_VERTEX; i++)
        strcpy(myGraph.graph[i].vertex.strName, "-1");

    readFile(myGraph, "input.txt");

    switch(myGraph.nOperation)
    {
    case DEPTHFIRSTTRAVERSAL:
        result = depthFirstTraversal(myGraph,myGraph.startVertex);
        writeFile("output.txt", result);
        break;
    case BREADTHFIRSTTRAVERSAL:
        result = breadthFirstTraversal(myGraph,myGraph.startVertex);
        writeFile("output.txt", result);
        break;
    case DEPTHTOPOSORT:
        result = depthTopoSort(myGraph);
        writeFile("output.txt", result);
        break;
    case BREADTHTOPOSORT:
        result = breadthTopoSort(myGraph);
        writeFile("output.txt", result);
        break;
    case MINIMUMSPANTREE:
        result = minSpanTree(myGraph, myGraph.startVertex);
        writeFile("output.txt", result);
        break;
    }

    return 0;
}




