import csv
import matplotlib.pyplot as plt

ns, c, b = [], [], []
with open("results/q3_comparisons.csv") as f:
    for r in csv.DictReader(f):
        ns.append(int(r["n"])); c.append(int(r["comparisons"])); b.append(float(r["bound_3n_2"]))

fig, ax = plt.subplots(1,2, figsize=(14,6))
ax[0].plot(ns, c, 'o-', label="Measured comparisons", color='tab:blue')
ax[0].plot(ns, b, '--', label="Bound: 3n/2 - 2", color='tab:red')
ax[0].set_xscale('log', base=2); ax[0].set_xlabel("n (log scale)"); ax[0].set_ylabel("comparisons")
ax[0].set_title("Comparisons vs n"); ax[0].legend(); ax[0].grid(True, alpha=0.3)

ratio = [ci/ni for ci,ni in zip(c,ns)]
ax[1].plot(ns, ratio, 'o-', color='tab:green')
ax[1].axhline(1.5, color='tab:red', linestyle='--', label="1.5 (=3/2)")
ax[1].set_xscale('log', base=2); ax[1].set_xlabel("n (log scale)"); ax[1].set_ylabel("comparisons / n")
ax[1].set_title("comparisons/n converges to 3/2"); ax[1].legend(); ax[1].grid(True, alpha=0.3)

fig.suptitle("Q3: Divide & Conquer Max-Min — comparisons bounded by ⌈3n/2⌉-2", fontsize=13, fontweight='bold')
plt.tight_layout(rect=[0,0,1,0.94])
plt.savefig("q3_order_of_growth.png", dpi=150)
print("Saved q3_order_of_growth.png")
