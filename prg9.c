#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function to compute the order of a modulo m
void compute_order(const mpz_t a, const mpz_t m) {
    mpz_t result;
    mpz_init(result);

    // Initialize k (order) as 1
    mpz_set_ui(result, 1);

    // Initialize base as a
    mpz_t base;
    mpz_init_set(base, a);

    // Loop until we find a^k ≡ 1 (mod m)
    while (1) {
        mpz_t exp_mod_m;
        mpz_init(exp_mod_m);

        // Calculate a^k mod m
        mpz_powm_ui(exp_mod_m, base, mpz_get_ui(result), m);

        // Check if a^k ≡ 1 (mod m)
        if (mpz_cmp_ui(exp_mod_m, 1) == 0) {
            // Found the order
            gmp_printf("%Zd", result);
            break;
        }

        // Increment k
        mpz_add_ui(result, result, 1);

        mpz_clear(exp_mod_m);
    }

    mpz_clears(result, base, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    mpz_t a, m;
    mpz_init_set_str(a, argv[1], 10);
    mpz_init_set_str(m, argv[2], 10);

    compute_order(a, m);

    mpz_clears(a, m, NULL);

    return 0;
}
