import matplotlib.pyplot as plt
import numpy as np

dt = 1/(10**np.linspace(3,7,5))
Tv = [0.033361531165, 0.000345575189, 0.000003457102, 0.000000034568, 0.000000000342]
Te = [0.068535807586, 0.005896741670, 0.000590297078, 0.000058509004, 0.000005319101]
fig, ax  = plt.subplots()
slopeV = np.polyfit(np.log(dt), np.log(Tv), 1)[0]
slopeE = np.polyfit(np.log(dt), np.log(Te), 1)[0]
ax.loglog(dt, Tv, label = f"Velocity verlet slope: {np.round(slopeV,3)}")
ax.loglog(dt, Te, label = f"Symplectic Euler slope: {np.round(slopeE,3)}")
ax.set_xlabel("dt")
ax.set_ylabel("Error")
ax.legend()
fig.savefig("plot.png")

N = np.array([100, 200, 300, 500, 1000, 2000, 3000])
T = np.array([0.047, 0.092, 0.143, 0.255, 0.626, 1.446, 2.365])
fig, ax  = plt.subplots()
slope1 = np.polyfit(np.log(N), np.log(N*np.log(N)), 1)[0]
slope2 = np.polyfit(np.log(N), np.log(T), 1)[0]
ax.loglog(N, T, label = "Experimental")
ax.loglog(N, 1e-4*N*np.log(N), label = "N log(N)")
ax.loglog(N,1e-7*N*N,label="$N^2$")
ax.set_xlabel("N")
ax.set_ylabel("Time")
ax.legend()
print(slope1, slope2)
fig.savefig("plot2.png")