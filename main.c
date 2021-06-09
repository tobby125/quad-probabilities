#include <stdio.h>
#include <stdlib.h>

int pow2(int n) {
    if (n == 0) {
        return 1;
    }
    return 2 * pow2(n - 1);
}

long long fact(int n, int stop) {
    if (n < 0) {
        printf("Error");
        exit(-1);
    }
    if (n == stop) {
        return 1;
    }
    return n * fact(n - 1, stop);
}

long long choose(int n, int k) {
    return fact(n, n - k) / fact(k, 0);
}

int is_quad(int *deal, int k) {
    for (int a = 0; a < k; a++) {
        for (int b = a + 1; b < k; b++) {
            for (int c = b + 1; c < k; c++) {
                for (int d = c + 1; d < k; d++) {
                    if (!(deal[a] ^ deal[b] ^ deal[c] ^ deal[d])) return 1;
                }
            }
        }
    }
    return 0;
}

double quad_prob(int n, int k) {
    int deck_size = pow2(n);
    if (k > deck_size) {
        printf("Error\n");
        exit(-1);
    }

    int *deal = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        deal[i] = i;
    }

    long long total = choose(deck_size, k);
    int c = 0;
    int count = 0;
    while (1) {
        c++;
        printf("%d / %lld\n", c, total);
        count += is_quad(deal, k);
        int i = k - 1;
        while (deal[i] == deck_size - (k - i)) {
            i--;
        }
        if (i == -1) break;
        deal[i]++;
        i++;
        while (i < k) {
            deal[i] = deal[i - 1] + 1;
            i++;
        }
    }
    return count / (double) total;
}

int main() {
    int n;
    printf("Enter n:\n");
    scanf_s("%d", &n);
    int k;
    printf("Enter k:\n");
    scanf_s("%d", &k);
    printf("Probability of quad: %f%%\n", 100 * quad_prob(n, k));
    return 0;
}