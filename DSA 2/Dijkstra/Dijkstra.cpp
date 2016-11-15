#include <iostream>
#include "Graph.h"

using namespace std;

int main(int argc, char** argv) {
    Graph* graph = new Graph();
    string name = argv[1]; 
    graph->readFromFile(name);
    string vertex = argv[2];
	if(!(graph->contains(vertex)))
		exit(-1);
	string outputfile = argv[3]; 
    graph->dijkstra(vertex, outputfile);
    return 0;
}
