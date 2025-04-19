// Author: Harein Abeysekera 

#ifndef BETTER_PRIORITY_QUEUE_H
#define BETTER_PRIORITY_QUEUE_H

#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <climits>

#define nodekey_t unsigned long long int
#define INVALID_NODE_KEY ULLONG_MAX

// Struct to represent a node in the priority queue
struct BPQNode {
	int pri = INT_MAX;  // Priority value and the lower the value the better
	bool visited = false;
	nodekey_t gnode = INVALID_NODE_KEY;

	// Comparison operator for priority. 
	// lower priority means higher precedence
	bool operator<(const BPQNode& other) const {
		return pri < other.pri;
	}


	// Greater-than operator used for std::greater in priority queue
	bool operator>(const BPQNode& other) const {
		return pri > other.pri;
	}

	// Equality operator compares nodes by their unique key
	bool operator==(const BPQNode& other) const {
		return gnode == other.gnode;
	}
};

class BetterPriorityQueue : public std::priority_queue<
	BPQNode,
	// for a .h file in c++ it bad to use namespace std as it could lead to name collisions for any file that uses this header file
	std::vector<BPQNode>, // Store nodes in a vector
	std::greater<BPQNode> // Use greater-than to make this a min-heap
> {
public:
	bool Contains(const BPQNode& n) const; 	// Check if a node with the same gnode exists in the queue
	bool Update(const BPQNode& n); 	// Update a node's priority if the new one is lower
	std::string ToString() const;
	static std::string BPQNodeToString(const BPQNode& n);
};

#endif