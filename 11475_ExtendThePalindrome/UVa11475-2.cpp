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
#include <unordered_map>

using namespace std;

// for debugging purposes
void printArray(char *arr, int length) {
    printf("[");
    for (int i = 0; i < length; ++i)
        printf("%d ", arr[i]);
    printf("]\n");
}

 int main() {

   string word, reversed, palindrome;
   int overlap; 
   unordered_map<string, int> suffix_map;

   // read strings until EOF
   while(cin >> word) {
       
      // get the reversed string
      reversed = string(word.rbegin(), word.rend());

       for (int i = 0; i < (int)word.length(); ++i) {
         suffix_map[word.substr(i, word.length()-i)] = word.length()-i;
      }
       
       overlap = 0;
       for (int i = 0; i < (int)reversed.length(); ++i) {
           auto it = suffix_map.find(reversed.substr(0, reversed.length()-i));
           if (it != suffix_map.end()) {
               overlap = it -> second;
               break;
           }
       }
      // if our reversed string overlaps completely then we already have a palindrone
      // otherwise we need to append to remainder to the original string
      palindrome = word.append(reversed, overlap, word.length()-overlap);
      if (overlap < (int)word.length())
         cout << palindrome << endl;
      else
         cout << word << endl;;
      
      suffix_map.clear();
   }
   return 0;
}

//gorgeousness
//gorgeousnes s sensuoegrog
//gorgeousnes sensuoegrog