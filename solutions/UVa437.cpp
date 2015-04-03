/* UVa problem: 437 - TowerOfBabylon
 *
 * Topic: Graph Traversal
 *
 * Level: trivial
 *
 * Brief problem description:
 *   Given a set of block types and assuming infinite supply of each block,
 *   find the tallest possible tower that can be constructed by stacking
 *   the blocks on top of eachother. Blocks must have smaller width/length dimensions
 *   on there stacking side then the block they're stacked on top of. Blocks can be rotated
 *   so any 2 of there 3 dimensions makes up the stacking side.
 *
 * Solution Summary:
 *  Even though you're give infinite blocks, you can't stack blocks with the
 *  same width/height dimensions on top of eachother so you can really only
 *  have 3 different blocks for each block type (xyz, xzy, zyx). These blocks
 *  will make up a DAG, so we really just have to find the longest possible
 *  path in this DAG (heights become path weights). I solved this by making
 *  a adjacency list out of the input, and then traversing the graph saving
 *  the max possible height at that node in a DP style manner.
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
#include <vector>
#include <algorithm>
using namespace std;


// block class for storing 3 dimensions of blocks
// and calculating whether one block can fit on top of another
struct Block {
    Block(const int &x, const int &y, const int &z)
        : visited(false), max_height(0), x(x), y(y), z(z) {}

    bool fits(const Block &node) const {
        if (node.x < x && node.y < y)
            return true;
        else if (node.x < y && node.y < x)
            return true;
        return false;
    }

    vector<int> neighbours;
    bool visited;
    unsigned int max_height;
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int z = 0;
};

vector<Block> blocks;
vector<int> paths;

// build the adjacency list for the graph
void initialize_neighbours(){
    for(int i = 0; i<(int)blocks.size(); ++i) {
        for(int j = 0; j<(int)blocks.size(); ++j) {
            if (blocks[i].fits(blocks[j]))
                blocks[i].neighbours.push_back(j);
        }
    }
}


// utility function for debugging
void print() {
    for(int i = 0; i<(int)blocks.size(); ++i) {
        printf("%d (%d, %d, %d): ", i, blocks[i].x, blocks[i].y, blocks[i].z);
        for(int j = 0; j<(int)blocks[i].neighbours.size(); ++i)
            printf("%d (%d, %d, %d) ", j, blocks[j].x, blocks[j].y, blocks[j].z);
        printf("\n");
    }
}

// find the longest path (max height) with the help of memoization
unsigned int longest_path(int src) {
    unsigned int &max_height = blocks[src].max_height;

    if (!blocks[src].max_height) {
        for (int i=0; i < (int)blocks[src].neighbours.size(); ++i)
            max_height = max(max_height, longest_path(blocks[src].neighbours[i]));
        max_height += blocks[src].z;
    }

    return max_height;
}

int main() {
    unsigned int max_height, n, x, y, z;
    int test_case = 1;

    while(scanf("%d", &n), n) {
        max_height = 0;
        blocks.clear();

        for(int i = 0; i < (int)n; ++i) {
            scanf("%d %d %d", &x, &y, &z);
            blocks.emplace_back(Block(x, y, z));
            blocks.emplace_back(Block(y, z, x));
            blocks.emplace_back(Block(z, x, y));
        }

        initialize_neighbours();
        //print();

        for(int i = 0; i < (int)blocks.size(); ++i)
            max_height = max(max_height, longest_path(i));


        printf("Case %d: maximum height = %d\n", test_case, max_height);
        ++test_case;
    }

}
