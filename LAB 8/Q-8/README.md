# Optimal Binary Search Tree (OBST)

## 1. Problem Title

**Optimal Binary Search Trees (OBST) using Dynamic Programming**

## 2. Problem Statement

Given `n` distinct sorted keys:

`k1, k2, ..., kn`

with successful search probabilities:

`p1, p2, ..., pn`

and `n + 1` dummy keys:

`d0, d1, ..., dn`

with unsuccessful search probabilities:

`q0, q1, ..., qn`, find the binary search tree having the **minimum expected search cost**.

The program uses **Dynamic Programming** to find the minimum expected cost.

---

## 3. Objective

The objective is to construct an Optimal Binary Search Tree such that the expected cost of searching for a key is minimum.

---

## 4. Possible Approaches

There are several possible approaches:

1. **Brute force:** Generate all possible BSTs and calculate their costs. This becomes very slow because the number of BSTs grows rapidly.
2. **Dynamic Programming:** Solve smaller subproblems and reuse their results.

For this lab, **Dynamic Programming** is the suitable approach because many smaller OBST problems are repeated.

---

## 5. Basic Idea

Let:

- `e[i][j]` = minimum expected search cost for keys `ki ... kj`
- `w[i][j]` = sum of all probabilities involved from `ki ... kj`
- `root[i][j]` = root key selected for the optimal subtree

For every interval `i...j`, try every key `r` from `i` to `j` as the root.

The recurrence is:

`e[i][j] = min(e[i][r-1] + e[r+1][j] + w[i][j])`

The weight is:

`w[i][j] = w[i][j-1] + p[j] + q[j]`

Base case:

`e[i][i-1] = q[i-1]`

This is the standard bottom-up Dynamic Programming solution.

---

## 6. Why Dynamic Programming?

The problem has **overlapping subproblems**. For example, the same smaller ranges of keys are needed while checking different possible roots.

It also has **optimal substructure**: an optimal tree for a range contains optimal subtrees for its left and right ranges.

Therefore, Dynamic Programming avoids recalculating the same subproblems.

---

## 7. Step-by-Step Algorithm

1. Read the number of keys `n`.
2. Read the successful search probabilities `p1 ... pn`.
3. Read the unsuccessful search probabilities `q0 ... qn`.
4. Initialize the empty-subtree costs:
   `e[i][i-1] = q[i-1]`.
5. Calculate the initial weights:
   `w[i][i-1] = q[i-1]`.
6. Consider subtrees of length 1, then length 2, and so on up to length `n`.
7. For every interval `i...j`, calculate its total probability weight.
8. Try every possible key `r` between `i` and `j` as the root.
9. Calculate:
   `cost = e[i][r-1] + e[r+1][j] + w[i][j]`.
10. Store the smallest cost in `e[i][j]`.
11. Store the root producing that minimum cost in `root[i][j]`.
12. After all intervals are processed, `e[1][n]` is the minimum expected search cost.
13. Print the minimum cost and the root table.

---

## 8. C Program

```c
#include <stdio.h>

#define MAX 20

double p[MAX + 1];
double q[MAX + 1];
double e[MAX + 2][MAX + 1];
double w[MAX + 2][MAX + 1];
int root[MAX + 1][MAX + 1];

void optimalBST(int n)
{
    int i, j, r, length;
    double cost;

    /* Base case: empty subtrees */
    for (i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    /* Consider subtrees of increasing length */
    for (length = 1; length <= n; length++)
    {
        for (i = 1; i <= n - length + 1; i++)
        {
            j = i + length - 1;

            /* Calculate total probability weight */
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            e[i][j] = 999999.0;

            /* Try every key as the root */
            for (r = i; r <= j; r++)
            {
                cost = e[i][r - 1] + e[r + 1][j] + w[i][j];

                if (cost < e[i][j])
                {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }
}

void printRootTable(int n)
{
    int i, j;

    printf("\nRoot Table:\n");

    for (i = 1; i <= n; i++)
    {
        for (j = i; j <= n; j++)
        {
            printf("root[%d][%d] = k%d\n", i, j, root[i][j]);
        }
    }
}

void printTree(int i, int j, int parent, char side)
{
    int r;

    if (i > j)
        return;

    r = root[i][j];

    if (parent == 0)
        printf("Root: k%d\n", r);
    else
        printf("k%d is the %s child of k%d\n", r,
               side == 'L' ? "left" : "right", parent);

    printTree(i, r - 1, r, 'L');
    printTree(r + 1, j, r, 'R');
}

int main()
{
    int n, i;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter successful search probabilities p1 to p%d:\n", n);
    for (i = 1; i <= n; i++)
    {
        scanf("%lf", &p[i]);
    }

    printf("Enter unsuccessful search probabilities q0 to q%d:\n", n);
    for (i = 0; i <= n; i++)
    {
        scanf("%lf", &q[i]);
    }

    optimalBST(n);

    printf("\nMinimum Expected Search Cost = %.3lf\n", e[1][n]);

    printRootTable(n);

    printf("\nOptimal Binary Search Tree:\n");
    printTree(1, n, 0, ' ');

    return 0;
}
```

---

## 9. Important Code Explanation

### `p[]`

```c
double p[MAX + 1];
```

Stores successful search probabilities.

`p[1]` stores the probability of searching for `k1`, `p[2]` for `k2`, and so on.

### `q[]`

```c
double q[MAX + 1];
```

Stores unsuccessful search probabilities.

`q[0]` is the probability of searching before `k1`, and `q[n]` is the probability after `kn`.

### `e[][]`

```c
double e[MAX + 2][MAX + 1];
```

Stores the minimum expected cost of every possible key interval.

For example:

`e[1][3]` = minimum cost for keys `k1, k2, k3`.

### `w[][]`

Stores the total probability of a subtree.

It allows us to avoid repeatedly adding all probabilities.

### `root[][]`

Stores which key gives the minimum cost for each interval.

For example:

`root[1][3] = 2`

means `k2` is the best root for keys `k1...k3`.

---

## 10. Function: `optimalBST()`

### Purpose

This is the main Dynamic Programming function.

### Parameter

`n` = number of keys.

### What it does

It:

1. Initializes empty subtrees.
2. Builds solutions from smaller intervals to larger intervals.
3. Calculates weights.
4. Tries every key as a root.
5. Stores the minimum cost and corresponding root.

---

## 11. Function: `printRootTable()`

This function prints the root selected for each interval.

It helps us verify the Dynamic Programming calculation.

---

## 12. Function: `printTree()`

This function uses the `root[][]` table to print the structure of the optimal BST.

It is recursive because a binary tree naturally contains left and right subtrees.

---

## 13. Dry Run

Consider:

- `n = 3`
- Keys: `k1, k2, k3`
- `p1 = 0.15`
- `p2 = 0.10`
- `p3 = 0.05`
- `q0 = 0.05`
- `q1 = 0.10`
- `q2 = 0.05`
- `q3 = 0.10`

The probabilities sum to:

`0.15 + 0.10 + 0.05 + 0.05 + 0.10 + 0.05 + 0.10 = 0.60`

For a probability distribution, the probabilities normally sum to 1. So for a cleaner OBST example, use:

- `p1 = 0.15`
- `p2 = 0.10`
- `p3 = 0.05`
- `q0 = 0.05`
- `q1 = 0.15`
- `q2 = 0.20`
- `q3 = 0.30`

These sum to 1.00.

### Step 1: Empty subtrees

`e[1][0] = q0 = 0.05`

`e[2][1] = q1 = 0.15`

`e[3][2] = q2 = 0.20`

`e[4][3] = q3 = 0.30`

### Step 2: One-key subtrees

For `k1`:

`w[1][1] = q0 + p1 + q1`

`= 0.05 + 0.15 + 0.15 = 0.35`

Cost:

`e[1][0] + e[2][1] + w[1][1]`

`= 0.05 + 0.15 + 0.35 = 0.55`

Therefore:

`e[1][1] = 0.55`

Similarly:

| Interval | Weight | Minimum Cost | Root |
|---|---:|---:|---|
| k1 | 0.35 | 0.55 | k1 |
| k2 | 0.45 | 0.80 | k2 |
| k3 | 0.55 | 1.05 | k3 |

### Step 3: Two-key subtree k1...k2

Weight:

`w[1][2] = 0.35 + p2 + q2`

`= 0.35 + 0.10 + 0.20 = 0.65`

Try `k1` as root:

`e[1][0] + e[2][2] + w[1][2]`

`= 0.05 + 0.80 + 0.65 = 1.50`

Try `k2` as root:

`e[1][1] + e[3][2] + w[1][2]`

`= 0.55 + 0.20 + 0.65 = 1.40`

So:

`e[1][2] = 1.40`

and root is `k2`.

### Step 4: Two-key subtree k2...k3

Weight:

`w[2][3] = 0.45 + p3 + q3`

`= 0.45 + 0.05 + 0.30 = 0.80`

Try `k2`:

`e[2][1] + e[3][3] + 0.80`

`= 0.15 + 0.90 + 0.80 = 1.85`

Try `k3`:

`e[2][2] + e[4][3] + 0.80`

`= 0.80 + 0.30 + 0.80 = 1.90`

Therefore root is `k2` and:

`e[2][3] = 1.90`

### Step 5: Three-key subtree k1...k3

Weight:

`w[1][3] = 0.65 + p3 + q3`

`= 0.65 + 0.05 + 0.30 = 1.00`

Try `k1`:

`e[1][0] + e[2][3] + 1.00`

`= 0.05 + 1.90 + 1.00`

`= 2.95`

Try `k2`:

`e[1][1] + e[3][3] + 1.00`

`= 0.55 + 1.05 + 1.00`

`= 2.60`

Try `k3`:

`e[1][2] + e[4][3] + 1.00`

`= 1.40 + 0.30 + 1.00`

`= 2.70`

Minimum = `2.60`

Therefore:

`root[1][3] = k2`

and:

`Minimum Expected Search Cost = 2.60`

The resulting tree is:

```text
       k2
      /  \
    k1    k3
```

---

## 14. Complexity Analysis

### Time Complexity

The algorithm considers all possible intervals.

There are approximately `O(n²)` intervals.

For every interval, the program tries every possible root, which can take up to `O(n)` choices.

Therefore:

`O(n²) × O(n) = O(n³)`

So the overall time complexity is:

**O(n³)**

### Best Case

The standard bottom-up Dynamic Programming implementation still checks all candidate roots, even if a good root is found early.

Therefore:

**Best-case time = O(n³)**

### Average Case

The same loops are executed regardless of the input probabilities.

Therefore:

**Average-case time = O(n³)**

### Worst Case

Again, all intervals and all possible roots are examined.

Therefore:

**Worst-case time = O(n³)**

### Space Complexity

The program stores:

- `e[][]` → O(n²)
- `w[][]` → O(n²)
- `root[][]` → O(n²)

Therefore:

**Space complexity = O(n²)**

The recursive `printTree()` uses at most O(n) call-stack space, but the DP tables dominate the memory usage.

---

## 15. Complexity Graph

The generated graph compares conceptual `O(n²)` and `O(n³)` growth.

It is **not measured execution-time data**. The curves only illustrate how the mathematical growth rates differ.

Download:

[OBST Complexity Graph](sandbox:/mnt/data/obst_complexity_graph.png)

---

## 16. Advantages

1. Avoids generating every possible BST.
2. Reuses solutions to smaller subproblems.
3. Gives the minimum expected search cost.
4. The approach is systematic and suitable for DAA.
5. The root table can also be used to reconstruct the optimal tree.

---

## 17. Disadvantages / Limitations

1. `O(n³)` time can become expensive for very large `n`.
2. It uses `O(n²)` memory.
3. The program uses fixed-size arrays, so `n` must remain within the chosen maximum.
4. Floating-point probabilities can have small rounding differences.

---

## 18. Viva Preparation

### Q1. What is an Optimal Binary Search Tree?

An OBST is a binary search tree arranged so that the expected search cost is minimum for the given successful and unsuccessful search probabilities.

### Q2. Which technique is used?

Dynamic Programming.

### Q3. Why is Dynamic Programming suitable?

Because the problem has overlapping subproblems and optimal substructure.

### Q4. What does `e[i][j]` represent?

It stores the minimum expected search cost for keys from `ki` to `kj`.

### Q5. What does `w[i][j]` represent?

It stores the total probability of successful and unsuccessful searches associated with that interval.

### Q6. What does `root[i][j]` store?

It stores the key selected as the root of the optimal subtree from `ki` to `kj`.

### Q7. What is the time complexity?

`O(n³)`.

There are `O(n²)` intervals and up to `n` roots are tested for each interval.

### Q8. What is the space complexity?

`O(n²)` because the DP tables contain a quadratic number of entries.

### Q9. Why are dummy keys required?

They represent unsuccessful searches for values that are not present in the key set.

### Q10. What is the base case?

For an empty subtree:

`e[i][i-1] = q[i-1]`.

### Q11. Why do we add `w[i][j]` to the cost?

When a subtree becomes one level deeper, all searches represented by that subtree have one additional comparison. The total probability of those searches is `w[i][j]`.

### Q12. Why do we try every key as the root?

Any key in the interval can potentially be the root. We must check all possibilities to guarantee the minimum cost.

### Q13. What happens when `n` increases?

The running time grows approximately cubically and the memory requirement grows quadratically.

### Q14. How is this better than brute force?

Brute force can generate a very large number of possible BSTs. Dynamic Programming avoids repeatedly solving the same subproblems.

### Q15. Why is `999999.0` used?

It acts as a large initial value so that the first calculated cost will be smaller and replace it.

---

## 19. C-Code Specific Viva Questions

### Q16. Why is `double` used for probabilities?

Probabilities can contain decimal values such as `0.15`, so `double` provides suitable floating-point storage.

### Q17. Why does the loop start with `length = 1`?

A subtree containing one key is the smallest non-empty subtree. Larger subtrees are then built using these smaller solutions.

### Q18. Why is `r` used?

`r` represents the candidate root position. The loop tries each key in the interval as the root.

### Q19. Why is `root[][]` an integer array?

It stores key positions such as `1`, `2`, and `3`, so an integer array is sufficient.

### Q20. Why is `printTree()` recursive?

A binary tree is naturally recursive: every node can have a left subtree and a right subtree. The function follows the stored root positions recursively.

---

## 20. How to Compile and Run

### GCC

Save the program as:

`obst.c`

Compile:

```bash
gcc obst.c -o obst
```

Run:

```bash
./obst
```

On Windows:

```bash
gcc obst.c -o obst.exe
obst.exe
```

---

## 21. Sample Input

```text
3
0.15 0.10 0.05
0.05 0.15 0.20 0.30
```

## 22. Sample Output

```text
Minimum Expected Search Cost = 2.600

Root Table:
root[1][1] = k1
root[1][2] = k2
root[1][3] = k2
root[2][2] = k2
root[2][3] = k2
root[3][3] = k3

Optimal Binary Search Tree:
Root: k2
k1 is the left child of k2
k3 is the right child of k2
```

---

## 23. Conclusion

The Optimal Binary Search Tree problem can be solved efficiently using Dynamic Programming. Instead of generating every possible BST, the algorithm stores the best result for smaller ranges of keys and uses them to solve larger ranges. The standard implementation takes `O(n³)` time and `O(n²)` space.

The most important idea to remember for viva is:

**"For every interval, try every key as the root, calculate the left and right subtree costs, add the interval probability weight, and keep the minimum."**


## 24. Teacher-Explanation Version

"Sir/Ma'am, this program finds an Optimal Binary Search Tree using Dynamic Programming. We are given successful search probabilities `p` and unsuccessful search probabilities `q`. For every range of keys, I try each key as the possible root. I calculate the cost of its left subtree, right subtree, and the total probability weight of that range. Then I store the minimum cost in the DP table `e` and the selected root in the `root` table.

The program first solves the smaller subtrees and then uses those results to solve larger subtrees. At the end, `e[1][n]` gives the minimum expected search cost. The `printTree()` function uses the root table to show the resulting tree. Since there are O(n²) intervals and up to O(n) roots for each interval, the time complexity is O(n³), while the DP tables require O(n²) space."
