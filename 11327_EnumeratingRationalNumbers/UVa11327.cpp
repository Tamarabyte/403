/* UVa problem: 11327 - EnumeratingRationalNumbers
 *
 * Topic: Number Theory
 *
 * Level: trivial
 *
 * Brief problem description:
 *
 * Solution Summary:
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.cs.uleth.ca/~cheng/contest/hints.html
 *   http://mathworld.wolfram.com/TotientFunction.html
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
#include <cstring>
#include <cmath>


using namespace std;
typedef long long ll;

const ll MAX = 10000001;
ll sieve_size;
bitset<10000001> bits;
long long phi[MAX];
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

int gcd(int i, int j) {
    return j == 0 ? i : gcd(j, i % j);
}

/*
0/1 1
1/1 1
1/2 2
1/3 2
2/3 4
1/4
3/4
1/5
2/5
*/
/* Prints the n-th fraction in Cantor's enumeration. */
void print_fraction(int n)
{
    int d = (-1 + sqrt(1 + 8 * n)) / 2;  /* Diagonals to skip */
    int e = n - d * (d + 1) / 2;         /* Extra steps after the skip.
*/
    int v1 = e <= 1 ? d + e : d + 2 - e;
    int v2 = e <= 1 ?     1 : e;


    printf("%d / %d\n", d % 2 == 0 ? v1 : v2,
                        d % 2 == 0 ? v2 : v1);
}


int phis (int n) {
    int result = n;
    for(int i = 2; i * i <= n; ++i)
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    if(n > 1)
        result -= result / n;
    return result;
}

int main() {
    long long k;
    sieve(100000);

/*
    int result = n;
    for(int i = 2; i * i <= n; ++i)
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    if(n > 1)
        result -= result / n;
    return result;*/

    /*
    memset(phi, 0, sizeof(phi));
    phi[0] = 1;
    for (long long i = 1; i < 10000; ++i)
        phi[i] = i;

    for (long long j = primes[0]; j < primes.size(); ++j)
        for

     for(long long i = 2; i <= 1000000; i++) {
        if(!primes[i]){
            phi[i] = i - 1;
            for(long long j=i;j*i<=1000000;j++){
                phi[j*i]=i;
            }
        }
     }*/




    while(scanf("%lld", &k), k) {
            ll p = EulerPhi(k);
            int m = k;
            int i;
        for(i = 0; ; i++) {
            if(gcd(i, m) == 1)
                p--;
            if(p == 0)  break;
        }
    printf("%d/%d\n", i, m);

    }
}
