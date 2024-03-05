import matplotlib.pyplot as plt
import numpy as np

times = np.array([0.044, 0.117, 0.375, 1.44, 4.93, 19.69, 54.22, 223.5])
N = np.array([100,200,400,800,1500,3000,5000,10000])
slope = np.polyfit(np.log(N),np.log(times),1)
print(slope)
fig,ax=plt.subplots()
ax.loglog(N,times,label="Measured values")
ax.plot(N,N**2*1e-5,'--',label="$N^2$")
ax.set_ylabel("Time (s)")
ax.set_xlabel("N")
ax.legend()
plt.savefig("plot.png")