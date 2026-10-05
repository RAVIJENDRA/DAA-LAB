# Minimum Coin Change

## 1. Problem Title

**Minimum Coin Change using Dynamic Programming**

## 2. Problem Statement

Given an integer array of coin denominations:

`C = {c1, c2, ..., cn}`

and an integer target amount `V`, find the minimum number of coins needed to make exactly `V`.

There is an infinite supply of every coin denomination.

If the target amount cannot be formed using any combination of the given coins, return `-1`.

---

## 3. Objective

The objective is to design a program that:

- Finds the minimum number of coins required to make the target amount.
- Handles an unlimited supply of every denomination.
- Returns `-1` when the target amount cannot be formed.
- Uses Dynamic Programming to avoid solving the same subproblems repeatedly.

---

## 4. Possible Approaches

There are several ways to solve this problem:

1. **Brute Force / Recursion**
   - Try different combinations of coins recursively.
   - It can repeat the same subproblems many times.
   - Its running time can become exponential.

2. **Greedy Method**
   - Repeatedly choose the largest possible coin.
   - This is fast, but it does not always give the minimum number of coins for arbitrary denominations.
   - For example, with coins `{1, 3, 4}` and amount `6`, greedy chooses `4 + 1 + 1` = 3 coins, while `3 + 3` = 2 coins.

3. **Dynamic Programming**
   - Solve smaller amounts first.
   - Store their answers and reuse them.
   - This guarantees the minimum number of coins for arbitrary positive denominations.

For this problem, **Dynamic Programming** is the most suitable general approach.

---

## 5. Basic Idea

Let:

`dp[i]` = minimum number of coins required to make amount `i`.

For amount `0`, we need zero coins:

`dp[0] = 0`

For every amount `i` from `1` to `V`, try every coin.

If a coin `coins[j]` can be used, then:

`dp[i] = min(dp[i], dp[i - coins[j]] + 1)`

The `+1` represents the current coin.

If an amount cannot be formed, its value remains a very large value called `INF`.

Finally:

- If `dp[V]` is still `INF`, return `-1`.
- Otherwise, return `dp[V]`.

---

## 6. Why Dynamic Programming is Suitable

The problem has **overlapping subproblems**.

For example, while calculating the answer for amount `6`, we may need the answer for amount `3` many times.

Dynamic Programming stores the answer for each smaller amount, so it does not calculate the same amount repeatedly.

It also has the **optimal substructure** property: an optimal solution for an amount can be built from an optimal solution of a smaller amount.

---

## 7. Step-by-Step Algorithm

1. Read the number of coin denominations `n`.
2. Read the `n` coin values into an array.
3. Read the target amount `V`.
4. Create a DP array `dp[0...V]`.
5. Set `dp[0] = 0`.
6. Set every other `dp[i]` to `INF`.
7. For every amount `i` from `1` to `V`:
   - Check every coin denomination.
   - If the coin value is less than or equal to `i` and `dp[i - coin]` is possible:
     - Calculate `dp[i - coin] + 1`.
     - Keep the smaller value.
8. After filling the DP array:
   - If `dp[V] == INF`, print `-1`.
   - Otherwise, print `dp[V]`.
9. Stop.

---

## 8. C Program

```c
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
```

---

## 9. Explanation of the Program

### `#include <stdio.h>`

This includes the standard input/output library.

It is required for `printf()` and `scanf()`.

### `#define INF 1000000`

`INF` means a very large value.

It represents an amount that currently cannot be formed.

We do not use actual infinity in C, so a sufficiently large integer is used.

---

### Function: `minCoins()`

```c
int minCoins(int coins[], int n, int V)
```

This function calculates the minimum number of coins.

#### Parameters

- `coins[]` → stores the coin denominations.
- `n` → number of denominations.
- `V` → target amount.

#### Return value

- Returns the minimum number of coins.
- Returns `-1` if the target cannot be formed.

---

### DP Array

```c
int dp[V + 1];
```

The array stores the answer for every amount from `0` to `V`.

For example:

- `dp[0]` → minimum coins for amount 0.
- `dp[1]` → minimum coins for amount 1.
- `dp[2]` → minimum coins for amount 2.
- ...
- `dp[V]` → minimum coins for the target.

---

### Initializing `dp[0]`

```c
dp[0] = 0;
```

Zero coins are required to make amount zero.

---

### Initializing Other Values

```c
for (i = 1; i <= V; i++)
{
    dp[i] = INF;
}
```

Initially, we assume every positive amount is impossible.

Later, the algorithm updates these values when a valid combination is found.

---

### Main DP Loops

```c
for (i = 1; i <= V; i++)
{
    for (j = 0; j < n; j++)
```

The outer loop considers every amount from `1` to `V`.

The inner loop checks every coin denomination.

Therefore, there are approximately:

`V × n`

iterations.

---

### Checking a Coin

```c
if (coins[j] <= i && dp[i - coins[j]] != INF)
```

This checks two things:

1. The current coin can fit into the current amount.
2. The remaining amount can already be formed.

For example, if:

`i = 6` and `coin = 4`

then the remaining amount is:

`6 - 4 = 2`

If `dp[2]` is possible, we can use the coin `4`.

---

### Updating the Minimum

```c
if (dp[i] > dp[i - coins[j]] + 1)
{
    dp[i] = dp[i - coins[j]] + 1;
}
```

The expression:

`dp[i - coins[j]] + 1`

means:

- minimum coins for the remaining amount
- plus the current coin.

We update `dp[i]` only if this gives a smaller number.

---

### Checking Whether the Target is Possible

```c
if (dp[V] == INF)
    return -1;
```

If the target still has `INF`, no combination of the given coins can make it.

---

### Returning the Answer

```c
return dp[V];
```

If the target is possible, return its minimum coin count.

---

## 10. Important Variables

| Variable | Meaning |
|---|---|
| `coins[]` | Stores all coin denominations |
| `n` | Number of coin denominations |
| `V` | Target amount |
| `dp[]` | Stores minimum coins for every amount |
| `i` | Current amount being calculated |
| `j` | Current coin being checked |
| `INF` | Large value representing an impossible amount |

---

## 11. Sample Input

```text
Enter the number of coin denominations: 3
Enter the coin denominations:
1 3 4
Enter the target amount: 6
```

## 12. Sample Output

```text
Minimum number of coins = 2
```

The answer is:

`3 + 3 = 6`

So only 2 coins are required.

---

## 13. Complete Dry Run

Consider:

- Coins = `{1, 3, 4}`
- Target = `6`

Initially:

| Amount | dp value |
|---:|---:|
| 0 | 0 |
| 1 | INF |
| 2 | INF |
| 3 | INF |
| 4 | INF |
| 5 | INF |
| 6 | INF |

### Amount = 1

Only coin `1` can be used.

`dp[1] = dp[0] + 1 = 1`

### Amount = 2

Using coin `1`:

`dp[2] = dp[1] + 1 = 2`

### Amount = 3

Using coin `1`:

`dp[3] = 3`

Using coin `3`:

`dp[3] = dp[0] + 1 = 1`

So:

`dp[3] = 1`

### Amount = 4

Using coin `1`:

`dp[4] = dp[3] + 1 = 2`

Using coin `3`:

`dp[4] = dp[1] + 1 = 2`

Using coin `4`:

`dp[4] = dp[0] + 1 = 1`

So:

`dp[4] = 1`

### Amount = 5

Using coin `1`:

`dp[5] = dp[4] + 1 = 2`

Using coin `3`:

`dp[5] = dp[2] + 1 = 3`

Using coin `4`:

`dp[5] = dp[1] + 1 = 2`

So:

`dp[5] = 2`

### Amount = 6

Using coin `1`:

`dp[6] = dp[5] + 1 = 3`

Using coin `3`:

`dp[6] = dp[3] + 1 = 2`

Using coin `4`:

`dp[6] = dp[2] + 1 = 3`

Therefore:

`dp[6] = 2`

Final answer = **2 coins**.

### Final DP Table

| Amount | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---:|---:|---:|---:|---:|---:|---:|
| Minimum coins | 0 | 1 | 2 | 1 | 1 | 2 | 2 |

---

## 14. Complexity Analysis

Let:

- `n` = number of coin denominations
- `V` = target amount

### Time Complexity

The outer loop runs from `1` to `V`.

So it runs `V` times.

For each amount, the inner loop checks all `n` coins.

So the total number of main iterations is approximately:

`V × n`

Therefore:

**Time Complexity = O(nV)**

More precisely, the algorithm always performs these two nested loops, so its running time is:

**Θ(nV)**

for the standard implementation.

### Best Case

**Θ(nV)**

Even when a good coin is found early, the program still checks the remaining coins for each amount.

### Average Case

**Θ(nV)**

The number of loop iterations does not depend on the particular coin values.

### Worst Case

**Θ(nV)**

All amounts from `1` to `V` are processed and all `n` coins are checked.

### Space Complexity

The DP array contains `V + 1` entries.

Therefore:

**Space Complexity = O(V)**

The input coin array requires `O(n)` space, so total storage is `O(n + V)`. The additional DP space is `O(V)`.

---

## 15. How the Complexity Was Obtained

The important part is:

```c
for (i = 1; i <= V; i++)
{
    for (j = 0; j < n; j++)
```

The first loop executes `V` times.

For each execution of the first loop, the second loop executes `n` times.

Therefore:

`V × n = nV`

Hence:

`Time = O(nV)`

The DP array has `V + 1` elements, so:

`Space = O(V)`

---

## 16. Complexity Graph

The included graph is based on the theoretical complexity `O(nV)`.

For the graph, the target amount `V` is fixed at 100, so:

`nV = 100n`

Therefore, when the number of denominations `n` increases, the theoretical operation count grows linearly with `n` for fixed `V`.

The graph is **not experimental benchmark data**. It is a visualization of the mathematical growth represented by `nV`.

File:

`minimum_coin_change_complexity.png`

---

## 17. Advantages

1. Gives the minimum number of coins.
2. Works for arbitrary positive coin denominations.
3. Handles unlimited supply of coins.
4. Avoids repeated subproblem calculations.
5. Easier to understand than recursive brute force after learning DP.
6. Has polynomial time complexity `O(nV)`.

---

## 18. Disadvantages / Limitations

1. It depends on the target amount `V`.
2. If `V` is extremely large, the DP array can become large.
3. It uses extra memory of `O(V)`.
4. It is not always possible to solve the problem efficiently when the target amount is extremely large.

---

## 19. Difference Between Greedy and Dynamic Programming

### Greedy

Greedy selects the locally largest or most suitable coin at each step.

It can fail for arbitrary denominations.

Example:

Coins = `{1, 3, 4}`, target = `6`

Greedy:

`4 + 1 + 1 = 6`

Number of coins = `3`

Optimal:

`3 + 3 = 6`

Number of coins = `2`

Therefore, greedy does not always give the optimal answer.

### Dynamic Programming

DP checks all relevant possibilities while storing previously calculated results.

For the same example, it correctly finds:

`3 + 3`

So the minimum is `2`.

---

## 20. How to Compile and Run

### Using GCC

Save the program as:

```text
minimum_coin_change.c
```

Compile:

```bash
gcc minimum_coin_change.c -o minimum_coin_change
```

Run:

```bash
./minimum_coin_change
```

On Windows, you can run:

```bash
minimum_coin_change.exe
```

---

## 21. Viva Preparation

### Q1. What is the main idea of this algorithm?

**Answer:** We use Dynamic Programming. We calculate the minimum number of coins for every amount from `0` to `V` and store the answers in a DP array.

### Q2. Why did you choose Dynamic Programming?

**Answer:** The problem has overlapping subproblems and optimal substructure. DP stores previously calculated answers and avoids repeated calculations.

### Q3. What does `dp[i]` represent?

**Answer:** `dp[i]` represents the minimum number of coins required to make amount `i`.

### Q4. Why is `dp[0] = 0`?

**Answer:** To make amount zero, we need zero coins.

### Q5. Why do you initialize the other DP values to `INF`?

**Answer:** Initially we assume those amounts cannot be formed. Later, valid combinations replace `INF` with smaller values.

### Q6. What is the recurrence used?

**Answer:**

`dp[i] = min(dp[i], dp[i - coin] + 1)`

It means we use one current coin plus the best solution for the remaining amount.

### Q7. What is the time complexity?

**Answer:** `O(nV)`, where `n` is the number of denominations and `V` is the target amount. The two nested loops run approximately `nV` times.

### Q8. What is the space complexity?

**Answer:** `O(V)` for the DP array. If input storage is also counted, total storage is `O(n + V)`.

### Q9. Does greedy always work for this problem?

**Answer:** No. Greedy does not always give the minimum number of coins for arbitrary denominations.

### Q10. What happens if the target cannot be formed?

**Answer:** `dp[V]` remains `INF`, so the function returns `-1`.

### Q11. Why is there an infinite supply of coins?

**Answer:** The same denomination can be selected multiple times. The DP recurrence naturally allows this because it can use `dp[i - coin]` again.

### Q12. Why do we check `dp[i - coins[j]] != INF`?

**Answer:** It ensures that the remaining amount is actually possible before using the current coin.

### Q13. Why is the array size `V + 1`?

**Answer:** We need positions from `0` through `V`, which is `V + 1` positions.

### Q14. Why is `j` used?

**Answer:** `j` is the index used to access each coin denomination in the `coins` array.

### Q15. Why is the function `minCoins()` used?

**Answer:** It keeps the main algorithm separate from input/output code and makes the program easier to understand and reuse.

---

## 22. C-Code-Specific Viva Questions

### Q1. Why do we use `scanf()`?

**Answer:** `scanf()` is used to take input from the user.

### Q2. Why do we use `printf()`?

**Answer:** `printf()` displays messages and the final answer on the screen.

### Q3. Why is `coins[]` passed to the function?

**Answer:** The function needs access to all coin denominations to calculate the minimum.

### Q4. Why are two loops used?

**Answer:** The outer loop processes each amount, while the inner loop checks every available coin for that amount.

### Q5. Why is `INF` used instead of zero for initialization?

**Answer:** Zero would incorrectly mean that the amount requires zero coins. `INF` represents an amount that has not been made possible yet.

---

## 23. Teacher-Explanation Version

If the teacher asks, **"Explain your algorithm and code,"** you can say:

> "This program solves the Minimum Coin Change problem using Dynamic Programming. We are given different coin denominations and a target amount, and we have to find the minimum number of coins needed to make that amount.
>
> I use a DP array where `dp[i]` stores the minimum number of coins required to make amount `i`. I initialize `dp[0]` to zero because zero coins are needed for amount zero, and initially set the other values to a large value called `INF`.
>
> Then I process every amount from 1 to the target amount. For each amount, I check every coin. If the coin can be used, I compare the current answer with `dp[i - coin] + 1` and keep the smaller value.
>
> After filling the DP array, `dp[V]` gives the minimum number of coins. If it is still `INF`, the amount cannot be formed, so I return `-1`.
>
> The time complexity is `O(nV)` because I check `n` coins for each of the `V` amounts, and the space complexity is `O(V)` because of the DP array."
