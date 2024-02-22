#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function to calculate Euler's totient function (phi)
void phi(const mpz_t m) {
    mpz_t result, i, gcd;
    mpz_init(result);
    mpz_init(i);
    mpz_init(gcd);

    mpz_set_ui(result, 1);

    for (mpz_set_ui(i, 2); mpz_cmp(i, m) < 0; mpz_add_ui(i, i, 1)) {
        mpz_gcd(gcd, i, m);
        if (mpz_cmp_ui(gcd, 1) == 0) {
            mpz_add_ui(result, result, 1);
        }
    }

    gmp_printf(" %Zd", result);

    mpz_clears(result, i, gcd, NULL);
}

// Function to calculate RRSM_m set of integers
void rrsm(const mpz_t m) {
    mpz_t i, gcd;
    mpz_init(i);
    mpz_init(gcd);

    // Print the first element of RRSM_m
   printf("1");

    // Iterate through numbers from 2 to m-1
    for (mpz_set_ui(i, 2); mpz_cmp(i, m) < 0; mpz_add_ui(i, i, 1)) {
        mpz_gcd(gcd, i, m);
        if (mpz_cmp_ui(gcd, 1) == 0) {
            // If i is coprime to m, print it
            printf(" %s", mpz_get_str(NULL, 10, i));
        }
    }


    mpz_clears(i, gcd, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <m>\n", argv[0]);
        return 1;
    }

    mpz_t m;
    mpz_init(m);
    mpz_set_str(m, argv[1], 10);

    rrsm(m);
    phi(m);

    mpz_clear(m);

    return 0;
}
