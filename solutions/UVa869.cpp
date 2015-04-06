/* UVa problem: 869 - AirlineComparison
 *
 * Topic: Graph Algorithms
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   Given a list of flights for two separate airlines (from one city to another city)
 *   output whether or not each airline can reach the same cities. (transitive closure)
 *
 * Solution Summary:
 *  As Howard Changs hints mention this is as simple as finding the transitive closures
 *  between the two airlines. The question is a bit confusing because it doesn't
 *  list many restrictions on input. I assumed that as per the sample input that
 *  cities are listed as capital letters only, that N and M can be >= 0 and,
 *  that flight connections are non-reflexive. These assumptions where either correct, or
 *  there were no tests to invalidate them. The input is then small enough
 *  to use Floyd Warshalls on. After running Floyd Warshalls on both graphs I just
 *  compared the result.
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
#include <algorithm>

#define INF 1
#define SIZE 26
#define TO_INT(X) X-65

using namespace std;

int N, M;

// reset graphs edge weights to INF
// each vertex can reach itself so set that weight
// to 0
void reset(int graph1[SIZE][SIZE], int graph2[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            graph1[i][j] = INF;
            graph2[i][j] = INF;
        }
        graph1[i][i] = 0;
        graph2[i][i] = 0;
    }
}

// floyd warshalls algorithm referenced from
// competitive programming 3
void floyd_warshalls(int graph[SIZE][SIZE]) {
    for (int k = 0; k < SIZE; ++k)
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

// create the graph from input
// we don't care about distance between cities just if they are
// reachable, so mark an edge weight as 0 if there is a flight
// from one city to the other
void create_graph(int &num, int graph[SIZE][SIZE]) {
    char letter1[2], letter2[2];

    scanf("%d", &num);
    for (int i = 0; i < num; ++i) {
        scanf("%s %s", letter1, letter2);
        graph[TO_INT(letter1[0])][TO_INT(letter2[0])] = 0;
    }
}


int main() {
    int test_cases;
    int graph1[SIZE][SIZE], graph2[SIZE][SIZE];
    bool equal_routes;

    scanf("%d", &test_cases);

    // for each test case
    while(test_cases--) {
        reset(graph1, graph2);

        // initialize graphs
        create_graph(N, graph1);
        create_graph(M, graph2);

        // run floyd warshalls on both graphs
        floyd_warshalls(graph1);
        floyd_warshalls(graph2);

        // compare the results
        // stop if one airline has a route between cities
        // the the other doesn't have
        equal_routes = true;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if ((!graph1[i][j] && graph2[i][j]) || (!graph2[i][j] && graph1[i][j])) {
                    equal_routes = false;
                    break;
                }
            }
            if (equal_routes == false)
                break;
        }

        equal_routes ? printf("YES\n") : printf("NO\n");
        if (test_cases)
            printf("\n");
    }
}
