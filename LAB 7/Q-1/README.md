# Invert the Coin Triangle

## Problem Statement

Consider an equilateral triangle formed by closely packed identical coins.

The triangle has `n` rows of coins. The task is to invert the triangle (turn it upside down) using the **minimum number of moves**.

In each move, only **one coin can be moved** to a new valid position.

The program calculates the minimum number of moves required to invert the triangle.

---

## Formula

For `n` rows, the total number of coins is:

```text
Total Coins = n(n + 1) / 2
```

The minimum number of moves is:

```text
Minimum Moves = floor(n(n + 1) / 6)
```

---

## Algorithm

1. Read the number of rows `n`.
2. Calculate the total number of coins using `n(n + 1)/2`.
3. Calculate the minimum number of moves using `n(n + 1)/6`.
4. Display the total number of coins and minimum moves.

---

## C Program

```c
#include <stdio.h>

long long minimumMoves(long long n)
{
    long long moves;

    moves = n * (n + 1) / 6;

    return moves;
}

int main()
{
    long long n;
    long long totalCoins;
    long long moves;

    printf("Enter the number of rows: ");
    scanf("%lld", &n);

    totalCoins = n * (n + 1) / 2;

    moves = minimumMoves(n);

    printf("Total number of coins = %lld\n", totalCoins);
    printf("Minimum number of moves = %lld\n", moves);

    return 0;
}
```

---

## Sample Input

```text
Enter the number of rows: 4
```

## Sample Output

```text
Total number of coins = 10
Minimum number of moves = 3
```

---

## Another Example

### Input

```text
Enter the number of rows: 5
```

### Output

```text
Total number of coins = 15
Minimum number of moves = 5
```

---

## Complexity Analysis

### Time Complexity

**O(1)**

The program performs a fixed number of arithmetic operations and does not use a loop depending on `n`.

### Space Complexity

**O(1)**

Only a constant number of variables are used.

---

## Approach Used

The solution uses a **mathematical / transform-and-conquer approach**.

Instead of simulating every coin movement or trying every possible arrangement, the geometric problem is converted into a direct mathematical formula.

This makes the solution simple and efficient.

---

## Important Variables

| Variable | Description |
|----------|-------------|
| `n` | Number of rows in the triangle |
| `totalCoins` | Total number of coins |
| `moves` | Minimum number of moves |

---

## Function

### `minimumMoves()`

Calculates the minimum number of moves.

**Parameter:** `n` — number of rows.

**Returns:** `moves` — minimum number of moves.

Formula:

```text
n(n + 1) / 6
```

---

## Edge Case

For `n = 1`:

```text
Total Coins = 1
Minimum Moves = 0
```

---

## How to Compile

Using GCC:

```bash
gcc coin_triangle.c -o coin_triangle
```

## How to Run

Linux/macOS:

```bash
./coin_triangle
```

Windows:

```bash
coin_triangle.exe
```

---

## DAA Concepts Used

- Mathematical optimization
- Transform and conquer
- Time complexity analysis
- Space complexity analysis
- Mathematical formula derivation

---

## Key Formula

```text
Total Coins = n(n + 1) / 2

Minimum Moves = floor(n(n + 1) / 6)
```

For `n = 4`:

```text
Total Coins = 4 × 5 / 2 = 10

Minimum Moves = floor(4 × 5 / 6)
              = floor(20 / 6)
              = 3
```

Therefore, the triangle can be inverted in **3 moves**.
