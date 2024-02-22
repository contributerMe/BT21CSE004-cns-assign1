#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    mpz_t product;
    mpz_init(product);
    mpz_set_ui(product, 1);

    int target = atoi(argv[1]);
    int printed = 0; // Flag to track if anything has been printed

    for (int i = 2; i <= target; i++) {
        if (is_prime(i)) {
            while (target % i == 0) {
                if (printed) {
                    printf(" "); // Print space only if something has been printed before
                }
                printf("%d", i);
                printed = 1;
                target /= i;
            }
        }
    }

    if (target > 1) {
        if (printed) {
            printf(" "); // Print space only if something has been printed before
        }
        printf("%d", target); // Print the remaining factor if it's prime
    }

    mpz_clear(product);
    return 0;
}
