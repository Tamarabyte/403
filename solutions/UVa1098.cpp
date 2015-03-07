/* UVa problem: 1098 - RobotsOnIce
 *
 * Topic: Backtracking
 *
 * Level: trivial/non-trivial: N
 *
 * Brief problem description:
 *   Find all possible paths that traverse the entire grid and stop
 *   at 3 checkpoints in order at the appropriate time. Grid sizes range from 2x2 to 8x8.
 *
 * Solution Summary:
 *   This is a 2^64 possible paths for the naive. The book suggested some pruning and
 *   meet in the middle but I couldn't get that implementation fast enough. I went back
 *   to aggressively pruning and after drawing paths out a few times realized that we
 *   always want to choose a neighbour that has only 1 exit over all other neighbours.
 *   If we have more than one neighbour with only 1 exit we should prune because one
 *   of those neigbours will either become unreachable or trap us.
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
#include <cstdlib>
#include <queue>
#include <set>
#include <vector>
#include <array>

using namespace std;

// obsene amount of global variables
int size, single_count, paths, case_num = 0; 
int rows, cols, row1, col1, row2, col2, row3, col3;
int time1, time2, time3;

bool seen[8][8], last_move;
queue<pair<int, int>> frontier;

array<array<int, 8>, 8> visited;
pair<int, int> single;

// Get all neighbours
vector<pair<int, int>> getNeighbours(int row, int col) {
    vector<pair<int, int>> neighbours;
    
    if (row > 0 && !visited[row-1][col]) 
        neighbours.push_back(make_pair(row - 1, col));
    if (col > 0 && !visited[row][col-1]) 
        neighbours.push_back(make_pair(row,  col - 1));
    if ( col < cols - 1 && !visited[row][col+1]) 
        neighbours.push_back(make_pair(row, col + 1));
    if (row < rows - 1 && !visited[row+1][col]) 
        neighbours.push_back(make_pair(row + 1, col));
    
    return neighbours;
}

// Get all neighbours excluding the end, we want to visit that last
vector<pair<int, int>> getNeighboursNoEnd(int row, int col) {
    vector<pair<int, int>> neighbours;
    
    if (row > 0 && !visited[row-1][col] && !(row-1 == 0 && col == 1)) 
        neighbours.push_back(make_pair(row - 1, col));
    if (col > 0 && !visited[row][col-1]  && !(row == 0 && col-1 == 1)) 
        neighbours.push_back(make_pair(row,  col - 1));
    if ( col < cols - 1 && !visited[row][col+1]  && !(row == 0 && col+1 == 1)) 
        neighbours.push_back(make_pair(row, col + 1));
    if (row < rows - 1 && !visited[row+1][col]  && !(row+1 == 0 && col == 1)) 
        neighbours.push_back(make_pair(row + 1, col));
    
    return neighbours;
}

// BFS to make sure all nodes are reachable from the end (0,1)
bool disconnected() {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                seen[i][j] = false;
        
        frontier.push(make_pair(0, 1));
        seen[0][1] = true;
    
        while (frontier.size() > 0) {
            pair<int, int> current = frontier.front();
            frontier.pop();
            for (auto& neighbour : getNeighbours(current.first, current.second)) {
                int row = neighbour.first;
                int col = neighbour.second;
                if (seen[row][col]) 
                    continue;
                
                frontier.push(make_pair(row,col));
                seen[row][col] = true;
            }
        }
        
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (!seen[i][j] && !visited[i][j]) 
                    return true;
        return false;
    }

void find_paths(int row, int col, int move) {
    
    if (move == size-1) {
        // we have found a valid path so increment our potential paths
        if ((row-1 == 0 && col == 1) || (row == 0 && col-1 == 1)) {
            ++paths;
        }
        return;
    }
    
    // prune the following invalid paths:
    
    // 1. hit a check-in point early
    if (row == row1 && col == col1 && move != time1) return;
    if (row == row2 && col == col2 && move != time2) return;
    if (row == row3 && col == col3 && move != time3) return;
    
    // 2. missed a check-in point
    if (move == time1 && ( row != row1 || col != col1 ))  return;
    if (move == time2 && ( row != row2 || col != col2 )) return;
    if (move == time3 && (row != row3 || col != col3 )) return;
    
    // 3. won't make the next check-in point
    if (move < time1 && move + abs(row1 - row) + abs(col1 - col) > time1) return;
    if (move < time2 && move + abs(row2 - row) + abs(col2 - col) > time2) return;
    if (move < time3 && move + abs(row3 - row) + abs(col3 - col) > time3) return;
    
    // 4. this move disconnects the graph
    if (disconnected()) 
        return;
    
    // everything so far is valid, so visit the node
    visited[row][col] = true;
    
    // get all neighbours
    vector<pair<int, int>> neighbours = getNeighboursNoEnd(row, col);
    
    // get the neighbours of these neighbours
    single_count = 0;
    for (int i = 0; i < neighbours.size(); i++) {
        vector<pair<int, int>> secondaryNeighbours = getNeighbours(neighbours[i].first, neighbours[i].second);
        if (secondaryNeighbours.size() == 1) {
            ++single_count;
            single = neighbours[i];
        }
    }
    
   // we want to explore nodes that have only one exit first because
    // we can't approach them from any other direction without getting stuck
   if (single_count == 1){ 
        find_paths(single.first, single.second, move + 1); 
    }
    // if we have multiple nodes with only 1 path from them than we're
    // going down a bad path and we can prune
    // otherwise explore neighbours iteratively
    else if (single_count == 0) {
        for (auto& neighbour : neighbours) {
            find_paths(neighbour.first, neighbour.second, move + 1);
        }
    }

    visited[row][col] = false;
}

int main() {

    
    // get size of gird
    while (scanf("%d %d", &rows, &cols), (rows || cols)) {
        // get coordinates for visitation points
        scanf("%d %d %d %d %d %d", &row1, &col1, &row2, &col2, &row3, &col3);
        set<pair<int, int>> points;
        
        // calculate check-in points
        size = rows * cols;
        time1 = size / 4;
        time2 = size / 2;
        time3 = (3 * size) / 4;
        
        // reset number of paths, visited locations
        paths = 0;
        
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                visited[i][j] = false;
        
        // get the number of solutions starting with the first move at coordinate (0, 0)
        find_paths(0, 0, 1);
        
        // iterate case number for printing
        ++case_num;
        printf("Case %i: %i\n", case_num, paths);
    }
}