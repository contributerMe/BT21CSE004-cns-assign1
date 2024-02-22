#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void print_divisors(const mpz_t n) {
    mpz_t i;
    mpz_init(i);

    int first = 1; // Flag to determine if it's the first divisor

    for (mpz_set_ui(i, 1); mpz_cmp(i, n) <= 0; mpz_add_ui(i, i, 1)) {
        // If 'n' is divisible by 'i', then 'i' is a divisor
        if (mpz_divisible_p(n, i)) {
            if (!first) {
                printf(" "); // Print space before each divisor (except the first one)
            } else {
                first = 0;
            }
            gmp_printf("%Zd", i);
        }
    }

    mpz_clear(i);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }

    int n = atoi(argv[1]);
    if (n != argc - 2) {
        return 1;
    }

    mpz_t gcd, temp;
    mpz_init(gcd);
    mpz_init(temp);

    // Process the numbers
    for (int i = 2; i < argc; i++) {
        if (mpz_set_str(temp, argv[i], 10) != 0) {
            mpz_clear(gcd);
            mpz_clear(temp);
            return 1;
        }
        if (i == 2) {
            mpz_set(gcd, temp);
        } else {
            mpz_gcd(gcd, gcd, temp);
        }
    }

    // Print common divisors
    print_divisors(gcd);

    // Clear memory
    mpz_clear(gcd);
    mpz_clear(temp);
    return 0;
}
