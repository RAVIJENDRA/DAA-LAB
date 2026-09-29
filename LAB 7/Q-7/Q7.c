#include <stdio.h>

#define MAX 20

int m[MAX][MAX];
int split[MAX][MAX];

/* Prints the optimal parenthesization */
void printOrder(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");
    printOrder(i, split[i][j]);
    printOrder(split[i][j] + 1, j);
    printf(")");
}

/* Finds minimum scalar multiplications using Dynamic Programming */
int matrixChainMultiplication(int p[], int n)
{
    int i, j, k, length;
    int cost;

    /* A single matrix needs 0 multiplications */
    for (i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    /* length is the number of matrices in the current chain */
    for (length = 2; length <= n; length++)
    {
        for (i = 1; i <= n - length + 1; i++)
        {
            j = i + length - 1;
            m[i][j] = 999999;

            /* Try every possible split point */
            for (k = i; k < j; k++)
            {
                cost = m[i][k] + m[k + 1][j]
                       + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    return m[1][n];
}

int main()
{
    int p[MAX];
    int n, i;
    int minimumCost;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX)
    {
        printf("Invalid number of matrices.\n");
        return 0;
    }

    printf("Enter %d dimensions:\n", n + 1);
    for (i = 0; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }

    minimumCost = matrixChainMultiplication(p, n);

    printf("\nMinimum number of scalar multiplications = %d\n",
           minimumCost);

    printf("Optimal parenthesization = ");
    printOrder(1, n);
    printf("\n");

    return 0;
}
