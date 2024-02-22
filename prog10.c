#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function to compute the greatest common divisor (gcd) of two integers
void calculate_gcd(const mpz_t a, const mpz_t b, mpz_t result) {
    mpz_gcd(result, a, b);
}

// Function to compute the totient function phi(m)
void compute_phi(const mpz_t m, mpz_t result) {
    mpz_t i, gcd_result;
    mpz_init_set_ui(result, 1);
    mpz_init(i);
    mpz_init(gcd_result);

    for (mpz_set_ui(i, 2); mpz_cmp(i, m) < 0; mpz_add_ui(i, i, 1)) {
        calculate_gcd(i, m, gcd_result);
        if (mpz_cmp_ui(gcd_result, 1) == 0) {
            mpz_add_ui(result, result, 1);
        }
    }

    mpz_clears(i, gcd_result, NULL);
}

// Function to compute the power of a modulo m
void mod_pow(mpz_t result, const mpz_t base, const mpz_t exp, const mpz_t mod) {
    mpz_powm(result, base, exp, mod);
}

// Function to check if a is a primitive root modulo m
int is_primitive_root(const mpz_t a, const mpz_t m) {
    mpz_t phi_m, i, res;
    mpz_inits(phi_m, i, res, NULL);

    // Compute phi(m)
    compute_phi(m, phi_m);

    // Check if a^phi(m) ≡ 1 (mod m)
    mod_pow(res, a, phi_m, m);
    if (mpz_cmp_ui(res, 1) != 0) {
        return 0; // a is not a primitive root
    }

    // Check if a^k ≡ 1 (mod m) for any k < phi(m)
    for (mpz_set_ui(i, 2); mpz_cmp(i, phi_m) < 0; mpz_add_ui(i, i, 1)) {
        mod_pow(res, a, i, m);
        if (mpz_cmp_ui(res, 1) == 0) {
            return 0; // a is not a primitive root
        }
    }

    mpz_clears(phi_m, i, res, NULL);
    return 1; // a is a primitive root
}

// Function to find and print all primitive roots modulo m
void find_primitive_roots(const mpz_t m) {
    mpz_t i, root;
    mpz_inits(i, root, NULL);
     int count = 0;
      for (mpz_set_ui(i, 2); mpz_cmp(i, m) < 0; mpz_add_ui(i, i, 1)) {
        if (is_primitive_root(i, m)) {
            count++;
        }
    }
    printf("%d ", count);

    // printf("Primitive roots modulo %s: ", mpz_get_str(NULL, 10, m));
     // Check each number from 2 to m-1
    for (mpz_set_ui(i, 2); mpz_cmp(i, m) < 0; mpz_add_ui(i, i, 1)) {
        if (is_primitive_root(i, m)) {
            printf("%s ", mpz_get_str(NULL, 10, i));
            count++;
        }
    }

    mpz_clears(i, root, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    mpz_t m;
    mpz_init_set_str(m, argv[1], 10);

    find_primitive_roots(m);

    mpz_clear(m);

    return 0;
}
