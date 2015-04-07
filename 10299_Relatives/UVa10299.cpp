/* UVa problem: 10299 - Relatives
 *
 * Topic: Number Theory
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Given positive integer n find the number of positive
 *  integers *less* than n are relatively prime to n.
 *
 * Solution Summary:
 *   This can be solved with the Euler Phi Totiten function.
 *   I implemented a sieve for finding primes, and then
 *   used those primes and the euler phi totient function
 *   to find the relatively prime positive integers less than N.
 *   Missed the 'less than N' on my first submission.
 *
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


// EulerPhi referenced from
// Competitive Programming 3
ll EulerPhi(ll num) {
    // special case for this problem
    // we want all positive integers
    // less than n
    if (num == 1)
        return 0;

    ll i = 0;
    ll prime_factor = primes[i];
    ll counts = num;

    // get relatively prime numbers < num
    while (prime_factor * prime_factor <= num) {
        if (num % prime_factor == 0)
            counts -= counts / prime_factor;

        while (num % prime_factor == 0)
            num /= prime_factor;

        prime_factor = primes[++i];
    }

    if (num!= 1)
        counts -= counts / num;
    return counts;
}

int main() {
    int n;
    sieve(100000);

    while(scanf("%d", &n), n)
        printf("%lld\n", EulerPhi(n));

}
