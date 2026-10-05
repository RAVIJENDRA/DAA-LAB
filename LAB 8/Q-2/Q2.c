#include <stdio.h>

#define MAX 1000

// Function to count the total number of combinations
long long countWays(int coins[], int n, int V)
{
    long long dp[MAX + 1];
    int i, j;

    // Initially, set all values to 0
    for (j = 0; j <= V; j++)
    {
        dp[j] = 0;
    }

    // There is one way to make amount 0:
    // by choosing no coins
    dp[0] = 1;

    // Process each coin one by one
    for (i = 0; i < n; i++)
    {
        // Process all amounts from the current coin
        // value up to the target amount
        for (j = coins[i]; j <= V; j++)
        {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    return dp[V];
}

int main()
{
    int coins[MAX];
    int n, V;
    int i;
    long long result;

    // Read number of coins
    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    // Read coin denominations
    printf("Enter the coin denominations:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);
    }

    // Read target amount
    printf("Enter target amount: ");
    scanf("%d", &V);

    // Calculate number of combinations
    result = countWays(coins, n, V);

    // Display result
    printf("Total number of combinations: %lld\n", result);

    return 0;
}