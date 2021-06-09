#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	return n * fact(n - 1, stop)
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

void random_deal(int *deal, int deck_size, int k) {
	int *checks = (int *) malloc(deck_size * sizeof(int));
	for (int i = 0; i < deck_size; i++) {
		checks[i] = 0;
	}
	for (int i = 0; i < k; i++) {
		int num = rand() % (deck_size - i);
		int j = -1;
		for (int _ = 0; _ < num + 1; _++) {
			j++;
			while (checks[j]) {
				j++;
			}
		}
		deal[i] = j;
		checks[deal[i]] = 1;
	}
	free(checks);
}

double sample_quad_prob(int n, int k, int sample_size) {
	int *deal = (int *) malloc(k * sizeof(int));
	int deck_size = pow2(n);
	if (k > deck_size) {
        printf("Error\n");
        exit(-1);
    }
	int count = 0;
	for (int i = 0; i < sample_size; i++) {
		random_deal(deal, deck_size, k);
		count += is_quad(deal, k); 	
	}
	free(deal);
	return (double) count / sample_size;
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
    long long c = 0;
    long long count = 0;
    clock_t tot_t = time(NULL);
    time_t t = clock();
    while (1) {
        c++;
		if (c % 1000000 == 0) {
			printf("%lld / %lld,\t%f seconds,\t%lu total seconds\n", c, total, (double) (clock() - t) / CLOCKS_PER_SEC, time(NULL) - tot_t);
			t = clock();
		}
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
	free(deal);
    return (double) count / total;
}

int main(int argc, char **argv) {
	srand(time(NULL));

	if (argc == 3) {
		int n;
    	sscanf(argv[1], "%d", &n);
    	int k;
    	sscanf(argv[2], "%d", &k);
		clock_t pt = clock();
		time_t t = time(NULL);
    	printf("\nProbability of quad: %f%%", 100 * quad_prob(n, k));
		printf("\n%s runtime: %lu / %f seconds\n\n", "main.c", time(NULL) - t, (double) (clock() - pt) / CLOCKS_PER_SEC); 
	}
	else if (argc == 4) {
		int n;
    	sscanf(argv[1], "%d", &n);
    	int k;
    	sscanf(argv[2], "%d", &k);
		int sample_size;
		sscanf(argv[3], "%d", &sample_size);
		clock_t pt = clock();
		time_t t = time(NULL);
    	printf("\nsSample size: %d,   Probability of quad: %f%%", sample_size, 100 * sample_quad_prob(n, k, sample_size));
		printf("\n%s runtime: %lu / %f seconds\n\n", "main.c", time(NULL) - t, (double) (clock() - pt) / CLOCKS_PER_SEC); 
	}
	else {
		printf("Error\n");
		exit(-1);
	}
    return 0;
}
