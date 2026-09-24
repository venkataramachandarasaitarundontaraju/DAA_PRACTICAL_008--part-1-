#include <iostream>
#include <unordered_set>
using namespace std;
struct Node {
    int id;
    struct Edge* edgeHead; 

    Node(int identifier) {
        id = identifier;
        edgeHead = nullptr;
    }
};
struct Edge {
    Node* destination;
    Edge* nextEdge; 
    Edge(Node* dest) {
        destination = dest;
        nextEdge = nullptr;
    }
};
struct QueueNode {
    Node* graphNode;
    QueueNode* next;
    QueueNode(Node* n) {
        graphNode = n;
        next = nullptr;
    }
};
class FIFOQueue {
    QueueNode* frontNode;
    QueueNode* rearNode;
public:
    FIFOQueue() {
        frontNode = nullptr;
        rearNode = nullptr;
    }
    bool isEmpty() {
        return frontNode == nullptr;
    }
    void enqueue(Node* n) {
        QueueNode* temp = new QueueNode(n);
        if (rearNode == nullptr) {
            frontNode = rearNode = temp;
            return;
        }
        rearNode->next = temp;
        rearNode = temp;
    }
    Node* dequeue() {
        if (isEmpty()) return nullptr;
        QueueNode* temp = frontNode;
        Node* nodeData = temp->graphNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp; 
        return nodeData;
    }
};

class Graph {
    int capacity;
    int nodeCount;
    Node** nodes; 
public:
    Graph(int maxVertices) {
        capacity = maxVertices;
        nodeCount = 0;
        nodes = new Node*[maxVertices];
        for (int i = 0; i < maxVertices; ++i) {
            nodes[i] = nullptr;
        }
    }
    ~Graph() {
        for (int i = 0; i < nodeCount; ++i) {
            if (nodes[i] != nullptr) {
                Edge* currentEdge = nodes[i]->edgeHead;
                while (currentEdge != nullptr) {
                    Edge* tempEdge = currentEdge;
                    currentEdge = currentEdge->nextEdge;
                    delete tempEdge;
                }
                delete nodes[i];
            }
        }
        delete[] nodes;
    }
    void addNode(int id) {
        if (nodeCount < capacity) {
            nodes[nodeCount++] = new Node(id);
        }
    }
    Node* findNode(int id) {
        for (int i = 0; i < nodeCount; ++i) {
            if (nodes[i] != nullptr && nodes[i]->id == id) {
                return nodes[i];
            }
        }
        return nullptr;
    }
    void addEdge(int srcId, int destId) {
        Node* srcNode = findNode(srcId);
        Node* destNode = findNode(destId);
        if (srcNode == nullptr || destNode == nullptr) return;
        Edge* newEdge1 = new Edge(destNode);
        newEdge1->nextEdge = srcNode->edgeHead;
        srcNode->edgeHead = newEdge1;
        Edge* newEdge2 = new Edge(srcNode);
        newEdge2->nextEdge = destNode->edgeHead;
        destNode->edgeHead = newEdge2;
    }
    void BFS(int startId) {
        Node* startNode = findNode(startId);
        if (startNode == nullptr) return;
        FIFOQueue q;
        unordered_set<int> visited;
        visited.insert(startNode->id);
        q.enqueue(startNode); 
        cout << "BFS Traversal using manual FIFO Queue: ";
        while (!q.isEmpty()) {
            Node* currentNode = q.dequeue();
            cout << currentNode->id << " ";

            Edge* currentEdge = currentNode->edgeHead;
            while (currentEdge != nullptr) {
                Node* neighborNode = currentEdge->destination;

                if (visited.find(neighborNode->id) == visited.end()) {
                    visited.insert(neighborNode->id);
                    q.enqueue(neighborNode); 
                }
                currentEdge = currentEdge->nextEdge;
            }
        }
        cout << endl;
    }
};
int main() {
    Graph g(5);
    g.addNode(10);
    g.addNode(20);
    g.addNode(30);
    g.addNode(40);
    g.addNode(50);
    g.addEdge(10, 20);
    g.addEdge(10, 30);
    g.addEdge(20, 40);
    g.addEdge(20, 50);
    g.addEdge(30, 50);
    g.BFS(10);
    return 0;
}

  
