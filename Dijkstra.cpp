// Author: Harein Abeysekera

#include "Dijkstra.h"
#include "BetterPriorityQueue.h"
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <stdexcept>

using namespace std;

// Dijkstra's algorithm to find the shortest path from 'start' to 'end' in a weighted graph
//The time complexity is O(log V)

int dijkstra(nodekey_t start, nodekey_t end, const Graph* g) {
    // Checks if both nodes exist in the graph
    if (!g->IsPresent(start) || !g->IsPresent(end)) {
        throw invalid_argument("Start or end node does not exist.");
    }

    BetterPriorityQueue queue; // priority queue to select next best node
    unordered_map<nodekey_t, int> distances; // stores shortest known distances
    unordered_set<nodekey_t> visited; // tracks visited nodes to avoid unecessary redos

    // Initialize all distances to infinity (INT_MAX)
    for (nodekey_t node : g->GetNodes()) {
        distances[node] = INT_MAX;
    }
    distances[start] = 0; // distance to start node is zero

    // Push the start node into the queue
    BPQNode startNode;
    startNode.pri = 0;
    startNode.gnode = start;
    queue.push(startNode);

    // Main Dijkstra loop
    while (!queue.empty()) {
        BPQNode current = queue.top(); // get the node with the smallest known distance
        queue.pop();

        cout << "Visiting node: " << current.gnode << ", pri: " << current.pri << endl;

        // Skip nodes we've already finalized
        if (visited.count(current.gnode)) continue;
        visited.insert(current.gnode);

        // If we've reached the destination, then return the distance
        if (current.gnode == end) {
            return current.pri;
        }

        // Explore neighbors of the current node
        for (const GraphEdge* edge : g->GetOutwardEdgesFrom(current.gnode)) {
            nodekey_t neighbor = edge->to;
            int newDist = current.pri + edge->weight; // calculate distance through current node

            cout << "  Checking neighbor: " << neighbor << ", edge weight: " << edge->weight
                 << ", current distance: " << distances[neighbor]
                 << ", new distance: " << newDist << endl;

            // If a shorter path to neighbor is found, update and add to queue
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;

                BPQNode node;
                node.pri = newDist;
                node.gnode = neighbor;
                queue.push(node);
            }
        }
    }

    // If the loop completes without returning, unfortunatley no path was found
    return -1;
}