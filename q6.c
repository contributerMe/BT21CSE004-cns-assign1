#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function to compute the multiplicative inverse of a modulo m
void multiplicative_inverse(const mpz_t a, const mpz_t m) {
    mpz_t gcd;
    mpz_init(gcd);

    // Compute the greatest common divisor of a and m
    mpz_gcd(gcd, a, m);

    // Check if gcd(a, m) equals 1 (i.e., a and m are coprime)
    if (mpz_cmp_ui(gcd, 1) == 0) {
        printf("Y ");

        // Compute the multiplicative inverse of a modulo m
        mpz_t inv;
        mpz_init(inv);
        mpz_invert(inv, a, m);

        // Print the multiplicative inverse
        gmp_printf("%Zd ", inv);

        // Clear memory
        mpz_clear(inv);
    } else {
        printf("N");
    }

    mpz_clear(gcd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    mpz_t a, m;
    mpz_init_set_str(a, argv[1], 10);
    mpz_init_set_str(m, argv[2], 10);

    multiplicative_inverse(a, m);

    mpz_clears(a, m, NULL);

    return 0;
}
