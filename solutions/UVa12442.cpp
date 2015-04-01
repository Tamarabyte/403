/* UVa problem: 12442 - ForwardingEmails
 *
 * Topic: Graph Traversal
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  You are given a directed graph where each node 1..N N <= 50000 is connected to one other node.
 *  This represents an email chain, where each person emails one other person (not themselves).
 *  Which person should you email to ensure your email reaches as many people possible.
 *  If there is a tie choose the smaller node.
 *
 * Solution Summary:
 *   The book suggests a modified DFS traversal. I used adj. list representation for my
 *   graph because each node is only connected to one other node you can just use
 *   and array for the graph in adj. list form. DFS only for nodes that we did not visit
 *   on a previous DFS. Watch out for cycles by marking each node visited during the dfs traversal.
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
#include <cstring>
#define UNSET -1

using namespace std;

int adj_list[50001];
int connections[50001];
bool marked[50001];
int martians;

// special DFS this checks for cycles
// by marking each node we visit
// and unmarking it as we unwind the recursion
int dfs(int i) {

    // graph is cycling, so stop dfs
    if (marked[adj_list[i]])
        return 0;

    marked[i] = true;
    connections[i] = 1 + dfs(adj_list[i]);
    marked[i] = false;

    return connections[i];
}

int main() {
    int test_cases, martian, neighbour, max_connections, solution;
    int current = 0;

    scanf("%d", &test_cases);

    // for each test case
    while(current++ < test_cases) {

        // reset # of connections
        memset(connections, UNSET, sizeof(connections));
        memset(marked, false, sizeof(marked));
        solution = max_connections = 0;

        scanf("%d", &martians);

        // because each node only has one neighbour
        // we can use an array for our adjacency list
        for(int i = 1; i <= martians; ++i) {
            scanf("%d %d", &martian, &neighbour);
            adj_list[martian] = neighbour;
        }


        for(int i = 1; i <= martians; ++i) {
            // we should only check the dfs for components
            // that weren't iterated over in our previous runs
            // otherwise our runtime will be O^3
            if (connections[i] == UNSET)
                dfs(i);

            // save max soluton;
            if(connections[i] > max_connections) {
                max_connections = connections[i];
                solution = i;
            }
        }
        printf("Case %d: %d\n", current, solution);
    }
}
