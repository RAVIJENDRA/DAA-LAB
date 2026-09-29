# Hitting a Moving Target - DAA Lab

## Problem Statement

A computer game has a shooter and a moving target. There are `n > 1`
hiding spots arranged along a straight line. The shooter can shoot any
hiding spot but cannot see the target.

Between every two consecutive shots, the target must move to an
adjacent hiding spot.

The objective is to design a sequence of shots that guarantees hitting
the target.

---

## Main Idea

A guaranteed strategy exists for every `n > 1`.

The target changes parity after every move:

- odd position -> even position
- even position -> odd position

We use a sweep through the interior hiding spots.

### For n = 2

Shoot:

    1, 1

### For n >= 3 and n odd

Shoot:

    2, 3, 4, ..., n-1,
    2, 3, 4, ..., n-1

### For n >= 4 and n even

Shoot:

    2, 3, 4, ..., n-1,
    n-1, n-2, ..., 2

For `n >= 3`, the number of shots is:

    2n - 4

---

## C Program

The program has two main functions:

1. `createStrategy()`
   - Creates the sequence of shots.

2. `validateStrategy()`
   - Simulates all possible target positions.
   - Checks whether any possible target path survives all shots.

The program uses:

- `shots[]` to store the shooting sequence.
- `possible[]` to store positions where the target can currently be.
- `next[]` to store possible positions after the target moves.

---

## Algorithm

1. Read `n`.
2. Generate the shooting sequence according to whether `n` is even or odd.
3. Initially assume the target can be at any hiding spot.
4. For every shot:
   - Remove the shot position from the possible positions.
   - Move every remaining possible position to its adjacent positions.
5. If no possible position remains, the strategy guarantees a hit.
6. Print the shooting sequence and validation result.

---

## Example

For:

    n = 6

The shooting sequence is:

    2 3 4 5 5 4 3 2

The possible positions of the target eventually become empty, so the
target is guaranteed to be hit.

---

## Sample Input

    Enter number of hiding spots: 6

## Sample Output

    Shooting sequence:
    2 3 4 5 5 4 3 2

    Result: Guaranteed to hit the target.
    Number of shots = 8

---

## Complexity Analysis

### Strategy Generation

For `n >= 3`, we generate `2n - 4` shots.

Time complexity:

    O(n)

### Validation

For every shot, the program checks up to `n` positions.

There are `O(n)` shots, so:

    O(n) * O(n) = O(n^2)

Therefore, the worst-case time complexity of validation is:

    O(n^2)

Space complexity:

    O(n)

because the program stores the `shots`, `possible`, and `next` arrays.

---

## Files

- `hitting_moving_target.c` - C implementation
- `hitting_moving_target_graph.png` - diagram for the algorithm
- `README.md` - project documentation

---

## How to Compile and Run

Using GCC:

    gcc hitting_moving_target.c -o hitting_moving_target

Run:

    ./hitting_moving_target

On Windows:

    gcc hitting_moving_target.c -o hitting_moving_target.exe
    hitting_moving_target.exe

---

## Viva Points

- The target must move to an adjacent spot after every shot.
- Moving one position changes the parity of the position.
- The strategy is different for even and odd `n`.
- For `n >= 3`, the strategy uses `2n - 4` shots.
- The actual strategy needs `O(n)` shots.
- The validation program takes `O(n^2)` time.
- The validation uses a possible-position simulation rather than guessing
  one particular target path.
