#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function to calculate the modular inverse of a (mod m)
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse does not exist
}

// Function to solve the system of congruences
void solve_congruences(int n, int *a, int *b, int *m) {
    int M = 1;
    for (int i = 0; i < n; i++) {
        M *= m[i];
    }

    int x = 0;
    for (int i = 0; i < n; i++) {
        int Mi = M / m[i];
        int Mi_inv = mod_inverse(Mi, m[i]);
        if (Mi_inv == -1) {
            printf("No common solution exists.\n");
            return;
        }
        x += b[i] * Mi * Mi_inv;
    }

    printf("Common solution x satisfying the system of congruences: %d\n", x % M);
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

    int *a, *b, *m;
    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    m = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = atoi(argv[i * 3 + 2]);
        b[i] = atoi(argv[i * 3 + 3]);
        m[i] = atoi(argv[i * 3 + 4]);
    }

    solve_congruences(n, a, b, m);

    free(a);
    free(b);
    free(m);

    return 0;
}
