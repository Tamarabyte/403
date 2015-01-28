/* UVa problem: 492 Pig-Latin
 *
 * Topic: String Processing
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   Convert input into pig latin for output.
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
 
 #include<iostream>
 #include <string>
 
 using namespace std;
 
 void pig_latinify(string pre) {
    char first = tolower(pre[0]);
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    
    for(char &vowel: vowels) {
        if(vowel==first) {
            printf("%say", pre.c_str());
            return;
        }
    }
    
     printf("%s%cay", pre.substr(1, pre.length()-1).c_str(), pre[0]);
 }
 
 int main() {
     
     int start, length;
     string line, latin;
     
     while(getline(cin, line)) {
         
        // parse each lines looking for the end of alphabetic sequences
        start = 0;
        length = line.length();
         
        for(int i=0; i<length; ++i) {
    
            if (!isalpha(line[i])) {
                
                // if we've formed an alphabetic sequence pig latin it
                if(i - start)
                    pig_latinify(line.substr(start, i-start));

                // print the non-alphabetic character
                printf("%c", line[i]);
                // reset or sequence
                start = i + 1;
            }
            else if (i == length-1) {
                // print the last string on the line
                pig_latinify(line.substr(start, i-start+1));
            }
        }
        
        // print end of line new line character
        printf("\n");
     }
 }