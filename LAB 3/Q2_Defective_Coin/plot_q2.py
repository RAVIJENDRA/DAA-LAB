import csv
import matplotlib.pyplot as plt

ns, w, th = [], [], []
with open("results/q2_weighings.csv") as f:
    for r in csv.DictReader(f):
        ns.append(int(r["n"])); w.append(int(r["max_weighings"])); th.append(float(r["theory_log2n"]))

fig, ax = plt.subplots(figsize=(9,6))
ax.plot(ns, w, 'o-', color='tab:red', label="Measured worst-case weighings")
ax.plot(ns, th, '--', color='tab:blue', label="log₂(n)")
ax.plot(ns, [t+2 for t in th], ':', color='tab:blue', alpha=0.6, label="log₂(n) + 2  (upper bound envelope)")
ax.set_xscale('log', base=2)
ax.set_xlabel("n (number of coins, log scale)")
ax.set_ylabel("number of weighings (worst case)")
ax.set_title("Q2: Defective Coin — weighings vs n\nMeasured curve tracks log₂(n)+c for a small constant c")
ax.legend()
ax.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig("q2_weighings.png", dpi=150)
print("Saved q2_weighings.png")
