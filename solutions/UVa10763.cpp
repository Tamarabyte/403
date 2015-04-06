/* UVa problem: 10763 - ForeignExchange
 *
 * Topic: Other
 *
 * Level: trivial
 *
 * Brief problem description:
 *  You are given a list of students who want to go on foreign exchange.
 *  They are represented by a pair of integers. The first integer
 *  is their start city, the second is their destination city.
 *  The foreign exchange only works if there is a student with an inverse
 *  source/destination for each student on the list. Number of students >= 50000;
 *
 * Solution Summary:
 *  Used a map data structure to solve this. I store the first <start, dest>
 *  pair encountered as 1, and then for each <start,dest> pair search for
 *  the matching pair in the map or the inverse pair. If the inverse pair is
 *  found I decrement the counter (we've found a match) otherwise I increment
 *  the counter. At the end I check for any entries in the map that != 0. If there
 *  are, then the exchange is not possible.
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
#include <algorithm>
#include <map>

using namespace std;
typedef pair<int, int> ii;

map<ii, int> students;
int main() {
    int n;

    while(scanf("%d", &n), n) {
        students.clear();

        // read in start/dest pairs
        // 1. if the pair exists in the map then increment it's value
        // 2. if the inverse exists in the map then decrement it's value
        // 3. otherwise add to map with a value of 1
        while (n--) {
            ii student;
            scanf("%d %d", &student.first, &student.second);
            ii inverse(student.second, student.first);

            if (students.find(student) != students.end())
                ++(students[student]);
            else if (students.find(inverse) != students.end())
                --(students[inverse]);
            else
                students[student] = 1;
        }

        // search for non-zeros in the map
        // if they exist the exhange is not possible
        bool flag = true;
        for (auto &it : students) {
            if (it.second) {
                printf("NO\n");
                flag = false;
                break;
            }
        }

        if (flag)
            printf("YES\n");
    }
}
