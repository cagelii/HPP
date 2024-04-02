import matplotlib.pyplot as plt
import numpy as np

dt = [1e-3, 1e-4, 1e-5, 1e-6, 1e-7]
Tv = [0.034177410879, 0.000450119736, 0.000040668383, 0.000004015230, 0.000000364885]
Te = [0.069, 0.00514, 0.000514, 0.000051, 0.0000046]
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
T = np.array([0.017786, 0.046375, 0.081239, 0.168263, 0.434840, 1.129324, 1.886747])
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