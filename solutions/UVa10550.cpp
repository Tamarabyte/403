/* UVa problem: 10550 - Combination Lock
 *
 * Topic: Other
 *
 * Level: trivial
 *
 * Brief problem description:
 *   Determine the number of degrees a combination lock
 *   is rotated.
 *
 * Solution Summary:
 *   Trick is realizing that on the lock turning clockwise makes the numbers go down
 *   and turning counter clockwise makes them go up.
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

int main() {

   int start, num1, num2, num3, degrees;

   while (scanf("%d %d %d %d", &start, &num1, &num2, &num3), (start || num1 || num2 || num3)) {

      // Each combination will have full clockwise turns and one counter-clockwise turn
      degrees = 1080;

      // first number
      if (num1 > start)
         degrees += (40-num1+start) * 9;
      else
         degrees += (start-num1) * 9;

      // second number
      if (num2 < num1)
         degrees += (40-num1+num2) * 9;
      else
         degrees += (num2-num1) * 9;

      // third number
      if (num3 > num2)
         degrees += (40-num3+num2) * 9;
      else
         degrees += (num2-num3) * 9;

      printf("%d\n", degrees);
   }
}
