// Author: Harein Abeysekera

#include "BetterPriorityQueue.h"
#include <sstream>
#include <algorithm>

using namespace std;

// Check if a node with the same gnode ID exists in the queue
bool BetterPriorityQueue::Contains(const BPQNode& node) const {
    for (const auto& elem : this->c) { 
        if (node == elem) { 
            return true; // match found based on gnode ID
        }
    }
    return false; // returns false if no match found
}

// Update the priority of a node if the new one is lower; rebuild heap if changed
bool BetterPriorityQueue::Update(const BPQNode& node) {
    bool priorityChanged = false;

    for (auto& entry : this->c) {
        if (node == entry) {
            if (node.pri < entry.pri) {
                entry.pri = node.pri;
                priorityChanged = true;
            }
            break;
        }
    }

    if (priorityChanged) {
        // restore the heap property after modifying a node's priority
        make_heap(this->c.begin(), this->c.end(), this->comp);
    }

    return priorityChanged;
}

// String representation of the full queue, and it is sorted by priority then ID
string BetterPriorityQueue::ToString() const {
    ostringstream output;
    output << "[";

    vector<BPQNode> temp(this->c);  // copy to preserve original heap structure
    sort(temp.begin(), temp.end(), [](const BPQNode& a, const BPQNode& b) {
        // sort primarily by priority, then by gnode if tie
        if (a.pri != b.pri) {
            return a.pri < b.pri;
        }
        return a.gnode < b.gnode;
    });

    for (size_t i = 0; i < temp.size(); ++i) {
        output << BPQNodeToString(temp[i]);
        if (i < temp.size() - 1) {
            output << ", ";
        }
    }

    output << "]";
    return output.str();
}

// Convert a single BPQNode to a string format
string BetterPriorityQueue::BPQNodeToString(const BPQNode& node) {
    return "(" + to_string(node.gnode) + ", pri: " + to_string(node.pri) + ")";
}