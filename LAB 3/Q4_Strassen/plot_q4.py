import csv
import matplotlib.pyplot as plt
import numpy as np

ns, nv, st = [], [], []
with open("results/q4_timings.csv") as f:
    for r in csv.DictReader(f):
        ns.append(int(r["n"])); nv.append(float(r["naive_ns"])); st.append(float(r["strassen_ns"]))

fig, ax = plt.subplots(1,2, figsize=(14,6))

ax[0].plot(ns, nv, 'o-', label="Naive O(n³)", color='tab:red')
ax[0].plot(ns, st, 's-', label="Strassen O(n^2.807)", color='tab:blue')
ax[0].set_xlabel("n"); ax[0].set_ylabel("time (ns)")
ax[0].set_title("Running time vs n"); ax[0].legend(); ax[0].grid(True, alpha=0.3)

log_n = np.log(ns)
slope_naive = np.polyfit(log_n, np.log(nv), 1)[0]
slope_strassen = np.polyfit(log_n, np.log(st), 1)[0]

ax[1].loglog(ns, nv, 'o-', label=f"Naive (measured slope ≈ {slope_naive:.2f}, theory 3.0)", color='tab:red')
ax[1].loglog(ns, st, 's-', label=f"Strassen (measured slope ≈ {slope_strassen:.2f}, theory 2.807)", color='tab:blue')
ax[1].set_xlabel("n (log scale)"); ax[1].set_ylabel("time (log scale)")
ax[1].set_title("log-log plot: slope = complexity exponent")
ax[1].legend(); ax[1].grid(True, alpha=0.3, which='both')

fig.suptitle("Q4: Strassen's Algorithm vs Naive Matrix Multiplication", fontsize=13, fontweight='bold')
plt.tight_layout(rect=[0,0,1,0.94])
plt.savefig("q4_order_of_growth.png", dpi=150)
print("Saved q4_order_of_growth.png")
print(f"naive slope={slope_naive:.3f} (theory 3.0), strassen slope={slope_strassen:.3f} (theory 2.807)")
