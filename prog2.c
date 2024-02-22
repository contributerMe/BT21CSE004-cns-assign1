#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void extendedEuclidean(mpz_t a, mpz_t b, mpz_t x, mpz_t y, mpz_t gcd) {
    if (mpz_cmp_ui(b, 0) == 0) {
        // Base case: b = 0, gcd(a, 0) = a, x = 1, y = 0
        mpz_set_ui(x, 1);
        mpz_set_ui(y, 0);
        mpz_set(gcd, a);
    } else {
        // Recursive case
        mpz_t q, r, x1, y1;
        mpz_inits(q, r, x1, y1, NULL);

        // Perform Euclidean division: a = bq + r
        mpz_fdiv_qr(q, r, a, b);

        // Recursive call with b, r
        extendedEuclidean(b, r, x1, y1, gcd);

        // Update x, y based on the recursive call
        mpz_set(x, y1);
        mpz_set(y, x1);

        // Update y based on the recursive call
        mpz_mul(q, q, y1);
        mpz_sub(y, x1, q);

        // Clean up temporary variables
        mpz_clears(q, r, x1, y1, NULL);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    mpz_t a, b, x, y, gcd;
    mpz_inits(a, b, x, y, gcd, NULL);

    // Input values from command line
    mpz_set_str(a, argv[1], 10);
    mpz_set_str(b, argv[2], 10);

    // Call extendedEuclidean function
    extendedEuclidean(a, b, x, y, gcd);

    // Output the result
    gmp_printf("%Zd %Zd", x, y);

    // Free allocated memory
    mpz_clears(a, b, x, y, gcd, NULL);

return 0;
}