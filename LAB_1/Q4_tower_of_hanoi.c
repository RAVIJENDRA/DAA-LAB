#include <stdio.h>

long long moves;

void towerOfHanoi(int n, char source, char auxiliary, char destination, int printMoves)
{
    if(n == 1)
    {
        moves++;

        if(printMoves)
            printf("Move disk 1 from %c to %c\n", source, destination);

        return;
    }

    towerOfHanoi(n - 1, source, destination, auxiliary, printMoves);

    moves++;

    if(printMoves)
        printf("Move disk %d from %c to %c\n", n, source, destination);

    towerOfHanoi(n - 1, auxiliary, source, destination, printMoves);
}

int main()
{
    int n, i;
    FILE *fp;

    printf("Enter number of disks to display the solution: ");
    scanf("%d", &n);

    if(n < 1)
    {
        printf("Number of disks must be at least 1.\n");
        return 1;
    }

    moves = 0;

    if(n <= 10)
    {
        towerOfHanoi(n, 'A', 'B', 'C', 1);
        printf("Total moves = %lld\n", moves);
    }
    else
    {
        towerOfHanoi(n, 'A', 'B', 'C', 0);
        printf("Total moves = %lld\n", moves);
        printf("Moves were not printed because the output becomes very large.\n");
    }

    fp = fopen("q4_data.csv", "w");

    if(fp == NULL)
    {
        printf("Could not create q4_data.csv\n");
        return 1;
    }

    fprintf(fp, "n,Moves\n");

    for(i = 1; i <= 20; i++)
    {
        moves = 0;
        towerOfHanoi(i, 'A', 'B', 'C', 0);
        fprintf(fp, "%d,%lld\n", i, moves);
    }

    fclose(fp);

    printf("\nData for the plot saved in q4_data.csv\n");

    return 0;
}
