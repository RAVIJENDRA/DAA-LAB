# Super Egg Testing Experiment

## Aim

To find the minimum number of egg drops required to determine the highest safe floor in a building using Dynamic Programming.

The solution is generalized for `E` eggs and `F` floors.

---

## Problem Statement

A company has `E` identical eggs and a building with `F` floors.

We need to determine the highest floor from which an egg can be dropped without breaking.

The same egg can be used multiple times as long as it does not break.

The objective is to find the minimum number of drops that are guaranteed to determine the highest safe floor in the worst case.

For the given problem:

- Number of eggs = 2
- Number of floors = 100
- Minimum guaranteed drops = 14

---

## Algorithm Used

### Dynamic Programming

We define:

`dp[e][f]`

as the minimum number of drops required in the worst case when we have `e` eggs and `f` floors.

For every possible floor `x`, we consider two cases.

### Case 1: Egg Breaks

If the egg breaks when dropped from floor `x`:

- One egg is lost.
- We need to check the floors below `x`.

Therefore:

`dp[e-1][x-1]`

### Case 2: Egg Does Not Break

If the egg does not break:

- The current floor is safe.
- We continue checking the floors above `x`.
- The number of eggs remains the same.

Therefore:

`dp[e][f-x]`

Since we need a guaranteed answer, we consider the worse of these two cases:

`max(dp[e-1][x-1], dp[e][f-x])`

We add one for the current drop and choose the minimum among all possible floors:

`dp[e][f] = 1 + min(max(dp[e-1][x-1], dp[e][f-x]))`

---

## Base Cases

1. If there are 0 floors:

`dp[e][0] = 0`

2. If there is 1 floor:

`dp[e][1] = 1`

3. If there is only 1 egg:

`dp[1][f] = f`

With one egg, floors must be checked one by one because if the egg breaks, no egg remains.

---

## Program

The program is written in C.

### File

`egg_drop.c`

### Compilation

Using GCC:

```bash
gcc egg_drop.c -o egg_drop
```

### Run

Linux/macOS:

```bash
./egg_drop
```

Windows:

```bash
egg_drop.exe
```

---

## Sample Input

```text
Enter number of eggs: 2
Enter number of floors: 100
```

## Sample Output

```text
Minimum number of drops required = 14
```

---

## Example

For:

```text
Eggs = 2
Floors = 6
```

the minimum number of drops required is:

```text
3
```

For the original problem:

```text
Eggs = 2
Floors = 100
```

the result is:

```text
14
```

---

## Time Complexity

The program uses three nested loops:

- One loop for the number of eggs: `E`
- One loop for the number of floors: `F`
- One loop for trying every possible dropping floor: `F`

Therefore:

`O(E × F²)`

---

## Space Complexity

A two-dimensional DP table is used:

`dp[E+1][F+1]`

Therefore:

`O(E × F)`

---

## Advantages

- Avoids repeated calculations.
- Simple and suitable for understanding Dynamic Programming.
- Gives the guaranteed minimum number of drops.
- Works for a generalized number of eggs and floors.

---

## Disadvantages

- Time complexity is `O(E × F²)`.
- Memory usage increases with the number of eggs and floors.
- More optimized approaches are possible for very large inputs.

---

## Important Variables

| Variable | Meaning |
|----------|---------|
| `eggs` | Number of eggs |
| `floors` | Number of floors |
| `dp[e][f]` | Minimum drops for `e` eggs and `f` floors |
| `e` | Current number of eggs |
| `f` | Current number of floors |
| `x` | Floor selected for dropping the egg |
| `breakCase` | Drops required if the egg breaks |
| `surviveCase` | Drops required if the egg survives |
| `drops` | Worst-case drops for the current floor |

---

## Key Recurrence

The most important formula is:

```text
dp[e][f] =
1 + min(
    max(
        dp[e-1][x-1],
        dp[e][f-x]
    )
)
```

where:

`1 <= x <= f`

---

## Conclusion

The Egg Dropping problem can be solved using Dynamic Programming.

The algorithm considers every possible floor for dropping the egg and stores previously calculated results in a DP table.

For **2 eggs and 100 floors**, the minimum guaranteed number of drops is:

**14**

---

## Author

DAA Lab Assignment  
Language: C  
Topic: Dynamic Programming  
Problem: Super Egg Testing Experiment
