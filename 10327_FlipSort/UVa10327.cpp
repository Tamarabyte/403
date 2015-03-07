/* UVa problem: 10327 - FlipSort
 *
 * Topic: Sorting
 *
 * Level: trivial/non-trivial: T
 *
 * Brief problem description:
 *   Count the number of times flips are needed to sort a set of numbers by flipping adjacent elements.
 * Solution Summary:
 *   This is just bubble sort counting the inversions.
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

using namespace std;

int bubblesort(int* elements, int n) {
    int temp, flips = 0;
    
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            
            if (elements[j] <= elements[j+1])
                continue;
            
            temp = elements[j];
            elements[j] = elements[j+1];
            elements[j+1] = temp;
            ++flips;
        }
    }
    
    return flips;
}

int main() {
    int elements[1000], n;
    
    while(scanf("%d", &n) != EOF) {

        for (int i = 0; i < n; ++i)
            scanf("%d", &elements[i]);

        printf("Minimum exchange operations : %d\n", bubblesort(elements, n));
    }
}