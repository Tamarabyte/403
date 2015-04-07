/* UVa problem: 12492 - RubikCycle
 *
 * Topic: Combinatorics
 *
 * Level: trivial
 *
 * Brief problem description:
 *  For a rubik's cube and a set of rotations. Find the minimum
 *  number of cycles of the set to return the cube to it's original position.
 *
 * Solution Summary:
 *   I tried Howard Cheng's hint on this (look at each cell individually,
 *   find the cycle length for that cell, and then lcm all cells to get the
 *   cycle length and I TLE'd. Just rotating until the cube is the same as when
 *   it started got me the AC. For each face I figured out the position of the
 *   cells after a clockwise rotation and then reversed this for a
 *   counter clockwise location.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.cplusplus.com/forum/beginner/51520/
 *   http://www.cs.uleth.ca/~cheng/contest/hints.html
 *   http://www.udebug.com/UVa/12492
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
#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <utility>

#define FACES 6
#define SIDE 9
#define N 54
#define GET_POS(x, f) x + SIDE*f

using namespace std;

// Faces of the cube
enum faces {F, L, U, B, R, D};
map<char, int> get_face = {{'F', 0}, {'f', 0}, {'L', 1}, {'l', 1}, {'U', 2}, {'u', 2},
                           {'B', 3}, {'b', 3}, {'R', 4}, {'r', 4}, {'D', 5}, {'d', 5}};

// 3 arrays, one to hold the original values of the cube
// one to hold the cells while we're rotating, and one to copy to
// during rotations.
array<int, N> temp;
array<int, N> original;
array<int, N> cells;

// given a face and whether or not the rotations is CW or CCW
// rotate the cube
void rotate(int face, bool clockwise) {

    temp = cells;

    // transformation of the cells on the face that is being rotated
    // ex. face [2] becomes face [1],
    int result[SIDE] = {2, 5, 8, 1, 4, 7, 0, 3, 6};
    if (clockwise) {
          for (int i = 0; i < SIDE; ++i)
            cells[GET_POS(result[i], face)] = temp[GET_POS(i, face)];
        }
    else {
        for (int i = 0; i < SIDE; ++i)
            cells[GET_POS(i, face)] = temp[GET_POS(result[i], face)];
    }

    // transformations for the faces around the face being rotated
    int rotations[FACES][4][4] = {
        // F
        {{faces::U, 6, 7, 8}, {faces::L, 8, 5, 2}, {faces::D, 2, 1, 0}, {faces::R, 0, 3, 6}},
        // L
        {{faces::U, 0, 3, 6}, {faces::B, 0, 3, 6}, {faces::D, 0, 3, 6}, {faces::F, 0, 3, 6}},
        // U
        {{faces::B, 6, 7, 8}, {faces::L, 2, 1, 0}, {faces::F, 2, 1, 0}, {faces::R, 2, 1, 0}},
        // B
        {{faces::D, 6, 7, 8}, {faces::L, 0, 3, 6}, {faces::U, 2, 1, 0}, {faces::R, 8, 5, 2}},
        // R
        {{faces::U, 8, 5, 2}, {faces::F, 8, 5, 2}, {faces::D, 8, 5, 2},  {faces::B, 8, 5, 2}},
        // D
        {{faces::F, 6, 7, 8}, {faces::L, 6, 7, 8},  {faces::B, 2, 1, 0}, {faces::R, 6, 7, 8}}
    };


    // use modulous to grab the side in front of or behind to
    // assign from during rotations
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 4; ++j) {
            int mod = (clockwise) ? 1 : -1;
            int faceA = rotations[face][i][0];
            int faceB = rotations[face][(4+i+mod)%4][0];
            int posA = rotations[face][i][j];
            int posB = rotations[face][(4+i+mod)%4][j];

            cells[GET_POS(posA, faceA)] = temp[GET_POS(posB, faceB)];
        }
    }
}

void setup(array<int, N> &cube) {
    for (int i = 0; i < N; ++i) {
        cube[i] = i;
    }
}

// run the chain of rotations until we have the original cube
// output the number of cycles we had to go through
void solve(vector<pair<int, bool>> &commands) {
    int counts = 0;
    do {
        ++counts;
        for (auto& command: commands) {
            rotate(command.first, command.second);
        }
    } while(original != cells);
    cout << counts << endl;
}

int main() {
    string line;
    vector<pair<int, bool>> commands;

    setup(original);

    // read in input, save rotation commands
    // in a vector
    while (getline(cin, line)) {

        if (line[0] =='\0')
            break;

        setup(cells);
        commands.clear();

        for (int i = 0; i < (int)line.size(); ++i) {
            commands.push_back(make_pair(get_face[line[i]], isupper(line[i])));
        }

        solve(commands);
    }
}
