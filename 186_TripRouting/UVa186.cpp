/* UVa problem: 186 - TripRouting
 *
 * Topic: Graph Algorithms
 *
 * Level: non-trivial
 *
 * Brief problem description: A all-pairs shortest path problem
 *  where you have to print the route taken. Given a list of pairs of cities,
 *  the highways and distance between them. For a set of city pairs output
 *  a report containing the shortest route taken including the highway names and
 *  distance between each connecting city.
 *
 *
 * Solution Summary:
 *  It's possible to use Floyd Warshalls on this because # of cities is <= 100.
 *  I used two maps for easy integer to string transformation between city
 *  names and indexes in the graph. I used another N * N matrix to store highway
 *  names. I referenced Competitive Programming 3 fir how to store routes
 *  in Floyd Warshalls (used another matrix for parents) and then traversed this
 *  printing the required output for the report.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://stackoverflow.com/questions/7297623/how-to-provide-your-own-delimeter-for-cin
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
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <utility>

#define SIZE 100
#define INF 999999

using namespace std;

typedef pair<int, int> ii;

vector <pair<int, int>> paths;
map<int, string> index2str;
map<string, int> str2index;
string routes[SIZE][SIZE];
int graph[SIZE][SIZE], parent[SIZE][SIZE], N;


// reset the weights in the graph
void reset() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE ; j++)
            graph[i][j] = INF;
}

// floyd warshalls algorithm referenced from
// competitive programming 3
void floyd_warshalls() {

    // parent matrix, where parent(i, j) is
    // the last vertex before j
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE ; j++)
            parent[i][j] = i;

    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    // store parent
                    parent[i][j] = parent[k][j];
                }
            }
}

// make the graph from input
// there are a few caveats
// 1. city names may have more than one route between them
// in this case take the smallest
// 2. routes are reflexive
void make_graph() {
    stringstream stream;
    string line, city1, city2, route, throwaway;
    int miles, index1, index2;

    N = 0;

    while(getline(cin, line)) {

        if (line == "\0")
            break;

        stream.clear();
        stream.str(line);

        // line information is deliminated by ','
        getline(stream, city1, ',');
        getline(stream, city2, ',');
        getline(stream, route, ',');
        stream >> miles;

        // add unseen cities to our string -> index /
        // index -> string mappings
        if (str2index.find(city1) == str2index.end()) {
            str2index[city1] = N;
            index2str[N] = city1;
            ++N;
        }

        if (str2index.find(city2) == str2index.end()) {
            str2index[city2] = N;
            index2str[N] = city2;
            ++N;
        } else {

        }

        index1 = str2index[city1];
        index2 = str2index[city2];

        // if a route is smaller than the previously
        // stored route save it
        if (miles < graph[index1][index2]) {
            graph[index1][index2] = miles;
            graph[index2][index1] = miles;
            routes[index1][index2] = route;
            routes[index2][index1] = route;
        }
    }
}

// read the city pairs we need to find paths for
void read_paths() {
    stringstream stream;
    string line, city1, city2;
    paths.clear();

    while(getline(cin, line)) {
        stream.clear();
        stream.str(line);
        getline(stream, city1, ',');
        getline(stream, city2, '\0');

        paths.emplace_back(ii(str2index[city1], str2index[city2]));
    }
}

// use the parent matrix to rebuild the path
// (referenced from competive programming 3)
void print_path(int i, int j) {
    int p = parent[i][j];
    if (i != j) {
        print_path(i, p);
        printf("%-20s %-20s %-10s %5d\n", index2str[p].c_str(), index2str[j].c_str(),
           routes[p][j].c_str(), graph[p][j]);
    }
}


// print the report of all routes taken to reach the desired city
void print_report() {
    for (int k = 0; k < (int)paths.size(); ++k) {
        printf("\n\nFrom                 To                   Route      Miles\n");
        printf("-------------------- -------------------- ---------- -----\n");

        int i = paths[k].first;
        int j = paths[k].second;
        print_path(i, j);
        printf("                                                     -----\n");
        printf("                                          Total      %5d\n", graph[i][j]);
    }
}

int main() {
    reset();
    make_graph();
    read_paths();
    floyd_warshalls();
    print_report();
}
