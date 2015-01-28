/* UVa problem: 11572 - Unique Snowflakes
 *
 * Topic: Data Structures
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   Get the longest sequence of unique elements. (in this case snowflakes with unique sizes)
 *
 * Solution Summary:
 *   This is in the map section of CP3. It's pretty straight forward with the map STL data structure.
 *   just map the size to the position it last occurred. And keep track of the start position in a series.
 *   Once you hit a snowflake that has an position >= start position you have to seal the bag.
 *   Count the size as position that ends the run - position of the first snowflake and update maximum if neccesary.
 *   Then start a new sequence from one index after the index of the previously saved duplicate.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *
 * I hereby certify that I have produced the following solution myself
 * using the resources listed above in accordance with the CMPUT 403
 * collaboration policy.
 *
 * --- Tamara Bain
 */

#include <cstdio>
#include <map>

using namespace std;

int main() {

   int testcases, snowflakes, start, max_run;
   long snowflake;

   // map size to position
   map<long, int> encountered;

   // for each test case
   scanf("%d", &testcases);
   while(testcases--) {

      // read each the number of snowflakes
      scanf("%d", &snowflakes);
      // reset the sequence starting position and the size of
      // the longest sequence
      start = 0;
      max_run = 0;

      for (int i = 0; i < snowflakes; ++i) {

         scanf("%ld", &snowflake);
         auto it = encountered.find(snowflake);

         // first time encountering the snowflake in this sequence
         if(it == encountered.end() || (it->second) < start) {
            encountered[snowflake] = i;
            continue;
         }

         // otherwise we have to end the sequence here
         // record the run if it exceeds the current maximum
         if (max_run < (i - start))
            max_run = i - start;

         // start a new sequence at the index just past
         // our recorded duplicate
         start = (it->second) + 1;

         // save the snowflakes position as the most
         // recent encounter for that snowflake in the new sequence
         encountered[snowflake] = i;
      }

     // record the run if it exceeds the current maximum
     if (max_run < (snowflakes - start))
        max_run = snowflakes - start;

      printf("%d\n", max_run);
      encountered.clear();
   }
}
