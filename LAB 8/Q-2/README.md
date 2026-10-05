# Coin Change: Total Number of Ways

## 1. Problem Title

**Coin Change: Total Number of Ways**

## 2. Problem Statement

Given an array of distinct positive integers representing coin denominations

`C = {c1, c2, ..., cn}`

and a target amount `V`, find the **total number of distinct combinations** of coins that sum up to `V`.

There is an infinite supply of every coin denomination.

The order of coins does not matter. For example:

- `1 + 2`
- `2 + 1`

are considered the **same combination**.

The program should implement the algorithm, validate it using input/output, and analyze its complexity.

---

## 3. Objective

The objective is to find the number of different ways to make the target amount using the given coin denominations, where:

- Each coin can be used any number of times.
- The order of coins does not matter.
- A dynamic programming approach is used.
- The program should be simple enough to understand and explain in a DAA lab viva.

---

## 4. Possible Approaches

There are several ways to solve this problem:

1. **Recursive / Brute Force**
   - Try taking or not taking each coin.
   - Simple to understand, but many subproblems are solved repeatedly.

2. **2D Dynamic Programming**
   - Store answers for different amounts and different numbers of coins.
   - Easy to visualize, but requires `O(nV)` memory.

3. **1D Dynamic Programming**
   - Store only the number of ways for each amount.
   - Uses `O(V)` memory.
   - By processing coins one by one, it counts combinations rather than different orders.

### Chosen Approach

We use **1D Dynamic Programming** because it is simple, efficient, and directly handles the fact that the order of coins does not matter.

---

## 5. Basic Idea of the Algorithm

Create a DP array:

`dp[j] = number of ways to make amount j`

Initially:

`dp[0] = 1`

because there is exactly one way to make amount 0: choose no coins.

All other entries are initially 0.

Then process each coin one at a time.

For a coin `c`, update:

`dp[j] = dp[j] + dp[j-c]`

for every amount `j` from `c` to `V`.

The important point is that **coins are processed in the outer loop** and amounts are processed in the inner loop. Therefore, the same combination is not counted again in a different order.

---

## 6. Why This Approach Is Suitable

Dynamic Programming is suitable because the problem contains repeated subproblems.

For example, while finding the number of ways to make a larger amount, we need the number of ways to make smaller amounts. Instead of calculating these smaller answers repeatedly, we store them in the `dp` array.

The 1D version also uses less memory than a 2D DP table.

---

## 7. Step-by-Step Algorithm

1. Read the number of coin denominations `n`.
2. Read the `n` coin denominations.
3. Read the target amount `V`.
4. Create an array `dp[0...V]`.
5. Set every value of `dp` to 0.
6. Set `dp[0] = 1`.
7. For every coin:
   - Start from the value of that coin.
   - Go up to `V`.
   - Add `dp[j - coin]` to `dp[j]`.
8. After all coins are processed, `dp[V]` contains the total number of combinations.
9. Print `dp[V]`.

---

## 8. C Program

```c
#include <stdio.h>

#define MAX 1000

// Function to count the number of combinations
long long countWays(int coins[], int n, int V)
{
    long long dp[MAX + 1];
    int i, j;

    // Initially, there are 0 ways to make every amount
    for (j = 0; j <= V; j++)
    {
        dp[j] = 0;
    }

    // There is one way to make amount 0:
    // choose no coins
    dp[0] = 1;

    // Process each coin one by one
    for (i = 0; i < n; i++)
    {
        // Update the number of ways for all
        // amounts that can use this coin
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

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    printf("Enter the coin denominations:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);
    }

    printf("Enter target amount: ");
    scanf("%d", &V);

    result = countWays(coins, n, V);

    printf("Total number of combinations: %lld\n", result);

    return 0;
}
```

---

## 9. Program Explanation

### Header File

```c
#include <stdio.h>
```

This includes the standard input/output library so that we can use `printf()` and `scanf()`.

### Constant

```c
#define MAX 1000
```

This sets the maximum size of the arrays used by the program.

For a normal college lab program, this keeps the implementation simple.

---

### `countWays()` Function

```c
long long countWays(int coins[], int n, int V)
```

This function calculates the number of combinations.

Parameters:

- `coins[]` → stores the coin denominations.
- `n` → number of denominations.
- `V` → target amount.

Return value:

- The total number of combinations.

`long long` is used because the number of combinations can become large.

---

### DP Array

```c
long long dp[MAX + 1];
```

`dp[j]` stores the number of ways to make amount `j` using the coins processed so far.

For example:

- `dp[0]` → ways to make 0
- `dp[1]` → ways to make 1
- `dp[2]` → ways to make 2
- ...
- `dp[V]` → ways to make the target amount

---

### Initialization

```c
for (j = 0; j <= V; j++)
{
    dp[j] = 0;
}
```

Initially, no amounts have been calculated, so all values are set to 0.

Then:

```c
dp[0] = 1;
```

There is exactly one way to make amount 0: use no coins.

---

### Processing Coins

```c
for (i = 0; i < n; i++)
```

This loop processes one denomination at a time.

For example, if the coins are:

`1 2 5`

the program first processes coin `1`, then coin `2`, and finally coin `5`.

---

### Processing Amounts

```c
for (j = coins[i]; j <= V; j++)
```

For the current coin, we consider every amount from the coin's value up to the target.

For example, for coin `2`, we start at amount `2`.

---

### DP Formula

```c
dp[j] = dp[j] + dp[j - coins[i]];
```

This means:

- `dp[j]` already contains the ways without using the current coin again.
- `dp[j - coins[i]]` tells us how many ways can be extended by adding the current coin.

So the new number of ways is:

`old ways + new ways obtained using the current coin`

---

### Main Function

The main function:

1. Reads `n`.
2. Reads the coin denominations.
3. Reads target `V`.
4. Calls `countWays()`.
5. Prints the answer.

---

## 10. Important Variables

| Variable | Meaning |
|---|---|
| `coins[]` | Stores coin denominations |
| `n` | Number of denominations |
| `V` | Target amount |
| `dp[]` | Stores number of ways for every amount |
| `i` | Controls the coin loop |
| `j` | Controls the amount loop |
| `result` | Stores final answer |

---

## 11. Dry Run

Consider:

```text
Coins = {1, 2, 5}
V = 5
```

We want the number of combinations that make 5.

### Initial DP

```text
dp = [1, 0, 0, 0, 0, 0]
```

Only amount 0 has one way.

### After Coin 1

```text
dp = [1, 1, 1, 1, 1, 1]
```

There is one way to make every amount using only 1-value coins.

### After Coin 2

| Amount `j` | Calculation | `dp[j]` |
|---:|---|---:|
| 2 | `1 + dp[0] = 2` | 2 |
| 3 | `1 + dp[1] = 2` | 2 |
| 4 | `1 + dp[2] = 3` | 3 |
| 5 | `1 + dp[3] = 3` | 3 |

Now:

```text
dp = [1, 1, 2, 2, 3, 3]
```

### After Coin 5

Only amount 5 can be updated:

```text
dp[5] = dp[5] + dp[0]
      = 3 + 1
      = 4
```

Final:

```text
dp = [1, 1, 2, 2, 3, 4]
```

Therefore:

```text
Total number of combinations = 4
```

The four combinations are:

```text
5
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1
```

Notice that `1 + 2 + 2` is not counted separately from `2 + 2 + 1`.

---

## 12. Complexity Analysis

Let:

- `n` = number of coin denominations
- `V` = target amount

### Time Complexity

There are two nested loops:

```c
for (i = 0; i < n; i++)
{
    for (j = coins[i]; j <= V; j++)
    {
        ...
    }
}
```

For each coin, the inner loop can run up to `V` times.

Therefore:

`T(n,V) = O(nV)`

More precisely, the number of amount-loop iterations is:

`sum(V - coins[i] + 1)`

for coins whose value is at most `V`.

If all denominations are at most `V`, this is at most about:

`nV`

Therefore the worst-case time complexity is:

**O(nV)**.

### Best Case

If denominations are larger than `V`, some inner loops do not execute. However, under the usual assumption that useful coin denominations are at most `V`, the algorithm still has:

**Theta(nV)**

time.

If arbitrary input values are allowed, the exact work depends on how many coins are `<= V`.

### Average Case

There is no separate algorithmic average-case behavior in the usual DP analysis. For a fixed `n` and `V`, the loop structure is determined by the coin values.

So it is commonly stated as:

**O(nV)** average/typical upper-bound analysis.

### Space Complexity

The program uses one DP array of size `V + 1`.

Therefore:

**O(V)** space.

This is better than a 2D DP solution requiring `O(nV)` space.

---

## 13. Complexity Graph

The accompanying file:

`coin_change_complexity.png`

shows the theoretical growth of the algorithm.

The graph uses:

`T(n) = n × V`

with `V = 100` fixed.

Therefore the plotted growth represents:

`O(nV)`

For fixed `V`, this grows linearly with `n`.

The graph is a theoretical complexity plot, not measured execution-time data.

---

## 14. Advantages

1. Simple to implement.
2. Easy to understand using the DP array.
3. Counts combinations without counting different orders separately.
4. Handles unlimited supply of coins.
5. Uses only `O(V)` extra space.
6. Faster than a naive recursive solution for larger inputs.

---

## 15. Disadvantages / Limitations

1. The DP array requires memory proportional to `V`.
2. If the target amount `V` is extremely large, the array can become large.
3. The number of combinations can become very large, so even `long long` can eventually overflow for sufficiently large inputs.
4. The program uses a fixed `MAX` value of 1000, so the target amount must not exceed this limit unless the program is modified.

---

## 16. Viva Preparation

### Q1. What is the main idea of this algorithm?

**Answer:**  
The main idea is Dynamic Programming. We store the number of ways to make every amount from 0 to `V` and build the final answer using smaller amounts.

### Q2. Why did you choose Dynamic Programming?

**Answer:**  
The problem has overlapping subproblems. The same smaller amounts are needed many times, so storing their answers avoids repeated calculations.

### Q3. Why is `dp[0] = 1`?

**Answer:**  
There is exactly one way to make amount 0: choose no coins.

### Q4. What does `dp[j]` represent?

**Answer:**  
`dp[j]` represents the number of combinations that make amount `j` using the coins processed so far.

### Q5. What is the DP formula?

**Answer:**

```text
dp[j] = dp[j] + dp[j - coin]
```

The first part contains the old ways, and the second part adds ways obtained by using the current coin.

### Q6. Why are coins processed in the outer loop?

**Answer:**  
This ensures that combinations are counted without considering different orders separately.

### Q7. What is the time complexity?

**Answer:**  
`O(nV)`, where `n` is the number of denominations and `V` is the target amount.

### Q8. What is the space complexity?

**Answer:**  
`O(V)` because only one DP array of size `V + 1` is used.

### Q9. What happens if the target amount increases?

**Answer:**  
The DP array becomes larger and the number of iterations increases. The running time grows approximately with `nV`.

### Q10. What happens if a coin is greater than `V`?

**Answer:**  
That coin cannot be used to make `V`, so its inner loop does not execute.

### Q11. What is the advantage of 1D DP over 2D DP?

**Answer:**  
1D DP uses `O(V)` memory, while a normal 2D DP table uses `O(nV)` memory.

### Q12. What is the disadvantage of this method?

**Answer:**  
It requires memory proportional to the target amount, so a very large `V` can require a large array.

### Q13. Why is `long long` used?

**Answer:**  
The number of combinations can become large, so `long long` provides a larger integer range than a normal `int`.

### Q14. Why is the inner loop started from `coins[i]`?

**Answer:**  
Amounts smaller than the current coin cannot use that coin, so there is no need to process them.

### Q15. Why is the function `countWays()` used?

**Answer:**  
It separates the main DP logic from input/output, making the program easier to understand and test.

---

## 17. C-Code-Specific Viva Questions

### Q1. Why is `dp` declared inside `countWays()`?

**Answer:**  
The DP array is only needed while calculating the answer, so it is kept inside the function.

### Q2. Why are two loops used?

**Answer:**  
The outer loop processes each coin, while the inner loop processes all possible amounts for that coin.

### Q3. Why does the inner loop start at `coins[i]`?

**Answer:**  
A coin cannot be used for an amount smaller than its own value.

### Q4. What does `dp[j - coins[i]]` mean?

**Answer:**  
It is the number of ways to make the remaining amount after adding the current coin.

### Q5. Why is `dp[0]` initialized to 1 instead of 0?

**Answer:**  
Because the empty combination is one valid way to make amount zero, and this is necessary to build the other combinations.

---

## 18. How to Compile and Run

### Using GCC

Save the program as:

```text
coin_change.c
```

Compile:

```bash
gcc coin_change.c -o coin_change
```

Run:

```bash
./coin_change
```

On Windows:

```bash
coin_change.exe
```

---

## 19. Sample Input

```text
Enter number of coin denominations: 3
Enter the coin denominations:
1 2 5
Enter target amount: 5
```

## 20. Sample Output

```text
Total number of combinations: 4
```

---

## 21. Short Teacher-Explanation Version

If the teacher asks, **"Explain your algorithm and code"**, you can say:

> "I used Dynamic Programming to solve the coin change problem. The objective is to find the number of different combinations of coins that make the target amount, where the order does not matter.
>
> I created a one-dimensional array `dp`, where `dp[j]` stores the number of ways to make amount `j`. Initially, `dp[0]` is 1 because there is one way to make zero, which is using no coins.
>
> Then I process every coin one by one. For each coin, I update all amounts from the coin value up to the target using `dp[j] = dp[j] + dp[j - coin]`. Processing coins in the outer loop makes sure that different orders of the same combination are not counted separately.
>
> Finally, `dp[V]` gives the total number of combinations. The time complexity is `O(nV)` and the space complexity is `O(V)`."

---

## 22. Conclusion

The Coin Change problem can be efficiently solved using Dynamic Programming. The 1D DP approach stores the number of ways to make each amount and builds the final answer from smaller amounts.

The important idea is to process the coins first and the amounts second. This makes the program count combinations instead of counting different arrangements of the same coins.

The final complexity is:

- **Time:** `O(nV)`
- **Space:** `O(V)`

This approach is simple, efficient, and suitable for a DAA laboratory implementation and viva.

