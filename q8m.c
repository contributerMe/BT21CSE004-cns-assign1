#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Extended Euclidean Algorithm to find multiplicative inverse
void extended_euclidean(const mpz_t a, const mpz_t b, mpz_t x, mpz_t y) {
    mpz_t old_r, r, old_s, s, old_t, t, quotient, temp;
    mpz_inits(old_r, r, old_s, s, old_t, t, quotient, temp, NULL);

    mpz_set(old_r, a);
    mpz_set(r, b);
    mpz_set_ui(old_s, 1);
    mpz_set_ui(s, 0);
    mpz_set_ui(old_t, 0);
    mpz_set_ui(t, 1);

    while (mpz_cmp_ui(r, 0) > 0) {
        mpz_div(quotient, old_r, r);

        // Update r
        mpz_set(temp, r);
        mpz_mod(r, old_r, r);
        mpz_set(old_r, temp);

        // Update s
        mpz_set(temp, s);
        mpz_mul(temp, quotient, s);
        mpz_sub(s, old_s, temp);
        mpz_set(old_s, temp);

        // Update t
        mpz_set(temp, t);
        mpz_mul(temp, quotient, t);
        mpz_sub(t, old_t, temp);
        mpz_set(old_t, temp);
    }

    mpz_set(x, old_s);
    mpz_set(y, old_t);

    mpz_clears(old_r, r, old_s, s, old_t, t, quotient, temp, NULL);
}

// Function to calculate the CRT solution
void crt_solution(const mpz_t *a, const mpz_t *b, const mpz_t *m, int n, mpz_t result) {
    mpz_t M, x, y, temp, temp2;
    mpz_inits(M, x, y, temp, temp2, NULL);

    mpz_set_ui(result, 0);
    mpz_set_ui(M, 1);

    // Calculate M
    for (int i = 0; i < n; i++) {
        mpz_mul(M, M, m[i]);
    }

    // Calculate x_i and sum up the result
    for (int i = 0; i < n; i++) {
        mpz_divexact(temp, M, m[i]);
        extended_euclidean(temp, m[i], x, y);
        mpz_mul(temp, b[i], temp);
        mpz_mul(temp, temp, x);
        mpz_add(result, result, temp);
    }

    mpz_mod(result, result, M);

    mpz_clears(M, x, y, temp, temp2, NULL);
}

// Function to check if there exists a common solution
int has_common_solution(const mpz_t *a, const mpz_t *b, const mpz_t *m, int n) {
    // Check if the moduli are pairwise coprime
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            mpz_t g;
            mpz_init(g);
            mpz_gcd(g, m[i], m[j]);
            if (mpz_cmp_ui(g, 1) != 0) {
                mpz_clear(g);
                return 0; // Moduli are not pairwise coprime
            }
            mpz_clear(g);
        }
    }

    // Calculate the CRT solution
    mpz_t result;
    mpz_init(result);
    crt_solution(a, b, m, n, result);

    // Check if the solution satisfies all congruences
    for (int i = 0; i < n; i++) {
        mpz_t temp;
        mpz_init(temp);
        mpz_mod(temp, result, m[i]);
        if (mpz_cmp(temp, b[i]) != 0) {
            mpz_clear(result);
            mpz_clear(temp);
            return 0; // Solution does not satisfy all congruences
        }
        mpz_clear(temp);
    }

    mpz_clear(result);
    return 1; // Common solution exists
}

// Function to print all the solutions
void print_solutions(const mpz_t *a, const mpz_t *b, const mpz_t *m, int n) {
    // Calculate the CRT solution
    mpz_t result;
    mpz_init(result);
    crt_solution(a, b, m, n, result);

    // Print the solution
    gmp_printf("Common solution x satisfying the system of congruences:\n");
    gmp_printf("x ≡ %Zd (mod ", result);
    for (int i = 0; i < n; i++) {
        gmp_printf("%Zd", m[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    mpz_clear(result);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || (argc - 2) % 3 != 0) {
        printf("Usage: %s n ai bi mi [ai bi mi ...]\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if ((argc - 2) / 3 != n) {
        printf("Number of pairs does not match n.\n");
        return 1;
    }

    mpz_t *a, *b, *m;
    a = (mpz_t *)malloc(n * sizeof(mpz_t));
    b = (mpz_t *)malloc(n * sizeof(mpz_t));
    m = (mpz_t *)malloc(n * sizeof(mpz_t));

    // Parse command line arguments
    for (int i = 0; i < n; i++) {
        mpz_inits(a[i], b[i], m[i], NULL);
        mpz_set_str(a[i], argv[i * 3 + 2], 10);
        mpz_set_str(b[i], argv[i * 3 + 3], 10);
        mpz_set_str(m[i], argv[i * 3 + 4], 10);
    }

    if (has_common_solution(a, b, m, n)) {
        print_solutions(a, b, m, n);
    } else {
        printf("No common solution exists.\n");
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        mpz_clears(a[i], b[i], m[i], NULL);
    }
    free(a);
    free(b);
    free(m);

    return 0;
}
