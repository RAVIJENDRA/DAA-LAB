# Collatz Conjecture - DAA Lab Assignment

## 1. Problem Title

**Collatz Conjecture (3n + 1 Problem)**

## 2. Problem Statement

The Collatz Conjecture defines the following rule for every positive integer `n`:

- If `n` is even, replace it with `n / 2`.
- If `n` is odd, replace it with `3n + 1`.

The process is repeated until `n` becomes `1`.

The conjecture says that every positive integer eventually reaches `1`, but this has **not been mathematically proved**.

The program should:

1. Accept a starting value `n >= 1`.
2. Display the Collatz trajectory for that value.
3. Count how many steps are required to reach `1`.
4. Find the maximum value reached during the trajectory.
5. Analyze all starting values in an interval `[a, b]`.
6. Display the number of steps for every value in the interval.
7. Find the starting value in the interval that takes the maximum number of steps.

---

## 3. Objective

The objective is to implement the Collatz process using a simple modular C program and study the number of operations performed for one starting value and for all values in an interval.

This problem is also useful for understanding why complexity analysis can sometimes be difficult when the mathematical behavior of an algorithm is not completely known.

---

## 4. Approaches That Could Be Used

Possible approaches include:

1. **Simple iterative simulation**  
   Start with `n` and repeatedly apply the Collatz rule until `n == 1`.

2. **Recursive simulation**  
   The function can call itself for the next value.

3. **Memoization**  
   Previously calculated stopping times can be stored and reused.

### Approach chosen

The program uses the **simple iterative simulation**.

This is the simplest approach for a DAA lab because:

- It directly follows the definition of the Collatz sequence.
- It is easy to understand and explain in a viva.
- It does not require complicated data structures.
- It uses functions to keep the program modular.

---

## 5. Basic Idea

For a starting value `n`:

```text
while n is not 1:
    if n is even:
        n = n / 2
    else:
        n = 3 * n + 1
    increase step count
```

For an interval `[a, b]`, repeat the same process for every starting value from `a` to `b`.

---

## 6. Step-by-Step Algorithm

### Algorithm for one starting value

1. Read `n`.
2. Set `steps = 0`.
3. Set `maxValue = n`.
4. While `n != 1`:
   - If `n` is even, calculate `n = n / 2`.
   - Otherwise calculate `n = 3 * n + 1`.
   - Increase `steps` by 1.
   - Update `maxValue` if the new value is larger.
5. Print the trajectory.
6. Print the number of steps.
7. Print the maximum value reached.

### Algorithm for interval `[a, b]`

1. Read `a` and `b`.
2. Check that `1 <= a <= b`.
3. For every `i` from `a` to `b`:
   - Start the Collatz process from `i`.
   - Count its steps.
   - Display the number of steps.
   - Add the steps to `totalSteps`.
   - Keep track of the starting value having the largest number of steps.
4. Display the interval summary.

---

## 7. C Program

```c
#include <stdio.h>

typedef unsigned long long ull;

/*
    Returns the next value in the Collatz sequence.
    If n is even: n / 2
    If n is odd : 3 * n + 1
*/
ull nextCollatz(ull n)
{
    if (n % 2 == 0)
        return n / 2;
    else
        return 3 * n + 1;
}

/*
    Prints the trajectory of one starting value.
    Returns the number of steps required to reach 1.
*/
ull analyzeStartingValue(ull n)
{
    ull original = n;
    ull steps = 0;
    ull maxValue = n;

    printf("\nTrajectory for n = %llu:\n", original);
    printf("%llu", n);

    while (n != 1)
    {
        n = nextCollatz(n);
        steps++;

        if (n > maxValue)
            maxValue = n;

        printf(" -> %llu", n);
    }

    printf("\nSteps to reach 1 = %llu\n", steps);
    printf("Maximum value reached = %llu\n", maxValue);

    return steps;
}

/*
    Analyzes every starting value in the interval [a, b].
*/
void analyzeInterval(ull a, ull b)
{
    ull i;
    ull steps;
    ull totalSteps = 0;
    ull maxSteps = 0;
    ull maxStart = a;

    printf("\nCollatz analysis for interval [%llu, %llu]\n", a, b);
    printf("\nStarting Value\tSteps to Reach 1\n");
    printf("--------------------------------\n");

    for (i = a; i <= b; i++)
    {
        steps = analyzeStartingValue(i);

        printf("%llu\t\t%llu\n", i, steps);

        totalSteps += steps;

        if (steps > maxSteps)
        {
            maxSteps = steps;
            maxStart = i;
        }

        /*
            Prevent overflow of i when b is the largest
            possible unsigned long long value.
        */
        if (i == b)
            break;
    }

    printf("\nInterval Summary\n");
    printf("----------------\n");
    printf("Total steps over interval = %llu\n", totalSteps);
    printf("Maximum steps = %llu\n", maxSteps);
    printf("Starting value with maximum steps = %llu\n", maxStart);
}

int main()
{
    ull n, a, b;

    printf("Enter starting value n (n >= 1): ");
    scanf("%llu", &n);

    if (n < 1)
    {
        printf("Invalid starting value. n must be at least 1.\n");
        return 0;
    }

    printf("\nEnter interval [a, b]: ");
    scanf("%llu %llu", &a, &b);

    if (a < 1 || b < a)
    {
        printf("Invalid interval. It must satisfy 1 <= a <= b.\n");
        return 0;
    }

    analyzeStartingValue(n);
    analyzeInterval(a, b);

    return 0;
}
```

---

## 8. Explanation of the Program

### `#include <stdio.h>`

This includes the standard input/output library so that we can use:

- `printf()`
- `scanf()`

### `typedef unsigned long long ull;`

`ull` is a short name for `unsigned long long`.

Collatz sequences can become larger than the original input, especially after the `3n + 1` operation. Using a larger unsigned integer type gives the program more range than a normal `int`.

It is still important to remember that integer overflow can occur for sufficiently large values.

---

### Function 1: `nextCollatz()`

```c
ull nextCollatz(ull n)
{
    if (n % 2 == 0)
        return n / 2;
    else
        return 3 * n + 1;
}
```

**Purpose:** Calculates exactly one next value in the Collatz sequence.

**Parameter:** `n` - current value.

**Return value:** The next Collatz value.

The condition:

```c
n % 2 == 0
```

checks whether `n` is even.

- Remainder `0` means even.
- Otherwise it is odd.

---

### Function 2: `analyzeStartingValue()`

This function performs the complete trajectory for one starting value.

Important variables:

| Variable | Meaning |
|---|---|
| `original` | Stores the original starting value |
| `n` | Stores the current Collatz value |
| `steps` | Counts how many transformations have been performed |
| `maxValue` | Stores the largest value reached |

The loop:

```c
while (n != 1)
```

continues until the sequence reaches `1`.

Every iteration:

1. Finds the next Collatz value.
2. Increases `steps`.
3. Checks whether the new value is the largest value seen.
4. Prints the new value.

The function returns `steps`.

---

### Function 3: `analyzeInterval()`

This function handles all starting values from `a` to `b`.

The loop:

```c
for (i = a; i <= b; i++)
```

selects each starting value.

For each value, `analyzeStartingValue(i)` is called.

Important variables:

| Variable | Meaning |
|---|---|
| `i` | Current starting value in the interval |
| `steps` | Steps for the current starting value |
| `totalSteps` | Sum of steps for all values |
| `maxSteps` | Largest number of steps found |
| `maxStart` | Starting value that produced `maxSteps` |

---

### Function 4: `main()`

`main()` is where program execution starts.

It:

1. Reads `n`.
2. Checks that `n >= 1`.
3. Reads `a` and `b`.
4. Checks that `1 <= a <= b`.
5. Calls `analyzeStartingValue(n)`.
6. Calls `analyzeInterval(a, b)`.

---

## 9. Sample Input

```text
Enter starting value n (n >= 1): 13

Enter interval [a, b]: 1 5
```

## 10. Sample Output

A shortened form of the output is:

```text
Trajectory for n = 13:
13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
Steps to reach 1 = 9
Maximum value reached = 40

Collatz analysis for interval [1, 5]

Starting Value    Steps to Reach 1
--------------------------------
1                 0
2                 1
3                 7
4                 2
5                 5

Interval Summary
----------------
Total steps over interval = 15
Maximum steps = 7
Starting value with maximum steps = 3
```

The actual program also prints the complete trajectory for every value in the interval.

---

## 11. Complete Dry Run

Take:

```text
n = 13
```

Initial values:

```text
n = 13
steps = 0
maxValue = 13
```

| Step | Current `n` | Even/Odd | Next value | `steps` | `maxValue` |
|---:|---:|---|---:|---:|---:|
| 0 | 13 | Odd | 40 | 1 | 40 |
| 1 | 40 | Even | 20 | 2 | 40 |
| 2 | 20 | Even | 10 | 3 | 40 |
| 3 | 10 | Even | 5 | 4 | 40 |
| 4 | 5 | Odd | 16 | 5 | 40 |
| 5 | 16 | Even | 8 | 6 | 40 |
| 6 | 8 | Even | 4 | 7 | 40 |
| 7 | 4 | Even | 2 | 8 | 40 |
| 8 | 2 | Even | 1 | 9 | 40 |

Now:

```text
n = 1
```

Therefore the loop stops.

Final result:

```text
Steps = 9
Maximum value = 40
```

Trajectory:

```text
13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
```

---

## 12. Interval Dry Run

For:

```text
[a, b] = [1, 5]
```

the program analyzes:

```text
1, 2, 3, 4, 5
```

| Starting value | Trajectory length (steps) |
|---:|---:|
| 1 | 0 |
| 2 | 1 |
| 3 | 7 |
| 4 | 2 |
| 5 | 5 |

Total:

```text
0 + 1 + 7 + 2 + 5 = 15
```

Maximum:

```text
7 steps
```

So the starting value with the maximum number of steps in this interval is:

```text
3
```

---

# 13. Complexity Analysis

The Collatz Conjecture creates an important complexity-analysis issue.

For one starting value `n`, let:

```text
T(n) = number of steps required for n to reach 1
```

The running time of the simulation is:

```text
O(T(n))
```

because the program performs approximately one constant-time operation for each Collatz step.

However, there is currently **no proven general upper bound for `T(n)` for every positive integer n**, because the Collatz Conjecture itself remains unproved.

Therefore, it would be incorrect to simply claim that the complete algorithm is always `O(n)` or `O(log n)`.

### One starting value

```text
Time = O(T(n))
```

where `T(n)` is the actual stopping time for that input.

### Interval `[a,b]`

The program performs the trajectory for every starting value.

Therefore:

```text
Time = O( T(a) + T(a+1) + ... + T(b) )
```

If:

```text
m = b - a + 1
```

and:

```text
S = maximum stopping time among a, a+1, ..., b
```

then a simple upper description is:

```text
Time = O(mS)
```

where `m` is the number of starting values and `S` is the largest observed stopping time in that interval.

### Best case

For one starting value, `n = 1` gives:

```text
T(1) = 0
```

so the simulation takes constant time:

```text
O(1)
```

For an interval, if every starting value is extremely close to 1 and has small stopping time, the work is small. A formal asymptotic best-case bound depends on how the interval is defined.

### Average case

There is no single simple proven asymptotic average-case complexity for arbitrary positive integers that can be stated independently of the input distribution.

For a particular finite interval, the program simply measures the stopping time of every value.

### Worst case

For a particular finite interval:

```text
O(mS)
```

where:

- `m = b - a + 1`
- `S` = maximum stopping time in the interval.

A universal closed-form worst-case bound for all positive integers is not known from the unresolved Collatz problem.

### Space complexity

The program uses a fixed number of variables and does not store the complete trajectory in an array.

Therefore, auxiliary space is:

```text
O(1)
```

The program prints the sequence directly rather than storing it.

---

## 14. Complexity Graph

The included PNG graph shows standard reference growth curves:

- `O(n)`
- `O(n log n)`
- `O(n²)`

These curves are included to help compare common complexity growth rates.

**Important:** They are **reference mathematical curves**, not measured Collatz execution times.

Because the stopping-time growth of the Collatz process does not have a known simple proven asymptotic bound, presenting one of these curves as the actual Collatz worst-case complexity would be misleading.

File:

```text
collatz_complexity_graph.png
```

---

## 15. Advantages

1. Very simple to understand.
2. Directly implements the definition of the Collatz sequence.
3. Uses modular functions.
4. Does not require complicated data structures.
5. Can analyze both one starting value and an interval.
6. Easy to demonstrate in a DAA lab viva.

---

## 16. Disadvantages / Limitations

1. The number of Collatz steps can become large.
2. The program repeatedly recalculates trajectories for different starting values.
3. No general proven stopping-time bound is known.
4. The Collatz Conjecture itself is still an open mathematical problem.
5. `unsigned long long` has a finite range, so sufficiently large intermediate values can overflow.
6. Printing a very long trajectory can itself take a lot of time and output space.

---

## 17. Viva Preparation

### Q1. What is the Collatz Conjecture?

**Answer:**  
It states that starting from any positive integer, repeatedly applying `n/2` for even numbers and `3n+1` for odd numbers eventually reaches `1`. It is still unproved.

### Q2. What is the main idea of your program?

**Answer:**  
The program repeatedly applies the Collatz rule until the current value becomes `1` and counts the number of steps.

### Q3. Why did you use an iterative approach?

**Answer:**  
It is simple, directly follows the problem statement, and is easy to understand and explain.

### Q4. What is the time complexity for one starting value?

**Answer:**  
It is `O(T(n))`, where `T(n)` is the number of Collatz steps required for that starting value to reach `1`.

### Q5. Is there a known simple worst-case complexity for all positive integers?

**Answer:**  
No. A universal stopping-time bound is not known in the form needed here because the Collatz Conjecture remains unresolved.

### Q6. What is the time complexity for an interval `[a,b]`?

**Answer:**  
It is proportional to the sum of the stopping times:

`O(T(a) + T(a+1) + ... + T(b))`.

If `m` values are present and `S` is the maximum stopping time, it can be described as `O(mS)`.

### Q7. What is the space complexity?

**Answer:**  
`O(1)` auxiliary space because only a fixed number of variables are used.

### Q8. Why is `n % 2 == 0` used?

**Answer:**  
The remainder after dividing an even number by 2 is zero, so this condition checks whether `n` is even.

### Q9. Why is `nextCollatz()` a separate function?

**Answer:**  
It keeps the main algorithm simple and makes the Collatz rule easy to understand and reuse.

### Q10. What does `steps` store?

**Answer:**  
It stores the number of transformations performed before reaching `1`.

### Q11. Why do we need `maxValue`?

**Answer:**  
It records the largest value reached during the trajectory.

### Q12. Why use `unsigned long long`?

**Answer:**  
The Collatz sequence can temporarily become much larger than the starting value, so a larger integer type gives more range than a normal `int`.

### Q13. What happens when `n = 1`?

**Answer:**  
The loop does not execute because the condition `n != 1` is false. Therefore, the number of steps is `0`.

### Q14. Why is the interval loop needed?

**Answer:**  
The problem asks us to analyze the trajectory across an interval, so every starting value from `a` through `b` must be considered.

### Q15. What is the main limitation of this implementation?

**Answer:**  
It may perform many operations and can overflow the integer type for sufficiently large intermediate values. Also, the general stopping behavior of the Collatz process is mathematically unresolved.

---

## 18. C-Code-Specific Viva Questions

### Q16. Why do we use `while (n != 1)`?

**Answer:**  
Because the Collatz sequence should continue until the current value becomes `1`.

### Q17. Why is `steps++` placed after calculating the next value?

**Answer:**  
Each transformation from the current value to the next value represents one Collatz step.

### Q18. Why is `if (n > maxValue)` used?

**Answer:**  
It checks whether the newly calculated value is larger than every value seen previously.

### Q19. Why does `analyzeStartingValue()` return `steps`?

**Answer:**  
The interval function needs the number of steps for each starting value, so the function returns it.

### Q20. Why is `if (i == b) break;` present?

**Answer:**  
It prevents the loop variable from wrapping around when `b` is the largest possible `unsigned long long` value.

---

## 19. How to Compile and Run

### GCC

Save the program as:

```text
collatz.c
```

Compile:

```bash
gcc collatz.c -o collatz
```

Run:

```bash
./collatz
```

On Windows:

```bash
gcc collatz.c -o collatz.exe
collatz.exe
```

---

## 20. Important Viva Point About the Open Problem

Do not say:

> "The Collatz algorithm has a proven O(n) complexity."

That would be incorrect.

A better answer is:

> "For one starting value, the running time is proportional to its Collatz stopping time, so I write it as O(T(n)). For an interval, the total work is the sum of the stopping times. A simple universal worst-case bound is not known because the Collatz Conjecture itself is still an open problem."

---

## 21. Conclusion

The program simulates the Collatz sequence using a simple iterative method. It analyzes one starting value as well as all values in a user-provided interval. The program counts steps, finds the maximum value reached, and summarizes the interval.

The important DAA lesson is that complexity is not always expressible using a simple function such as `O(n)` or `O(n²)`. In this problem, the running time depends on the stopping behavior of the Collatz sequence, which is itself connected to an unresolved mathematical conjecture.

