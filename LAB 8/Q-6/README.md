# Edit Distance with Traceback Information

## 1. Problem Title

**Edit Distance with Traceback Information**

## 2. Problem Statement

Given two strings `A` of length `m` and `B` of length `n`, find the minimum number of operations required to transform `A` into `B`.

The allowed operations are:

1. **Insertion** – insert a character.
2. **Deletion** – delete a character.
3. **Substitution** – replace one character by another.

The program must also print the **traceback information**, which shows the sequence of operations used to obtain the minimum edit distance.

---

## 3. Objective

The objectives are:

- Calculate the minimum edit distance between two strings.
- Use Dynamic Programming to avoid repeated calculations.
- Store traceback information for every DP state.
- Reconstruct and print the operations that give the minimum cost.
- Analyze the time and space complexity.

---

## 4. Possible Approaches

There are two common approaches:

### 1. Brute Force / Recursive Approach

The recursive method tries different insertion, deletion, and substitution possibilities. It creates many repeated subproblems, so its running time becomes exponential in the input length.

### 2. Dynamic Programming

Dynamic Programming stores the answer of each smaller subproblem in a table. Each state is calculated only once.

**Chosen approach: Dynamic Programming**, because it is simple to implement, efficient, and naturally supports traceback.

---

## 5. Basic Idea

Let:

`dp[i][j]` = minimum number of operations needed to transform the first `i` characters of `A` into the first `j` characters of `B`.

For every pair of positions:

### If the characters are equal

If:

`A[i-1] == B[j-1]`

then no operation is required for these two characters:

`dp[i][j] = dp[i-1][j-1]`

### If the characters are different

There are three choices:

- Insert `B[j-1]`: `dp[i][j-1] + 1`
- Delete `A[i-1]`: `dp[i-1][j] + 1`
- Substitute `A[i-1]` with `B[j-1]`: `dp[i-1][j-1] + 1`

Therefore:

`dp[i][j] = min(insert, delete, substitute)`

Along with the cost, the program stores which operation was selected in the `trace` table.

---

## 6. Why Dynamic Programming is Suitable

The edit distance problem has **overlapping subproblems** and **optimal substructure**.

For example, calculating the edit distance for two prefixes may be needed several times if a recursive solution is used.

Dynamic Programming stores these results once, reducing the time from exponential to:

**O(m × n)**

It also makes traceback easy because the chosen operation can be stored at every DP cell.

---

## 7. Step-by-Step Algorithm

1. Read strings `A` and `B`.
2. Find their lengths `m` and `n`.
3. Create a DP table `dp[m+1][n+1]`.
4. Create a traceback table `trace[m+1][n+1]`.
5. Initialize the first column:
   - `dp[i][0] = i`
   - This means deleting all `i` characters.
6. Initialize the first row:
   - `dp[0][j] = j`
   - This means inserting all `j` characters.
7. For every `i` from 1 to `m` and `j` from 1 to `n`:
   - If the characters are equal, copy the diagonal value.
   - Otherwise calculate insertion, deletion, and substitution costs.
   - Store the minimum cost.
   - Store the operation that produced the minimum.
8. The final answer is `dp[m][n]`.
9. Start traceback from `(m,n)`.
10. Move through the `trace` table until `(0,0)` is reached.
11. Store the operations and print them in forward order.

---

## 8. C Program

```c
#include <stdio.h>
#include <string.h>

#define MAX 100

/* Print the operations in forward order using the traceback table. */
void printTrace(char A[], char B[], char trace[MAX + 1][MAX + 1],
                int i, int j)
{
    char steps[MAX + MAX][120];
    int count = 0;

    while (i > 0 || j > 0)
    {
        if (i > 0 && j > 0 && trace[i][j] == 'M')
        {
            sprintf(steps[count],
                    "Match: '%c' -> '%c' (no operation)",
                    A[i - 1], B[j - 1]);
            count++;
            i--;
            j--;
        }
        else if (i > 0 && j > 0 && trace[i][j] == 'S')
        {
            sprintf(steps[count],
                    "Substitute: '%c' -> '%c'",
                    A[i - 1], B[j - 1]);
            count++;
            i--;
            j--;
        }
        else if (i > 0 && trace[i][j] == 'D')
        {
            sprintf(steps[count],
                    "Delete: '%c'",
                    A[i - 1]);
            count++;
            i--;
        }
        else if (j > 0 && trace[i][j] == 'I')
        {
            sprintf(steps[count],
                    "Insert: '%c'",
                    B[j - 1]);
            count++;
            j--;
        }
    }

    /* The traceback is collected from the end to the beginning,
       so print it in reverse to show the forward transformation. */
    for (i = count - 1; i >= 0; i--)
    {
        printf("%d. %s\n", count - i, steps[i]);
    }
}

int min3(int a, int b, int c)
{
    int min = a;

    if (b < min)
        min = b;

    if (c < min)
        min = c;

    return min;
}

int main()
{
    char A[MAX + 1], B[MAX + 1];
    int dp[MAX + 1][MAX + 1];
    char trace[MAX + 1][MAX + 1];
    int m, n;
    int i, j;

    printf("Enter first string: ");
    scanf("%100s", A);

    printf("Enter second string: ");
    scanf("%100s", B);

    m = strlen(A);
    n = strlen(B);

    /* Base cases */
    for (i = 0; i <= m; i++)
    {
        dp[i][0] = i;
        if (i > 0)
            trace[i][0] = 'D';
    }

    for (j = 0; j <= n; j++)
    {
        dp[0][j] = j;
        if (j > 0)
            trace[0][j] = 'I';
    }

    /* Fill the DP table and store the choice used at every cell. */
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
                trace[i][j] = 'M';
            }
            else
            {
                int insertCost = dp[i][j - 1] + 1;
                int deleteCost = dp[i - 1][j] + 1;
                int substituteCost = dp[i - 1][j - 1] + 1;

                dp[i][j] = min3(insertCost, deleteCost, substituteCost);

                if (dp[i][j] == substituteCost)
                    trace[i][j] = 'S';
                else if (dp[i][j] == deleteCost)
                    trace[i][j] = 'D';
                else
                    trace[i][j] = 'I';
            }
        }
    }

    printf("\nMinimum edit distance = %d\n", dp[m][n]);

    printf("\nTraceback operations:\n");
    printTrace(A, B, trace, m, n);

    return 0;
}

```

---

## 9. Important Functions

### `min3()`

```c
int min3(int a, int b, int c)
```

**Purpose:** Finds the smallest of three integer values.

**Parameters:**
- `a` = insertion cost
- `b` = deletion cost
- `c` = substitution cost

**Returns:** The smallest value.

It is used while calculating the DP table.

### `printTrace()`

```c
void printTrace(char A[], char B[], char trace[MAX + 1][MAX + 1],
                int i, int j)
```

**Purpose:** Reconstructs the operations used to obtain the minimum edit distance.

It starts from the final DP cell `(m,n)` and follows the stored decisions backward.

The operations are temporarily stored in `steps[]`, and then printed in reverse so that the user sees the transformation from `A` to `B`.

---

## 10. Important Variables

| Variable | Meaning |
|---|---|
| `A` | First input string |
| `B` | Second input string |
| `m` | Length of `A` |
| `n` | Length of `B` |
| `dp[i][j]` | Minimum edit distance for prefixes of lengths `i` and `j` |
| `trace[i][j]` | Operation selected at DP cell `(i,j)` |
| `i`, `j` | Row and column indexes |
| `insertCost` | Cost of inserting a character |
| `deleteCost` | Cost of deleting a character |
| `substituteCost` | Cost of substituting a character |
| `steps` | Stores traceback operations before printing |

The traceback table uses:

- `M` = Match
- `S` = Substitution
- `D` = Deletion
- `I` = Insertion

---

## 11. Sample Input

```text
Enter first string: kitten
Enter second string: sitting
```

## 12. Sample Output

One possible output is:

```text
Minimum edit distance = 3

Traceback operations:
1. Substitute: 'k' -> 's'
2. Match: 'i' -> 'i' (no operation)
3. Match: 't' -> 't' (no operation)
4. Match: 't' -> 't' (no operation)
5. Substitute: 'e' -> 'i'
6. Match: 'n' -> 'n' (no operation)
7. Insert: 'g'
```

**Note:** The exact operation sequence printed for cases with multiple equally optimal edit sequences can differ. The important result is that the minimum number of edit operations is correct.

For `kitten -> sitting`, the minimum distance is `3`. A standard transformation is:

```text
kitten
sitten    (substitute k -> s)
sittin    (substitute e -> i)
sitting   (insert g)
```

---

## 13. Dry Run

Use the small example:

```text
A = cat
B = cut
```

Here:

- `m = 3`
- `n = 3`

The DP table becomes:

|   | Ø | c | u | t |
|---|---:|---:|---:|---:|
| Ø | 0 | 1 | 2 | 3 |
| c | 1 | 0 | 1 | 2 |
| a | 2 | 1 | 1 | 2 |
| t | 3 | 2 | 2 | 1 |

Therefore:

`dp[3][3] = 1`

So only one operation is required.

### Traceback

Start at `(3,3)`:

- `t` matches `t` → move diagonally to `(2,2)`.
- `a` is different from `u`.
- The minimum operation is substitution → replace `a` with `u`.
- Move diagonally to `(1,1)`.
- `c` matches `c` → move diagonally to `(0,0)`.

Forward transformation:

```text
cat
cut
```

Operation:

```text
Substitute 'a' -> 'u'
```

Minimum edit distance:

```text
1
```

---

## 14. Complexity Analysis

Let the lengths of the two strings be `m` and `n`.

### Time Complexity

The DP table has:

`(m + 1) × (n + 1)`

cells.

Each cell performs only a constant amount of work: comparison and calculation of at most three costs.

Therefore:

**Time Complexity = O(m × n)**

### Best Case

**Θ(m × n)** for the standard full-table implementation.

Even if many characters match, the program still fills the complete DP table.

### Average Case

**Θ(m × n)**

The same DP table is filled regardless of the particular character arrangement.

### Worst Case

**Θ(m × n)**

Every DP cell is processed once.

### When `m = n`

If both strings have approximately the same length `n`:

**Θ(n²)**

### Space Complexity

The program uses:

- DP table: `O(m × n)`
- Traceback table: `O(m × n)`
- Traceback operation storage: `O(m + n)`

Therefore the overall space complexity is:

**O(m × n)**

---

## 15. How the Complexity Was Derived

There are approximately `m × n` DP cells.

For each cell, the program calculates a fixed number of values:

- insertion
- deletion
- substitution

A constant amount of work per cell gives:

`m × n × constant`

which simplifies to:

**O(m × n)**

For equal-sized strings, `m = n`, so:

`O(n × n) = O(n²)`

---

## 16. Complexity Graph

The generated graph is based on the theoretical complexity, not experimental timing data.

For equal input lengths (`m = n`), the edit-distance DP algorithm has:

**Θ(n²)** time complexity.

The graph plots a normalized quadratic growth curve against input size.

File:

`edit_distance_complexity.png`

---

## 17. Advantages

1. Gives the minimum number of edit operations.
2. Much faster than the basic recursive approach.
3. Easy to understand using a DP table.
4. Traceback gives the actual operations.
5. Works for arbitrary strings.
6. Has predictable `O(m × n)` time complexity.

---

## 18. Disadvantages / Limitations

1. Requires `O(m × n)` memory.
2. For very large strings, the DP table can become large.
3. The program uses a fixed maximum string length of 100 characters.
4. When multiple optimal solutions exist, the program stores one possible traceback based on its tie-breaking order.

---

## 19. Viva Preparation

### Q1. What is edit distance?

Edit distance is the minimum number of insertions, deletions, and substitutions required to transform one string into another.

### Q2. Which algorithm is used?

Dynamic Programming.

### Q3. Why did you use Dynamic Programming?

Because the problem has overlapping subproblems and optimal substructure. DP avoids calculating the same subproblem repeatedly.

### Q4. What does `dp[i][j]` represent?

It represents the minimum operations required to transform the first `i` characters of `A` into the first `j` characters of `B`.

### Q5. What are the three operations?

Insertion, deletion, and substitution.

### Q6. What happens when the two current characters are equal?

No operation is needed, so:

`dp[i][j] = dp[i-1][j-1]`

### Q7. What happens when the characters are different?

The program considers insertion, deletion, and substitution and chooses the minimum cost.

### Q8. What is the time complexity?

`O(m × n)`.

If both strings have length `n`, it becomes `O(n²)`.

### Q9. What is the space complexity?

`O(m × n)` because the DP and traceback tables are stored.

### Q10. What is traceback?

Traceback means starting from the final DP cell and following the stored decisions to reconstruct the operations that produced the optimal answer.

### Q11. Why is the `trace` table needed?

The DP table tells us the minimum cost, but the trace table tells us which operation produced that cost.

### Q12. What does `M` mean in the trace table?

`M` means the two characters matched, so no operation was needed.

### Q13. What does `S` mean?

`S` means substitution.

### Q14. What happens if input size increases?

The number of DP cells increases approximately as `m × n`. For equal lengths, doubling `n` increases the theoretical table size by about four times.

### Q15. What is the disadvantage compared with a recursive approach?

The recursive approach can use much more time because of repeated subproblems. DP uses extra memory to store results but is much more efficient.

---

## 20. C-Code Specific Viva Questions

### Q1. Why are `dp` and `trace` two-dimensional arrays?

Because each state depends on two prefix lengths: `i` characters of `A` and `j` characters of `B`.

### Q2. Why do we use `A[i-1]` and `B[j-1]`?

The DP indexes start from 1, while C strings use indexes starting from 0. Therefore DP cell `(i,j)` corresponds to characters `A[i-1]` and `B[j-1]`.

### Q3. Why is `dp[i][0] = i`?

Transforming a string of `i` characters into an empty string requires deleting all `i` characters.

### Q4. Why is `dp[0][j] = j`?

Transforming an empty string into a string of `j` characters requires inserting all `j` characters.

### Q5. Why is `min3()` used?

At every mismatching pair of characters there are three possible operations. `min3()` selects the operation with the minimum cost.

---

## 21. Compilation and Execution

### Using GCC

Save the program as:

```text
edit_distance.c
```

Compile:

```bash
gcc edit_distance.c -o edit_distance
```

Run:

```bash
./edit_distance
```

On Windows:

```bash
gcc edit_distance.c -o edit_distance.exe
edit_distance.exe
```

---

## 22. Teacher-Explanation Version

You can explain the program like this:

> "My problem is to find the minimum number of insertions, deletions, and substitutions needed to convert one string into another. I have used Dynamic Programming because the same smaller string problems occur repeatedly.
>
> I created a DP table where `dp[i][j]` represents the minimum operations needed to convert the first `i` characters of the first string into the first `j` characters of the second string. I initialize the first row and column because converting to or from an empty string requires only insertions or deletions.
>
> If the current characters are equal, I copy the diagonal value. Otherwise, I calculate the cost of insertion, deletion, and substitution and take the minimum. Along with the minimum value, I store the selected operation in a traceback table.
>
> After filling the table, `dp[m][n]` gives the minimum edit distance. Then I start from the last cell and follow the traceback information back to the first cell. This gives me the actual sequence of operations.
>
> The time complexity is `O(m*n)` because there are `m*n` DP cells and constant work is done at each cell. The space complexity is also `O(m*n)` because I store the DP and traceback tables."
