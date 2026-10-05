#include <stdio.h>

#define MAX 20

double p[MAX + 1];
double q[MAX + 1];

double e[MAX + 2][MAX + 1];
double w[MAX + 2][MAX + 1];

int root[MAX + 1][MAX + 1];

/* Function to calculate the Optimal BST */
void optimalBST(int n)
{
    int i, j, r, length;
    double cost;

    /* Base case: empty subtrees */
    for (i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    /* Consider subtrees of increasing length */
    for (length = 1; length <= n; length++)
    {
        for (i = 1; i <= n - length + 1; i++)
        {
            j = i + length - 1;

            /* Calculate total probability weight */
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            /* Start with a very large cost */
            e[i][j] = 999999.0;

            /* Try every key as the root */
            for (r = i; r <= j; r++)
            {
                cost = e[i][r - 1] + e[r + 1][j] + w[i][j];

                if (cost < e[i][j])
                {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }
}

/* Function to print the root table */
void printRootTable(int n)
{
    int i, j;

    printf("\nRoot Table:\n");

    for (i = 1; i <= n; i++)
    {
        for (j = i; j <= n; j++)
        {
            printf("root[%d][%d] = k%d\n",
                   i, j, root[i][j]);
        }
    }
}

/* Function to print the actual tree */
void printTree(int i, int j, int parent, char side)
{
    int r;

    if (i > j)
        return;

    r = root[i][j];

    if (parent == 0)
    {
        printf("Root: k%d\n", r);
    }
    else
    {
        printf("k%d is the %s child of k%d\n",
               r,
               side == 'L' ? "left" : "right",
               parent);
    }

    printTree(i, r - 1, r, 'L');
    printTree(r + 1, j, r, 'R');
}

int main()
{
    int n, i;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter successful search probabilities p1 to p%d:\n", n);

    for (i = 1; i <= n; i++)
    {
        scanf("%lf", &p[i]);
    }

    printf("Enter unsuccessful search probabilities q0 to q%d:\n", n);

    for (i = 0; i <= n; i++)
    {
        scanf("%lf", &q[i]);
    }

    optimalBST(n);

    printf("\nMinimum Expected Search Cost = %.3lf\n",
           e[1][n]);

    printRootTable(n);

    printf("\nOptimal Binary Search Tree:\n");

    printTree(1, n, 0, ' ');

    return 0;
}