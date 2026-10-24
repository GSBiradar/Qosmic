import numpy as np
import matplotlib.pyplot as plt

# FSM Bode plot with margins
f = np.logspace(1, 4, 1000)
w = 2*np.pi*f
# Example open loop (plant + controller simplified)
# Plant: 1/((s^2/w_n^2)+2*zeta/w_n*s+1)*K/(1+s/tau)
w_n = 2*np.pi*1200
zeta = 0.02
K=20
# Notch approximation not shown fully; plot magnitude/phase
s = 1j*w
G = K / ((1 + 2*zeta/w_n*s + (s/w_n)**2))
# Controller lead/lag + notch simplified
Gc = 0.1 * (1 + 0.01*s)/(1 + 0.001*s) / (1 + 2*0.1*(s/(2*np.pi*1100)) + (s/(2*np.pi*1100))**2)
L = Gc*G
mag = 20*np.log10(np.abs(L)+1e-18)
ph = np.unwrap(np.angle(L))*180/np.pi
# Find crossover
idx = np.where(mag <= 0)[0][0]
pm = 180 + ph[idx]
gm_idx = np.where(ph <= -180)[0][0]
gm = -mag[gm_idx]
plt.figure(figsize=(10,6))
plt.subplot(2,1,1)
plt.semilogx(f,mag)
plt.axhline(0,color='r',ls='--'); plt.axvline(f[idx],color='g',ls='--')
plt.title(f'FSM Open-Loop Bode | PM~{pm:.1f}?, GM~{gm:.1f}dB'); plt.grid()
plt.subplot(2,1,2)
plt.semilogx(f,ph)
plt.axhline(-180,color='r',ls='--'); plt.axvline(f[idx],color='g',ls='--')
plt.grid()
plt.tight_layout()
plt.savefig('sim/fsm_bode_margins.png',dpi=150)
plt.close()
print('bode done')
