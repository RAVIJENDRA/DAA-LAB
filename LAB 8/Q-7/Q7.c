#include <stdio.h>

#define MAX 100

void rodCutting(int price[], int n, int dp[], int cut[]) {
    int i, j;
    int maxRevenue;

    dp[0] = 0;

    for (i = 1; i <= n; i++) {
        maxRevenue = -1;

        for (j = 1; j <= i; j++) {
            if (price[j] + dp[i - j] > maxRevenue) {
                maxRevenue = price[j] + dp[i - j];
                cut[i] = j;
            }
        }

        dp[i] = maxRevenue;
    }
}

void printSolution(int cut[], int n) {
    int length = n;

    printf("Pieces in optimal decomposition: ");

    while (length > 0) {
        printf("%d ", cut[length]);
        length = length - cut[length];
    }

    printf("\n");
}

int main() {
    int n, i;
    int price[MAX + 1];
    int dp[MAX + 1];
    int cut[MAX + 1];

    printf("Enter the length of the rod: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid rod length. Enter a value between 1 and %d.\n", MAX);
        return 0;
    }

    printf("Enter prices for lengths 1 to %d:\n", n);

    for (i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }

    rodCutting(price, n, dp, cut);

    printf("\nMaximum revenue = %d\n", dp[n]);

    printSolution(cut, n);

    return 0;
}