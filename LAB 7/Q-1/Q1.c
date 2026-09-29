#include <stdio.h>

// Function to calculate the minimum number of moves
long long minimumMoves(long long n)
{
    long long moves;

    // Minimum moves = floor(n * (n + 1) / 6)
    moves = n * (n + 1) / 6;

    return moves;
}

int main()
{
    long long n;
    long long totalCoins;
    long long moves;
    
    // Read number of rows
    printf("Enter the number of rows: ");
    scanf("%lld", &n);

    // Calculate total number of coins
    totalCoins = n * (n + 1) / 2;

    // Calculate minimum number of moves
    moves = minimumMoves(n);

    // Display the result
    printf("Total number of coins = %lld\n", totalCoins);
    printf("Minimum number of moves = %lld\n", moves);

    return 0;
}