/* UVa problem: 11475 - Extend the Palindrome
 *
 * Topic: Strings
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   Add the smallest amount of letters to a string to make it a palindrone
 *
 * Solution Summary:
 * Used the hint in Competitive Programming 3 (says to use KMP). We want to add
 * the minimum amount of letters to the end. Reverse the original string and search
 * for it in the existing string. For a palindrome, the reversed string will complete its match
 * at the last index of the of the existing string. Otherwise we want to keep track of where
 * we were in the reversed string. This overlap between the reversed and regular string are
 * areas we don't need to append for our palindrone.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.cplusplus.com/reference/iterator/reverse_iterator/
 *
 * I hereby certify that I have produced the following solution myself
 * using the resources listed above in accordance with the CMPUT 403
 * collaboration policy.
 *
 * --- Tamara Bain
 *
 *  Language: C++11
 */

#include <iostream>
#include <string>
#include <iterator>

using namespace std;


// create the KMP Table
// Code adapted from Competitive Programming 3
void fillKMPTable(int* kmpTable, const char* pattern, char len) {
    int i = 0;
    int j = -1;

    kmpTable[0] = -1;
    while (i < len) {
        while (j >=0 && pattern[i] != pattern[j])
            j = kmpTable[j];
        ++j;
        ++i;
        kmpTable[i] = j;
    }
}

// use KMP Search
// Code adapted from Competitive Programming 3
size_t kmpSearch(const char* word, const char* reversed, int* table, int len) {
    int i = 0;
    int j = 0;

    while (i < len) {
        while (j >= 0 && word[i] != reversed[j])
            j = table[j];
        ++i;
        ++j;
        if (j == len) {
            break;
        }
    }
    return j;
}

// for debugging purposes
void printArray(char *arr, int length) {
    printf("[");
    for (int i = 0; i < length; ++i)
        printf("%d ", arr[i]);
    printf("]\n");
}

 int main() {

   string word, reversed;
   int* kmpTable;

   // read strings until EOF
   while(cin >> word) {

      // fill the kmp table for kmb search
      kmpTable = new int[word.length()+1];
      fillKMPTable(kmpTable, word.c_str(), word.length());

      // get the reversed string
      reversed = string(word.rbegin(), word.rend());

      // get the last position we matched in the reversed string at the end
      // of the original stringword.length()-overlap_end
      size_t overlap_end = kmpSearch(word.c_str(), reversed.c_str(), kmpTable, word.length());

      // if our reversed string overlaps completely then we already have a palindrone
      // otherwise we need to append to remainder to the original string
      if (overlap_end != word.length())
         cout << word.append(reversed, overlap_end, word.length()-overlap_end) << endl;
      else
         cout << word << endl;;

      delete[] kmpTable;

   }
}

