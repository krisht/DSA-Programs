/**
 * Krishna Thiyagarajan
 * DSA II - Project #3
 * Graph.cpp
 * Implements all data members and member functions defined in Graph.h
 */

#include "Graph.h"
#include "Heap.h"
#include <fstream>
#include <stack>

Graph::Graph() {
    nodeTable = new HashTable(0);
}

/**
 * Reads graph from a file given a certain format
 * @param file File location and name
 */
void Graph::readFromFile(string &file) {
    ifstream reader(file.c_str());
    string vertex1, vertex2;
    int distance;

    while (!reader.eof()) {
        reader >> vertex1 >> vertex2 >> distance;

        if (!nodeTable->contains(vertex1)) {
            Node *newNode = new Node();
            newNode->name = vertex1;
            nodeTable->insert(vertex1, newNode);
            nodeList.push_back(newNode);
        }

        if (!nodeTable->contains(vertex2)) {
            Node *newNode = new Node();
            newNode->name = vertex2;
            nodeTable->insert(vertex2, newNode);
            nodeList.push_back(newNode);
        }

        bool v1exists, v2exists;

        Node *v1 = static_cast<Node *>(nodeTable->getPointer(vertex1, v1exists));
        Node *v2 = static_cast<Node *>(nodeTable->getPointer(vertex2, v2exists));

        if (v1exists && v2exists)
            v1->insertEdge(v2, distance);
        else {
            cerr << "Fatality!";
            exit(-1);
        }
    }

    reader.close();
}

/**
 * Dijkstra's algorithm to calculate least distance to all verticies
 * @param vertex Starting vertex
 */
void Graph::dijkstra(string &vertex, string &file) {
    if (nodeList.empty()) {
        cout << "Am I being tricked into becoming an evil AI?" << endl;
        return;
    }

    clock_t start = clock();

    bool v1exists;
    Node *v1 = static_cast<Node *>(nodeTable->getPointer(vertex, v1exists));

    if (!v1exists) {
        cerr << "Fatality!";
        exit(-1);
    }

    v1->dist = 0;
    v1->prev = v1;

    Heap *heap = new Heap(nodeList.size());

    for (int kk = 0; kk < nodeList.size(); kk++)
        heap->insert(nodeList[kk]->name, nodeList[kk]->dist, &nodeList[kk]);


    int currDist;

    Node *nextVertex;

    while (heap->deleteMin(&vertex, &currDist, &nextVertex) == 0) {
        bool tempBool;

        nextVertex = static_cast<Node *>(nodeTable->getPointer(vertex, tempBool));
        nextVertex->known = true;

        if (nextVertex->prev == nullptr)
            continue;

        for (int kk = 0; kk < nextVertex->edges.size(); kk++)
            if (!nextVertex->edges[kk].next->known) {
                int newDist = nextVertex->edges[kk].cost + currDist;
                if (newDist >= nextVertex->edges[kk].next->dist)
                    continue;
                nextVertex->edges[kk].next->dist = newDist;
                heap->setKey(nextVertex->edges[kk].next->name, nextVertex->edges[kk].next->dist);
                nextVertex->edges[kk].next->prev = nextVertex;
            }
    }

    clock_t end = clock();

    double diff = ((double) (end - start)) / CLOCKS_PER_SEC;
    writeOut(v1, diff, file);
}

/**
 * Writes information to file about vertex with time of running
 * @param vertex     Vertex to start from to run Dijkstra's
 * @param difference Time taken to run Dijkstra's
 */
void Graph::writeOut(Node *vertex, double difference, string &file) {
    cout << "Total time is: " << difference << endl;

    string outputFile=file; 

    ofstream readOut(outputFile.c_str());

    for (int kk = 0; kk < nodeList.size(); kk++) {
        readOut << nodeList[kk]->name << ": ";
        if (nodeList[kk]->prev == nullptr)
            readOut << "NO PATH" << endl;
        else {
            readOut << nodeList[kk]->dist << " ";

            stack<string> path;

            if (nodeList[kk] != vertex)
                path.push(nodeList[kk]->name);

            Node *trace = nodeList[kk]->prev;

            while (trace != vertex) {
                path.push(trace->name);
                trace = trace->prev;
            }

            readOut << "[" << vertex->name;

            while (!path.empty()) {
                readOut << ", " << path.top();
                path.pop();
            }

            readOut << "]" << endl;
        }
    }
    readOut.close();
}

/**
 * Checks if a vertex exists in a graph
 * @param  vertex Vertex to start from
 * @return        Boolean indicating whether it was there
 */
bool Graph::contains(string &vertex) {
    return nodeTable->contains(vertex);
}

/**
 * Inserting an edge into the graph
 * @param next 	Pointer to the Node
 * @param cost 	Cost of the edge
 */
void Graph::Node::insertEdge(Node *next, int cost) {
    Edge newEdge;
    newEdge.next = next;
    newEdge.cost = cost;
    edges.push_back(newEdge);
}