#include <stdio.h>

#define MAX_N 20
#define INF 1000000000000000LL

long long dp[MAX_N + 1];
int bestK[MAX_N + 1];

int peg[4][MAX_N];
int top[4];

char pegName[4] = {'A', 'B', 'C', 'D'};

/* Function to calculate 2^n - 1 */
long long hanoiMoves(int n)
{
    long long result = 1;
    int i;

    for (i = 0; i < n; i++)
        result = result * 2;

    return result - 1;
}

/* Find minimum number of moves for n disks */
void calculateDP(int n)
{
    int i, k;
    long long moves;

    dp[0] = 0;

    for (i = 1; i <= n; i++)
    {
        if (i == 1)
        {
            dp[i] = 1;
            bestK[i] = 0;
        }
        else
        {
            dp[i] = INF;

            for (k = 1; k < i; k++)
            {
                moves = 2 * dp[k] + hanoiMoves(i - k);

                if (moves < dp[i])
                {
                    dp[i] = moves;
                    bestK[i] = k;
                }
            }
        }
    }
}

/* Move one disk and check whether the move is legal */
void moveDisk(int from, int to)
{
    int disk;

    if (top[from] == 0)
    {
        printf("ERROR: Source peg is empty.\n");
        return;
    }

    disk = peg[from][top[from] - 1];

    /* Check whether a larger disk is placed on a smaller disk */
    if (top[to] > 0 &&
        peg[to][top[to] - 1] < disk)
    {
        printf("ERROR: Illegal move!\n");
        return;
    }

    /* Remove disk from source peg */
    top[from]--;
    
    /* Put disk on destination peg */
    peg[to][top[to]] = disk;
    top[to]++;

    printf("Move disk %d from %c to %c\n",
           disk, pegName[from], pegName[to]);
}

/* Standard 3-peg Tower of Hanoi */
void solve3(int n, int source, int destination, int auxiliary)
{
    if (n == 0)
        return;

    solve3(n - 1, source, auxiliary, destination);

    moveDisk(source, destination);

    solve3(n - 1, auxiliary, destination, source);
}

/* 4-peg Reve's Puzzle */
void solve4(int n, int source, int destination,
            int auxiliary1, int auxiliary2)
{
    int k;

    if (n == 0)
        return;

    if (n == 1)
    {
        moveDisk(source, destination);
        return;
    }

    /* Get the best value of k */
    k = bestK[n];

    /*
       Step 1:
       Move k smaller disks from source to auxiliary1
       using 4 pegs.
    */
    solve4(k, source, auxiliary1,
           destination, auxiliary2);

    /*
       Step 2:
       Move remaining n-k disks from source to destination
       using normal 3-peg Tower of Hanoi.
    */
    solve3(n - k, source, destination, auxiliary2);

    /*
       Step 3:
       Move the k disks from auxiliary1 to destination
       using 4 pegs.
    */
    solve4(k, auxiliary1, destination,
           source, auxiliary2);
}

/* Initialize all disks on source peg */
void initialize(int n)
{
    int i;

    for (i = 0; i < 4; i++)
        top[i] = 0;

    /*
       Largest disk is placed first,
       then smaller disks.
    */
    for (i = n; i >= 1; i--)
    {
        peg[0][top[0]] = i;
        top[0]++;
    }
}

int main()
{
    int n;
    int i;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_N)
    {
        printf("Please enter n between 1 and %d.\n", MAX_N);
        return 0;
    }

    /* Calculate minimum moves and best k */
    calculateDP(n);

    printf("\nMinimum number of moves = %lld\n", dp[n]);

    if (n > 1)
        printf("Best value of k = %d\n", bestK[n]);

    printf("\nMove sequence:\n");

    /* Put all disks initially on peg A */
    initialize(n);

    /* Solve from A to B using C and D as auxiliary pegs */
    solve4(n, 0, 1, 2, 3);

    printf("\nTotal moves = %lld\n", dp[n]);

    return 0;
}