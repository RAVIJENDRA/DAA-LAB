#include <stdio.h>

#define INF 1000000

// Function to find the minimum number of coins
int minCoins(int coins[], int n, int V)
{
    int dp[V + 1];
    int i, j;

    // dp[0] = 0 because no coin is needed to make amount 0
    dp[0] = 0;

    // Initially, all other amounts are marked as impossible
    for (i = 1; i <= V; i++)
    {
        dp[i] = INF;
    }

    // Calculate the minimum coins for every amount from 1 to V
    for (i = 1; i <= V; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (coins[j] <= i && dp[i - coins[j]] != INF)
            {
                if (dp[i] > dp[i - coins[j]] + 1)
                {
                    dp[i] = dp[i - coins[j]] + 1;
                }
            }
        }
    }

    // If V cannot be formed, return -1
    if (dp[V] == INF)
        return -1;

    return dp[V];
}

int main()
{
    int n, V, i;
    int coins[100];

    printf("Enter the number of coin denominations: ");
    scanf("%d", &n);

    printf("Enter the coin denominations:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);
    }

    printf("Enter the target amount: ");
    scanf("%d", &V);

    printf("Minimum number of coins = %d\n", minCoins(coins, n, V));

    return 0;
}
