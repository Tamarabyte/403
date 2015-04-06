/* UVa problem: 10187 - FromDuskTillDawn
 *
 * Topic: Graph Algorithms
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  You are given a list train routes between cities. A route includes the
 *  destination and starting city, the departure time, and the travel time.
 *  Given a starting city and a destination city, if you can only travel from 18:00 to 6:00
 *  what is the minimum number of days it will take to get to the destination.
 *
 * Solution Summary:
 *  This is dijkstras with a twist, you need to keep track of departure time/arrival time
 *  so you can determine if you can depart on the same day or the next day. To simplify
 *  time comparisons, I added 6 hours to all departure times so that the time window is between
 *  0:00 and 12:00. This allows for an arrival_time > departure_time check to see if we need
 *  to wait a day before taking that train. I stored the graph in a Adj List (I used a map
 *  to link city names to their corresponding departure routes).
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.udebug.com/UVa/10187 (for generating test cases)
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
#include <map>
#include <vector>
#include <queue>
#include <set>
#define INF 9999999

using namespace std;
typedef pair<int, string> is;
typedef vector<is> vis;

struct Route {
    string name;
    int departure;
    int travel;
    int arrival;
    int days;

    Route(string &name, int departure, int arrival, int travel, int days) :
        name(name), departure(departure), travel(travel), arrival(arrival), days(days) {}

    bool operator>(const Route &r) const {
        return days > r.days;
    }
};

map<string, vector<Route>> graph;
map<string, int> days;
set<string> names;

void dijkstras(string start) {
    int current_cost;
    priority_queue<Route, vector<Route>, greater<Route>> frontier;

    // Our start route takes 0 travel time and arrives at the start of the day.
    days[start] = 0;
    frontier.push(Route(start, 0, 0, 0, 0));

    while(!frontier.empty()) {
        Route current = frontier.top(); frontier.pop();

        for (int i = 0; i < (int)graph[current.name].size(); ++i) {

            Route neigh = graph[current.name][i];
            current_cost = days[current.name];

            // if we arrive after the departure time for this train
            // we will have to wait until the next day to take it
            if (current.arrival > neigh.departure)
                ++current_cost;

            // if we have a faster route saved then don't consider this route
            if (current_cost >= days[neigh.name])
                continue;

            days[neigh.name] = current_cost;
            frontier.push(Route(neigh.name, neigh.departure, neigh.arrival, neigh.travel, current_cost));
        }
    }

    return;
}


// make an Adj List for the graph representation
// using a map of vectors
void make_graph() {
    int connections, departure_time, travel_time, arrival_time;
    string cityA, cityB;

    graph.clear();

    scanf("%d", &connections);
    while(connections--) {
        cin >> cityA >> cityB;
        scanf("%d %d", &departure_time, &travel_time);

        if (travel_time > 12)
            continue;

        // add 6 to everything for easy comparisons between
        // arrival and departure times
        departure_time = (departure_time + 6) % 24;
        arrival_time = (departure_time + travel_time) % 24;

        // don't include routes we won't be able to take due
        // to our time restrictions
        if (departure_time >= 12 || arrival_time > 12)
            continue;


        if (graph.find(cityA) == graph.end()) {
            graph[cityA] = vector<Route>();
            names.insert(cityA);
            days[cityA] = INF;
        }

        if (graph.find(cityB) == graph.end()) {
            graph[cityB] = vector<Route>();
            names.insert(cityB);
            days[cityB] = INF;
        }

        graph[cityA].emplace_back(Route(cityB, departure_time, arrival_time, travel_time, INF));
    }
}


int main() {
    int test_cases, current_case = 0;
    string cityA, cityB;

    scanf("%d", &test_cases);
    while(test_cases--) {

        ++current_case;

        make_graph();

        cin >> cityA >> cityB;

        printf("Test Case %d.\n", current_case);

        // special case where our destination is our starting city
        // no need to run dijkstras
        if (cityA == cityB) {
            printf("Vladimir needs 0 litre(s) of blood.\n");
            continue;
        }

        // special case where our city isn't in our graph
        // no need to run dijkstras
        if (graph.find(cityA) == graph.end() || graph.find(cityB) == graph.end()) {
            printf(
            "There is no route Vladimir can take.\n");
            continue;
        }

        dijkstras(cityA);

        if (days[cityB] == INF)
            printf("There is no route Vladimir can take.\n");
        else
            printf("Vladimir needs %d litre(s) of blood.\n", days[cityB]);
    }

}

