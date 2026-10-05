# Longest Common Subsequence (LCS) — DAA Lab

## 1. Problem Title

**Longest Common Subsequence (LCS)**

## 2. Problem Statement

Given two sequences:

- `X = <x1, x2, ..., xm>`
- `Y = <y1, y2, ..., yn>`

find:

1. The **length** of their Longest Common Subsequence (LCS).
2. The **actual LCS string**.

The solution should use an appropriate algorithm, be implemented in C, and include complexity analysis.

---

## 3. Objective

The objective is to learn how to solve the LCS problem using **Dynamic Programming (DP)** and reconstruct the actual subsequence from the DP table.

---

## 4. Possible Approaches

There are two common approaches:

### 4.1 Brute Force / Recursive Approach

We can generate possible subsequences and compare them.

- It is simple to understand.
- However, it repeats many subproblems.
- Its worst-case time complexity is exponential, approximately `O(2^n)` for two sequences of comparable size.

### 4.2 Dynamic Programming

Dynamic Programming stores solutions of smaller subproblems in a table and reuses them.

- Time complexity: `O(mn)`
- Space complexity: `O(mn)` when the full table is kept for reconstruction.

**Chosen approach:** Dynamic Programming, because it is much more efficient and directly supports reconstruction of the actual LCS.

---

## 5. Basic Idea

Let `dp[i][j]` represent the length of the LCS of:

- the first `i` characters of string `X`
- the first `j` characters of string `Y`

There are two cases.

### Case 1: Characters match

If:

```text
X[i-1] == Y[j-1]
```

then that character can be included in the LCS:

```text
dp[i][j] = dp[i-1][j-1] + 1
```

### Case 2: Characters do not match

If:

```text
X[i-1] != Y[j-1]
```

we consider removing one character from either sequence:

```text
dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

After filling the table, `dp[m][n]` contains the length of the LCS.

To reconstruct the actual LCS, start from `dp[m][n]` and move backwards through the table.

---

## 6. Step-by-Step Algorithm

1. Read the two strings `X` and `Y`.
2. Find their lengths `m` and `n`.
3. Create a DP table `dp[m+1][n+1]`.
4. Set the first row and first column to `0`.
5. For every `i` from `1` to `m`:
   - For every `j` from `1` to `n`:
     - If `X[i-1] == Y[j-1]`, set:
       `dp[i][j] = dp[i-1][j-1] + 1`.
     - Otherwise, set:
       `dp[i][j]` to the larger of `dp[i-1][j]` and `dp[i][j-1]`.
6. The LCS length is `dp[m][n]`.
7. Start from row `m`, column `n`.
8. If the current characters are equal:
   - Put that character into the LCS.
   - Move diagonally to `i-1, j-1`.
9. If the characters are different:
   - Move to the neighboring cell having the larger DP value.
10. The characters are collected backwards, so reverse them before printing.
11. Print the LCS length and the actual LCS.

---

## 7. C Program

> This beginner-friendly version supports strings of up to 100 characters.

```c
#include <stdio.h>
#include <string.h>

#define MAX 100

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

/* Builds the DP table and returns the LCS length */
int findLCS(char X[], char Y[], int m, int n, int dp[MAX + 1][MAX + 1])
{
    int i, j;

    /* First row and first column are already zero */
    for (i = 0; i <= m; i++)
        dp[i][0] = 0;

    for (j = 0; j <= n; j++)
        dp[0][j] = 0;

    /* Fill the DP table */
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

/* Reconstructs the actual LCS from the DP table */
void printLCS(char X[], char Y[], int m, int n,
              int dp[MAX + 1][MAX + 1])
{
    char lcs[MAX + 1];
    int i = m;
    int j = n;
    int k = dp[m][n];

    lcs[k] = '\0';

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[k - 1] = X[i - 1];
            i--;
            j--;
            k--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("LCS: %s\n", lcs);
}

int main()
{
    char X[MAX + 1];
    char Y[MAX + 1];

    int m, n;
    int dp[MAX + 1][MAX + 1];
    int length;

    printf("Enter first string: ");
    scanf("%100s", X);

    printf("Enter second string: ");
    scanf("%100s", Y);

    m = strlen(X);
    n = strlen(Y);

    length = findLCS(X, Y, m, n, dp);

    printf("Length of LCS: %d\n", length);

    printLCS(X, Y, m, n, dp);

    return 0;
}
```

---

## 8. Explanation of the C Program

### Header files

```c
#include <stdio.h>
#include <string.h>
```

- `stdio.h` is required for `printf()` and `scanf()`.
- `string.h` is required for `strlen()`.

### Maximum size

```c
#define MAX 100
```

This program accepts strings with at most 100 characters.

---

### `max()` function

```c
int max(int a, int b)
```

This function receives two integers and returns the larger one.

It is used when the two current characters are different.

---

### `findLCS()` function

```c
int findLCS(char X[], char Y[], int m, int n,
            int dp[MAX + 1][MAX + 1])
```

This function:

- receives the two strings,
- receives their lengths,
- receives the DP table,
- fills the DP table,
- returns the LCS length.

#### Important variables

- `i` — represents the current position in `X`.
- `j` — represents the current position in `Y`.
- `dp[i][j]` — stores the LCS length for the first `i` characters of `X` and first `j` characters of `Y`.

---

### Initializing the first row and column

```c
for (i = 0; i <= m; i++)
    dp[i][0] = 0;

for (j = 0; j <= n; j++)
    dp[0][j] = 0;
```

If one string has length zero, the LCS length is zero.

Therefore, the first row and first column contain zero.

---

### Filling the DP table

```c
for (i = 1; i <= m; i++)
{
    for (j = 1; j <= n; j++)
```

These nested loops examine every pair of positions.

There are approximately `m × n` table cells.

---

### When characters match

```c
if (X[i - 1] == Y[j - 1])
{
    dp[i][j] = dp[i - 1][j - 1] + 1;
}
```

If the current characters are equal, that character is included in the LCS.

We take the diagonal value and add `1`.

The `-1` is needed because C arrays use zero-based indexing while the DP table uses row/column numbers starting from `1`.

---

### When characters do not match

```c
else
{
    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
}
```

There are two possibilities:

- ignore the current character of `X`, or
- ignore the current character of `Y`.

We choose the larger LCS length.

---

## 9. LCS Reconstruction

The function:

```c
void printLCS(...)
```

reconstructs the actual LCS.

It starts from:

```c
i = m;
j = n;
```

which means the bottom-right corner of the DP table.

### If characters are equal

```c
if (X[i - 1] == Y[j - 1])
```

The character belongs to an LCS.

It is stored in:

```c
lcs[k - 1] = X[i - 1];
```

Then both `i` and `j` are decreased because we move diagonally.

### If characters are different

```c
else if (dp[i - 1][j] > dp[i][j - 1])
```

If the value above is larger, move upward:

```c
i--;
```

Otherwise, move left:

```c
j--;
```

### Why is the LCS stored backwards?

We start at the end of both strings, so we discover the LCS from right to left.

Instead of reversing it later, the program places every discovered character directly at position `k-1`.

---

# 10. Important Variables

| Variable | Meaning |
|---|---|
| `X` | First input string |
| `Y` | Second input string |
| `m` | Length of first string |
| `n` | Length of second string |
| `dp` | Dynamic programming table |
| `i` | Current row / position in `X` |
| `j` | Current column / position in `Y` |
| `lcs` | Stores the reconstructed LCS |
| `k` | Current position while reconstructing |

---

# 11. Sample Input

```text
Enter first string: ABCBDAB
Enter second string: BDCABA
```

# 12. Sample Output

```text
Length of LCS: 4
LCS: BCBA
```

Another valid LCS of length 4 can exist, such as `BDAB`. The exact LCS produced can depend on how ties in the DP table are handled.

---

# 13. Dry Run

Take:

```text
X = ABCBDAB
Y = BDCABA
```

Their lengths are:

```text
m = 7
n = 6
```

The DP table is:

|   | 0 | B | D | C | A | B | A |
|---|---:|---:|---:|---:|---:|---:|---:|
| **0** | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| **A** | 0 | 0 | 0 | 0 | 1 | 1 | 1 |
| **B** | 0 | 1 | 1 | 1 | 1 | 2 | 2 |
| **C** | 0 | 1 | 1 | 2 | 2 | 2 | 2 |
| **B** | 0 | 1 | 1 | 2 | 2 | 3 | 3 |
| **D** | 0 | 1 | 2 | 2 | 2 | 3 | 3 |
| **A** | 0 | 1 | 2 | 2 | 3 | 3 | 4 |
| **B** | 0 | 1 | 2 | 2 | 3 | 4 | 4 |

Therefore:

```text
dp[7][6] = 4
```

So the LCS length is **4**.

---

## 14. Reconstruction Dry Run

Start at:

```text
i = 7, j = 6
```

We move from the bottom-right of the table.

| Step | `i` | `j` | Characters | Action | LCS character |
|---:|---:|---:|---|---|---|
| 1 | 7 | 6 | B, A | Values are different; move left | — |
| 2 | 7 | 5 | B, B | Match; move diagonally | B |
| 3 | 6 | 4 | A, A | Match; move diagonally | A |
| 4 | 5 | 3 | D, C | Move according to larger DP value | — |
| 5 | 4 | 3 | B, C | Move according to DP table | — |
| 6 | 4 | 2 | B, D | Move according to DP table | — |
| 7 | 4 | 1 | B, B | Match | B |
| 8 | 3 | 0 | Stop | — | — |

Depending on tie choices, reconstruction can follow a different valid path. The important point is that the resulting sequence is common to both strings and has the maximum length.

For the sample implementation, one valid output is:

```text
BCBA
```

---

# 15. Why Dynamic Programming Works

The LCS problem has **overlapping subproblems**.

For example, the LCS of smaller prefixes is required repeatedly while solving larger prefixes.

It also has **optimal substructure**: the solution to a larger problem can be constructed from solutions to smaller problems.

Dynamic Programming stores these smaller answers in `dp`, so each subproblem is solved only once.

---

# 16. Time Complexity

Let:

- `m` = length of first string
- `n` = length of second string

The program uses two nested loops:

```c
for (i = 1; i <= m; i++)
{
    for (j = 1; j <= n; j++)
```

The outer loop runs `m` times.

The inner loop runs `n` times for every value of `i`.

Therefore, the number of DP cells processed is approximately:

```text
m × n
```

So:

```text
Time Complexity = O(mn)
```

For two strings of approximately the same length, where `m ≈ n`:

```text
O(mn) ≈ O(n²)
```

### Best Case

**Theta(mn)** for this implementation.

Even if many characters match, the program still fills the complete DP table.

### Average Case

**Theta(mn)**.

The program does not stop early based on the input.

### Worst Case

**Theta(mn)**.

Every DP table cell is processed.

So for this implementation:

```text
Best Case    = Θ(mn)
Average Case = Θ(mn)
Worst Case   = Θ(mn)
```

---

# 17. Space Complexity

The program stores:

```text
dp[MAX+1][MAX+1]
```

The DP table requires `O(mn)` space.

The LCS character array requires `O(min(m,n))` additional space.

Therefore, the overall space complexity is:

```text
O(mn)
```

The full DP table is kept because it is needed to reconstruct the actual LCS.

> If we only wanted the LCS length, the DP table could be optimized to use less memory. But for this assignment, the actual LCS must also be reconstructed.

---

# 18. Complexity Graph

The generated graph represents the theoretical growth of the LCS Dynamic Programming algorithm for the square-input case:

```text
m = n
```

Therefore:

```text
O(mn) = O(n²)
```

The graph uses `n²` as a normalized operation-growth measure. It is **not measured execution time** from a real computer.

The graph has:

- X-axis: **Input Size (n)**
- Y-axis: **Number of Operations / Time**
- Curve: **O(n²)**

Download the graph:

**[Download LCS Complexity Graph](sandbox:/mnt/data/lcs_complexity_graph.png)**

---

# 19. Advantages

1. Much faster than the brute-force recursive approach.
2. Avoids solving the same subproblem repeatedly.
3. Finds the length of the LCS efficiently.
4. The full DP table allows reconstruction of the actual LCS.
5. The algorithm is systematic and easy to implement using nested loops.
6. It is a good example of Dynamic Programming.

---

# 20. Disadvantages / Limitations

1. The full DP table requires `O(mn)` memory.
2. The program has a maximum input size of 100 characters because of the fixed arrays.
3. There can be more than one valid LCS of the same maximum length.
4. The program returns one valid LCS rather than all possible LCSs.

---

# 21. Brute Force vs Dynamic Programming

| Feature | Brute Force | Dynamic Programming |
|---|---|---|
| Main idea | Try possible subsequences | Store smaller subproblem results |
| Time | Exponential in general | `O(mn)` |
| Repeated work | High | Avoided |
| LCS reconstruction | Possible | Easy using DP table |
| Suitable for larger inputs | No | Much better |

---

# 22. How to Compile and Run

### Using GCC

Save the program as:

```text
lcs.c
```

Compile:

```bash
gcc lcs.c -o lcs
```

Run:

### Windows

```bash
lcs.exe
```

### Linux / macOS

```bash
./lcs
```

Then enter the two strings when prompted.

---

# 23. Viva Preparation

### 1. What is LCS?

LCS stands for **Longest Common Subsequence**. It is the longest sequence that appears in both strings in the same order, but the characters do not have to be continuous.

### 2. What is the main idea of this algorithm?

The algorithm uses Dynamic Programming. It stores the LCS lengths of smaller prefixes in a table and uses those values to solve larger prefixes.

### 3. Why did you use Dynamic Programming?

Because the LCS problem has overlapping subproblems and optimal substructure. Dynamic Programming avoids repeated calculations.

### 4. What does `dp[i][j]` mean?

`dp[i][j]` stores the length of the LCS between the first `i` characters of `X` and the first `j` characters of `Y`.

### 5. What happens when `X[i-1] == Y[j-1]`?

We include that character in the LCS:

```text
dp[i][j] = dp[i-1][j-1] + 1
```

### 6. What happens when the characters are different?

We take the larger value from the cell above or the cell to the left:

```text
dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

### 7. What is the time complexity?

The time complexity is **O(mn)** because the program fills an `m × n` DP table.

For equal-sized strings, it becomes **O(n²)**.

### 8. What is the space complexity?

The space complexity is **O(mn)** because the complete DP table is stored.

### 9. Why do you need the complete DP table?

The table is needed not only to find the LCS length but also to trace backward and reconstruct the actual LCS.

### 10. Why is the first row and column zero?

If one string is empty, there cannot be any common subsequence. Therefore, the LCS length is zero.

### 11. What is a subsequence?

A subsequence is obtained by deleting zero or more characters without changing the order of the remaining characters.

For example, `ACE` is a subsequence of `ABCDE`.

### 12. Is an LCS always unique?

No. There can be multiple different LCSs having the same maximum length.

### 13. Why is `i-1` used in `X[i-1]`?

The DP table starts indexing from 1, but C strings use zero-based indexing. Therefore, DP position `i` corresponds to string position `i-1`.

### 14. Why is the `max()` function used?

When the current characters are different, we need to choose the larger LCS length obtained by excluding one character from either string.

### 15. Why does `printLCS()` start from the bottom-right?

The bottom-right cell `dp[m][n]` contains the LCS length for both complete strings. Tracing backward from there reconstructs one LCS.

---

# 24. C-Code-Specific Viva Questions

### Q1. Why is `strlen()` used?

`strlen()` finds the number of characters in a string. It is used to obtain `m` and `n`.

### Q2. Why are nested loops used?

The DP table has two dimensions. One loop processes the characters of the first string and the other processes the characters of the second string.

### Q3. Why is `lcs[k] = '\0'` used?

C strings must end with the null character `'\0'`. It tells C where the string ends.

### Q4. Why does `k--` happen after finding a matching character?

A matching character is stored at position `k-1`, so `k` is decreased to prepare for the next character.

### Q5. Why are `i--` and `j--` used during reconstruction?

They move backward through the DP table. When characters match, both are decreased because we move diagonally.

---

# 25. Short Teacher-Explanation Version

If the teacher asks, **"Explain your algorithm and code,"** you can say:

> "My problem is to find the Longest Common Subsequence of two strings and also print the actual subsequence. I used Dynamic Programming because the same smaller LCS problems occur repeatedly.
>
> I created a DP table where `dp[i][j]` stores the LCS length of the first `i` characters of the first string and the first `j` characters of the second string. If the current characters are equal, I add one to the diagonal value. If they are different, I take the maximum of the value above and the value on the left.
>
> After filling the table, `dp[m][n]` gives the LCS length. To print the actual LCS, I start from the bottom-right cell and move backwards. If the characters match, I include that character and move diagonally. Otherwise, I move toward the neighboring cell with the larger value.
>
> Since I fill an `m × n` table, the time complexity is `O(mn)`, and because I store the complete table, the space complexity is also `O(mn)`. For strings of equal length, the time complexity is `O(n²)`."

---

# 26. Conclusion

The LCS problem is a classic Dynamic Programming problem. By storing the solutions of smaller subproblems in a DP table, the algorithm reduces the repeated work of brute-force methods.

The program finds both the **length** and **actual LCS**, with:

```text
Time Complexity  : O(mn)
Space Complexity : O(mn)
```

For two strings of equal length `n`, the time complexity is `O(n²)`.

This makes the approach suitable for a DAA lab demonstration of Dynamic Programming and solution reconstruction.
