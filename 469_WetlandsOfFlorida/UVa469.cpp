/* UVa problem: 469 - WetlandsOfFlorida
 *
 * Topic: Graph Traversal
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   Given a grid of water and land tiles and given a coordiate
 *   of a water tile on that grid, determine the size of the associated patch of water.
 *
 * Solution Summary:
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   uDebug - http://www.udebug.com/UVa/469 (to compare expected output)
 *   http://www.cplusplus.com/reference/istream/istream/getline/
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
#include <string>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;

char grid[100][100];
int cache[100][100];
int n, m;
vector<pair<int, int>> positions;
vector<pair<int, int>> recolored;

// trick for explring grid from Competitive Programming 3
int row_mod[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int col_mod[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// recolor the graph and count the squares that were refilled
int count_wetlands(int row, int col) {
    if (row < 0 || row >= n
        || col < 0 || col >= m)
        return 0;

    if (grid[row][col] != 'W')
        return 0;

    // recolor
    int filled = 1;
    grid[row][col] =  '-';
    recolored.push_back(make_pair(row, col));

    for (int i = 0; i < 8; ++i) {
        filled += count_wetlands(row + row_mod[i], col + col_mod[i]);
    }

    return filled;
}

// build the graph from input
// the input requirements for this problem were
// the trickiest part
void build_grid() {
    int test_cases, row, col, answer;
    string line;
    pair<int, int> position;
    scanf("%d", &test_cases);

    // two lines before test data is given
    getline(cin, line);
    getline(cin, line);

    while(test_cases--) {
        n = 0;
        m = 0;
        positions.clear();
        memset(cache, 0, sizeof(cache));

        // get lines until we reach a blank line
        // that signals the end of this test case
        while (getline(cin, line)) {
            m = m ? m : line.size();

            if (line == "\0") {
                break;
            }

            // if there's a space in the string it's
            // a coordinate, otherwise it's part of the map
            if (line.find(" ") == string::npos) {
                for(int m=0; line[m] != '\0'; ++m)
                    grid[n][m] = line[m];
                ++n;
            }
            else {
                sscanf(line.c_str(), "%d %d", &row, &col);
                positions.emplace_back(make_pair(row-1, col-1));
            }
        }

        // call the recoloring function
        // cache the results so if we hit a piece
        // of wetland that is in the wetland we just
        // recolored we don't have to recount
        for (auto& pos:positions) {
            answer = cache[pos.first][pos.second];
            if (!answer) {
                recolored.clear();
                answer = count_wetlands(pos.first, pos.second);
                for (auto &wetland : recolored)
                    cache[wetland.first][wetland.second] = answer;
            }
            printf("%d\n", answer);
        }
        if (test_cases)
            printf("\n");
    }
}

int main() {
    build_grid();
}
