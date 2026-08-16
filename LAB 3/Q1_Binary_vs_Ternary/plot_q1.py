import csv
import matplotlib.pyplot as plt

ns, b, t, tb, tt = [], [], [], [], []
with open("results/q1_comparisons.csv") as f:
    for r in csv.DictReader(f):
        ns.append(int(r["n"])); b.append(float(r["binary_probes"])); t.append(float(r["ternary_probes"]))
        tb.append(float(r["theory_binary"])); tt.append(float(r["theory_ternary"]))

fig, ax = plt.subplots(figsize=(9,6))
ax.plot(ns, b, 'o-', color='tab:blue', label="Binary search (measured)")
ax.plot(ns, t, 's-', color='tab:red', label="Ternary search (measured)")
ax.plot(ns, tb, '--', color='tab:blue', alpha=0.5, label="Binary theory: ⌊log₂ n⌋+1")
ax.plot(ns, tt, '--', color='tab:red', alpha=0.5, label="Ternary theory: 2⌈log₃ n⌉")
ax.set_xscale('log', base=2)
ax.set_xlabel("n (log scale)")
ax.set_ylabel("worst-case probes (array elements compared to x)")
ax.set_title("Q1: Binary Search vs Ternary Search — worst-case comparisons\n"
             "Binary search needs fewer comparisons despite shrinking the search space more slowly")
ax.legend()
ax.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig("q1_binary_vs_ternary.png", dpi=150)
print("Saved q1_binary_vs_ternary.png")
