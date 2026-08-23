import csv
import matplotlib.pyplot as plt
import numpy as np

ns, t = [], []
with open("results/q3_timings.csv") as f:
    for r in csv.DictReader(f):
        ns.append(int(r["n"])); t.append(float(r["time_ns"]))

fig, ax = plt.subplots(1,2, figsize=(14,6))
ax[0].plot(ns, t, 'o-', color='tab:blue', label="measured, k=3")
theory = [n*n*np.log2(n) for n in ns]
scale = t[-1]/theory[-1]
ax[0].plot(ns, [th*scale for th in theory], '--', color='tab:red', label=r"shape of $n^2 \log n$ (scaled)")
ax[0].set_xlabel("n"); ax[0].set_ylabel("time (ns)")
ax[0].set_title("k=3: running time vs n"); ax[0].legend(); ax[0].grid(True, alpha=0.3)

log_n = np.log(ns)
slope = np.polyfit(log_n, np.log(t), 1)[0]
ax[1].loglog(ns, t, 'o-', color='tab:blue', label=f"measured (slope≈{slope:.2f}, theory≈2.0 for n²·logn)")
ax[1].set_xlabel("n (log scale)"); ax[1].set_ylabel("time (log scale)")
ax[1].set_title("log-log plot"); ax[1].legend(); ax[1].grid(True, alpha=0.3, which='both')

fig.suptitle(r"Q3: k-Sum (k=3) — $O(n^{k-1}\log n) = O(n^2\log n)$", fontsize=13, fontweight='bold')
plt.tight_layout(rect=[0,0,1,0.93])
plt.savefig("q3_order_of_growth.png", dpi=150)
print("Saved q3_order_of_growth.png, measured slope =", slope)
