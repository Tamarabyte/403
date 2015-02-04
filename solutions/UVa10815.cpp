/* UVa problem: 10815 - Andy's First Dictionary
 *
 * Topic: Data Structures
 *
 * Level: trivial
 *
 * Brief problem description:
 *   Read in words and sort them in case-insensitive order.
 *
 * Solution Summary:
 *   Competitive Programming suggets 'strings and sets' for this problem.
 *   Gave that a try. Had to filter out non-numerics. Took me a few submissions
 *   because I wasn't handling apostrophes properly
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.cplusplus.com/reference/cctype/isalpha/
 *
 * I hereby certify that I have produced the following solution myself
 * using the resources listed above in accordance with the CMPUT 403
 * collaboration policy.
 *
 * --- Tamara Bain
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main() {

   string substring, word;
   set<string> dict;

   while(cin >> word) {

      int len = word.size();

      // transform to lowercase
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);

      // iterate through each character
      // processing strings to store
      for (int i = 0; i < len; i++) {

         if (word[i] >= 'a' && word[i] <='z') {

            if(i==len-1)
               dict.insert(word);
         }
         else {

            // store the previous string if neccesary
            if(i) {
               substring = word.substr(0, i);
               dict.insert(substring);
            }

            // if we've reached the end of the word then stop
            if(i==len-1)
               break;

            // our word is the next substring, reset start and end
            // positions for the for loop
            word = word.substr(i+1, len);
            i = -1;
            len = word.length();
         }
      }

   }

   for(auto it : dict)
      cout << it << "\n";
}
