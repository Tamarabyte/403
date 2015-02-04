/* UVa problem: 10608 - Friends
 *
 * Topic: Data Structures
 *
 * Level: trivial
 *
 * Brief problem description:
 *   Determine the largest set of friends given pairs of friends.
 *
 * Solution Summary:
 *   Used disjoint sets as suggested by competitive programming 3.
 *   I didn't implement path compressing/ranks because it wasn't
 *   neccesary for the time limit.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.mathblog.dk/disjoint-set-data-structure/
 *
 * I hereby certify that I have produced the following solution myself
 * using the resources listed above in accordance with the CMPUT 403
 * collaboration policy.
 *
 * --- Tamara Bain
 */

#include <cstdio>

using namespace std;

struct disjoint_set {

   // array of represenatives
   int* reps;
   int* sizes;
   // constructor
   disjoint_set(int size) {

      // offset by 1 so we can look up by friend number
      reps = new int[size+1];
      // reps[0] will hold the length
      reps[0] = size;

      // size[0] will be max size so far
      sizes = new int[size+1];
      sizes[0] = 1;

      // each element starts out represeting itself
      for (int i = 1; i <= size; ++i) {
         reps[i] = i;
         sizes[i] = 1;
      }
   }

   //destructor
   ~disjoint_set() {
      delete[] reps;
      delete[] sizes;
   }

   int find_rep(int element) {
      int parent = reps[element];

      // if the parent is the element
      // then we've reached the root of our set
      if (parent == element) {
         return element;
      }

      // otherwise continue traverssing until
      // we reach the root
      return find_rep(parent);
   }

   void merge_set(int element1, int element2) {
      int rep1 = find_rep(element1);
      int rep2 = find_rep(element2);

      // if representatives are the same
      // then both friends are in the same group
      if (rep1 == rep2)
         return;

      // otherwise point the representative of
      // friend1 to the representative of friend2
      reps[rep1] = rep2;
      sizes[rep2] = sizes[rep1] + sizes[rep2];

      if (sizes[rep2] > sizes[0]) {
         sizes[0] = sizes[rep2];
      }
   }
};

int main() {

   int test_cases, population, pairs, friend1, friend2;

   // read number of test cases
   scanf("%d", &test_cases);

   // read test cases
   while(test_cases--) {
      scanf("%d %d", &population, &pairs);
      disjoint_set friends(population);

      // read pairs
      while(pairs--) {
         scanf("%d %d", &friend1, &friend2);
         friends.merge_set(friend1, friend2);
      }

      printf("%d\n", friends.sizes[0]);
   }

}
