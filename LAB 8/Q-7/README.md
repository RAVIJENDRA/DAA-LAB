# Rod Cutting with Reconstruction

## 1. Problem Title

**Rod Cutting with Reconstruction using Dynamic Programming**

## 2. Problem Statement

Given a rod of length `n` inches and an array of prices:

`P = [p1, p2, ..., pn]`

where `pi` is the selling price of a rod piece of length `i`, find:

1. The maximum revenue that can be obtained by cutting the rod.
2. The exact lengths of the pieces that form an optimal decomposition.

The cuts are integral, and the sum of all piece lengths must be exactly `n`. The rod may also be left uncut.

---

## 3. Objective

The objective is to use **Dynamic Programming** to:

- Calculate the maximum possible revenue.
- Store enough information to reconstruct the actual pieces used.
- Analyze the time and space complexity of the solution.

---

## 4. Possible Approaches

There are two common approaches:

1. **Recursive / Brute Force:** Try every possible first cut recursively. This is simple but has exponential running time because many subproblems are solved repeatedly.
2. **Dynamic Programming:** Store the best answer for every smaller rod length and reuse those answers.

For this lab, **Dynamic Programming** is chosen because it is simple to implement and avoids repeated calculations.

---

## 5. Basic Idea

Let:

`dp[i] = maximum revenue obtainable from a rod of length i`

For a rod of length `i`, the first piece can have any length from `1` to `i`.

If the first piece has length `j`, then:

`revenue = price[j] + dp[i-j]`

Therefore:

`dp[i] = max(price[j] + dp[i-j])` for `1 <= j <= i`

To reconstruct the solution, another array called `cut[]` stores the first piece length that gives the best revenue for each rod length.

After calculating `dp[n]`, we repeatedly use `cut[n]`, then move to `n - cut[n]`, until the remaining length becomes zero.

---

## 6. Why Dynamic Programming is Suitable

The problem has **overlapping subproblems** and **optimal substructure**.

- The same smaller rod lengths are needed many times in the recursive solution.
- The optimal solution for a rod of length `i` can be constructed using an optimal solution for a smaller length `i-j`.

Dynamic Programming calculates each smaller problem once and stores its result.

---

## 7. Step-by-Step Algorithm

1. Read the rod length `n`.
2. Read the prices for lengths `1` through `n`.
3. Set `dp[0] = 0` because a rod of length zero gives zero revenue.
4. For each rod length `i` from `1` to `n`:
   - Set `maxRevenue` to a small value.
   - Try every possible first piece length `j` from `1` to `i`.
   - Calculate `price[j] + dp[i-j]`.
   - If this value is greater than the current maximum:
     - Update `maxRevenue`.
     - Store `j` in `cut[i]`.
   - Store `maxRevenue` in `dp[i]`.
5. The maximum revenue is `dp[n]`.
6. To reconstruct the pieces:
   - Start with `length = n`.
   - Print `cut[length]`.
   - Replace `length` by `length - cut[length]`.
   - Repeat until `length` becomes zero.
7. Print the maximum revenue and the piece lengths.

---

## 8. C Program

```c
#include <stdio.h>

#define MAX 100

void rodCutting(int price[], int n, int dp[], int cut[]) {
    int i, j;
    int maxRevenue;

    dp[0] = 0;

    for (i = 1; i <= n; i++) {
        maxRevenue = -1;

        for (j = 1; j <= i; j++) {
            if (price[j] + dp[i - j] > maxRevenue) {
                maxRevenue = price[j] + dp[i - j];
                cut[i] = j;
            }
        }

        dp[i] = maxRevenue;
    }
}

void printSolution(int cut[], int n) {
    int length = n;

    printf("Pieces in optimal decomposition: ");

    while (length > 0) {
        printf("%d ", cut[length]);
        length = length - cut[length];
    }

    printf("\n");
}

int main() {
    int n, i;
    int price[MAX + 1];
    int dp[MAX + 1];
    int cut[MAX + 1];

    printf("Enter the length of the rod: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid rod length. Enter a value between 1 and %d.\n", MAX);
        return 0;
    }

    printf("Enter prices for lengths 1 to %d:\n", n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }

    rodCutting(price, n, dp, cut);

    printf("\nMaximum revenue = %d\n", dp[n]);
    printSolution(cut, n);

    return 0;
}

```

---

## 9. Important Functions

### `rodCutting()`

**Purpose:** Calculates the maximum revenue for every rod length and stores the choice used for reconstruction.

**Parameters:**
- `price[]` - array containing prices.
- `n` - length of the rod.
- `dp[]` - stores maximum revenue for every length.
- `cut[]` - stores the first piece length selected for every length.

**Return value:** It does not return a value. It modifies `dp[]` and `cut[]`.

### `printSolution()`

**Purpose:** Prints the actual piece lengths in the optimal decomposition.

It starts from the full rod length and repeatedly follows the values stored in `cut[]`.

---

## 10. Important Variables

| Variable | Meaning |
|---|---|
| `n` | Total length of the rod |
| `price[i]` | Price of a piece of length `i` |
| `dp[i]` | Maximum revenue for a rod of length `i` |
| `cut[i]` | First piece length selected for a rod of length `i` |
| `i` | Current rod length being solved |
| `j` | Possible first piece length |
| `maxRevenue` | Best revenue found for the current length |
| `length` | Remaining rod length during reconstruction |

---

## 11. Sample Input

```text
Enter the length of the rod: 8
Enter prices for lengths 1 to 8:
1 5 8 9 10 17 17 20
```

## 12. Sample Output

```text
Maximum revenue = 22
Pieces in optimal decomposition: 2 6
```

The two pieces have lengths `2` and `6`.

Their total length is:

`2 + 6 = 8`

Their total revenue is:

`price[2] + price[6] = 5 + 17 = 22`

---

## 13. Complete Dry Run

Consider:

- `n = 8`
- Prices = `[1, 5, 8, 9, 10, 17, 17, 20]`

We calculate the DP table.

| Rod length `i` | Best calculation | `dp[i]` | `cut[i]` |
|---:|---|---:|---:|
| 0 | No piece | 0 | - |
| 1 | 1 + dp[0] | 1 | 1 |
| 2 | max(1+1, 5+0) | 5 | 2 |
| 3 | max(1+5, 5+1, 8+0) | 8 | 3 |
| 4 | max(1+8, 5+5, 8+1, 9+0) | 10 | 2 |
| 5 | max(1+10, 5+8, 8+5, 9+1, 10+0) | 13 | 2 |
| 6 | max(1+13, 5+10, 8+8, 9+5, 10+1, 17+0) | 17 | 6 |
| 7 | max(1+17, 5+13, 8+10, 9+8, 10+5, 17+1, 17+0) | 18 | 1 |
| 8 | max(1+17, 5+17, 8+13, 9+10, 10+8, 17+5, 17+1, 20+0) | 22 | 2 |

So:

`dp[8] = 22`

and:

`cut[8] = 2`

### Reconstruction

Start with:

`length = 8`

1. `cut[8] = 2`  
   Choose piece `2`.  
   Remaining length = `8 - 2 = 6`.

2. `cut[6] = 6`  
   Choose piece `6`.  
   Remaining length = `6 - 6 = 0`.

Stop.

Therefore, the optimal decomposition is:

`2 + 6`

and the maximum revenue is:

`5 + 17 = 22`

---

## 14. Complexity Analysis

### Time Complexity

The outer loop runs from `1` to `n`.

For every `i`, the inner loop runs from `1` to `i`.

Therefore, the total number of inner-loop iterations is:

`1 + 2 + 3 + ... + n`

Using the sum of first `n` natural numbers:

`n(n+1)/2`

This is:

`Theta(n^2)`

Therefore:

- **Best case:** `Theta(n^2)`
- **Average case:** `Theta(n^2)`
- **Worst case:** `Theta(n^2)`

The reason all three are the same is that the program checks the same set of possible cuts regardless of the price values. The `if` condition may select different cuts, but the loops still perform the same number of iterations.

### Space Complexity

The program uses:

- `price[]` of size `n`
- `dp[]` of size `n`
- `cut[]` of size `n`

Therefore, the total additional storage is:

`Theta(n)`

So the **space complexity is Theta(n)**.

---

## 15. Complexity Graph

The accompanying PNG file is:

**`rod_cutting_complexity.png`**

The main curve represents the actual number of inner-loop iterations:

`n(n+1)/2`

which grows as `Theta(n^2)`.

The graph also shows `O(n)` and `O(n log n)` reference growth curves to make the quadratic growth easier to compare.

The graph uses:

- X-axis: **Input Size (n)**
- Y-axis: **Number of Operations / Time**
- White background
- Input sizes from `1` to `100`

The curves are mathematical growth representations, not experimental benchmark results.

---

## 16. Advantages

1. Avoids repeated calculations.
2. Finds the maximum revenue efficiently compared with brute force.
3. Also reconstructs the actual pieces used.
4. Easy to implement using arrays.
5. Suitable for understanding Dynamic Programming.

---

## 17. Disadvantages / Limitations

1. Requires extra memory for the DP and reconstruction arrays.
2. Time complexity is quadratic.
3. The program uses a fixed maximum size (`MAX = 100`).
4. The solution assumes integer rod lengths and integer price values.

---

## 18. Difference from Brute Force

### Brute Force

Brute force tries different cutting combinations recursively. It can repeatedly solve the same smaller rod-length problems, resulting in exponential time in the straightforward recursive implementation.

### Dynamic Programming

Dynamic Programming stores the answer for each smaller rod length and reuses it.

Therefore, the DP solution takes:

`Theta(n^2)`

time and `Theta(n)` space.

---

## 19. Viva Preparation

### Q1. What is the main idea of this algorithm?

**Answer:** The main idea is to use Dynamic Programming. We calculate the maximum revenue for every smaller rod length and use those results to calculate the answer for the complete rod.

### Q2. Why did you choose Dynamic Programming?

**Answer:** Because the rod cutting problem has overlapping subproblems and optimal substructure. Dynamic Programming avoids calculating the same subproblem repeatedly.

### Q3. What does `dp[i]` store?

**Answer:** `dp[i]` stores the maximum revenue that can be obtained from a rod of length `i`.

### Q4. What does `cut[i]` store?

**Answer:** `cut[i]` stores the first piece length selected in an optimal solution for a rod of length `i`.

### Q5. What is the recurrence relation?

**Answer:**

`dp[i] = max(price[j] + dp[i-j])`

for all `j` from `1` to `i`.

### Q6. What is the time complexity?

**Answer:** Theta(n²), because the inner loop runs `1 + 2 + ... + n = n(n+1)/2` times.

### Q7. What is the space complexity?

**Answer:** Theta(n), because we use the `price`, `dp`, and `cut` arrays.

### Q8. Why is `dp[0] = 0`?

**Answer:** A rod of length zero has no pieces, so its maximum revenue is zero.

### Q9. How is reconstruction performed?

**Answer:** We start from `n`, use `cut[n]` to find the first piece, subtract it from the remaining length, and continue until the remaining length becomes zero.

### Q10. What happens if the input size increases?

**Answer:** The running time grows approximately quadratically, so increasing `n` makes the computation grow faster than a linear algorithm.

### Q11. What is the advantage over simple recursion?

**Answer:** Simple recursion repeatedly solves the same smaller problems. Dynamic Programming stores their results and avoids this repeated work.

### Q12. Can the rod be left uncut?

**Answer:** Yes. The case `j = i` means the whole rod is selected as one piece.

### Q13. Why is `maxRevenue` reset for every `i`?

**Answer:** Because for every new rod length `i`, we must find the best revenue independently among all possible first cuts.

### Q14. Why is the `while` loop used in `printSolution()`?

**Answer:** It follows the stored choices in `cut[]` until the complete rod length has been reconstructed.

### Q15. Why do we use `cut[i] = j`?

**Answer:** When a better revenue is found by taking a first piece of length `j`, we store `j` so that we can later reconstruct the actual solution.

---

## 20. How to Compile and Run

### Using GCC

Save the program as:

`rod_cutting.c`

Compile:

```bash
gcc rod_cutting.c -o rod_cutting
```

Run:

```bash
./rod_cutting
```

On Windows:

```bash
rod_cutting.exe
```

---

## 21. Teacher-Explanation Version

If the teacher asks, **"Explain your algorithm and code"**, you can say:

> "This is the rod cutting problem, and I have solved it using Dynamic Programming. The main idea is to find the maximum revenue for every rod length from 1 to n. For each length `i`, I try every possible first cut `j`. The revenue for that choice is `price[j] + dp[i-j]`, where `dp[i-j]` is the best revenue already calculated for the remaining rod.
>
> I store the best revenue in the `dp` array. Along with that, I use another `cut` array to remember which first piece length gave the best result. After calculating `dp[n]`, I reconstruct the solution by starting from `n` and repeatedly subtracting `cut[length]`. This gives me the exact piece lengths.
>
> The time complexity is Theta(n²), because the inner loop runs 1, 2, up to n times, giving `n(n+1)/2` iterations. The space complexity is Theta(n) because I use arrays for prices, DP values, and reconstruction. This approach is better than simple recursion because it avoids solving the same subproblems repeatedly."

---

## 22. Conclusion

The Rod Cutting problem can be efficiently solved using Dynamic Programming. The algorithm calculates the maximum revenue for all smaller rod lengths and stores the first cut that gives the best result. This makes it possible to obtain both the maximum revenue and the exact optimal decomposition.

The final complexity is:

- **Time:** `Theta(n²)`
- **Space:** `Theta(n)`

This approach is simple, efficient, and suitable for a DAA laboratory implementation.
