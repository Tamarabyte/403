/* UVa problem: 665
 *
 * Topic: Data Structures
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   A false coin weighs differently from the real coins. Given the
 *   results of the weighings, find the false coin if possible.
 *
 * Solution Summary:
 *   Used an array of ints for coins where 1 represents the coin being real
 *   and 0 represents the coin being unknown. Used a flag to keep track if we know
 *   the fake coin is heavier or lighter than a real coin.
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

using namespace std;

// return whehter we know the left side is all real coins
// the right side is all real coins or we're unsure
// this is useful for determining whether the fake coin is
// heavier or lighter tha the real coins
enum {unknown, left_real, right_real};

// read in input for the two sides and their
// comparator value
void weigh(int placed, int *sideA, int *sideB, char *op) {
  for(int i = 0; i < placed; ++i)
    scanf("%d", &sideA[i]);

  for(int i = 0; i < placed; ++i)
    scanf("%d", &sideB[i]);

  scanf("%s", &op[0]);
}

// given a list of coins from a side of the scale
// mark the corresponding coins in the coin array
// as real (integer 1)
void mark_true(int *coins, int* side, int placed) {
  int coin;

  for(int i=0; i < placed; ++i) {
    coin = side[i];
    coins[coin-1] = 1;
  }
}

// Check if all the left side or all the right side is known
// to be real. Used to determine if the fake coin is heavier or lighter
// then the real coins.
int check_sides(int *coins, int *sideA, int *sideB, int placed) {
  bool left = true;
  bool right = true;
  int coin;

  for(int i=0; i < placed; ++i) {
    coin = sideA[i];
    if (!coins[coin-1]) {
      left = false;
      break;
    }
  }

  if(left)
    return left_real;

  for(int i=0; i < placed; ++i) {
    coin = sideB[i];
    if (!coins[coin-1]) {
      right = false;
      break;
    }
  }

  if(right)
    return right_real;

  return unknown;
}

 int main() {

  int testcases, total, weighings, placed, result, fakeIsHeavier;
  int *coins, *sideA, *sideB;
  char *op = new char[1];

  testcases = 1;
  scanf("%d", &testcases);

  // for each test case
  while(testcases--) {

    // set up the number of coins and weighings done
    scanf("%d %d", &total, &weighings);
    // reset the array of coins
    coins = new int[total]();
    // reset our knowledge about whether the fake is
    // heavier or not
    fakeIsHeavier = -1;

    // for each weighing
    while(weighings--) {

      // read the number of coins placed on each
      // side of the scale and initialize
      // an array for each side
      scanf("%d", &placed);

      sideA = new int[placed];
      sideB = new int[placed];

      // weight the coins (record coins placed)
      // on scale and the difference between the
      // two sides
      weigh(placed, sideA, sideB, op);

      // cases based on comparison of the two sides
      switch(op[0]) {

        // left side is lighter
        // the fake is present
        case '<' :
          // if we already know that the fake is
          // heavier we can mark the lighter side as
          // all real
          if(fakeIsHeavier == 1) {
              mark_true(coins, sideA, placed);
          }
          // vice versa
          else if (fakeIsHeavier == 0) {
              mark_true(coins, sideB, placed);
          }
          // if we don't have knowledge about whether
          // the fake is heavier/lighter we should
          // see if we can deduce that by checking
          // the coin on each side
          else {
            result = check_sides(coins, sideA, sideB, placed);
            if (result == left_real)
              fakeIsHeavier = 1;
            else if (result == right_real)
              fakeIsHeavier = 0;
          }
          break;

        // opposite of the above
        case '>' :
          if(fakeIsHeavier == 0) {
              mark_true(coins, sideA, placed);
          }
          else if (fakeIsHeavier == 1) {
              mark_true(coins, sideB, placed);
          }
          else {
            result = check_sides(coins, sideA, sideB, placed);
            if (result == left_real)
              fakeIsHeavier = 0;
            else if (result == right_real)
              fakeIsHeavier = 1;
          }
          break;

        // if both sides are equal we are
        // dealing with real coins on each side
        case '=' :
          mark_true(coins, sideA, placed);
          mark_true(coins, sideB, placed);
          break;
      }

      // clear our sides
      delete[] sideA;
      delete[] sideB;
    }

    // after all weighings we'll count potential fakes
    // if we have more than one we can't determine the fake
    int count_potential_fakes = 0, fake = 0;
    for(int i = 0; i < total; ++i) {
      if(!coins[i]) {
        fake = i+1;
        ++count_potential_fakes;
      }
    }

    if (count_potential_fakes > 1)
      printf("%d", unknown);
    else
      printf("%d", fake);

    // UVA will mark it wrong if you have two
    // newlines at the end :(
    if (testcases)
      printf("\n\n");
    else
      printf("\n");

    delete[] coins;
  }

  delete op;
 }
