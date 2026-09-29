# Security Switches - DAA Lab Assignment

## Problem Statement

There are `n` security switches arranged in a row. Initially, all switches are ON.

Rules:
1. The rightmost switch can be toggled at any time.
2. Any other switch can be toggled only if the switch immediately to its right is ON and all switches further to its right are OFF.
3. Only one switch can be toggled at a time.

The goal is to turn all switches OFF using the minimum number of moves.

## Approach

A recursive approach is used.

Let `T(n)` be the minimum number of moves for `n` switches.

The recurrence is:

```text
T(n) = 2*T(n-1) + (n % 2)
T(1) = 1
```

The exact number of moves is:

```text
T(n) = floor(2^(n+1) / 3)
```

For example, for `n = 3`, the minimum sequence is:

```text
3 1 3 2 3
```

which requires 5 moves.

## Functions Used

- `generateMoves()` - recursively generates the minimum sequence of switch numbers.
- `isLegalMove()` - checks whether a move follows the given rules.
- `toggleSwitch()` - changes a switch from ON to OFF or OFF to ON.
- `printSwitches()` - displays the current switch states.
- `allOff()` - verifies that all switches are OFF at the end.

## Sample Input

```text
3
```

## Sample Output

```text
Enter number of switches: 3

Initial state:
ON ON ON

Sequence of moves:
Move 1: Toggle switch 3 -> ON ON OFF
Move 2: Toggle switch 1 -> OFF ON OFF
Move 3: Toggle switch 3 -> OFF ON ON
Move 4: Toggle switch 2 -> OFF OFF ON
Move 5: Toggle switch 3 -> OFF OFF OFF

Total moves = 5
All switches are OFF.
Algorithm successfully validated.
```

## Complexity Analysis

The number of moves follows:

```text
T(n) = 2*T(n-1) + (n % 2)
```

Therefore, the number of moves is:

```text
O(2^n)
```

The program stores the complete move sequence, so space complexity is:

```text
O(2^n)
```

Since `isLegalMove()` may check up to `n` switches for each move, the complete program including validation has worst-case time complexity:

```text
O(n * 2^n)
```

## Important Values

| n | Minimum Moves |
|---:|---:|
| 1 | 1 |
| 2 | 2 |
| 3 | 5 |
| 4 | 10 |
| 5 | 21 |
| 6 | 42 |
| 7 | 85 |
| 8 | 170 |

## Compile and Run

Save the C program as:

```text
security_switches.c
```

Compile using GCC:

```bash
gcc security_switches.c -o security_switches
```

Run on Linux/macOS:

```bash
./security_switches
```

Run on Windows:

```text
security_switches.exe
```

## Recommended Project Structure

```text
Security-Switches/
├── security_switches.c
└── README.md
```

## Viva Points

- The algorithm uses recursion.
- The solution for `n` switches is constructed using the solution for `n-1` switches.
- The recurrence is `T(n) = 2*T(n-1) + (n % 2)`.
- The number of moves grows exponentially.
- For `n = 3`, the minimum number of moves is 5.
- In the C program, `1` represents ON and `0` represents OFF.
- `move - 1` is used because C arrays start from index 0.
- The move array is processed backwards while expanding it to avoid overwriting values.
- `isLegalMove()` validates each generated move.
- `allOff()` verifies the final state.

## Conclusion

The recursive algorithm generates a valid minimum sequence of switch toggles and turns all switches OFF.

The important formula is:

```text
Minimum moves = floor(2^(n+1) / 3)
```

The algorithm is optimal in the sense that it uses the minimum possible number of moves, although the number of required moves is exponential in `n`.
