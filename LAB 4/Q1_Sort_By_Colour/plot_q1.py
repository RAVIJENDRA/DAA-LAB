import csv
import matplotlib.pyplot as plt
import numpy as np

ns, on, qs = [], [], []
with open("results/q1_timings.csv") as f:
    for r in csv.DictReader(f):
        ns.append(int(r["n"])); on.append(float(r["on_algorithm_ns"])); qs.append(float(r["qsort_baseline_ns"]))

fig, ax = plt.subplots(1,2, figsize=(14,6))
ax[0].plot(ns, on, 'o-', label="Our algorithm: O(n)", color='tab:blue')
ax[0].plot(ns, qs, 's-', label="qsort baseline: O(n log n)", color='tab:red')
ax[0].set_xlabel("n"); ax[0].set_ylabel("time (ns)")
ax[0].set_title("Running time vs n"); ax[0].legend(); ax[0].grid(True, alpha=0.3)

log_n = np.log(ns)
slope_on = np.polyfit(log_n, np.log(on), 1)[0]
slope_qs = np.polyfit(log_n, np.log(qs), 1)[0]
ax[1].loglog(ns, on, 'o-', label=f"O(n) algorithm (slope≈{slope_on:.2f}, theory 1.0)", color='tab:blue')
ax[1].loglog(ns, qs, 's-', label=f"qsort baseline (slope≈{slope_qs:.2f}, theory ~1.0-1.1 incl. log factor)", color='tab:red')
ax[1].set_xlabel("n (log scale)"); ax[1].set_ylabel("time (log scale)")
ax[1].set_title("log-log plot"); ax[1].legend(); ax[1].grid(True, alpha=0.3, which='both')

fig.suptitle("Q1: Sort-by-Colour — O(n) bucket algorithm vs O(n log n) baseline", fontsize=13, fontweight='bold')
plt.tight_layout(rect=[0,0,1,0.94])
plt.savefig("q1_order_of_growth.png", dpi=150)
print("Saved q1_order_of_growth.png")
