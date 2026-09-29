#include <stdio.h>

#define MAX_MOVES 100000

/*
    Generates the minimum sequence of moves.

    The moves for n-1 switches are already stored in moves[].
    We expand them in-place by inserting switch n.
*/
int generateMoves(int n, int moves[])
{
    int previousMoves;
    int i;

    /* Base case */
    if (n == 1)
    {
        moves[0] = 1;
        return 1;
    }

    /* Generate moves for n-1 switches */
    previousMoves = generateMoves(n - 1, moves);

    /*
        If n is even:
        S(n) = s1,n,s2,n,s3,n,...
    */
    if (n % 2 == 0)
    {
        for (i = previousMoves - 1; i >= 0; i--)
        {
            moves[2 * i] = moves[i];
            moves[2 * i + 1] = n;
        }

        return 2 * previousMoves;
    }

    /*
        If n is odd:
        S(n) = n,s1,n,s2,n,s3,n,...
    */
    else
    {
        for (i = previousMoves - 1; i >= 0; i--)
        {
            moves[2 * i + 1] = moves[i];
            moves[2 * i + 2] = n;
        }

        moves[0] = n;

        return 2 * previousMoves + 1;
    }
}

/*
    Checks whether a particular switch can legally be toggled.
*/
int isLegalMove(int switches[], int n, int move)
{
    int i;

    /* Rightmost switch can always be toggled */
    if (move == n)
    {
        return 1;
    }

    /*
        The immediate right switch must be ON.
        All switches further to the right must be OFF.
    */

    if (switches[move] == 0)
    {
        return 0;
    }

    for (i = move + 1; i < n; i++)
    {
        if (switches[i] == 1)
        {
            return 0;
        }
    }

    return 1;
}

/*
    Toggles the required switch.
*/
void toggleSwitch(int switches[], int move)
{
    switches[move - 1] = 1 - switches[move - 1];
}

/*
    Prints the current state of all switches.
*/
void printSwitches(int switches[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (switches[i] == 1)
            printf("ON ");
        else
            printf("OFF ");
    }

    printf("\n");
}

/*
    Checks whether all switches are OFF.
*/
int allOff(int switches[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (switches[i] == 1)
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    int n;
    int switches[100];
    int moves[MAX_MOVES];

    int totalMoves;
    int i;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0 || n > 15)
    {
        printf("Please enter n between 1 and 15.\n");
        return 0;
    }

    /* Initially all switches are ON */
    for (i = 0; i < n; i++)
    {
        switches[i] = 1;
    }

    /* Generate the minimum sequence */
    totalMoves = generateMoves(n, moves);

    printf("\nInitial state:\n");
    printSwitches(switches, n);

    printf("\nSequence of moves:\n");

    for (i = 0; i < totalMoves; i++)
    {
        if (!isLegalMove(switches, n, moves[i]))
        {
            printf("Invalid move found: Switch %d\n", moves[i]);
            return 0;
        }

        toggleSwitch(switches, moves[i]);

        printf("Move %d: Toggle switch %d -> ", i + 1, moves[i]);
        printSwitches(switches, n);
    }

    printf("\nTotal moves = %d\n", totalMoves);

    if (allOff(switches, n))
    {
        printf("All switches are OFF.\n");
        printf("Algorithm successfully validated.\n");
    }
    else
    {
        printf("Error: Some switches are still ON.\n");
    }

    return 0;
}