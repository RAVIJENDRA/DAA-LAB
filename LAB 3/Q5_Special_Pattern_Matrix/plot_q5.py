import csv
import matplotlib.pyplot as plt
import numpy as np

ns, nv, sp = [], [], []
with open("results/q5_timings.csv") as f:
    for r in csv.DictReader(f):
        ns.append(int(r["n"])); nv.append(float(r["naive_ns"])); sp.append(float(r["special_ns"]))

fig, ax = plt.subplots(1,2, figsize=(14,6))
ax[0].plot(ns, nv, 'o-', label="Naive full multiply O(n³)", color='tab:red')
ax[0].plot(ns, sp, 's-', label="Special-pattern algorithm O(n²)", color='tab:blue')
ax[0].set_xlabel("n (matrix dimension)"); ax[0].set_ylabel("time (ns)")
ax[0].set_title("Running time vs n"); ax[0].legend(); ax[0].grid(True, alpha=0.3)

log_n=np.log(ns)
slope_naive = np.polyfit(log_n, np.log(nv), 1)[0]
slope_special = np.polyfit(log_n, np.log(sp), 1)[0]
ax[1].loglog(ns, nv, 'o-', label=f"Naive (slope≈{slope_naive:.2f}, theory 3.0)", color='tab:red')
ax[1].loglog(ns, sp, 's-', label=f"Special (slope≈{slope_special:.2f}, theory 2.0)", color='tab:blue')
ax[1].set_xlabel("n (log scale)"); ax[1].set_ylabel("time (log scale)")
ax[1].set_title("log-log plot: slope = complexity exponent")
ax[1].legend(); ax[1].grid(True, alpha=0.3, which='both')

fig.suptitle("Q5: Special-Pattern Matrix Multiply — O(n²) vs naive O(n³)", fontsize=13, fontweight='bold')
plt.tight_layout(rect=[0,0,1,0.94])
plt.savefig("q5_order_of_growth.png", dpi=150)
print("Saved q5_order_of_growth.png")
print(f"naive slope={slope_naive:.3f}, special slope={slope_special:.3f}")
