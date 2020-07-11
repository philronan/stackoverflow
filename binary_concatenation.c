#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*

https://stackoverflow.com/q/62832231/1679849

OEIS sequence #A047778 (https://oeis.org/A047778) contains the numbers made
by concatenating successive binary numbers 1, 10, 11, 100, 101, 110, 111,
1000, 1001, etc.

    So for example, a(1) = 0b1 = 1
                    a(2) = 0b110 = 6
                    a(3) = 0b11011 = 27
                    a(4) = 0b11011100 = 220
                    ... etc...

This program calculates the nth number in this sequence modulo 10^9+7, for
0 < n < 10^9

To produce faster results, it uses precomputed values for multiples of 2^24

The value of n is specified as a command line argument. If absent, this
program outputs the lookup table values instead.

*/

#define MODULUS 1000000007ULL

// Uncomment to use slower method
// #define SLOW

#ifdef SLOW

// Slow method. Takes about 4 seconds when n==10^9

int binary_seq_val(int n) {
    int i, j, size = 0;
    uint64_t result = 0;
    for (i=1, j=0; i<=n; i++, j++) {
        if (!(i & j)) size++;
        result = ((result << size) | i) % MODULUS;
    }
    return (int)result;
}

#else

// Faster method with precomputed lookup table

int binary_seq_val(int n) {
    int precomputed[64] = { 0, 602314637, 51379122, 465651263, 684104024, 195521544,
                            29040762, 843581539, 261014002, 848303231, 993209631,
                            725831972, 967930126, 947284282, 618061897, 334537561,
                            803962448, 125527804, 602809957, 214414317, 418280627,
                            431601111, 451036446, 917874844, 979573585, 24044881,
                            828122192, 919844164, 619477858, 159183972, 285377864,
                            519701203, 140415634, 732040424, 352054480, 180877210,
                            771913019, 793074781, 182309639, 397724167, 551695211,
                            396003433, 877138330, 499763341, 129600701, 44917160,
                            248777949, 738380982, 828137692, 867475290, 418953303,
                            642060801, 844698532, 641754445, 192324896, 973391673,
                            379762209, 958404293, 442065381, 886142150, 5097144,
                            942850195, 289634875, 976685002 };
    int i, j, x, size;
    uint64_t result;
    
    x = n >> 24;
    if (x > 63) x = 63;
    j = x << 24;
    result = precomputed[x];
    for (size = 0; (1 << size) <= j; size++);
    for (i=j+1; i<=n; i++, j++) {
        if (!(i & j)) size++;
        result = ((result << size) | i) % MODULUS;
    }
    return (int)result;
}

#endif

void generate_lookup_table() {
    int i, j, size = 0;
    uint64_t result = 0;
    for (i=1, j=0; i<1<<30; i++, j++) {
        if (!(j & 0xffffff)) printf("%lld, ", result);
        if (!(i & j)) size++;
        result = ((result << size) | i) % MODULUS;
    }
    putchar('\n');
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        generate_lookup_table();
        return 0;
    }
    int n = atoi(argv[1]);
    printf("%d\n", binary_seq_val(n));
    return 0;
}
