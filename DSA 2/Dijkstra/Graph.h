/**
 * Krishna Thiyagarajan
 * DSA II - Project #3
 * Graph.h
 * Defines data members and member functions for implementing Dijkstra's
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <climits>
#include "HashTable.h"
#include <iostream>

using namespace std;

class Graph {
public:
    Graph();
    ~Graph();
    void readFromFile(string &name);
    void dijkstra(string &vertex, string &file);
    bool contains(string &vertex);

private:
    class Node{
    private:
        class Edge{
        public: Node* next;
            int cost = 1;
        };

    public:
        bool known = false;
        string name = "";
        Node* prev  = nullptr;
        int dist = INT_MAX;
        vector <Edge> edges;
        void insertEdge(Node* next, int cost=1);
    };

    vector<Node*> nodeList;
    HashTable* nodeTable;
    void writeOut(Node* V1, double diff, string &file);
};

#endif //GRAPH_H
