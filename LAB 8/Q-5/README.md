# Maximum Sum Increasing Subsequence

## 1. Problem Title

**Maximum Sum Increasing Subsequence (MSIS)**

## 2. Problem Statement

Given an array of `n` positive integers:

`A = [a0, a1, ..., an-1]`

find the **maximum possible sum of a strictly increasing subsequence**.

A subsequence does not have to contain consecutive elements, but the order of the selected elements must remain the same.

For example, for:

`[1, 101, 2, 3, 100, 4, 5]`

one increasing subsequence is:

`[1, 2, 3, 100]`

Its sum is:

`1 + 2 + 3 + 100 = 106`

So the maximum sum is **106**.

---

## 3. Objective

The objective is to:

1. Find the maximum sum of a strictly increasing subsequence.
2. Use a suitable Dynamic Programming approach.
3. Implement the algorithm in C.
4. Analyze its time and space complexity.

---

## 4. Possible Approaches

There are several ways to solve this problem:

### 1. Brute Force

Generate all possible subsequences and check which ones are increasing. This can require exponential time, approximately `O(2^n)`.

### 2. Dynamic Programming

Store the best increasing-subsequence sum ending at every index.

Time complexity: `O(n^2)`  
Space complexity: `O(n)`

### 3. More Advanced Optimizations

Some related increasing-subsequence problems can be optimized using data structures such as Fenwick trees or segment trees after coordinate compression. However, those approaches are more complicated.

### Approach Chosen

We choose **Dynamic Programming with O(n²) time and O(n) extra space** because it is simple, beginner-friendly, and directly demonstrates the Dynamic Programming technique required in a DAA lab.

---

## 5. Basic Idea

Define:

`dp[i]` = maximum sum of a strictly increasing subsequence that **ends at index i**.

Initially:

`dp[i] = a[i]`

because the element `a[i]` itself is always a subsequence.

For every earlier index `j`:

- If `a[j] < a[i]`, then `a[i]` can be added after the subsequence ending at `j`.
- The new possible sum is:

`dp[j] + a[i]`

- If this is greater than the current `dp[i]`, update `dp[i]`.

Finally, the answer is the largest value in `dp[]`.

---

## 6. Why Dynamic Programming Is Suitable

The problem has overlapping subproblems.

For each element `a[i]`, we need the best increasing subsequence ending at earlier elements. These results can be stored in `dp[]` and reused instead of calculating them again.

The DP solution is also much simpler than generating all possible subsequences.

---

## 7. Step-by-Step Algorithm

1. Read `n` and the array.
2. Create an array `dp[]`.
3. Set `dp[i] = a[i]` for every element.
4. For every element `a[i]`, check all previous elements `a[j]`.
5. If `a[j] < a[i]`, then an increasing subsequence can continue from `j` to `i`.
6. Check whether `dp[j] + a[i]` is greater than `dp[i]`.
7. If it is greater, update `dp[i]`.
8. After filling `dp[]`, find the largest value in it.
9. Print that value as the maximum sum.

---

## 8. C Program

```c
#include <stdio.h>

#define MAX 100

int maximumSumIncreasingSubsequence(int a[], int n)
{
    int dp[MAX];
    int i, j;
    int maxSum;

    /* Initially, each element forms an increasing subsequence by itself. */
    for (i = 0; i < n; i++)
    {
        dp[i] = a[i];
    }

    /* Find the best increasing subsequence ending at each position. */
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (a[j] < a[i] && dp[i] < dp[j] + a[i])
            {
                dp[i] = dp[j] + a[i];
            }
        }
    }

    /* Find the largest value in dp[]. */
    maxSum = dp[0];

    for (i = 1; i < n; i++)
    {
        if (dp[i] > maxSum)
        {
            maxSum = dp[i];
        }
    }

    return maxSum;
}

int main()
{
    int a[MAX];
    int n, i;
    int result;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d positive integers:\n", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    result = maximumSumIncreasingSubsequence(a, n);

    printf("Maximum sum of increasing subsequence = %d\n", result);

    return 0;
}
```

---

## 9. Program Explanation

### `#include <stdio.h>`

This includes the standard input/output library so that `printf()` and `scanf()` can be used.

### `#define MAX 100`

This sets the maximum array size to 100 for this simple lab program.

### Function: `maximumSumIncreasingSubsequence()`

```c
int maximumSumIncreasingSubsequence(int a[], int n)
```

This function receives:

- `a[]` - the input array
- `n` - number of elements

It returns the maximum sum.

### `dp[]`

```c
int dp[MAX];
```

`dp[i]` stores the maximum sum of an increasing subsequence ending at `a[i]`.

For example:

```text
a  = 1  2  3  100
dp = 1  3  6  106
```

The `dp` values can be larger than the individual array values because they represent sums.

### Initializing `dp[]`

```c
for (i = 0; i < n; i++)
{
    dp[i] = a[i];
}
```

Every element by itself is an increasing subsequence. Therefore, the initial sum ending at each element is that element itself.

### Nested loops

```c
for (i = 1; i < n; i++)
{
    for (j = 0; j < i; j++)
```

For every current element `a[i]`, we check every previous element `a[j]`.

### Increasing condition

```c
a[j] < a[i]
```

This ensures that the subsequence is **strictly increasing**.

For example:

```text
2 < 5       true
5 < 5       false
7 < 4       false
```

Equal values cannot be selected one after another because the subsequence must be strictly increasing.

### Updating `dp[i]`

```c
dp[i] < dp[j] + a[i]
```

If adding `a[i]` to the best subsequence ending at `j` gives a larger sum, we update `dp[i]`.

```c
dp[i] = dp[j] + a[i];
```

### Finding the final answer

```c
maxSum = dp[0];

for (i = 1; i < n; i++)
{
    if (dp[i] > maxSum)
    {
        maxSum = dp[i];
    }
}
```

The best increasing subsequence can end at any position, so we find the largest value in `dp[]`.

---

## 10. Important Variables

| Variable | Meaning |
|---|---|
| `a[]` | Stores the input array |
| `n` | Number of elements |
| `dp[]` | Stores the best increasing-subsequence sum ending at each index |
| `i` | Current element index |
| `j` | Previous element index being checked |
| `maxSum` | Largest value found in `dp[]` |
| `result` | Stores the value returned by the DP function |

---

## 11. Dry Run

Consider:

```text
A = [1, 101, 2, 3, 100, 4, 5]
```

Initially:

```text
dp = [1, 101, 2, 3, 100, 4, 5]
```

Now process each element.

| `i` | `a[i]` | Important previous values | `dp[i]` after processing |
|---:|---:|---|---:|
| 0 | 1 | None | 1 |
| 1 | 101 | 1 | 102 |
| 2 | 2 | 1 | 3 |
| 3 | 3 | 1, 2 | 6 |
| 4 | 100 | 1, 2, 3 | 106 |
| 5 | 4 | 1, 2, 3 | 10 |
| 6 | 5 | 1, 2, 3, 4 | 15 |

Final:

```text
dp = [1, 102, 3, 6, 106, 10, 15]
```

The maximum value is:

```text
106
```

The corresponding increasing subsequence is:

```text
1, 2, 3, 100
```

Its sum is:

```text
1 + 2 + 3 + 100 = 106
```

Therefore:

```text
Maximum sum = 106
```

---

## 12. Sample Input

```text
Enter the number of elements: 7
Enter 7 positive integers:
1 101 2 3 100 4 5
```

## 13. Sample Output

```text
Maximum sum of increasing subsequence = 106
```

---

## 14. Complexity Analysis

### Time Complexity

There are two main parts.

#### Initialization

```c
for (i = 0; i < n; i++)
```

runs `n` times:

`O(n)`

#### Nested DP loops

The outer loop runs approximately `n` times.

For each `i`, the inner loop runs `i` times.

The total number of iterations is:

`0 + 1 + 2 + ... + (n - 1)`

Using the sum of the first `n-1` integers:

`n(n-1)/2`

Therefore, the nested loops take:

`O(n²)`

#### Finding the maximum

The final loop takes:

`O(n)`

Overall:

`O(n) + O(n²) + O(n) = O(n²)`

### Best Case

**Theta(n²)**

Even if the array is already decreasing, the program still checks all previous elements for every current element.

### Average Case

**Theta(n²)**

The nested loops execute the same number of index comparisons regardless of the values. The condition only determines whether an update occurs.

### Worst Case

**Theta(n²)**

The same nested loops perform approximately:

`n(n-1)/2`

comparisons.

### Space Complexity

**O(n)** extra space.

The main additional structure is the `dp[]` array of size `n`.

The input array `a[]` also uses `O(n)` storage, so total array storage is `O(n)`. In terms of **auxiliary space**, the DP array requires `O(n)`.

---

## 15. Complexity Graph

The accompanying file:

`msis_complexity_graph.png`

shows the quadratic growth of the algorithm.

The graph uses:

`n(n-1)/2`

as a representative count of iterations of the main inner comparison loop.

This is not an experimental benchmark. It is a mathematical representation of the operation count implied by the nested loops.

The x-axis is:

**Input Size (n)**

The y-axis is:

**Number of Operations / Time**

Because the operation count grows approximately as `n²`, the curve represents **O(n²)** growth.

---

## 16. Advantages

1. Easy to understand and implement.
2. Uses the Dynamic Programming technique clearly.
3. Much faster than brute-force enumeration for larger inputs.
4. Uses only `O(n)` extra DP space.
5. Suitable for a DAA laboratory assignment.
6. Easy to explain during viva.

---

## 17. Disadvantages / Limitations

1. The time complexity is `O(n²)`.
2. It is not the most optimized possible approach for very large arrays.
3. The program uses a fixed `MAX` value of 100.
4. The program calculates the maximum sum but does not reconstruct and print the actual subsequence.

---

## 18. Comparison with Brute Force

### Brute Force

A brute-force method can generate many possible subsequences.

For `n` elements, there can be up to:

`2^n`

subsequences.

Therefore, its running time can become exponential.

### Dynamic Programming

The DP method stores the best answer ending at each position and reuses it.

Time:

`O(n²)`

Space:

`O(n)`

Thus, Dynamic Programming avoids repeatedly solving the same smaller problems.

---

## 19. Viva Preparation

### Q1. What is the main idea of the algorithm?

**Answer:**  
I use Dynamic Programming. `dp[i]` stores the maximum sum of a strictly increasing subsequence ending at index `i`.

### Q2. Why did you choose Dynamic Programming?

**Answer:**  
Because the problem has overlapping subproblems. The best result for an earlier element can be reused when calculating the result for a later element.

### Q3. What does `dp[i]` represent?

**Answer:**  
It represents the maximum sum of a strictly increasing subsequence that ends at `a[i]`.

### Q4. Why is `dp[i]` initially equal to `a[i]`?

**Answer:**  
Because every single element by itself forms an increasing subsequence.

### Q5. Why do we check `a[j] < a[i]`?

**Answer:**  
To make sure the subsequence remains strictly increasing.

### Q6. Why do we use `dp[j] + a[i]`?

**Answer:**  
If `a[j] < a[i]`, we can append `a[i]` to the best increasing subsequence ending at `j`.

### Q7. What is the time complexity?

**Answer:**  
Theta(n²), because there are two nested loops and the total number of comparisons is approximately `n(n-1)/2`.

### Q8. What is the space complexity?

**Answer:**  
O(n) auxiliary space because of the `dp[]` array.

### Q9. What happens if the array is in decreasing order?

**Answer:**  
No two elements can form a longer increasing subsequence. Therefore, the answer will be the largest single element. The program still takes Theta(n²) time because it checks all previous elements.

### Q10. What happens if the array is already increasing?

**Answer:**  
The DP values keep increasing because each new element can extend the previous subsequence. The algorithm still takes Theta(n²) time.

### Q11. Why do we need the final loop?

**Answer:**  
The maximum-sum subsequence can end at any position, so we find the largest value in `dp[]`.

### Q12. What is the difference between subsequence and subarray?

**Answer:**  
A subarray contains consecutive elements, while a subsequence does not need to contain consecutive elements. The relative order must still be maintained.

### Q13. Is the subsequence strictly increasing?

**Answer:**  
Yes. We use `a[j] < a[i]`, not `a[j] <= a[i]`.

### Q14. Why is `MAX` used in the C program?

**Answer:**  
It sets the maximum number of input elements that the simple lab program can store.

### Q15. Why is the function return type `int`?

**Answer:**  
The function returns the maximum sum, which is stored as an integer in this program.

---

## 20. C-Code-Specific Viva Questions

### Q1. Why are there two loops inside the function?

**Answer:**  
The outer loop selects the current element, and the inner loop checks all previous elements that could come before it in an increasing subsequence.

### Q2. Why is `j` initialized to 0?

**Answer:**  
Because for each current element `i`, we need to check previous elements starting from the first element.

### Q3. Why is the inner loop condition `j < i`?

**Answer:**  
Only elements before `i` can appear before `a[i]` in the subsequence.

### Q4. Why is `dp` declared inside the function?

**Answer:**  
It is only needed while calculating the maximum sum, so it is kept local to the function.

### Q5. Why does the function return `maxSum`?

**Answer:**  
After calculating all `dp` values, `maxSum` contains the maximum sum over all possible ending positions.

---

## 21. How to Compile and Run

### GCC

Save the program as:

```text
msis.c
```

Compile:

```bash
gcc msis.c -o msis
```

Run:

```bash
./msis
```

On Windows using MinGW:

```bash
gcc msis.c -o msis.exe
msis.exe
```

---

## 22. Teacher-Explanation Version

If the teacher asks, **"Explain your algorithm and code"**, you can say:

> "This problem asks us to find the maximum sum of a strictly increasing subsequence. I have used Dynamic Programming because we can store the best sum ending at every element and reuse those results.
>
> I create a `dp` array where `dp[i]` represents the maximum sum of an increasing subsequence ending at `a[i]`. Initially, every `dp[i]` is just `a[i]`, because a single element is also a subsequence.
>
> Then for every element, I check all previous elements. If `a[j]` is smaller than `a[i]`, I can extend the subsequence ending at `j`. So I compare the current `dp[i]` with `dp[j] + a[i]` and update it if the new sum is larger.
>
> After all elements are processed, I find the largest value in the `dp` array. That value is the maximum sum.
>
> The nested loops take Theta(n²) time because the total comparisons are `n(n-1)/2`. The extra space is O(n) because of the `dp` array."

---

## 23. Conclusion

The Maximum Sum Increasing Subsequence problem can be solved efficiently using Dynamic Programming.

The important idea is to store the best sum ending at every element and use these stored values to build solutions for later elements.

The final algorithm has:

- **Time Complexity:** Theta(n²)
- **Auxiliary Space Complexity:** O(n)

It is simple to implement, easy to understand, and suitable for a DAA laboratory program.

---

## 24. Files

- `README.md` - Complete explanation, C program, dry run, complexity analysis, and viva questions.
- `msis_complexity_graph.png` - Complexity graph showing the O(n²) growth.
