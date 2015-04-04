/* UVa problem: 929 - Number Maze
 *
 * Topic: Graph Algorithms
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Given a (1..1000 by 1..1000) grid of tiles where each tile has a number
 *  from 1 to 9 find the minimum cost of going from the top left corner to the
 *  bottom right corner.
 *
 * Solution Summary:
 *  This seems like a classical dijkstras problem on a grid instead of a graph.
 *  Howard Changs hints says to use 10 queues but trying with just one queue was
 *  fast enough (1.5 seconds). Maybe C++11 Priority Queue is better than older C++
 *  priority queue?
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.cs.uleth.ca/~cheng/contest/hints.html
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
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#define ADJ 4
#define INF 999999

using namespace std;

struct Node {
    int weight;
    int x;
    int y;

    // needed for ordering in the priority queue
    Node(const int &x, const int &y, const int &weight)
        : weight(weight), x(x), y(y) {};

    bool operator>(const Node &node) const {
        return weight > node.weight;
    }
};

int grid[1000][1000];
int dist[1000][1000];
int rows, cols;

// trick for getting neighbours in a grid
int row_mod[ADJ] = {-1, 0, 0, 1};
int col_mod[ADJ] = {0, -1, 1, 0};


// classic dijkstras
// referenced Competitive Programming 3 for the implementation
void dijkstras() {
    int neigh_x, neigh_y;
    priority_queue<Node, vector<Node>, greater<Node>> frontier;

    // clear distances
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            dist[i][j] = INF;

    // We start at upper left corner
    dist[0][0] = grid[0][0];
    frontier.push(Node(0, 0, grid[0][0]));

    while(!frontier.empty()) {
        Node current = frontier.top(); frontier.pop();

        for (int i = 0; i < ADJ; ++i) {
            neigh_x = current.x + row_mod[i];
            neigh_y = current.y + col_mod[i];

            if (neigh_x < 0 || neigh_x >= rows || neigh_y < 0 || neigh_y >= cols)
                continue;

            if (current.weight + grid[neigh_x][neigh_y] >= dist[neigh_x][neigh_y])
                continue;

            // only continue if the current path is less than the previous
            // stored cost to reach this node
            dist[neigh_x][neigh_y] = current.weight + grid[neigh_x][neigh_y];
            frontier.push(Node(neigh_x, neigh_y, dist[neigh_x][neigh_y]));
        }
    }

    return;
}



int main() {
    int test_cases, n;

    scanf("%d", &test_cases);

    // read in the grid
    while(test_cases--) {
        scanf("%d", &rows);
        scanf("%d", &cols);
        n = 0;

        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                scanf("%d", &grid[i][j]);
                ++n;
            }
        }

        dijkstras();
        printf("%d\n", dist[rows-1][cols-1]);
    }


}
