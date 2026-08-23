import csv
import matplotlib.pyplot as plt

ns, t = [], []
with open("results/q5_timings.csv") as f:
    for r in csv.DictReader(f):
        ns.append(int(r["n"])); t.append(float(r["time_ns"]))

fig, ax = plt.subplots(1,2, figsize=(14,6))
ax[0].plot(ns, t, 'o-', color='tab:blue')
ax[0].set_xlabel("n"); ax[0].set_ylabel("time (ns)")
ax[0].set_title("Running time vs n"); ax[0].grid(True, alpha=0.3)

ax[1].plot(ns, [ti/n for ti,n in zip(t,ns)], 'o-', color='tab:green')
ax[1].set_xscale('log')
ax[1].set_xlabel("n (log scale)"); ax[1].set_ylabel("time / n")
ax[1].set_title("T(n)/n vs log(n) — rising straight line confirms Θ(n log n)")
ax[1].grid(True, alpha=0.3)

fig.suptitle("Q5: Merge Overlapping Intervals — Θ(n log n)", fontsize=13, fontweight='bold')
plt.tight_layout(rect=[0,0,1,0.93])
plt.savefig("q5_order_of_growth.png", dpi=150)
print("Saved q5_order_of_growth.png")
