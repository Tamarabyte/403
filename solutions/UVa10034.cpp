/* UVa problem: 10034 - Freckles
 *
 * Topic: Graph Algorithms
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Given a list of coordinates, find the minimum distance that must be travelled
 *  to visit each coordinate.
 *
 * Solution Summary:
 *  Straightforward application of primms algorithm. I referenced the
 *  implementation in Competitive Programming 3. The maximum input is 100
 *  so this O^2 algorithm is more than fast enough and there is no need
 *  to try something faster.
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
#include <utility>
#include <cmath>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
typedef pair<double, double> dd;
typedef pair<double, int> di;

vector<dd> coords;
vector<vector<di>> graph;
priority_queue<di> pq;
bool taken[101];

double distance(dd& p1, dd& p2) {
    return sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
}


// build the adjacency graph by calculating the weight (distance)
// between each point to all other points
void build_graph() {
    for(int i = 0; i < (int)coords.size()-1; ++i) {
        for(int j = i+1; j < (int)coords.size(); ++j) {
            double d = distance(coords[i], coords[j]);
            graph[i].emplace_back(di(d, j));
            graph[j].emplace_back(di(d, i));
        }
    }
}

void process(int i) {
    taken[i] = true;
    for (int j = 0; j < (int)graph[i].size(); ++j) {
        di next = graph[i][j];
        // negates the values because priority queues
        // serve up largest first, and we want smallest
        if (!taken[next.second])
            pq.push(di(-next.first, -next.second));
    }
}

// implementation referenced from Competitive Programming 3
double primms() {
    int vertex;
    double weight, cost = 0;
    di front;

    memset(taken, false, sizeof(taken));
    process(0);

    while(!pq.empty()) {
        front = pq.top(); pq.pop();
        weight = -front.first;
        vertex = -front.second;
        // if we have not processes this vertex
        // yet then add it's weight to the graph and do so now
        if (!taken[vertex]) {
            cost+= weight;
            process(vertex);
        }
    }

    return cost;
}


int main() {
    int test_cases, n;
    double x, y;

    scanf("%d", &test_cases);
    while(test_cases--) {

        coords.clear();
        graph.clear();
        scanf("%d", &n);

        while(n--) {
            scanf("%lf %lf", &x , &y);
            coords.emplace_back(dd(x, y));
            graph.emplace_back(vector<di>());
        }

        build_graph();
        printf("%.2lf\n", primms());
        if (test_cases)
            printf("\n");
    }
}
