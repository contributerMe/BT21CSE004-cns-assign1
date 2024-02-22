#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function to compute the greatest common divisor (gcd) of two integers
void gcd(const mpz_t a, const mpz_t b, mpz_t result) {
    mpz_gcd(result, a, b);
}

// Function to check if two integers are coprime
int are_coprime(const mpz_t a, const mpz_t b) {
    mpz_t g;
    mpz_init(g);
    gcd(a, b, g);
    int coprime = mpz_cmp_ui(g, 1) == 0;
    mpz_clear(g);
    return coprime;
}

// Function to find the number of solutions to the congruence a*x ≡ b (mod m)
int num_solutions(const mpz_t a, const mpz_t b, const mpz_t m) {
    mpz_t g;
    mpz_init(g);
    gcd(a, m, g);

    // If a and m are not coprime and b is not divisible by their gcd, there are no solutions
    if (!are_coprime(a, m) && mpz_divisible_p(b, g) == 0) {
        mpz_clear(g);
        return 0;
    }

    mpz_clear(g);
    return 1;
}

// Function to find all solutions to the congruence a*x ≡ b (mod m)
void find_solutions(const mpz_t a, const mpz_t b, const mpz_t m) {
    mpz_t g;
    mpz_init(g);
    gcd(a, m, g);

    // If a and m are not coprime and b is not divisible by their gcd, there are no solutions
    if (!are_coprime(a, m) && mpz_divisible_p(b, g) == 0) {
        mpz_clear(g);
        return;
    }

    // Calculate the multiplicative inverse of a modulo m
    mpz_t inv;
    mpz_init(inv);
    mpz_invert(inv, a, m);

    // Calculate the solution x = b * inv (mod m)
    mpz_t solution;
    mpz_init(solution);
    mpz_mul(solution, b, inv);
    mpz_mod(solution, solution, m);

    printf("Y ");
    gmp_printf("%Zd", solution);

    mpz_clears(g, inv, solution, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    mpz_t a, b, m;
    mpz_init_set_str(a, argv[1], 10);
    mpz_init_set_str(b, argv[2], 10);
    mpz_init_set_str(m, argv[3], 10);

    // Check if the congruence a*x ≡ b (mod m) has solutions
    if (num_solutions(a, b, m) == 0) {
        printf("N");
    } else {
        // Find and print the solutions
        find_solutions(a, b, m);
    }

    mpz_clears(a, b, m, NULL);

    return 0;
}
