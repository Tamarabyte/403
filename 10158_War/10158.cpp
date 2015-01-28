/* UVa problem: 10158 - War
 *
 * Topic: Data Structures
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   Determine which group of people are friends and which are enemies. Answer true and false statements
     about them based on input.
 *
 * Solution Summary:
 *   Used disjoint sets as suggested by competitive programming 3.
 *   Contains a second array 'enemies' which maps the root of a
 *   disjoint set to the root of it's enemy set. Also implemented path compressing.
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
#include <iostream>

using namespace std;


struct disjoint_set {

  // array of represenatives
  int* reps;

  // root of the set containing enemies
  // all members of one country will have the same enemies
  int* enemies;

  // constructor
  disjoint_set(int size) {

    reps = new int[size];
    enemies = new int[size];

    // each element starts out represeting itself
    for (int i = 0; i < size; ++i) {
      reps[i] = i;
      // no enemies at the start
      enemies[i] = -1;
    }
  }

  //destructor
  ~disjoint_set() {
    delete[] reps;
    delete[] enemies;
  }

  int find_rep(int element) {
    int parent = reps[element];

    // if the parent is the element
    // then we've reached the root of our set
    if (parent == element) {
      return element;
    }

    // shorten the path to the root
    // by updating rep with root
    reps[element] = find_rep(parent);

    // return root
    return reps[element];
  }

  // check if two elements belong to the same set
  bool same_set(int element1, int element2) {
    int rep1 = find_rep(element1);
    int rep2 = find_rep(element2);

    if (rep1 == rep2)
      return true;

    return false;
  }

  void merge_set(int element1, int element2) {
    int rep1 = find_rep(element1);
    int rep2 = find_rep(element2);

    // if representatives are the same
    // then both elements are in the same group
    if (rep1 == rep2)
      return;

    // otherwise we have to merge

    // merge friends
    reps[rep1] = rep2;

    // merge enemies
    int enemies1 = enemies[rep1];
    int enemies2 = enemies[rep2];

    if(enemies1 == -1) {
        return;
    }
    else if (enemies2 == -1) {
      // set the enemies of rep2 to the enemies of rep1
      enemies[rep2] = enemies1;
      // link the enemies back to rep2
      enemies[enemies1] = rep2;
    }
    else {
      // link rep1's enemies to rep2's
      reps[enemies1] = enemies2;
      // link the set of enemies back to rep2
      enemies[enemies2] = rep2;
    }
  }

  // set two groups as enemies to eachother
  void set_enemies(int rep1, int rep2) {
    if(enemies[rep1] == -1)
      enemies[rep1] = rep2;
    else
      merge_set(enemies[rep1], rep2);

    if(enemies[rep2] == -1)
      enemies[rep2] = rep1;
    else
      merge_set(enemies[rep2], rep1);

  }
};

void print_answer(int answer) {
  printf("%d\n", answer);
}

int main() {

  int total, code, personA, personB, repA, repB;
  enum codes { SetFriends=1, SetEnemies, AreFriends, AreEnemies };
  enum answer { error=-1, no, yes };

  // read number of people
  scanf("%d", &total);

  // set up our disjoint set
  disjoint_set countrymen(total);

  // read line
  while(scanf("%d %d %d", &code, &personA, &personB), (code || personA || personB)) {

    repA = countrymen.find_rep(personA);
    repB = countrymen.find_rep(personB);

    switch(code) {
      case SetFriends :
        if(countrymen.enemies[repA] == repB)
          print_answer(error);
        else
          countrymen.merge_set(repA, repB);
        break;

      case SetEnemies :
        if((countrymen.enemies[repA] == countrymen.enemies[repB] && countrymen.enemies[repA] != -1) || repA == repB)
          print_answer(error);
        else
          countrymen.set_enemies(repA, repB);
        break;

      case AreFriends :
        if (repA == repB)
          print_answer(yes);
        else
          print_answer(no);
        break;

      case AreEnemies :
        if(countrymen.enemies[repA] == repB && countrymen.enemies[repA] != -1)
          print_answer(yes);
        else
          print_answer(no);
        break;
    }
  }

}
