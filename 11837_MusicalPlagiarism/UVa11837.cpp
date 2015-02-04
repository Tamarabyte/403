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
#include <iostream>
#include <map>
#include <string>
#include <cmath>

using namespace std;

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

void kmpSearch(int* song, int* snippet, int* table, int song_len, int snip_len) {
    int i = 0;
    int j = 0;

    if (snip_len <= 1) {
        printf("S\n");
        return;
    }
    
    while (i < song_len) {
        while (j >= 0 && song[i] != snippet[j])
            j = table[j];
        ++i;
        ++j;
        if (j == snip_len) {
            printf("S\n");
            return;
        }
    }
    printf("N\n");
}

// print semitone array for debugging
void printSemitoneArray(int *arr, int length) {
    printf("[");
    for (int i = 0; i < length; ++i)
        printf("%d ", arr[i]);
    printf("]\n");
}

void getSemitoneDifferences(int *song, int length) {
    
    map<string, int> notes = {
        {"A", 0},
        {"A#", 1}, {"Bb", 1}, 
        {"B", 2}, {"Cb", 2},
        {"B#", 3}, {"C", 3}, 
        {"C#", 4}, {"Db", 4}, 
        {"D", 5}, 
        {"D#", 6}, {"Eb", 6},
        {"E", 7}, {"Fb", 7}, 
        {"E#", 8}, {"F", 8},
        {"F#", 9}, {"Gb", 9},
        {"G", 10},
        {"G#", 11}, {"Ab", 11}
    };
    
    string note;
    int current, prev, diff;
    
    for (int i = 0; i < length; ++i) {
        cin >> note;
        current = notes[note];
        
        // record the first difference in semitones as 0
        if (i == 0) {
            prev = current;
            song[0] = 0;
            continue;
        }
        
        diff = abs(current - prev);
        if (diff > 6)
            diff = 12 - diff;
        
        song[i] = diff;
        prev = current;
    }
}

int main() {
    int *song;
    int *snippet;
    int *kmpTable;
    
    int song_len, snippet_len;
    
    while (1) {
        cin >> song_len;
        cin >> snippet_len;

        if (!snippet_len && !song_len)
            break;
        
        printf("%d, %d", song_len, snippet_len);
        song = new int[song_len];
        snippet = new int[snippet_len];
        kmpTable = new int[snippet_len + 1];
        
        getSemitoneDifferences(song, song_len);
        getSemitoneDifferences(snippet, snippet_len);
        
        fillKMPTable(kmpTable, snippet, snippet_len);
        
        //for debugging
        // printSemitoneArray(song, song_len);
        // printSemitoneArray(snippet, snippet_len);
        // printSemitoneArray(kmpTable, snippet_len+1);
        
        kmpSearch(song, snippet, kmpTable, song_len, snippet_len);

        delete[] song;
        delete[] snippet;
        delete[] kmpTable;
    }
}