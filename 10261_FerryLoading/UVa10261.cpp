/* UVa problem: 10261 - FerryLoading
 *
 * Topic: Dynamic Programming
 *
 * Level: non-trivial
 *
 * Brief problem description: Given a double-lane ferry of a certain length
 *   and a queue of cars with varying lenghts, find the maximum number
 *   of cars you can fit on the ferry and the sides of the ferry (port/starboard)
 *   that these cars should be loaded on. You are not allowed to skip cars in the queue.
 *
 * Solution Summary: Use dynamic programming top-down approach. As suggested by
 *   Competitive Programming 3 the state is (current_car, length_of_left, length_of_right).
 *   This is memoized by the length of the left hand side (this is sufficient because
 *   if cars are loaded on oppsite sides the results are symmetrical. After the memo
 *   table is build, traverse it to print out the directions for where the cars should be loaded.
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
#include <cstring>
#include <algorithm>
#include <cassert>

#define UNSET -1
using namespace std;

const int max_cars = 201;
int cars[max_cars];
int memo[max_cars][10001];
int N, ferry_size, result;

/* This function outputs the answer by and using
 * the memo table, as suggest in Competitive Programming 3
 * Section 3.5 */
void print_side(int i, int left, int right) {

    // stop once we've gone over the number
    // included in the result
    if (i == result)
        return;
    
    // The following logic echos the traversal
    // in 'onboard' except it uses the memo table
    // to lookup the correct path
    
    int new_left = left + cars[i];
    int new_right = right + cars[i];

    if (new_left > ferry_size)  {
        printf("starboard\n");
        print_side(i+1, left, new_right);
    }
    else if (new_right > ferry_size) {
        printf("port\n"); 
        print_side(i+1, new_left, right);
    }
    else {
        if( memo[i+1][new_left] >= memo[i+1][left] ) {
            printf("port\n"); 
            print_side(i+1, new_left, right);
        } else {
            printf("starboard\n");
            print_side(i+1, left, new_right);
        }
    }
}

/* Dynamic programming top-down approach
 * traverse the possible solutions and cache results in
 * a memo table */
int onboard(int i, int left, int right) {
    
    // Stop once we've gone over each car in input
    if (i == N) 
        return 0;
    
    // caculate the new length of the cars on the
    // right/left side with the addition of the current car
    int new_left = left + cars[i];
    int new_right = right + cars[i];
    
    // if neither side can be added to without exceeding 
    // the ferry boundary then stop
    if (new_left > ferry_size && new_right > ferry_size)
        return 0;

    // retrieve value from cache or continue
    // recursive traversal and save result in cache
    int &cached = memo[i][left];
    
    if (cached == UNSET) {
        if (new_left > ferry_size) // left is out of bounds, add to right
            cached = onboard(i+1, left, new_right) + 1;
        else if (new_right > ferry_size) // right is out of bounds, add to left
            cached = onboard(i+1, new_left, right) + 1;
        else
            cached = max(onboard(i+1, new_left, right) + 1, onboard(i+1, left, new_right) + 1); // take best result of left or right
    }
    
    return cached;
}

int main() {
    int test_cases, car_size;
    scanf("%d", &test_cases);
    
    // for each test case
    while(test_cases--) {
        scanf("%d", &ferry_size);
        ferry_size *= 100;
        
        // reset # of cars and memo table
        N = 0;
        memset(memo, UNSET, sizeof(memo));
        
        // read in cars
        while(scanf("%d", &car_size), car_size) {
            cars[N] = car_size;
            ++N;
            if (N == max_cars)
                break;
        }
        
        if (N == 0 || cars[0] > ferry_size) { result = 0; }
        else { result = onboard(0, 0, 0); } 

        // print results
        printf("%d\n", result);
        print_side(0, 0, 0);
        if (test_cases)
            printf("\n");
    }
}