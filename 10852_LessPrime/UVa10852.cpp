/* UVa problem: 10852 - LessPrime
 *
 * Topic: Number Theory
 *
 * Level: trivial
 *
 * Brief problem description:
 *  Given a number n (<= 10000 and >= 100) find a prime number x
 *  x <= n such that n - p*x is as large as possible and p*x <= n < (p+1)*x.
 *  (because x is maximized when p = 1 this is: x <= n < 2x
 *
 * Solution Summary:
 *  I implemented sieve of eratosthenes to generate all primes less than
 *  the max input (we know the prime is less than n). I then brute-forced looking for the
 *  lowest prime that met the criteria.
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
#include <bitset>
#include <vector>

using namespace std;
typedef long long ll;

ll sieve_size;
bitset<10000001> bits;
vector<int> primes;


// sieve implementation referenced from
// Competitive Programming 3
void sieve(ll upper) {
    sieve_size = upper + 1;
    bits.set();

    for (ll i = 2; i <= sieve_size; ++i) {

        // if i is already crossed out then continue
        if (!bits[i])
            continue;

        // cross out multiples of i
        for (ll j = i*i; j <= sieve_size; j +=i)
            bits[j] = 0;

        primes.push_back((int)i);
    }
}

bool is_prime(ll num) {

    // retrieve from sieve if possible
    if (num <= sieve_size)
        return bits[num];

    // otherwise use the sieve to calculate
    for (int i = 0; i < (int)primes.size(); i++) {
        if (num % primes[i] == 0)
            return false;
    }

    return true;
}

int main() {
    int tests, n;

    sieve(10000/2);
    scanf("%d", &tests);

    while(tests--) {
        scanf("%d", &n);

        // 2x must be greater than n
        // so any number within 2x + 1 and n fits our criteria
        for (int i = n/2 + 1; i <= n; ++i)
            if (is_prime(i)) {
                printf("%d\n", i);
                break;
            }
    }


}
