/* UVa problem: 554 Ceaser Cipher
 *
 * Topic: String Processing
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   Given a dictionary of words and a enciphered word, determine the K value
 *   for the classic Caesar Cipher utilizing the dictionary to select a K value which
 *   produces the most matches with words in the dictionary.
 *
 * Solution Summary:
 *   Read input line by line. Split into a substring when a non-alpha character is encountered.
 *   Pass that substring to pig_latinfiy to output per pig latin rules. Output non-alpha characters
 *   as normal.
 *
 * Used Resources:
 *   http://stackoverflow.com/questions/236129/split-a-string-in-c
 *   http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
 *   http://www.udebug.com/UVa/554 (apparently we're supposed to trim leading/trailing whitespace on each line ~_~;)
 *
 * I hereby certify that I have produced the following solution myself
 * using the resources listed above in accordance with the CMPUT 403
 * collaboration policy.
 *
 * --- Tamara Bain
 */
 
 #include <cstdlib>
 #include <iostream>
 #include <set>
 #include <vector>
 #include <string>
 #include <sstream>
 
 
 using namespace std;

// print dictionary for debugging
void print_dictionary(set<string> &dictionary) {
    printf("[ ");
    for(auto &word: dictionary) 
        printf("%s ", word.c_str());

    printf("] \n");
}

void print_encoded_words(string &encoded) {

    int end;
    
    // trim leading and trailing whitespace
    encoded = encoded.substr(encoded.find_first_not_of(" "), encoded.find_last_not_of(" ") + 1);
    
    // for each line greater than 60 characters
    // print the largest complete substring <= 60 characters
   while (encoded.length() > 60) {
        string line = encoded.substr(0, 60);
        end = line.find_last_of(" ");
       
        if (end == -1)
            end = 60;
            
        line = encoded.substr(0, end);
        printf("%s\n", line.c_str());
       
        // set encoded to the remaining string and trim leading whitespace
        encoded = encoded.substr(end+1, encoded.length());
        encoded = encoded.substr(encoded.find_first_not_of(" "), encoded.find_last_not_of(" ") + 1);
    }
    
    // print remaining string
    printf("%s\n", encoded.c_str());
}

void use_key(string &encoded, int K) {
    for (int i = 0; i < encoded.length(); ++i) {
        encoded[i] = (encoded[i] + K) % 91;
        
        // roll over to space instead of the null character
        if (!encoded[i])
            encoded[i] += 32;
        
        // roll over to 'A' instead of '!'
        if ((int)encoded[i] == 33)
            encoded[i] += 32;
    }
}

// find the shift in letters that
// results in the most matching words in our dictionary
void break_encoding(string &encoded, set<string> &dictionary) {
    vector<string> decodes;
    int max_matches = 0, best_cipher = 0;
    int matches;
     
    for (int i = 0; i < 27; ++i) {
        use_key(encoded, 1);
        decodes.push_back(encoded);
        
        // reset matches
        matches = 0;
        
        istringstream iss(encoded);
        while(iss) {
            string word;
            iss >> word;
            
            if (dictionary.count(word))
                matches++;
        }
        
        // record if better than the current best
        if (matches > max_matches) {
            max_matches = matches;
            best_cipher = i;
        }
    }
    
    // print the best decrypted text
    print_encoded_words(decodes.at(best_cipher));
}

int main() {
    
    string word, encoded;
    set<string> dictionary;
    
    // build the dictionary grouping words based on length
    while(getline(cin, word)) {
        
        // stop when we hit the pound symbol
        if (word == "#")
            break;
        
        dictionary.insert(word);
    }

    // get the encoded text
    getline(cin, encoded);
    break_encoding(encoded, dictionary);
}