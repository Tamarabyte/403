/* UVa problem: 11572 - GATTICA
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
