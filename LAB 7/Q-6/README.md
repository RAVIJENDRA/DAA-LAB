# The Best Time to Be Alive - DAA Lab

## Problem

Given an index containing prominent scientists and their birth and death years, find the year when the largest number of prominent scientists were alive.

If one scientist dies in the same year another scientist is born, the death is considered to happen first.

## Approach Used

The program uses the **Event Sorting / Sweep Line** approach.

For every scientist:

- Birth year is treated as `+1`.
- Death year is treated as `-1`.

All events are sorted by year. If two events have the same year, the death event is processed before the birth event.

Then we scan the events from left to right:

1. Update the number of scientists currently alive.
2. If the count becomes greater than the previous maximum, store the count and year.
3. Continue until all events are processed.

This directly handles the condition that death happens before birth in the same year.

## Why This Approach?

The input index is alphabetically sorted by name, not by year. Therefore, we first convert the data into birth/death events and sort those events chronologically.

This is simpler and more general than checking every possible year.

## Complexity

For `n` scientists, there are `2n` events.

- Creating events: `O(n)`
- Sorting events: `O(n log n)`
- Scanning events: `O(n)`
- Total time: **O(n log n)**
- Extra space: **O(n)**

## C Program

Save the program as `best_time_to_be_alive.c` and compile it with:

```bash
gcc best_time_to_be_alive.c -o best_time_to_be_alive
```

Run:

```bash
./best_time_to_be_alive
```

## Sample Input

```text
10
Galileo 1564 1642
Kepler 1571 1630
Newton 1642 1727
Euler 1707 1783
Lavoisier 1743 1794
Laplace 1749 1827
Faraday 1791 1867
Darwin 1809 1882
Einstein 1879 1955
Bohr 1885 1962
```

## Sample Output

```text
Maximum number of scientists alive = 4
Best year = 1791
```

## Important Note

The names are not used for the algorithm itself. They are included because the original problem says the input comes from an alphabetically sorted index.

The graph file `best_time_to_be_alive_graph.png` shows how the number of living scientists changes over time.

## Viva Points

- This is a sweep-line/event-counting technique.
- Every birth increases the count by 1.
- Every death decreases the count by 1.
- Sorting events lets us process them chronologically.
- Death is sorted before birth for equal years.
- The maximum count found during the scan gives the answer.
