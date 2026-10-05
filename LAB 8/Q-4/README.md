# Longest Increasing Subsequence (LIS)

## 1. Problem Title

**Longest Increasing Subsequence**

## 2. Problem Statement

Given an integer array `A = [a0, a1, ..., an-1]`, find the length of the longest subsequence such that all elements of the subsequence are **strictly increasing**.

A subsequence does not need to contain consecutive elements. The order of the selected elements must remain the same.

For example:

```text
Array: 10 22 9 33 21 50 41 60

One LIS: 10 22 33 50 60

Length = 5
```

## 3. Objective

The objective is to design and implement an algorithm that finds the length of the Longest Increasing Subsequence (LIS) and analyze its time and space complexity.

## 4. Possible Approaches

There are two common approaches:

1. **Dynamic Programming - O(n²)**  
   Easy to understand and suitable for a DAA lab because the subproblem and recurrence are clear.

2. **Binary Search / Patience Sorting - O(n log n)**  
   Faster, but the implementation and explanation are slightly more complicated.

For this lab, the **Dynamic Programming O(n²) approach** is selected because it is simple and easy to explain in a viva.

## 5. Basic Idea

Create an array `dp`.

`dp[i]` stores the length of the longest strictly increasing subsequence that **ends at index `i`**.

Initially:

```text
dp[i] = 1
```

because every single element by itself is an increasing subsequence of length 1.

For every pair of indices `j` and `i`, where `j < i`:

- If `A[j] < A[i]`, then `A[i]` can be added after the increasing subsequence ending at `j`.
- Therefore:

```text
dp[i] = max(dp[i], dp[j] + 1)
```

Finally, the answer is the maximum value in `dp`.

## 6. Why Dynamic Programming Is Suitable

The problem has overlapping subproblems.

The answer for position `i` depends on the best increasing subsequences ending at earlier positions `0, 1, ..., i-1`.

Instead of calculating the same smaller problems repeatedly, we store their answers in `dp`.

This makes the solution simple and systematic.

## 7. Step-by-Step Algorithm

1. Read the size `n`.
2. Read the array elements.
3. Create a `dp` array of size `n`.
4. Set every `dp[i]` to `1`.
5. For each index `i` from `1` to `n-1`:
   - Check every previous index `j` from `0` to `i-1`.
   - If `A[j] < A[i]`, calculate `dp[j] + 1`.
   - If this value is greater than `dp[i]`, update `dp[i]`.
6. Find the largest value in `dp`.
7. Print the largest value as the length of the LIS.

## 8. C Program

```c
#include <stdio.h>

int longestIncreasingSubsequence(int a[], int n)
{
    int dp[100];
    int i, j;
    int maxLength = 1;

    /* Every element alone forms a subsequence of length 1 */
    for (i = 0; i < n; i++)
    {
        dp[i] = 1;
    }

    /* Find the best increasing subsequence ending at each index */
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (a[j] < a[i] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
            }
        }

        if (dp[i] > maxLength)
        {
            maxLength = dp[i];
        }
    }

    return maxLength;
}

int main()
{
    int a[100];
    int n, i;
    int answer;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    answer = longestIncreasingSubsequence(a, n);

    printf("Length of Longest Increasing Subsequence = %d\n", answer);

    return 0;
}
```

## 9. Important Code Explanation

### `#include <stdio.h>`

This includes the standard input/output library so that `printf()` and `scanf()` can be used.

### Function: `longestIncreasingSubsequence()`

```c
int longestIncreasingSubsequence(int a[], int n)
```

This function receives:

- `a[]` - the input array.
- `n` - number of elements.

It returns:

- The length of the longest strictly increasing subsequence.

### `dp[]`

```c
int dp[100];
```

`dp[i]` stores the length of the longest increasing subsequence ending at index `i`.

For example:

```text
a  = 10 22 9 33
dp =  1  2 1  3
```

The value `3` at index 3 means that the longest increasing subsequence ending at `33` has length 3.

### Initialization

```c
for (i = 0; i < n; i++)
{
    dp[i] = 1;
}
```

Every individual element is an increasing subsequence by itself, so every value starts at 1.

### Nested loops

```c
for (i = 1; i < n; i++)
{
    for (j = 0; j < i; j++)
```

For every element `a[i]`, we check all previous elements `a[j]`.

We only check previous positions because a subsequence must preserve the original order.

### Increasing condition

```c
if (a[j] < a[i] && dp[i] < dp[j] + 1)
```

The first condition:

```text
a[j] < a[i]
```

ensures that the subsequence is **strictly increasing**.

The second condition checks whether adding `a[i]` gives a longer subsequence than the current best value.

### Updating `dp[i]`

```c
dp[i] = dp[j] + 1;
```

If `a[j]` can come before `a[i]`, we extend the best subsequence ending at `j`.

### `maxLength`

```c
int maxLength = 1;
```

This stores the largest LIS length found so far.

It is updated whenever a larger `dp[i]` is found.

### `return maxLength`

At the end of the function, the largest LIS length is returned to `main()`.

## 10. Variable Explanation

| Variable | Meaning |
|---|---|
| `a[]` | Stores the input array |
| `n` | Number of elements |
| `dp[]` | Stores LIS length ending at each index |
| `i` | Current element/index |
| `j` | Previous element/index being checked |
| `maxLength` | Largest LIS length found so far |
| `answer` | Stores the value returned by the LIS function |

## 11. Sample Input

```text
Enter the number of elements: 8
Enter the elements:
10 22 9 33 21 50 41 60
```

## 12. Sample Output

```text
Length of Longest Increasing Subsequence = 5
```

One possible LIS is:

```text
10 22 33 50 60
```

Therefore, the length is `5`.

## 13. Complete Dry Run

Consider:

```text
A = [10, 22, 9, 33, 21, 50]
```

Initially:

```text
dp = [1, 1, 1, 1, 1, 1]
```

### For `i = 1`, A[i] = 22

Check `10 < 22`.

```text
dp[1] = dp[0] + 1
      = 1 + 1
      = 2
```

Now:

```text
dp = [1, 2, 1, 1, 1, 1]
```

### For `i = 2`, A[i] = 9

Check:

```text
10 < 9  -> No
22 < 9  -> No
```

So:

```text
dp = [1, 2, 1, 1, 1, 1]
```

### For `i = 3`, A[i] = 33

Check previous elements:

| `j` | `A[j]` | Condition | New possible length |
|---:|---:|---|---:|
| 0 | 10 | 10 < 33 | 2 |
| 1 | 22 | 22 < 33 | 3 |
| 2 | 9 | 9 < 33 | 2 |

The maximum is 3.

```text
dp = [1, 2, 1, 3, 1, 1]
```

### For `i = 4`, A[i] = 21

Check:

```text
10 < 21 -> possible length 2
22 < 21 -> No
9 < 21  -> possible length 2
33 < 21 -> No
```

Therefore:

```text
dp[4] = 2
```

Now:

```text
dp = [1, 2, 1, 3, 2, 1]
```

### For `i = 5`, A[i] = 50

Check:

| `j` | `A[j]` | `dp[j]` | `A[j] < 50` | Possible `dp[j]+1` |
|---:|---:|---:|---|---:|
| 0 | 10 | 1 | Yes | 2 |
| 1 | 22 | 2 | Yes | 3 |
| 2 | 9 | 1 | Yes | 2 |
| 3 | 33 | 3 | Yes | 4 |
| 4 | 21 | 2 | Yes | 3 |

Maximum value is 4.

Final:

```text
dp = [1, 2, 1, 3, 2, 4]
```

Therefore:

```text
LIS length = 4
```

One LIS is:

```text
10 22 33 50
```

## 14. Complexity Analysis

### Time Complexity

The algorithm contains two nested loops.

The outer loop runs approximately `n` times.

For each `i`, the inner loop checks all previous elements:

```text
0 + 1 + 2 + ... + (n-1)
```

This sum is:

```text
n(n-1)/2
```

Therefore, the number of pair comparisons grows quadratically.

So:

```text
Time Complexity = O(n²)
```

More precisely, the standard DP implementation performs Θ(n²) pair checks because the loops run through the same index ranges regardless of the input values.

### Best Case

```text
Θ(n²)
```

Even if the array is decreasing and almost no updates occur, the program still checks all required pairs.

### Average Case

```text
Θ(n²)
```

The same nested loops are executed for a typical input.

### Worst Case

```text
Θ(n²)
```

The nested loops still perform approximately `n(n-1)/2` pair checks.

### Space Complexity

The program uses:

- Input array: `O(n)`
- DP array: `O(n)`

Therefore:

```text
Space Complexity = O(n)
```

The algorithm does not use recursion, so there is no additional recursion stack.

## 15. Complexity Graph

The generated graph is based on the mathematical pair-comparison count:

```text
n(n-1)/2
```

This represents the number of `(j, i)` pairs examined by the nested loops. It demonstrates the quadratic growth of the algorithm without using fabricated experimental execution times.

The graph covers input sizes from `n = 1` to `n = 50`.

File:

```text
LIS_complexity_graph.png
```

## 16. Advantages

1. Easy to understand.
2. Uses a clear Dynamic Programming concept.
3. Easy to implement in C.
4. Easy to explain in a DAA viva.
5. Works correctly with duplicate values because the condition uses `<`.
6. Does not require recursion.
7. The DP table clearly shows how the solution is built.

## 17. Disadvantages / Limitations

1. Time complexity is `O(n²)`.
2. Space complexity is `O(n)`.
3. For very large arrays, the `O(n²)` running time can become expensive.
4. This program uses fixed arrays of size 100, so inputs larger than 100 need a larger array or dynamic memory allocation.

## 18. Difference from a Brute-Force Approach

A brute-force method can generate many possible subsequences and check which one is increasing.

There can be up to `2^n` subsequences, so brute force becomes very expensive.

The Dynamic Programming method avoids checking every possible subsequence explicitly. It stores the best answer ending at each position.

Therefore, the DP approach reduces the time complexity to:

```text
O(n²)
```

## 19. How to Compile and Run

### Using GCC

Save the program as:

```text
lis.c
```

Compile:

```bash
gcc lis.c -o lis
```

Run on Linux/macOS:

```bash
./lis
```

On Windows:

```bash
lis.exe
```

## 20. Viva Preparation

### Q1. What is the main idea of this algorithm?

**Answer:**  
The main idea is Dynamic Programming. `dp[i]` stores the length of the longest increasing subsequence ending at index `i`.

### Q2. Why did you choose Dynamic Programming?

**Answer:**  
It is simple to implement and clearly demonstrates overlapping subproblems. It also gives an `O(n²)` solution, which is suitable for a DAA lab.

### Q3. What does `dp[i]` represent?

**Answer:**  
`dp[i]` represents the length of the longest strictly increasing subsequence that ends at `a[i]`.

### Q4. Why is every `dp[i]` initialized to 1?

**Answer:**  
Because every single element by itself forms an increasing subsequence of length 1.

### Q5. Why do we check `a[j] < a[i]`?

**Answer:**  
Because the problem asks for a strictly increasing subsequence. Therefore, the previous element must be smaller than the current element.

### Q6. What is the recurrence relation?

**Answer:**

```text
if a[j] < a[i]:

dp[i] = max(dp[i], dp[j] + 1)
```

### Q7. What is the time complexity?

**Answer:**  
The time complexity is `Θ(n²)` because two nested loops check all previous element pairs.

### Q8. What is the space complexity?

**Answer:**  
The space complexity is `O(n)` because we use the input array and a DP array of size `n`.

### Q9. What happens if the array is in decreasing order?

**Answer:**  
The LIS length will be 1. However, the algorithm still checks the pairs, so its time complexity remains `Θ(n²)`.

### Q10. What happens if the array is already increasing?

**Answer:**  
The LIS length will be `n`. The algorithm still performs the nested-loop comparisons, so the time complexity remains `Θ(n²)`.

### Q11. What is the difference between a subsequence and a subarray?

**Answer:**  
A subarray normally contains consecutive elements, while a subsequence can skip elements but must preserve their original order.

### Q12. What is the difference between this and brute force?

**Answer:**  
Brute force can examine exponentially many subsequences. The DP solution stores intermediate results and reduces the time complexity to `O(n²)`.

### Q13. Why is `maxLength` needed?

**Answer:**  
`dp[i]` gives the LIS length ending at a particular index. `maxLength` stores the largest value among all `dp[i]` values.

### Q14. Why is the inner loop written as `j < i`?

**Answer:**  
Only elements before `i` can be previous elements in a subsequence. This also preserves the original order.

### Q15. What is the role of the function `longestIncreasingSubsequence()`?

**Answer:**  
It performs the complete DP calculation and returns the length of the LIS to the `main()` function.

## 21. C-Code Specific Viva Questions

### Q1. Why are `i` and `j` used?

**Answer:**  
`i` represents the current element, while `j` is used to check all previous elements before `i`.

### Q2. Why is the condition written as:

```c
a[j] < a[i] && dp[i] < dp[j] + 1
```

**Answer:**  
The first part checks whether the elements are strictly increasing. The second part checks whether extending the subsequence gives a better answer.

### Q3. Why does the function return `int`?

**Answer:**  
The length of the LIS is an integer, so the function returns an `int`.

### Q4. Why is `dp` an array?

**Answer:**  
We need to store a separate best LIS length for every array position.

### Q5. Why is `scanf()` used?

**Answer:**  
`scanf()` is used to take the array size and array elements from the user.

## 22. Teacher-Explanation Version

If the teacher asks, **"Explain your algorithm and code,"** you can say:

> "This program finds the length of the Longest Increasing Subsequence using Dynamic Programming. A subsequence does not have to contain consecutive elements, but the selected elements must remain in the same order and must be strictly increasing.
>
> I use a `dp` array where `dp[i]` stores the length of the longest increasing subsequence ending at `a[i]`. Initially every `dp[i]` is 1 because a single element itself is a subsequence.
>
> Then I use two loops. For every current element `a[i]`, I check all previous elements `a[j]`. If `a[j]` is smaller than `a[i]`, I can extend the subsequence ending at `j`, so I update `dp[i]` using `dp[j] + 1`.
>
> Finally, I find the maximum value in the `dp` array, and that is the length of the LIS.
>
> The two nested loops perform about `n(n-1)/2` comparisons, so the time complexity is `Theta(n²)`. The DP array requires `O(n)` extra space."

## 23. Conclusion

The Dynamic Programming solution provides a simple and systematic way to find the length of the Longest Increasing Subsequence.

By storing the best increasing subsequence length ending at every position, repeated work is avoided.

The final complexities are:

```text
Time:  Θ(n²)
Space: O(n)
```

This implementation is suitable for a college DAA lab because the code, recurrence, dry run, and complexity analysis are straightforward to understand and explain.
