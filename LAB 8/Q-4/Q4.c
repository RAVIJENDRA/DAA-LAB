#include <stdio.h>

int longestIncreasingSubsequence(int a[], int n)
{
    int dp[100];
    int i, j;
    int maxLength = 1;

    /* Every element alone forms a subsequence of length 1 */
    for (i = 0; i < n; i++)
    {
        dp[i] = 1;
    }

    /* Find the best increasing subsequence ending at each index */
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (a[j] < a[i] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
            }
        }

        if (dp[i] > maxLength)
        {
            maxLength = dp[i];
        }
    }

    return maxLength;
}

int main()
{
    int a[100];
    int n, i;
    int answer;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    answer = longestIncreasingSubsequence(a, n);

    printf("Length of Longest Increasing Subsequence = %d\n", answer);

    return 0;
}