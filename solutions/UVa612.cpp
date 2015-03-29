/* UVa problem: 612 - DNASorting
 *
 * Topic: Sorting
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   Sort and output DNA strings in order of most lexiographically sorted to least.
 *   Keep DNA strings with equal sortedness in the same order that they were received.
 *
 * Solution Summary:
 *   Book suggests count inversions and use STL stable sort. Implemented
 *   this with a simple struct to hold sequences/strings together. Count inversions
 *   in n^2 time by comparing letters (doable because strings are small). Stable sort based
 *   on inversions.
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
 
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// struct for holding sequence plus inversion count
struct DNA {
    char sequence[101];
    int inversions = 0;
};

// compare by number of inversions
bool compare_inversions(DNA a, DNA b) {
    return a.inversions < b.inversions;
}

// count the number of our of place characters
// strings are short enough to use n^2 comparison
int count_inversions(char* sequence, int len) {
    int inversions = 0;
    for (int i = 0; i < len-1; ++i) {
        for (int j = i+1; j < len; ++j) {
            if (sequence[i] > sequence[j])
                ++inversions;
        }
    }
    
    return inversions;
}

int main() {
    int datasets, str_len, lines;
    vector<DNA> sequences;
    
    cin >> datasets;
    
    while(datasets--) {
        cin >> str_len;
        cin >> lines;
        scanf("%d %d", &str_len, &lines);
        
        sequences.clear();

        // read lines from stdin and build DNA object
        while(lines--) {
            
            DNA dna;
            cin >> dna.sequence;
            dna.sequence[str_len] = '\0';
            dna.inversions = count_inversions(dna.sequence, str_len);
    
            sequences.push_back(dna);
        }
        
        // sort DNA by inversions keeping equally sorted sequences in the same order
        stable_sort(sequences.begin(), sequences.end(), compare_inversions);
        
        // print sorted list of DNA sequences
        for(auto &it : sequences) {
            printf("%s\n", it.sequence);
        }
        
        if (datasets)
            printf("\n");
    }

}