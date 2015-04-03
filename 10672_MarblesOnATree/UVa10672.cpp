/* UVa problem: 10672 - MarblesOnATree
 *
 * Topic: Graph Traversal
 *
 * Level: trivial
 *
 * Brief problem description:
 *  Given a tree of N nodes with N marbles distributed randomly amidst the nodes.
 *  Find the minimum moves neccesary to move marbles such that each node
 *  has exactly 1 marble. (A move is adding/subtracting a single marble
 *  between directly connected nodes).
 *
 * Solution Summary:
 *  I realized that if you balance the levels of the tree
 *  one at a time starting at the lower levels (highest height), by the time
 *  you reach the top, all nodes will have 1 marble. To get the
 *  nodes ordered from lowest to highest level I just used bfs
 *  and as I encountered each node I added it to a vector.
 *  Traversing this vector in reverse gave me the order of nodes
 *  I should use when balancing the marbles.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *
 * I hereby certify that I have produced the following solution myself
 * using the resources listed above in accordance with the CMPUT 403
 * collaboration policy.
 *
 * --- Tamara Bain
 *
 * Language: C++11
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <cassert>
#define UNSET -1

using namespace std;


// node holds the number of marbles, children and parent
struct Node {
    int marbles = 0;
    int parent = UNSET;
    int label = UNSET;

    vector<int> neighbours;
};


//data structure to hold the tree
struct Tree {

    Tree(): size(0), root(UNSET) {}

    // clear nodes, ordering vector, and visited vector
    void initialize(const int &size) {
        this->size = size;
        this->nodes.clear();
        this->visited.clear();
        this->order.clear();
        this->root = UNSET;

        for(int i = 0; i < size; ++i) {
            nodes.emplace_back(Node());
            nodes[i].label = i;
            visited.emplace_back(false);
        }
    }

    // override [] for access to nodes
    Node& operator[](const int &i){
        assert(i < (int)nodes.size());
        return nodes[i];
    }

    // add a child to the given node
    void connectChild(const int &i, const int &j) {
        Node &parent = (*this)[i];
        Node &child = (*this)[j];
        parent.neighbours.emplace_back(j);
        child.parent = i;
    }

    // find the root node and save it
    void setRoot() {
        if (root != UNSET)
            return;

        for(int i = 0; i < size; ++i) {
            if ((*this)[i].parent == UNSET) {
                root = i;
                break;
            }
        }
    }

    // used to get the order of the nodes by level
    // essentially a bfs that add node indexes to a vector
    void levelOrder() {
        queue<int> q;

        setRoot();
        visited[root] = true;
        order.push_back(root);
        q.push(root);

        while(!q.empty()) {
            int current = q.front(); q.pop();
            for(int i = 0; i < (int)(*this)[current].neighbours.size(); ++i) {
                int neighbour = (*this)[current].neighbours[i];
                if (!visited[neighbour]) {
                    visited[neighbour] = true;
                    order.push_back(neighbour);
                    q.push(neighbour);
                }

            }
        }
    }

    vector<unsigned int> order;
    private:
        int size;
        int root;
        vector<Node> nodes;
        vector<bool> visited;
};

int main() {
    Tree graph;
    int n, vertex, marbles, children, child, moves;

    while(scanf("%d", &n), n) {

        graph.initialize(n);
        moves = 0;

        // read in the graph data
        for(int i = 0; i < n; ++i) {
            scanf("%d %d %d", &vertex, &marbles, &children);
            graph[vertex-1].marbles = marbles;

            for (int j = 0; j < children; ++j) {
                scanf("%d", &child);
                graph.connectChild(vertex-1, child-1);
            }
        }

        // get the order of the graph by level
        graph.levelOrder();

        // traverse the node from lower to higher levels
        // all nodes in a level have 1 marble each
        // by pushing excess nodes up the tree and
        // pulling missing marbles from parents
        for(int i = n-1; i >= 1; --i) {
            int j = graph.order[i];

            int parent = graph[j].parent;

            while(graph[j].marbles != 1) {
                if (graph[j].marbles > 1) {
                    ++(graph[parent].marbles);
                    --(graph[j].marbles);
                }
                else {
                    --(graph[parent].marbles);
                    ++(graph[j].marbles);
                }
                ++moves;
            }
        }
        printf("%d\n", moves);
    }
}
