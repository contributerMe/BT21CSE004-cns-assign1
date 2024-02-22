#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function to compute (base^exp) % mod using modular exponentiation
void mod_exp(mpz_t result, const mpz_t base, const mpz_t exp, const mpz_t mod) {
    mpz_powm(result, base, exp, mod);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    mpz_t a, x, n, result;
    mpz_inits(a, x, n, result, NULL);

    // Set values from command line arguments
    mpz_set_str(a, argv[1], 10);
    mpz_set_str(x, argv[2], 10);
    mpz_set_str(n, argv[3], 10);

    // Calculate mod = a^x mod n
    mod_exp(result, a, x, n);
    gmp_printf("%Zd",  result);

    // Clear memory
    mpz_clears(a, x, n, result, NULL);

    return 0;
}
