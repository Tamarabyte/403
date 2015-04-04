/* UVa problem: 124 - FollowingOrders
 *
 * Topic: Graph Traversal
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *
 * Solution Summary:
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.eecis.udel.edu/~breech/progteam/stringstream.html
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
#include <sstream>
#include <algorithm>

#define INDEX(X) X - 97
#define LETTER(X) X + 97

using namespace std;

int n;
char letters[27];
bool greater_than[27][27];
int ind[27];

void generate_permutations() {
    
    do {
        bool invalid = false;
        for (int i = n-1; i > 0; --i) {
            for (int j = 0; j < i; ++j) {
                if (greater_than[INDEX(letters[i])][INDEX(letters[j])]) {
                    //printf("%c > %c\n", letters[i], letters[j]);
                    invalid = true;
                    break;
                }
            }
            if (invalid)
                break;
        }
        
        if (invalid)
            continue;

        printf("%s\n", letters);
    } while (next_permutation(letters, letters+n));
}

void get_input(string& line) {

    n = 0;
    char letter, letter2;
    stringstream stream;
            
    stream.clear();
    stream.str(line);
    
    while(stream >> letter) {
        letters[n] = letter;
        ++n;
    }
    
    sort(letters, letters+n*sizeof(char));
    
    getline(cin, line);
    stream.clear();
    stream.str(line);
    while(stream >> letter >> letter2) {
       greater_than[INDEX(letter)][INDEX(letter2)] = true;
    }
}

void print() {
    for(int i = 0; i < n; ++i) {
        printf("%c ", letters[i]);
    }
    printf("\n");
    
    for(int i = 0; i < n; ++i) {
        printf("%c: ", letters[i]);
        for (int j = 0; j < 26; ++j) {
            if (greater_than[INDEX(letters[i])][j])
                printf("%c ", LETTER(j));
        }
        printf("\n");
    }
    
        
}

int main() {
    string line;
    int test_case = 0;
    
    
    while(getline(cin, line)) {
        
        if (line == "\0")
            break;
        
        if (test_case)
            printf("\n");
        
        memset(greater_than, false, sizeof(greater_than));
        memset(letters, '\0', sizeof(letters));
        memset(ind, -1, sizeof(ind));
        
        get_input(line);
        //print();
        generate_permutations();
        ++test_case;
    }
}