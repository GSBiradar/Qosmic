import numpy as np
import matplotlib.pyplot as plt

# Closed loop step response
t = np.linspace(0,0.01,10000)
w_c = 2*np.pi*500
# 2nd order approx for CL with PM
zeta_cl = 0.707
wn_cl = w_c/np.sqrt(1-2*zeta_cl**2+np.sqrt(2-4*zeta_cl**2+4*zeta_cl**4))
s2 = -zeta_cl*wn_cl*t
y = 1 - np.exp(s2)*np.cos(wn_cl*np.sqrt(1-zeta_cl**2)*t + np.arctan(zeta_cl/np.sqrt(1-zeta_cl**2)))
plt.figure()
plt.plot(t*1000,y)
plt.grid(); plt.xlabel('ms'); plt.ylabel('Normalized'); plt.title('FSM Closed-Loop Step Response')
plt.savefig('sim/fsm_cl_step.png',dpi=150)
plt.close()
print('step done')
