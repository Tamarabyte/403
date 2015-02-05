/* UVa problem: 11512 - GATTACA
 *
 * Topic: Strings
 *
 * Level: trivial/non-trivial: trivial
 *
 * Brief problem description:
 *
 * Solution Summary:
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
#include <iostream>
#include <string>
#include <algorithm>
#define MAX_N 1001

using namespace std;

void computeLCP(int *lcp, int *suff_arr, const char* sequence, int n) {
    lcp[0] = 0;
    
    for (int i = 1; i < n; i++) {
        // default value // compute LCP by definition // always reset L to 0 // same L-th char, L++
        int L = 0;
        // compute LCP by definition
        while (sequence[suff_arr[i] + L] == sequence[suff_arr[i-1] + L]) {
            L++; 
            lcp[i] = L;
        }
    }
}

void countingSort(int *rank_arr, int *suff_arr, int k, int n) {
    int index, sum, maxi;
    int freq_table[n];
    int temp_suff[n];
    // string length or 'A', 'G', 'C', T', '$'
    maxi = max(5, n);
    
    // clear table
    memset(freq_table, 0, sizeof(freq_table));
    
    // count frequency of each rank
    for (int i = 0; i < n; i++) {
        index = i + k < n ? rank_arr[i+k] : 0;
        freq_table[index]++;  
    }
    
    sum = 0;
    for (int i = 0; i < maxi; i++) {
        int t = freq_table[i];
        freq_table[i] = sum; 
        sum += t;
    }
    
    // shuffle the suffix array if neccesary
    for (int i = 0; i < n; i++) {
        index = suff_arr[i]+k < n ? rank_arr[suff_arr[i]+k] : 0;
        temp_suff[index++] = suff_arr[i];
    }
    
    // update the suffix array
    for (int i = 0; i < n; ++i) {
        suff_arr[i] = temp_suff[i];
    }
    
    printf("%d\n", suff_arr[0]);
    printf("%d\n", suff_arr[1]);
    printf("%d\n", suff_arr[2]);
        
}

// adapted from Competitive Programming 3
void constructSA(int *suff_arr, const char *sequence, int n) {
    int rank_arr[n];
    int temp_rank[n];
    
    // initial rankings
    for (int i = 0; i < n; ++i) 
        rank_arr[i] = sequence[i];
    
    // set suffix substrings in initial order
    for (int i = 0; i < n; ++i) {
        suff_arr[i] = i;
        printf("%d: %d\n", i, suff_arr[i]);
    }
    
    // sort log n times
    printf("%d\n", n);
    printf("\n");
    for (int k = 0; k < n; k <<= 1) {
        // radix sort based on the second item
        countingSort(rank_arr, suff_arr, k, n);
        // stable sort based on the first item
        countingSort(rank_arr, suff_arr, 0, n);
        
        printf("test\n");
        temp_rank[suff_arr[0]] =  0;
        int r = 0;
        printf("5\n");
        // if our two suffixes are the same then their ranks are the same
        for (int i = 0; i < n; ++i) {
            cout << suff_arr[i] << " "; 
            /*
            if (rank_arr[suff_arr[i]] == rank_arr[suff_arr[i-1]]) {
                //rank_arr[suff_arr[i]+k] == rank_arr[suff_arr[i-1]+k]
                printf("6\n");
                temp_rank[suff_arr[i]] = r;
            }
            else {
                printf("7\n");
                temp_rank[suff_arr[i]] = ++r;
            }*/
        }
        cout << endl;
        
        // update rank array
        for (int i = 0; i < n; ++i) 
            rank_arr[i] = temp_rank[i];

        if (rank_arr[suff_arr[n-1]] == n-1) 
            break;
    }
}

int main() {
    
    int testcases;
    string sequence;
    int *suff_arr;;
    int *lcp;
    size_t n;

    scanf("%d", &testcases);
    while(testcases--) {
        
        cin >> sequence;
        sequence = sequence + "$";
        n = sequence.length();
        
        suff_arr = new int[n]();
        lcp = new int[n]();
        
        constructSA(suff_arr, sequence.c_str(), n);
        computeLCP(lcp, suff_arr, sequence.c_str(), n);
        
        // find the index of the largest value in the lcp
        size_t max_index = 0;
        for (size_t i = 0; i < n; ++i) {
            if (lcp[i] > lcp[max_index])
                max_index = i;
        }
        
        if (lcp[max_index = 0])
            printf("No repetitions found!");
        else
            printf("%s %d\n", sequence.substr(suff_arr[max_index], lcp[max_index]).c_str(), lcp[max_index]);
        
        delete[] suff_arr;
        delete[] lcp;
    }
    
}