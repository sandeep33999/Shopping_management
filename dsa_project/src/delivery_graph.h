#ifndef DELIVERY_GRAPH_H
#define DELIVERY_GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>
#include <sstream>
#include <stack>

using namespace std;

class DeliveryGraph{

private:
    unordered_map<string,vector<pair<string,int>>> adj;


public:
    void addEdge(const string& u, const string& v, int weight);
    void loadGraph(const string& filename);
    void saveGraph(const string& filename);
    void dijkstra(const string& start, const string& end);
    void displayGraph();

    unordered_map<string, vector<pair<string,int>>>& getAdjList();

};

#endif
