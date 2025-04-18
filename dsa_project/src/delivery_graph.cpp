#include "delivery_graph.h"



// DeliveryGraph class implementation
void DeliveryGraph::addEdge(const string& u,const string& v,int weight){



    adj[u].push_back({v, weight});
    adj[v].push_back({u, weight}); // Assuming undirected routes

}


// Load the graph from a file
void DeliveryGraph::loadGraph(const string& filename){

    ifstream in(filename);
    if(!in){

        cerr << "❌ Error opening file: " << filename << "\n";   //
        cerr << "Error loading delivery routes.\n";

        return;
    }

    string u,v;
    int weight;
    while (in>>u>>v>>weight){


        addEdge(u,v,weight);
    }

    in.close();
    
}

// Save the graph to a file
void DeliveryGraph::saveGraph(const string& filename){


    ofstream out(filename);
    for (auto& [u, neighbors] : adj){

        for(auto& [v, weight] : neighbors){

            if(u<v) // Avoid duplicate writing
                out << u << " " << v << " " << weight << "\n";

        }
    }

    out.close();
}

// Dijkstra's algorithm for shortest path
void DeliveryGraph::dijkstra(const string& start, const string& end){

    unordered_map<string, int> dist;
    unordered_map<string, string> parent;
    for (auto& [node, _] : adj)
        dist[node] = INT_MAX;

    dist[start]=0;
    priority_queue<pair<int,string>, vector<pair<int, string>>, greater<>> pq;
    pq.push({0, start});

    while(!pq.empty()){

        auto [d, node] = pq.top();
        pq.pop();

        for(auto& [neighbor, weight] : adj[node]){
            if (dist[neighbor] > dist[node] + weight){

                dist[neighbor] = dist[node] + weight;
                parent[neighbor] = node;

                pq.push({dist[neighbor], neighbor});
            }
        }

    }

    if (dist[end] == INT_MAX){
        cout << "❌ No delivery route found from " << start << " to " << end << ".\n";
        return;
    }


    stack<string> path;
    string current = end;
    while (current != start){
        
        path.push(current);
        current = parent[current];
    }
    path.push(start);

    cout << "🚚 Shortest Path: ";
    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " → ";
    }
    cout << "\nEstimated Delivery Distance: " << dist[end] << " km/min\n";

}

// Display the graph
void DeliveryGraph::displayGraph(){


    for (auto& [u, neighbors] : adj){

        cout << u << ": ";
        for (auto& [v, weight] : neighbors) {
            cout << "(" << v << ", " << weight << ") ";
        }
        cout << "\n";

    }

}


// Get the adjacency list
unordered_map<string, vector<pair<string, int>>>& DeliveryGraph::getAdjList(){


    return adj;
}
