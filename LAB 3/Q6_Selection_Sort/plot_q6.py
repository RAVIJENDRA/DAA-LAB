import csv
import matplotlib.pyplot as plt
from collections import defaultdict

rows=[]
with open("results/q6_selection_sort.csv") as f:
    for r in csv.DictReader(f): rows.append(r)

by_case=defaultdict(lambda: {"n":[], "cmp":[], "swaps":[], "theory":[], "time":[]})
for r in rows:
    c=r["case"]
    by_case[c]["n"].append(int(r["n"]))
    by_case[c]["cmp"].append(int(r["comparisons"]))
    by_case[c]["swaps"].append(int(r["swaps"]))
    by_case[c]["theory"].append(int(r["theory_n_n_1_2"]))
    by_case[c]["time"].append(float(r["time_ns"]))

fig, ax = plt.subplots(1,3, figsize=(19,6))

colors={"sorted":"tab:green","reverse":"tab:red","random":"tab:blue"}
for case,d in by_case.items():
    ax[0].plot(d["n"], d["cmp"], 'o-', label=f"{case} input", color=colors[case])
ax[0].plot(by_case["sorted"]["n"], by_case["sorted"]["theory"], 'k--', label="theory: n(n-1)/2")
ax[0].set_xlabel("n"); ax[0].set_ylabel("comparisons")
ax[0].set_title("Comparisons: IDENTICAL for every input order\n(all three lines overlap exactly -> best case = worst case)")
ax[0].legend(); ax[0].grid(True, alpha=0.3)

for case,d in by_case.items():
    ax[1].plot(d["n"], d["swaps"], 'o-', label=f"{case} input", color=colors[case])
ax[1].set_xlabel("n"); ax[1].set_ylabel("swaps")
ax[1].set_title("Swaps: DOES depend on input order\n(0 for sorted input; this is the only thing that varies)")
ax[1].legend(); ax[1].grid(True, alpha=0.3)

for case,d in by_case.items():
    ax[2].plot(d["n"], d["time"], 'o-', label=f"{case} input", color=colors[case])
ax[2].set_xlabel("n"); ax[2].set_ylabel("time (ns)")
ax[2].set_title("Wall-clock time: all ~Θ(n²), nearly identical")
ax[2].legend(); ax[2].grid(True, alpha=0.3)

fig.suptitle("Q6: Selection Sort — comparisons are Θ(n²) regardless of input order", fontsize=13, fontweight='bold')
plt.tight_layout(rect=[0,0,1,0.93])
plt.savefig("q6_order_of_growth.png", dpi=150)
print("Saved q6_order_of_growth.png")
