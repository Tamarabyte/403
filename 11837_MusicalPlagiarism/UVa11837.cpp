/* UVa problem: 11837 - Musical Plaigiarism
 *
 * Topic: Strings
 *
 * Level: trivial
 *
 * Brief problem description:
 *   Determine whether a musical snippet contains the same semitones as the entire score.
 *
 * Solution Summary:
 * First I transformed each set of notes to an array of digits where each digit is the number
 * of semitones difference between the note and the previous note. Then I used
 * the KMP algorithm (as presented in competitive programming 3) to compare
 * the musical snippet array with the array for the entire score.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   uDebug - http://www.udebug.com/UVa/11837 (to compare expected output)
 *
 * I hereby certify that I have produced the following solution myself
 * using the resources listed above in accordance with the CMPUT 403
 * collaboration policy.
 *
 * --- Tamara Bain
 *
 *  Language: C++11
 */

#include <cstdio>
#include <map>
#include <string>

using namespace std;

// create the KMP Table
// Code adapted from Competitive Programming 3
void fillKMPTable(int* kmpTable, int* snippet, int len) {
    int i = 0;
    int j = -1;

    kmpTable[0] = -1;
    while (i < len) {
        while (j >=0 && snippet[i] != snippet[j])
            j = kmpTable[j];
        ++j;
        ++i;
        kmpTable[i] = j;
    }
}

// use KMP Search
// Code adapted from Competitive Programming 3
void kmpSearch(int* song, int* snippet, int* table, int song_len, int snip_len) {
    int i = 0;
    int j = 0;

    if (snip_len == 1) {
        printf("S\n");
        return;
    }

    // we care 1 less than song size
    // because we only care about the differences
    // between notes
    while (i < song_len-1) {
        while (j >= 0 && song[i] != snippet[j])
            j = table[j];
        ++i;
        ++j;
        if (j == snip_len-1) {
            printf("S\n");
            return;
        }
    }
    printf("N\n");
}

// translate the input into semitone differences
void getSemitoneDifferences(int *song, int length) {

    // spaces between our notes
    map<char, int> notes = {
        {'A', 0},
        {'B', 2},
        {'C', 3},
        {'D', 5},
        {'E', 7},
        {'F', 8},
        {'G', 10},
    };
   // modifier values
   map<char, int> modifiers = {
        {'#', 1},
        {'b', -1},
        {'\0', 0}
    };


    char note[3];
    int current, prev, diff;
    prev = 0;

    for (int i = 0; i < length; ++i) {
        scanf("%s", note);

        current = notes[note[0]] + modifiers[note[1]];
        current = (current + 12) % 12;

        // record the first difference in semitones as 0
        if (i == 0) {
            prev = current;
            song[0] = 0;
            continue;
        }

        diff = (current - prev + 12) % 12;
        prev = current;
        song[i-1] = diff;
    }
}

int main() {
    int *song;
    int *snippet;
    int *kmpTable;

    int song_len, snippet_len;

    while (scanf("%d %d", &song_len, &snippet_len) && (song_len || snippet_len)) {
        // read the song length and snippet length
        song = new int[song_len];
        snippet = new int[snippet_len];
        // create the kmp table
        kmpTable = new int[snippet_len + 1];

        getSemitoneDifferences(song, song_len);
        getSemitoneDifferences(snippet, snippet_len);

        fillKMPTable(kmpTable, snippet, snippet_len);

        kmpSearch(song, snippet, kmpTable, song_len, snippet_len);

        delete[] song;
        delete[] snippet;
        delete[] kmpTable;
    }
}